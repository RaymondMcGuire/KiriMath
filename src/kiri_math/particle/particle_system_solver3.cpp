/*
 * @Author: Doyub Kim 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2019-12-14 02:26:02 
 */
#include <kiri_math/pch.h>

#include <kiri_math/array/array_utils.h>
#include <kiri_math/math/constant_vector_field3.h>
#include <kiri_math/parallel.h>
#include <kiri_math/particle/particle_system_solver3.h>
#include <kiri_math/timer.h>

#include <algorithm>

namespace kiri_math
{

    ParticleSystemSolver3::ParticleSystemSolver3()
        : ParticleSystemSolver3(1e-3, 1e-3, false, 10.0)
    {
    }

    ParticleSystemSolver3::ParticleSystemSolver3(
        double radius,
        double mass,
        bool lifeCycle,
        double maxLifeCycle)
    {
        _particleSystemData = std::make_shared<ParticleSystemData3>();
        _particleSystemData->setRadius(radius);
        _particleSystemData->setMass(mass);
        _particleSystemData->setLifeCycle(lifeCycle);
        _particleSystemData->setMaxLifeCycle(maxLifeCycle);
        _wind = std::make_shared<ConstantVectorField3>(Vector3D());
    }

    ParticleSystemSolver3::~ParticleSystemSolver3()
    {
    }

    double ParticleSystemSolver3::dragCoefficient() const
    {
        return _dragCoefficient;
    }

    void ParticleSystemSolver3::setDragCoefficient(double newDragCoefficient)
    {
        _dragCoefficient = std::max(newDragCoefficient, 0.0);
    }

    double ParticleSystemSolver3::restitutionCoefficient() const
    {
        return _restitutionCoefficient;
    }

    void ParticleSystemSolver3::setRestitutionCoefficient(
        double newRestitutionCoefficient)
    {
        _restitutionCoefficient = clamp(newRestitutionCoefficient, 0.0, 1.0);
    }

    const Vector3D &ParticleSystemSolver3::gravity() const
    {
        return _gravity;
    }

    void ParticleSystemSolver3::setGravity(const Vector3D &newGravity)
    {
        _gravity = newGravity;
    }

    const ParticleSystemData3Ptr &
    ParticleSystemSolver3::particleSystemData() const
    {
        return _particleSystemData;
    }

    const Collider3Ptr &ParticleSystemSolver3::collider() const
    {
        return _collider;
    }

    void ParticleSystemSolver3::setCollider(
        const Collider3Ptr &newCollider)
    {
        _collider = newCollider;
    }

    const ParticleEmitter3Ptr &ParticleSystemSolver3::emitter() const
    {
        return _emitter;
    }

    void ParticleSystemSolver3::setEmitter(
        const ParticleEmitter3Ptr &newEmitter)
    {
        _emitter = newEmitter;
        newEmitter->setTarget(_particleSystemData);
    }

    const VectorField3Ptr &ParticleSystemSolver3::wind() const
    {
        return _wind;
    }

    void ParticleSystemSolver3::setWind(const VectorField3Ptr &newWind)
    {
        _wind = newWind;
    }

    void ParticleSystemSolver3::onInitialize()
    {
        // When initializing the solver, update the collider and emitter state as
        // well since they also affects the initial condition of the simulation.
        Timer timer;
        updateCollider(0.0);

#ifdef BBR_LOGGING
        BBR_INFO << "Update collider took "
                 << timer.durationInSeconds() << " seconds";
#endif
        timer.reset();
        updateEmitter(0.0);

#ifdef BBR_LOGGING
        BBR_INFO << "Update emitter took "
                 << timer.durationInSeconds() << " seconds";
#endif
    }

