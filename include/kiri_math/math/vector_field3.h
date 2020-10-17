/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-03 18:34:11 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:37:04
 */

#ifndef _KIRI_MATH_VECTOR_FIELD3_H_
#define _KIRI_MATH_VECTOR_FIELD3_H_

#include <kiri_math/math/field3.h>
#include <kiri_math/math/vector3.h>
#include <functional>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-D vector field.
    class VectorField3 : public Field3
    {
    public:
        //! Default constructor.
        VectorField3();

        //! Default destructor.
        virtual ~VectorField3();

        //! Returns sampled value at given position \p x.
        virtual Vector3D sample(const Vector3D &x) const = 0;

        //! Returns divergence at given position \p x.
        virtual double divergence(const Vector3D &x) const;

        //! Returns curl at given position \p x.
        virtual Vector3D curl(const Vector3D &x) const;

        //! Returns sampler function object.
        virtual std::function<Vector3D(const Vector3D &)> sampler() const;
    };

    //! Shared pointer for the VectorField3 type.
    typedef std::shared_ptr<VectorField3> VectorField3Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_VECTOR_FIELD3_H_
