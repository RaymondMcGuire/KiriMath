/*
 * @Author: Doyub Kim 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2019-12-14 02:25:52 
 */
#include <kiri_math/pch.h>
#include <kiri_math/particle/point_particle_emitter3.h>
#include <kiri_math/math/samplers.h>

namespace kiri_math
{

    PointParticleEmitter3::PointParticleEmitter3(
        const Vector3D &origin,
        const Vector3D &direction,
        double speed,
        bool loop,
        double spreadAngleInDegrees,
        size_t maxNumOfNewParticlesPerSec,
        size_t maxNumOfParticles,
        uint32_t seed) : _rng(seed),
                         _maxNumberOfNewParticlesPerSecond(maxNumOfNewParticlesPerSec),
                         _maxNumberOfParticles(maxNumOfParticles),
                         _origin(origin),
                         _direction(direction),
                         _speed(speed),
                         _spreadAngleInRadians(degreesToRadians(spreadAngleInDegrees)),
                         _loop(loop)
    {
    }

    size_t PointParticleEmitter3::maxNumberOfNewParticlesPerSecond() const
    {
        return _maxNumberOfNewParticlesPerSecond;
    }

    void PointParticleEmitter3::setMaxNumberOfNewParticlesPerSecond(size_t rate)
    {
        _maxNumberOfNewParticlesPerSecond = rate;
    }

    size_t PointParticleEmitter3::maxNumberOfParticles() const
    {
        return _maxNumberOfParticles;
    }

    void PointParticleEmitter3::setMaxNumberOfParticles(
        size_t maxNumberOfParticles)
    {
        _maxNumberOfParticles = maxNumberOfParticles;
    }

    void PointParticleEmitter3::onUpdate(
        double currentTimeInSeconds,
        double timeIntervalInSeconds)
    {
        auto particles = target();

        if (particles == nullptr)
        {
            return;
        }

        if (_numberOfEmittedParticles == 0)
        {
            _firstFrameTimeInSeconds = currentTimeInSeconds;
        }

        double elapsedTimeInSeconds = currentTimeInSeconds - _firstFrameTimeInSeconds;

        size_t newMaxTotalNumberOfEmittedParticles = static_cast<size_t>(
            std::ceil((elapsedTimeInSeconds + timeIntervalInSeconds) * _maxNumberOfNewParticlesPerSecond));

        if (!_loop)
        {
            newMaxTotalNumberOfEmittedParticles = std::min(
                newMaxTotalNumberOfEmittedParticles,
                _maxNumberOfParticles);
        }

        size_t maxNumberOfNewParticles = newMaxTotalNumberOfEmittedParticles - _numberOfEmittedParticles;

        if (maxNumberOfNewParticles > 0)
        {
            Array1<Vector3D> candidatePositions;
            Array1<Vector3D> candidateVelocities;

            Array1<Vector3D> newPositions;
            Array1<Vector3D> newVelocities;
            Array1<Vector3D> newForces;
            Array1<double> newLifeTimes;

            emit(
                &candidatePositions,
                &candidateVelocities,
                maxNumberOfNewParticles);

            newPositions.append(candidatePositions);
            newVelocities.append(candidateVelocities);
            newForces.resize(newPositions.size());
            newLifeTimes.resize(newPositions.size());
            particles->addParticles(newPositions, newVelocities, newForces, newLifeTimes);

            _numberOfEmittedParticles += newPositions.size();
        }
    }

    void PointParticleEmitter3::emit(
        Array1<Vector3D> *newPositions,
        Array1<Vector3D> *newVelocities,
        size_t maxNewNumberOfParticles)
    {
        for (size_t i = 0; i < maxNewNumberOfParticles; ++i)
        {
            Vector3D newDirection = uniformSampleCone(
                random(),
                random(),
                _direction,
                _spreadAngleInRadians);

            newPositions->append(_origin);
            newVelocities->append(_speed * newDirection);
        }
    }

    double PointParticleEmitter3::random()
    {
        std::uniform_real_distribution<> d(0.0, 1.0);
        return d(_rng);
    }

    PointParticleEmitter3::Builder PointParticleEmitter3::builder()
    {
        return Builder();
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withOrigin(const Vector3D &origin)
    {
        _origin = origin;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withDirection(const Vector3D &direction)
    {
        _direction = direction;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withSpeed(double speed)
    {
        _speed = speed;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withLoop(bool loop)
    {
        _loop = loop;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withSpreadAngleInDegrees(
        double spreadAngleInDegrees)
    {
        _spreadAngleInDegrees = spreadAngleInDegrees;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withMaxNumberOfNewParticlesPerSecond(
        size_t maxNumOfNewParticlesPerSec)
    {
        _maxNumberOfNewParticlesPerSecond = maxNumOfNewParticlesPerSec;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withMaxNumberOfParticles(
        size_t maxNumberOfParticles)
    {
        _maxNumberOfParticles = maxNumberOfParticles;
        return *this;
    }

    PointParticleEmitter3::Builder &
    PointParticleEmitter3::Builder::withRandomSeed(uint32_t seed)
    {
        _seed = seed;
        return *this;
    }

    PointParticleEmitter3 PointParticleEmitter3::Builder::build() const
    {
        return PointParticleEmitter3(
            _origin,
            _direction,
            _speed,
            _loop,
            _spreadAngleInDegrees,
            _maxNumberOfNewParticlesPerSecond,
            _maxNumberOfParticles,
            _seed);
    }

    PointParticleEmitter3Ptr PointParticleEmitter3::Builder::makeShared() const
    {
        return std::shared_ptr<PointParticleEmitter3>(
            new PointParticleEmitter3(
                _origin,
                _direction,
                _speed,
                _loop,
                _spreadAngleInDegrees,
                _maxNumberOfNewParticlesPerSecond,
                _maxNumberOfParticles,
                _seed),
            [](PointParticleEmitter3 *obj) {
                delete obj;
            });
    }

} // namespace kiri_math
