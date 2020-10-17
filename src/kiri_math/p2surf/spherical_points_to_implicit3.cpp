#include <kiri_math/pch.h>

#include <kiri_math/level_set/fmm_level_set_solver3.h>
#include <kiri_math/particle/particle_system_data3.h>
#include <kiri_math/p2surf/spherical_points_to_implicit3.h>

using namespace kiri_math;

SphericalPointsToImplicit3::SphericalPointsToImplicit3(double radius,
                                                       bool isOutputSdf)
    : _radius(radius), _isOutputSdf(isOutputSdf) {}

void SphericalPointsToImplicit3::convert(
    const ConstArrayAccessor1<Vector3D> &points, ScalarGrid3 *output) const
{
    if (output == nullptr)
    {
        BBR_WARN << "Null scalar grid output pointer provided.";
        return;
    }

    const auto res = output->resolution();
    if (res.x * res.y * res.z == 0)
    {
        BBR_WARN << "Empty grid is provided.";
        return;
    }

    const auto bbox = output->boundingBox();
    if (bbox.isEmpty())
    {
        BBR_WARN << "Empty domain is provided.";
        return;
    }

    ParticleSystemData3 particles;
    particles.addParticles(points);
    particles.buildNeighborSearcher(2.0 * _radius);

    const auto neighborSearcher = particles.neighborSearcher();

    auto temp = output->clone();
    temp->fill([&](const Vector3D &x) {
        double minDist = 2.0 * _radius;
        neighborSearcher->forEachNearbyPoint(
            x, 2.0 * _radius, [&](size_t, const Vector3D &xj) {
                minDist = std::min(minDist, (x - xj).length());
            });

        return minDist - _radius;
    });

    if (_isOutputSdf)
    {
        FmmLevelSetSolver3 solver;
        solver.reinitialize(*temp, kMaxD, output);
    }
    else
    {
        temp->swap(output);
    }
}
