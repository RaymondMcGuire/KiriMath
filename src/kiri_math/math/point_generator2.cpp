#include <kiri_math/pch.h>
#include <kiri_math/math/point_generator2.h>

namespace kiri_math
{

    PointGenerator2::PointGenerator2()
    {
    }

    PointGenerator2::~PointGenerator2()
    {
    }

    void PointGenerator2::generate(
        const BoundingBox2D &boundingBox,
        double spacing,
        Array1<Vector2D> *points) const
    {
        forEachPoint(
            boundingBox,
            spacing,
            [&points](const Vector2D &point) {
                points->append(point);
                return true;
            });
    }

} // namespace kiri_math
