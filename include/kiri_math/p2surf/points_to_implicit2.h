#ifndef _BBR_POINTS_TO_IMPLICIT2_H_
#define _BBR_POINTS_TO_IMPLICIT2_H_

#include <kiri_math/array/array_accessor1.h>
#include <kiri_math/math/scalar_grid2.h>
#include <kiri_math/math/vector2.h>

#include <memory>

namespace kiri_math
{

    //! Abstract base class for 2-D points-to-implicit converters.
    class PointsToImplicit2
    {
    public:
        //! Default constructor.
        PointsToImplicit2();

        //! Default destructor.
        virtual ~PointsToImplicit2();

        //! Converts the given points to implicit surface scalar field.
        virtual void convert(const ConstArrayAccessor1<Vector2D> &points,
                             ScalarGrid2 *output) const = 0;
    };

    //! Shared pointer for the PointsToImplicit2 type.
    typedef std::shared_ptr<PointsToImplicit2> PointsToImplicit2Ptr;

} // namespace kiri_math

#endif // _POINTS_TO_IMPLICIT2_H_
