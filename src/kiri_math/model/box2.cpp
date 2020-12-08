/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-07 17:27:13 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-07 17:27:13 
 */
#include <kiri_math/pch.h>

#include <kiri_math/model/box2.h>
#include <kiri_math/model/plane2.h>

using namespace kiri_math;

Box2::Box2(const Transform2 &transform, bool isNormalFlipped)
    : Surface2(transform, isNormalFlipped) {}

Box2::Box2(const Vector2D &LowestPoint, const Vector2D &HighestPoint,
           const Transform2 &transform, bool isNormalFlipped)
    : Box2(BoundingBox2D(LowestPoint, HighestPoint), transform,
           isNormalFlipped) {}

Box2::Box2(const BoundingBox2D &boundingBox, const Transform2 &transform,
           bool isNormalFlipped)
    : Surface2(transform, isNormalFlipped), bound(boundingBox) {}

Box2::Box2(const Box2 &other) : Surface2(other), bound(other.bound) {}

Vector2D Box2::closestPointLocal(const Vector2D &otherPoint) const
{
    if (bound.contains(otherPoint))
    {
        Plane2 planes[4] = {Plane2(Vector2D(1, 0), bound.HighestPoint),
                            Plane2(Vector2D(0, 1), bound.HighestPoint),
                            Plane2(Vector2D(-1, 0), bound.LowestPoint),
                            Plane2(Vector2D(0, -1), bound.LowestPoint)};

        Vector2D result = planes[0].closestPoint(otherPoint);
        double distanceSquared = result.distanceSquaredTo(otherPoint);

        for (int i = 1; i < 4; ++i)
        {
            Vector2D localResult = planes[i].closestPoint(otherPoint);
            double localDistanceSquared =
                localResult.distanceSquaredTo(otherPoint);

            if (localDistanceSquared < distanceSquared)
            {
                result = localResult;
                distanceSquared = localDistanceSquared;
            }
        }

        return result;
    }
    else
    {
        return clamp(otherPoint, bound.LowestPoint, bound.HighestPoint);
    }
}

Vector2D Box2::closestNormalLocal(const Vector2D &otherPoint) const
{
    Plane2 planes[4] = {Plane2(Vector2D(1, 0), bound.HighestPoint),
                        Plane2(Vector2D(0, 1), bound.HighestPoint),
                        Plane2(Vector2D(-1, 0), bound.LowestPoint),
                        Plane2(Vector2D(0, -1), bound.LowestPoint)};

    if (bound.contains(otherPoint))
    {
        Vector2D closestNormal = planes[0].normal;
        Vector2D closestPoint = planes[0].closestPoint(otherPoint);
        double minDistanceSquared = (closestPoint - otherPoint).lengthSquared();

        for (int i = 1; i < 4; ++i)
        {
            Vector2D localClosestPoint = planes[i].closestPoint(otherPoint);
            double localDistanceSquared =
                (localClosestPoint - otherPoint).lengthSquared();

            if (localDistanceSquared < minDistanceSquared)
            {
                closestNormal = planes[i].normal;
                minDistanceSquared = localDistanceSquared;
            }
        }

        return closestNormal;
    }
    else
    {
        Vector2D closestPoint =
            clamp(otherPoint, bound.LowestPoint, bound.HighestPoint);
        Vector2D closestPointToInputPoint = otherPoint - closestPoint;
        Vector2D closestNormal = planes[0].normal;
        double maxCosineAngle = closestNormal.dot(closestPointToInputPoint);

        for (int i = 1; i < 4; ++i)
        {
            double cosineAngle = planes[i].normal.dot(closestPointToInputPoint);

            if (cosineAngle > maxCosineAngle)
            {
                closestNormal = planes[i].normal;
                maxCosineAngle = cosineAngle;
            }
        }

        return closestNormal;
    }
}

bool Box2::intersectsLocal(const Ray2D &ray) const
{
    return bound.intersects(ray);
}

SurfaceRayIntersection2 Box2::closestIntersectionLocal(const Ray2D &ray) const
{
    SurfaceRayIntersection2 intersection;
    BoundingBoxRayIntersection2D KIRIayIntersection =
        bound.closestIntersection(ray);
    intersection.isIntersecting = KIRIayIntersection.isIntersecting;
    if (intersection.isIntersecting)
    {
        intersection.distance = KIRIayIntersection.tNear;
        intersection.point = ray.pointAt(KIRIayIntersection.tNear);
        intersection.normal = closestNormalLocal(intersection.point);
    }
    return intersection;
}

BoundingBox2D Box2::boundingBoxLocal() const { return bound; }

Box2::Builder Box2::builder() { return Builder(); }

Box2::Builder &Box2::Builder::withLowestPoint(const Vector2D &pt)
{
    mLowestPoint = pt;
    return *this;
}

Box2::Builder &Box2::Builder::withHighestPoint(const Vector2D &pt)
{
    mHighestPoint = pt;
    return *this;
}

Box2::Builder &Box2::Builder::withBoundingBox(const BoundingBox2D &bbox)
{
    mLowestPoint = bbox.LowestPoint;
    mHighestPoint = bbox.HighestPoint;
    return *this;
}

Box2 Box2::Builder::build() const
{
    return Box2(mLowestPoint, mHighestPoint, _transform, _isNormalFlipped);
}

Box2Ptr Box2::Builder::makeShared() const
{
    return std::shared_ptr<Box2>(
        new Box2(mLowestPoint, mHighestPoint, _transform, _isNormalFlipped),
        [](Box2 *obj) { delete obj; });
}
