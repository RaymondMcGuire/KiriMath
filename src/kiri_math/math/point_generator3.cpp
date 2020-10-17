/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-02 00:21:49 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 20:57:53
 */
#include <kiri_math/pch.h>
#include <kiri_math/math/point_generator3.h>

namespace kiri_math
{

    PointGenerator3::PointGenerator3()
    {
    }

    PointGenerator3::~PointGenerator3()
    {
    }

    void PointGenerator3::generate(
        const BoundingBox3D &boundingBox,
        double spacing,
        Array1<Vector3D> *points)
    {
        forEachPoint(
            boundingBox,
            spacing,
            [&points](const Vector3D &point) {
                points->append(point);
                return true;
            });
    }

    void PointGenerator3::generate(
        const BoundingBox3F &boundingBox,
        float spacing,
        Array1<Vector3F> *points)
    {
        forEachPoint(
            boundingBox,
            spacing, 0,
            [&points](const Vector3F &point) {
                points->append(point);
                return true;
            });
    }

} // namespace kiri_math
