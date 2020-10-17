/*
 * @Author: Xu.Wang 
 * @Date: 2020-04-18 20:43:05 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:43:29
 */

#include <kiri_math/pch.h>
#include <kiri_math/math/vector_field3F.h>

using namespace kiri_math;

VectorField3F::VectorField3F()
{
}

VectorField3F::~VectorField3F()
{
}

double VectorField3F::divergence(const Vector3F &) const
{
    return 0.0;
}

Vector3F VectorField3F::curl(const Vector3F &) const
{
    return Vector3F();
}

std::function<Vector3F(const Vector3F &)> VectorField3F::sampler() const
{
    const VectorField3F *self = this;
    return [self](const Vector3F &x) -> Vector3F {
        return self->sample(x);
    };
}
