/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-07 17:25:25 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-07 17:25:25 
 */
#ifndef _KIRI_MATH_BOX2_H_
#define _KIRI_MATH_BOX2_H_

#include <kiri_math/physics/surface2.h>
#include <kiri_math/physics/bounding_box2.h>

namespace kiri_math
{

    //!
    //! \brief 2-D box geometry.
    //!
    //! This class represents 2-D box geometry which extends Surface2 by overriding
    //! surface-related queries. This box implementation is an axis-aligned box
    //! that wraps lower-level primitive type, BoundingBox2D.
    //!
    class Box2 final : public Surface2
    {
    public:
        class Builder;

        //! Bounding box of this box.
        BoundingBox2D bound = BoundingBox2D(Vector2D(), Vector2D(1.0, 1.0));

        //! Constructs (0, 0) x (1, 1) box.
        Box2(
            const Transform2 &transform = Transform2(),
            bool isNormalFlipped = false);

        //! Constructs a box with given \p LowestPoint and \p HighestPoint.
        Box2(
            const Vector2D &LowestPoint,
            const Vector2D &HighestPoint,
            const Transform2 &transform = Transform2(),
            bool isNormalFlipped = false);

        //! Constructs a box with BoundingBox2D instance.
        Box2(
            const BoundingBox2D &boundingBox,
            const Transform2 &transform = Transform2(),
            bool isNormalFlipped = false);

        //! Copy constructor.
        Box2(const Box2 &other);

        //! Returns builder fox Box2.
        static Builder builder();

    protected:
        // Surface2 implementations

        Vector2D closestPointLocal(const Vector2D &otherPoint) const override;

        bool intersectsLocal(const Ray2D &ray) const override;

        BoundingBox2D boundingBoxLocal() const override;

        Vector2D closestNormalLocal(const Vector2D &otherPoint) const override;

        SurfaceRayIntersection2 closestIntersectionLocal(
            const Ray2D &ray) const override;
    };

    //! Shared pointer type for the Box2.
    typedef std::shared_ptr<Box2> Box2Ptr;

    //!
    //! \brief Front-end to create Box2 objects step by step.
    //!
    class Box2::Builder final : public SurfaceBuilderBase2<Box2::Builder>
    {
    public:
        //! Returns builder with lower corner set.
        Builder &withLowestPoint(const Vector2D &pt);

        //! Returns builder with upper corner set.
        Builder &withHighestPoint(const Vector2D &pt);

        //! Returns builder with bounding box.
        Builder &withBoundingBox(const BoundingBox2D &bbox);

        //! Builds Box2.
        Box2 build() const;

        //! Builds shared pointer of Box2 instance.
        Box2Ptr makeShared() const;

    private:
        Vector2D mLowestPoint{0, 0};
        Vector2D mHighestPoint{1, 1};
    };

} // namespace kiri_math

#endif // _KIRI_MATH_BOX2_H_
