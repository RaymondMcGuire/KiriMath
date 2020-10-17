/*
 * @Author:  Xu.Wang 
 * @Date: 2020-04-18 20:42:17 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:42:41
 */

#ifndef _KIRI_MATH_VECTOR_FIELD3F_H_
#define _KIRI_MATH_VECTOR_FIELD3F_H_

#include <kiri_math/math/field3.h>
#include <kiri_math/math/vector3.h>
#include <functional>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-F vector field.
    class VectorField3F : public Field3
    {
    public:
        //! Default constructor.
        VectorField3F();

        //! Default destructor.
        virtual ~VectorField3F();

        //! Returns sampled value at given position \p x.
        virtual Vector3F sample(const Vector3F &x) const = 0;

        //! Returns divergence at given position \p x.
        virtual double divergence(const Vector3F &x) const;

        //! Returns curl at given position \p x.
        virtual Vector3F curl(const Vector3F &x) const;

        //! Returns sampler function object.
        virtual std::function<Vector3F(const Vector3F &)> sampler() const;
    };

    //! Shared pointer for the VectorField3 type.
    typedef std::shared_ptr<VectorField3F> VectorField3FPtr;

} // namespace kiri_math

#endif // _KIRI_MATH_VECTOR_FIELD3_H_
