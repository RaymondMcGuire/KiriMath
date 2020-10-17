/*
 * @Author: Doyub Kim 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2019-12-14 02:26:23 
 */
#include <kiri_math/pch.h>

#include <kiri_math/parallel.h>
#include <kiri_math/particle/particle_emitter3.h>

#include <limits>

namespace kiri_math
{

    ParticleEmitter3::ParticleEmitter3() {}

    ParticleEmitter3::~ParticleEmitter3() {}

    const ParticleSystemData3Ptr &ParticleEmitter3::target() const
    {
        return _particles;
    }

    void ParticleEmitter3::setTarget(const ParticleSystemData3Ptr &particles)
    {
        _particles = particles;

        onSetTarget(particles);
    }

    bool ParticleEmitter3::isEnabled() const { return _isEnabled; }

    void ParticleEmitter3::setIsEnabled(bool enabled) { _isEnabled = enabled; }

    void ParticleEmitter3::update(double currentTimeInSeconds,
                                  double timeIntervalInSeconds)
    {
        if (_onBeginUpdateCallback)
        {
            _onBeginUpdateCallback(this, currentTimeInSeconds,
                                   timeIntervalInSeconds);
        }

        onUpdate(currentTimeInSeconds, timeIntervalInSeconds);
    }

    void ParticleEmitter3::onSetTarget(const ParticleSystemData3Ptr &particles)
    {
        UNUSED_VARIABLE(particles);
    }

    void ParticleEmitter3::setOnBeginUpdateCallback(
        const OnBeginUpdateCallback &callback)
    {
        _onBeginUpdateCallback = callback;
    }

} // namespace kiri_math
