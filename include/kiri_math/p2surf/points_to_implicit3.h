#ifndef _KIRI_POINTS_TO_IMPLICIT3_H_
#define _KIRI_POINTS_TO_IMPLICIT3_H_

#include <kiri_math/array/array_accessor1.h>
#include <kiri_math/math/scalar_grid3.h>
#include <kiri_math/math/vector3.h>

#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-D points-to-implicit converters.
    class PointsToImplicit3
    {
    public:
        //! Default constructor.
        PointsToImplicit3();

        //! Default destructor.
        virtual ~PointsToImplicit3();

        //! Converts the given points to implicit surface scalar field.
        virtual void convert(const ConstArrayAccessor1<Vector3D> &points,
                             ScalarGrid3 *output) const = 0;
    };

    //! Shared pointer for the PointsToImplicit3 type.
    typedef std::shared_ptr<PointsToImplicit3> PointsToImplicit3Ptr;

} // namespace kiri_math

#endif // _POINTS_TO_IMPLICIT3_H_
