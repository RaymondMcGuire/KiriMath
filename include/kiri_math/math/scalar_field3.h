

#ifndef _KIRI_MATH_SCALAR_FIELD3_H_
#define _KIRI_MATH_SCALAR_FIELD3_H_

#include <kiri_math/math/field3.h>
#include <kiri_math/math/vector3.h>
#include <functional>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-D scalar field.
    class ScalarField3 : public Field3
    {
    public:
        //! Default constructor.
        ScalarField3();

        //! Default destructor.
        virtual ~ScalarField3();

        //! Returns sampled value at given position \p x.
        virtual double sample(const Vector3D &x) const = 0;

        //! Returns gradient vector at given position \p x.
        virtual Vector3D gradient(const Vector3D &x) const;

        //! Returns Laplacian at given position \p x.
        virtual double laplacian(const Vector3D &x) const;

        //! Returns sampler function object.
        virtual std::function<double(const Vector3D &)> sampler() const;
    };

    //! Shared pointer for the ScalarField3 type.
    typedef std::shared_ptr<ScalarField3> ScalarField3Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_SCALAR_FIELD3_H_
