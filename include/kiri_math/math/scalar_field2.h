

#ifndef _KIRI_MATH_SCALAR_FIELD2_H_
#define _KIRI_MATH_SCALAR_FIELD2_H_

#include <kiri_math/math/field2.h>
#include <kiri_math/math/vector2.h>
#include <functional>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 2-D scalar field.
    class ScalarField2 : public Field2
    {
    public:
        //! Default constructor.
        ScalarField2();

        //! Default destructor.
        virtual ~ScalarField2();

        //! Returns sampled value at given position \p x.
        virtual double sample(const Vector2D &x) const = 0;

        //! Returns gradient vector at given position \p x.
        virtual Vector2D gradient(const Vector2D &x) const;

        //! Returns Laplacian at given position \p x.
        virtual double laplacian(const Vector2D &x) const;

        //! Returns sampler function object.
        virtual std::function<double(const Vector2D &)> sampler() const;
    };

    //! Shared pointer for the ScalarField2 type.
    typedef std::shared_ptr<ScalarField2> ScalarField2Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_SCALAR_FIELD2_H_
