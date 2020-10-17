/*
 * @Author: Bart Adams and Martin Wicke
 * @Date: 2020-03-28 01:45:51 
 * @Ref: "Meshless Approximation Methods and Applications in Physics Based Modeling and Animation", Eurographics 2009 Tutorial
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-19 03:50:41
 */

#ifndef _BBR_DETAIL_SPH_KERNELS3_INL_H_
#define _BBR_DETAIL_SPH_KERNELS3_INL_H_

#include <kiri_math/constants.h>

namespace kiri_math
{

    //Poly6 3-D
    inline SphStdKernel3::SphStdKernel3()
        : h(0), h2(0), h3(0), h5(0) {}

    inline SphStdKernel3::SphStdKernel3(double kernelRadius)
        : h(kernelRadius), h2(h * h), h3(h2 * h), h5(h2 * h3) {}

    inline SphStdKernel3::SphStdKernel3(const SphStdKernel3 &other)
        : h(other.h), h2(other.h2), h3(other.h3), h5(other.h5) {}

    inline double SphStdKernel3::operator()(double distance) const
    {
        if (distance * distance >= h2)
        {
            return 0.0;
        }
        else
        {
            double x = 1.0 - distance * distance / h2;
            return 315.0 / (64.0 * kPiD * h3) * x * x * x;
        }
    }

    inline double SphStdKernel3::firstDerivative(double distance) const
    {
        if (distance >= h)
        {
            return 0.0;
        }
        else
        {
            double x = 1.0 - distance * distance / h2;
            return -945.0 / (32.0 * kPiD * h5) * distance * x * x;
        }
    }

    inline Vector3D SphStdKernel3::gradient(
        const Vector3D &point) const
    {
        double dist = point.length();
        if (dist > 0.0)
        {
            return gradient(dist, point / dist);
        }
        else
        {
            return Vector3D(0, 0, 0);
        }
    }

    inline Vector3D SphStdKernel3::gradient(
        double distance,
        const Vector3D &directionToCenter) const
    {
        return -firstDerivative(distance) * directionToCenter;
    }

    inline double SphStdKernel3::secondDerivative(double distance) const
    {
        if (distance * distance >= h2)
        {
            return 0.0;
        }
        else
        {
            double x = distance * distance / h2;
            return 945.0 / (32.0 * kPiD * h5) * (1 - x) * (5 * x - 1);
        }
    }

    //Poly6 3-F
    inline SphStdKernel3F::SphStdKernel3F()
        : h(0), h2(0), h3(0), h5(0) {}

    inline SphStdKernel3F::SphStdKernel3F(float kernelRadius)
        : h(kernelRadius), h2(h * h), h3(h2 * h), h5(h2 * h3) {}

    inline SphStdKernel3F::SphStdKernel3F(const SphStdKernel3F &other)
        : h(other.h), h2(other.h2), h3(other.h3), h5(other.h5) {}

    inline float SphStdKernel3F::operator()(float distance) const
    {
        if (distance * distance >= h2)
        {
            return 0.0f;
        }
        else
        {
            float x = 1.0f - distance * distance / h2;
            return 315.0f / (64.0f * kPiF * h3) * x * x * x;
        }
    }

    inline float SphStdKernel3F::firstDerivative(float distance) const
    {
        if (distance >= h)
        {
            return 0.0f;
        }
        else
        {
            float x = 1.0f - distance * distance / h2;
            return -945.0f / (32.0f * kPiF * h5) * distance * x * x;
        }
    }

    inline Vector3F SphStdKernel3F::gradient(
        const Vector3F &point) const
    {
        float dist = point.length();
        if (dist > 0.0f)
        {
            return gradient(dist, point / dist);
        }
        else
        {
            return Vector3F(0, 0, 0);
        }
    }

    inline Vector3F SphStdKernel3F::gradient(
        float distance,
        const Vector3F &directionToCenter) const
    {
        return -firstDerivative(distance) * directionToCenter;
    }

    inline float SphStdKernel3F::secondDerivative(float distance) const
    {
        if (distance * distance >= h2)
        {
            return 0.0;
        }
        else
        {
            float x = distance * distance / h2;
            return 945.0f / (32.0f * kPiF * h5) * (1 - x) * (5 * x - 1);
        }
    }

    // 3-D spiky kernel
    inline SphSpikyKernel3::SphSpikyKernel3()
        : h(0), h2(0), h3(0), h4(0), h5(0) {}

    inline SphSpikyKernel3::SphSpikyKernel3(double h_)
        : h(h_), h2(h * h), h3(h2 * h), h4(h2 * h2), h5(h3 * h2) {}

    inline SphSpikyKernel3::SphSpikyKernel3(const SphSpikyKernel3 &other)
        : h(other.h), h2(other.h2), h3(other.h3), h4(other.h4), h5(other.h5) {}

    inline double SphSpikyKernel3::operator()(double distance) const
    {
        if (distance >= h)
        {
            return 0.0;
        }
        else
        {
            double x = 1.0 - distance / h;
            return 15.0 / (kPiD * h3) * x * x * x;
        }
    }

    inline double SphSpikyKernel3::firstDerivative(double distance) const
    {
        if (distance >= h)
        {
            return 0.0;
        }
        else
        {
            double x = 1.0 - distance / h;
            return -45.0 / (kPiD * h4) * x * x;
        }
    }