    void ParticleSystemSolver3::onAdvanceTimeStep(double timeStepInSeconds)
    {
        beginAdvanceTimeStep(timeStepInSeconds);

        Timer timer;
        accumulateForces(timeStepInSeconds);

#ifdef BBR_LOGGING
        BBR_INFO << "Accumulating forces took "
                 << timer.durationInSeconds() << " seconds";
#endif
        timer.reset();
        timeIntegration(timeStepInSeconds);

#ifdef BBR_LOGGING
        BBR_INFO << "Time integration took "
                 << timer.durationInSeconds() << " seconds";
#endif
        timer.reset();
        resolveCollision();

#ifdef BBR_LOGGING
        BBR_INFO << "Resolving collision took "
                 << timer.durationInSeconds() << " seconds";
#endif
        endAdvanceTimeStep(timeStepInSeconds);
    }

    void ParticleSystemSolver3::accumulateForces(double timeStepInSeconds)
    {
        UNUSED_VARIABLE(timeStepInSeconds);

        // Add external forces
        accumulateExternalForces();
    }

    void ParticleSystemSolver3::beginAdvanceTimeStep(double timeStepInSeconds)
    {
        // Clear forces
        auto forces = _particleSystemData->forces();
        setRange1(forces.size(), Vector3D(), &forces);

        // Update collider and emitter
        Timer timer;
        updateCollider(timeStepInSeconds);

#ifdef BBR_LOGGING
        BBR_INFO << "Update collider took "
                 << timer.durationInSeconds() << " seconds";
#endif
        timer.reset();
        updateEmitter(timeStepInSeconds);

#ifdef BBR_LOGGING
        BBR_INFO << "Update emitter took "
                 << timer.durationInSeconds() << " seconds";
#endif
        // Allocate buffers
        size_t n = _particleSystemData->numberOfParticles();
        _newPositions.resize(n);
        _newVelocities.resize(n);
        _newForces.resize(n);
        _newLifeTimes.resize(n);

        onBeginAdvanceTimeStep(timeStepInSeconds);
    }

    void ParticleSystemSolver3::updateLifeCycle()
    {
        auto lifeCycle = _particleSystemData->lifeCycle();
        if (!lifeCycle)
            return;

        auto maxLifeCycle = _particleSystemData->maxLifeCycle();
        auto lt = _particleSystemData->lifeTimes();

        Array1<size_t> idxArray;
        for (size_t i = kZeroSize; i < lt.size(); i++)
        {
            if (lt[i] >= maxLifeCycle)
            {
                idxArray.append(i);
            }
        }

        if (idxArray.size() > 0)
        {
            for (size_t i = 0; i < idxArray.size(); i++)
            {
                size_t idx = idxArray.size() - 1 - i;
                ;
                _newPositions.removeq(idxArray[idx]);
                _newVelocities.removeq(idxArray[idx]);
                _newForces.removeq(idxArray[idx]);
                _newLifeTimes.removeq(idxArray[idx]);
            }

            auto positions = _particleSystemData->positions();
            auto velocities = _particleSystemData->velocities();
            auto lifeTimes = _particleSystemData->lifeTimes();

            size_t n = _newPositions.size();
            _particleSystemData->resize(n);

            parallelFor(
                kZeroSize,
                n,
                [&](size_t i) {
                    positions[i] = _newPositions[i];
                    velocities[i] = _newVelocities[i];
                    lifeTimes[i] = _newLifeTimes[i];
                });
        }
    }

    void ParticleSystemSolver3::endAdvanceTimeStep(double timeStepInSeconds)
    {
        // Update data
        size_t n = _particleSystemData->numberOfParticles();
        auto positions = _particleSystemData->positions();
        auto velocities = _particleSystemData->velocities();
        auto lifeTimes = _particleSystemData->lifeTimes();
        parallelFor(
            kZeroSize,
            n,
            [&](size_t i) {
                positions[i] = _newPositions[i];
                velocities[i] = _newVelocities[i];
                lifeTimes[i] = _newLifeTimes[i];
            });

        updateLifeCycle();
        onEndAdvanceTimeStep(timeStepInSeconds);
    }

