/*
 * @Author: Xu.Wang 
 * @Date: 2020-04-18 20:43:59 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:45:13
 */

#include <kiri_math/pch.h>
#include <kiri_math/math/constant_vector_field3F.h>

using namespace kiri_math;

ConstantVectorField3F::ConstantVectorField3F(const Vector3F &value) : _value(value)
{
}

Vector3F ConstantVectorField3F::sample(const Vector3F &x) const
{
    UNUSED_VARIABLE(x);

    return _value;
}

std::function<Vector3F(const Vector3F &)> ConstantVectorField3F::sampler() const
{
    return [this](const Vector3F &) -> Vector3F {
        return _value;
    };
}

ConstantVectorField3F::Builder ConstantVectorField3F::builder()
{
    return Builder();
}

ConstantVectorField3F::Builder &
ConstantVectorField3F::Builder::withValue(const Vector3F &value)
{
    _value = value;
    return *this;
}

ConstantVectorField3F ConstantVectorField3F::Builder::build() const
{
    return ConstantVectorField3F(_value);
}

ConstantVectorField3FPtr ConstantVectorField3F::Builder::makeShared() const
{
    return std::shared_ptr<ConstantVectorField3F>(
        new ConstantVectorField3F(_value),
        [](ConstantVectorField3F *obj) {
            delete obj;
        });
}