    inline Vector3D SphSpikyKernel3::gradient(
        const Vector3D &point) const
    {
        double dist = point.length();
        if (dist > 0.0)
        {
            return gradient(dist, point / dist);
        }
        else
        {
            return Vector3D(0, 0, 0);
        }
    }

    inline Vector3D SphSpikyKernel3::gradient(
        double distance,
        const Vector3D &directionToCenter) const
    {
        return -firstDerivative(distance) * directionToCenter;
    }

    inline double SphSpikyKernel3::secondDerivative(double distance) const
    {
        if (distance >= h)
        {
            return 0.0;
        }
        else
        {
            double x = 1.0 - distance / h;
            return 90.0 / (kPiD * h5) * x;
        }
    }

    // 3-F spiky kernel
    inline SphSpikyKernel3F::SphSpikyKernel3F()
        : h(0), h2(0), h3(0), h4(0), h5(0) {}

    inline SphSpikyKernel3F::SphSpikyKernel3F(float h_)
        : h(h_), h2(h * h), h3(h2 * h), h4(h2 * h2), h5(h3 * h2) {}

    inline SphSpikyKernel3F::SphSpikyKernel3F(const SphSpikyKernel3F &other)
        : h(other.h), h2(other.h2), h3(other.h3), h4(other.h4), h5(other.h5) {}

    inline float SphSpikyKernel3F::operator()(float distance) const
    {
        if (distance >= h)
        {
            return 0.0f;
        }
        else
        {
            float x = 1.0f - distance / h;
            return 15.0f / (kPiF * h3) * x * x * x;
        }
    }

    inline float SphSpikyKernel3F::firstDerivative(float distance) const
    {
        if (distance >= h)
        {
            return 0.0f;
        }
        else
        {
            float x = 1.0f - distance / h;
            return -45.0f / (kPiF * h4) * x * x;
        }
    }

    inline Vector3F SphSpikyKernel3F::gradient(
        const Vector3F &point) const
    {
        float dist = point.length();
        if (dist > 0.0)
        {
            return gradient(dist, point / dist);
        }
        else
        {
            return Vector3F(0, 0, 0);
        }
    }

    inline Vector3F SphSpikyKernel3F::gradient(
        float distance,
        const Vector3F &directionToCenter) const
    {
        return -firstDerivative(distance) * directionToCenter;
    }

    inline float SphSpikyKernel3F::secondDerivative(float distance) const
    {
        if (distance >= h)
        {
            return 0.0f;
        }
        else
        {
            float x = 1.0f - distance / h;
            return 90.0f / (kPiF * h5) * x;
        }
    }

    // 3-F cubic kernel
    inline SphCubicKernel3F::SphCubicKernel3F()
        : h(0), h2(0), h3(0), mk(8.0f / (pi<float>() * h3)), ml(48.0f / (pi<float>() * h3))
    {
        mWZero = W(Vector3F());
    }

    inline SphCubicKernel3F::SphCubicKernel3F(float h_)
        : h(h_), h2(h * h), h3(h2 * h), mk(8.0f / (pi<float>() * h3)), ml(48.0f / (pi<float>() * h3))
    {
        mWZero = W(Vector3F());
    }

    inline SphCubicKernel3F::SphCubicKernel3F(const SphCubicKernel3F &other)
        : h(other.h), h2(other.h2), h3(other.h3), mk(8.0f / (pi<float>() * h3)), ml(48.0f / (pi<float>() * h3))
    {
        mWZero = W(Vector3F());
    }

    inline float SphCubicKernel3F::W_zero() const
    {
        return mWZero;
    }

    inline float SphCubicKernel3F::W(Vector3F r) const
    {
        float ret = 0.0;
        const float rl = r.length();
        const float q = rl / h;
#ifndef NO_DISTANCE_TEST
        if (q <= 1.0)
#endif
        {
            if (q <= 0.5)
            {
                const float q2 = q * q;
                const float q3 = q2 * q;
                ret = mk * (6.0f * q3 - 6.0f * q2 + 1.0f);
            }
            else
            {
                ret = mk * (2.0f * pow(1.0f - q, 3));
            }
        }
        return ret;
    }

    inline float SphCubicKernel3F::operator()(Vector3F r) const
    {
        return W(r);
    }

    inline Vector3F SphCubicKernel3F::gradW(Vector3F r) const
    {
        Vector3F ret;
        const float rl = r.length();
        const float q = rl / h;
#ifndef NO_DISTANCE_TEST
        if (q <= 1.0)
#endif
        {
            if (rl > 1.0e-6)
            {
                const Vector3F gradq = r * (1.0f / (rl * h));
                if (q <= 0.5)
                {
                    ret = ml * q * (3.0f * q - 2.0f) * gradq;
                }
                else
                {
                    const float factor = 1.0f - q;
                    ret = ml * (-factor * factor) * gradq;
                }
            }
        }
#ifndef NO_DISTANCE_TEST
        else
            ret.setZero();
#endif

        return ret;
    }
} // namespace kiri_math

#endif // _BBR_DETAIL_SPH_KERNELS3_INL_H_
