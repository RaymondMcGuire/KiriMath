/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-18 20:37:06 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-18 20:37:06 
 */

#ifndef _KIRI_MATH_VECTOR_FIELD2_H_
#define _KIRI_MATH_VECTOR_FIELD2_H_

#include <kiri_math/math/field2.h>
#include <kiri_math/math/vector2.h>
#include <functional>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 2-D vector field.
    class VectorField2 : public Field2
    {
    public:
        //! Default constructor.
        VectorField2();

        //! Default destructor.
        virtual ~VectorField2();

        //! Returns sampled value at given position \p x.
        virtual Vector2D sample(const Vector2D &x) const = 0;

        //! Returns divergence at given position \p x.
        virtual double divergence(const Vector2D &x) const;

        //! Returns curl at given position \p x.
        virtual double curl(const Vector2D &x) const;

        //! Returns sampler function object.
        virtual std::function<Vector2D(const Vector2D &)> sampler() const;
    };

    //! Shared pointer for the VectorField2 type.
    typedef std::shared_ptr<VectorField2> VectorField2Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_VECTOR_FIELD2_H_
