/*
 * @Author: Xu.Wang 
 * @Date: 2020-04-18 20:44:33 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:45:15
 */

#ifndef _KIRI_MATH_CONSTANT_VECTOR_FIELD3F_H_
#define _KIRI_MATH_CONSTANT_VECTOR_FIELD3F_H_

#include <kiri_math/math/vector_field3F.h>
#include <memory>

namespace kiri_math
{

    //! 3-D constant vector field.
    class ConstantVectorField3F final : public VectorField3F
    {
    public:
        class Builder;

        //! Constructs a constant vector field with given \p value.
        explicit ConstantVectorField3F(const Vector3F &value);

        //! Returns the sampled value at given position \p x.
        Vector3F sample(const Vector3F &x) const override;

        //! Returns the sampler function.
        std::function<Vector3F(const Vector3F &)> sampler() const override;

        //! Returns builder fox ConstantVectorField3F.
        static Builder builder();

    private:
        Vector3F _value;
    };

    //! Shared pointer for the ConstantVectorField3F type.
    typedef std::shared_ptr<ConstantVectorField3F> ConstantVectorField3FPtr;

    //!
    //! \brief Front-end to create ConstantVectorField3F objects step by step.
    //!
    class ConstantVectorField3F::Builder final
    {
    public:
        //! Returns builder with value.
        Builder &withValue(const Vector3F &value);

        //! Builds ConstantVectorField3F.
        ConstantVectorField3F build() const;

        //! Builds shared pointer of ConstantVectorField3F instance.
        ConstantVectorField3FPtr makeShared() const;

    private:
        Vector3F _value{0, 0, 0};
    };

} // namespace kiri_math

#endif // _KIRI_MATH_CONSTANT_VECTOR_FIELD3_H_