    void ParticleSystemSolver3::onBeginAdvanceTimeStep(double timeStepInSeconds)
    {
        UNUSED_VARIABLE(timeStepInSeconds);
    }

    void ParticleSystemSolver3::onEndAdvanceTimeStep(double timeStepInSeconds)
    {
        UNUSED_VARIABLE(timeStepInSeconds);
    }

    void ParticleSystemSolver3::resolveCollision()
    {
        resolveCollision(
            _newPositions.accessor(),
            _newVelocities.accessor());
    }

    void ParticleSystemSolver3::resolveCollision(
        ArrayAccessor1<Vector3D> newPositions,
        ArrayAccessor1<Vector3D> newVelocities)
    {
        if (_collider != nullptr)
        {
            size_t numberOfParticles = _particleSystemData->numberOfParticles();
            const double radius = _particleSystemData->radius();

            parallelFor(
                kZeroSize,
                numberOfParticles,
                [&](size_t i) {
                    _collider->resolveCollision(
                        radius,
                        _restitutionCoefficient,
                        &newPositions[i],
                        &newVelocities[i]);
                });
        }
    }

    void ParticleSystemSolver3::setParticleSystemData(
        const ParticleSystemData3Ptr &newParticles)
    {
        _particleSystemData = newParticles;
    }

    void ParticleSystemSolver3::accumulateExternalForces()
    {
        size_t n = _particleSystemData->numberOfParticles();
        auto forces = _particleSystemData->forces();
        auto velocities = _particleSystemData->velocities();
        auto positions = _particleSystemData->positions();
        const double mass = _particleSystemData->mass();

        parallelFor(
            kZeroSize,
            n,
            [&](size_t i) {
                // Gravity
                Vector3D force = mass * _gravity;

                // Wind forces
                Vector3D relativeVel = velocities[i] - _wind->sample(positions[i]);
                force += -_dragCoefficient * relativeVel;

                forces[i] += force;
            });
    }

    void ParticleSystemSolver3::timeIntegration(double timeStepInSeconds)
    {
        size_t n = _particleSystemData->numberOfParticles();
        auto forces = _particleSystemData->forces();
        auto velocities = _particleSystemData->velocities();
        auto positions = _particleSystemData->positions();
        auto lifeTimes = _particleSystemData->lifeTimes();
        const double mass = _particleSystemData->mass();

        parallelFor(
            kZeroSize,
            n,
            [&](size_t i) {
                // Integrate velocity first
                Vector3D &newVelocity = _newVelocities[i];
                newVelocity = velocities[i] + timeStepInSeconds * forces[i] / mass;

                // Integrate position.
                Vector3D &newPosition = _newPositions[i];
                newPosition = positions[i] + timeStepInSeconds * newVelocity;

                double &newTimeLife = _newLifeTimes[i];
                newTimeLife = lifeTimes[i] + 1.0 / 60.0;
            });
    }

    void ParticleSystemSolver3::updateCollider(double timeStepInSeconds)
    {
        if (_collider != nullptr)
        {
            _collider->update(currentTimeInSeconds(), timeStepInSeconds);
        }
    }

    void ParticleSystemSolver3::updateEmitter(double timeStepInSeconds)
    {
        if (_emitter != nullptr)
        {
            _emitter->update(currentTimeInSeconds(), timeStepInSeconds);
        }
    }

    ParticleSystemSolver3::Builder ParticleSystemSolver3::builder()
    {
        return Builder();
    }

    ParticleSystemSolver3 ParticleSystemSolver3::Builder::build() const
    {
        return ParticleSystemSolver3(_radius, _mass, _lifeCycle, _maxLifeCycle);
    }

    ParticleSystemSolver3Ptr ParticleSystemSolver3::Builder::makeShared() const
    {
        return std::shared_ptr<ParticleSystemSolver3>(
            new ParticleSystemSolver3(_radius, _mass, _lifeCycle, _maxLifeCycle),
            [](ParticleSystemSolver3 *obj) {
                delete obj;
            });
    }

} // namespace kiri_math
