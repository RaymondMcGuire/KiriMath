/*
 * @Author: Xu.Wang 
 * @Date: 2020-04-26 00:53:37 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 23:19:16
 */

#ifndef _KIRI_BBOX_SURFACE_POINT_GENERATOR_H_
#define _KIRI_BBOX_SURFACE_POINT_GENERATOR_H_

#include <kiri_math/math/point_generator3.h>

namespace kiri_math
{

    class BboxSurfacePointGenerator final : public PointGenerator3
    {
    public:
        void forEachPoint(
            const BoundingBox3D &boundingBox,
            double spacing,
            const std::function<bool(const Vector3D &)> &callback) override;

        void forEachPoint(
            const BoundingBox3F &boundingBox,
            float spacing,
            float layerNum,
            const std::function<bool(const Vector3F &)> &callback) override;

        void forEachPointWithNoOffset(
            const BoundingBox3F &boundingBox,
            float spacing,
            const std::function<bool(const Vector3F &)> &callback) override;

        void forEachPointInBottom(
            const BoundingBox3F &boundingBox,
            float spacing,
            float layerNum,
            const std::function<bool(const Vector3F &)> &callback);

        void forEachPointNoTop(
            const BoundingBox3F &boundingBox,
            float spacing,
            float layerNum,
            const std::function<bool(const Vector3F &)> &callback);

        void forEachPlane(
            const Vector3D &p1,
            const Vector3D &p2,
            double spacing,
            const std::function<bool(const Vector3D &)> &callback);

        void forEachPlane(
            const Vector3F &p1,
            const Vector3F &p2,
            float spacing,
            const std::function<bool(const Vector3F &)> &callback);

    private:
        void offsetNormDir(Vector3F &p1, Vector3F &p2, float spacing, float layerNum, float sign, bool sketch = false, bool onlyX = false, bool onlyY = false, bool onlyZ = false);
    };

    //! Shared pointer type for the BboxSurfacePointGenerator.
    typedef std::shared_ptr<BboxSurfacePointGenerator> BboxSurfacePointGeneratorPtr;

} // namespace kiri_math

#endif // _KIRI_BBOX_POINT_GENERATOR_H_
