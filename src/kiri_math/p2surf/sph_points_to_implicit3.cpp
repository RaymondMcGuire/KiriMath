#include <kiri_math/pch.h>

#include <kiri_math/level_set/fmm_level_set_solver3.h>
#include <kiri_math/p2surf/sph_points_to_implicit3.h>
#include <kiri_math/sph/sph_system_data3.h>

using namespace kiri_math;

SphPointsToImplicit3::SphPointsToImplicit3(double kernelRadius,
                                           double cutOffDensity,
                                           bool isOutputSdf)
    : _kernelRadius(kernelRadius),
      _cutOffDensity(cutOffDensity),
      _isOutputSdf(isOutputSdf) {}

void SphPointsToImplicit3::convert(const ConstArrayAccessor1<Vector3D> &points,
                                   ScalarGrid3 *output) const
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

    SphSystemData3 sphParticles;
    sphParticles.addParticles(points);
    sphParticles.setKernelRadius(_kernelRadius);
    sphParticles.buildNeighborSearcher();
    sphParticles.updateDensities();

    Array1<double> constData(sphParticles.numberOfParticles(), 1.0);
    auto temp = output->clone();
    temp->fill([&](const Vector3D &x) {
        double d = sphParticles.interpolate(x, constData);
        return _cutOffDensity - d;
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
