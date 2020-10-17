#ifndef _BBR_IMPLICIT_SURFACE2_H_
#define _BBR_IMPLICIT_SURFACE2_H_

#include <kiri_math/physics/surface2.h>

namespace kiri_math
{

    //! Abstract base class for 2-D implicit surface.
    class ImplicitSurface2 : public Surface2
    {
    public:
        //! Default constructor.
        ImplicitSurface2(
            const Transform2 &transform = Transform2(),
            bool isNormalFlipped = false);

        //! Copy constructor.
        ImplicitSurface2(const ImplicitSurface2 &other);

        //! Default destructor.
        virtual ~ImplicitSurface2();

        //! Returns signed distance from the given point \p otherPoint.
        double signedDistance(const Vector2D &otherPoint) const;

    protected:
        //! Returns signed distance from the given point \p otherPoint in local
        //! space.
        virtual double signedDistanceLocal(const Vector2D &otherPoint) const = 0;

    private:
        double closestDistanceLocal(const Vector2D &otherPoint) const override;

        bool isInsideLocal(const Vector2D &otherPoint) const override;
    };

    //! Shared pointer type for the ImplicitSurface2.
    typedef std::shared_ptr<ImplicitSurface2> ImplicitSurface2Ptr;

} // namespace kiri_math

#endif // _BBR_IMPLICIT_SURFACE2_H_
