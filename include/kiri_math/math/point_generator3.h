/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-02 00:21:19 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 22:01:46
 */
#ifndef _KIRI_POINT_GENERATOR3_H_
#define _KIRI_POINT_GENERATOR3_H_

#include <kiri_math/array/array1.h>
#include <kiri_math/physics/bounding_box3.h>

#include <functional>
#include <memory>

namespace kiri_math
{

    //!
    //! \brief Abstract base class for 3-D point generator.
    //!
    //! This class provides interface for 3-D point generator. For given bounding
    //! box and point spacing, the inherited classes generates points with specified
    //! pattern.
    //!
    class PointGenerator3
    {
    public:
        PointGenerator3();

        virtual ~PointGenerator3();

        //! Generates points to output array \p points inside given \p boundingBox
        //! with target point \p spacing.
        void generate(
            const BoundingBox3D &boundingBox,
            double spacing,
            Array1<Vector3D> *points);

        void generate(
            const BoundingBox3F &boundingBox,
            float spacing,
            Array1<Vector3F> *points);

        virtual void forEachPoint(
            const BoundingBox3D &boundingBox,
            double spacing,
            const std::function<bool(const Vector3D &)> &callback) = 0;

        virtual void forEachPoint(
            const BoundingBox3F &boundingBox,
            float spacing,
            float layerNum,
            const std::function<bool(const Vector3F &)> &callback) = 0;

        virtual void forEachPointWithNoOffset(
            const BoundingBox3F &boundingBox,
            float spacing,
            const std::function<bool(const Vector3F &)> &callback) = 0;
    };

    //! Shared pointer for the PointGenerator3 type.
    typedef std::shared_ptr<PointGenerator3> PointGenerator3Ptr;

} // namespace kiri_math

#endif // _KIRI_POINT_GENERATOR3_H_
