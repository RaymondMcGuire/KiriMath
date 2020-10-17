/*
 * @Author: Doyub Kim 
 * @Date: 2020-03-28 01:45:38 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-19 03:48:37
 * 
 * Müller, Matthias, David Charypar, and Markus Gross.
 * "Particle-based fluid simulation for interactive applications."
 * Proceedings of the 2003 ACM SIGGRAPH/Eurographics symposium on Computer
 * animation. Eurographics Association, 2003.
 */
#ifndef _KIRI_SPH_KERNELS3_H_
#define _KIRI_SPH_KERNELS3_H_

#include <kiri_math/constants.h>
#include <kiri_math/math/vector3.h>

namespace kiri_math
{

    //! \brief Poly6 3-D SPH kernel function object.
    struct SphStdKernel3
    {
        //! Kernel radius.
        double h;

        //! Square of the kernel radius.
        double h2;

        //! Cubic of the kernel radius.
        double h3;

        //! Fifth-power of the kernel radius.
        double h5;

        //! Constructs a kernel object with zero radius.
        SphStdKernel3();

        //! Constructs a kernel object with given radius.
        explicit SphStdKernel3(double kernelRadius);

        //! Copy constructor
        SphStdKernel3(const SphStdKernel3 &other);

        //! Returns kernel function value at given distance.
        double operator()(double distance) const;

        //! Returns the first derivative at given distance.
        double firstDerivative(double distance) const;

        //! Returns the gradient at a point.
        Vector3D gradient(const Vector3D &point) const;

        //! Returns the gradient at a point defined by distance and direction.
        Vector3D gradient(double distance, const Vector3D &direction) const;

        //! Returns the second derivative at given distance.
        double secondDerivative(double distance) const;
    };

    //! \brief Poly6 3-F SPH kernel function object.
    struct SphStdKernel3F
    {
        //! Kernel radius.
        float h;

        //! Square of the kernel radius.
        float h2;

        //! Cubic of the kernel radius.
        float h3;

        //! Fifth-power of the kernel radius.
        float h5;

        //! Constructs a kernel object with zero radius.
        SphStdKernel3F();

        //! Constructs a kernel object with given radius.
        explicit SphStdKernel3F(float kernelRadius);

        //! Copy constructor
        SphStdKernel3F(const SphStdKernel3F &other);

        //! Returns kernel function value at given distance.
        float operator()(float distance) const;

        //! Returns the first derivative at given distance.
        float firstDerivative(float distance) const;

        //! Returns the gradient at a point.
        Vector3F gradient(const Vector3F &point) const;

        //! Returns the gradient at a point defined by distance and direction.
        Vector3F gradient(float distance, const Vector3F &direction) const;

        //! Returns the second derivative at given distance.
        float secondDerivative(float distance) const;
    };

    //! \brief Spiky 3-D SPH kernel function object.
    struct SphSpikyKernel3
    {
        //! Kernel radius.
        double h;

        //! Square of the kernel radius.
        double h2;

        //! Cubic of the kernel radius.
        double h3;

        //! Fourth-power of the kernel radius.
        double h4;

        //! Fifth-power of the kernel radius.
        double h5;

        //! Constructs a kernel object with zero radius.
        SphSpikyKernel3();

        //! Constructs a kernel object with given radius.
        explicit SphSpikyKernel3(double kernelRadius);

        //! Copy constructor
        SphSpikyKernel3(const SphSpikyKernel3 &other);

        //! Returns kernel function value at given distance.
        double operator()(double distance) const;

        //! Returns the first derivative at given distance.
        double firstDerivative(double distance) const;

        //! Returns the gradient at a point.
        Vector3D gradient(const Vector3D &point) const;

        //! Returns the gradient at a point defined by distance and direction.
        Vector3D gradient(double distance, const Vector3D &direction) const;

        //! Returns the second derivative at given distance.
        double secondDerivative(double distance) const;
    };

    //! \brief Spiky 3-F SPH kernel function object.
    struct SphSpikyKernel3F
    {
        //! Kernel radius.
        float h;

        //! Square of the kernel radius.
        float h2;

        //! Cubic of the kernel radius.
        float h3;

        //! Fourth-power of the kernel radius.
        float h4;

        //! Fifth-power of the kernel radius.
        float h5;

        //! Constructs a kernel object with zero radius.
        SphSpikyKernel3F();

        //! Constructs a kernel object with given radius.
        explicit SphSpikyKernel3F(float kernelRadius);

        //! Copy constructor
        SphSpikyKernel3F(const SphSpikyKernel3F &other);

        //! Returns kernel function value at given distance.
        float operator()(float distance) const;

        //! Returns the first derivative at given distance.
        float firstDerivative(float distance) const;

        //! Returns the gradient at a point.
        Vector3F gradient(const Vector3F &point) const;

        //! Returns the gradient at a point defined by distance and direction.
        Vector3F gradient(float distance, const Vector3F &direction) const;

        //! Returns the second derivative at given distance.
        float secondDerivative(float distance) const;
    };

    //! \brief Cubic Kernel:https://github.com/InteractiveComputerGraphics/PositionBasedDynamics/blob/master/PositionBasedDynamics/SPHKernels.h
    struct SphCubicKernel3F
    {
        //! Kernel radius.
        float h;

        //! Square of the kernel radius.
        float h2;

        //! Cubic of the kernel radius.
        float h3;

        float mk;

        float ml;

        float mWZero;

        //! Constructs a kernel object with zero radius.
        SphCubicKernel3F();

        //! Constructs a kernel object with given radius.
        explicit SphCubicKernel3F(float kernelRadius);

        //! Copy constructor
        SphCubicKernel3F(const SphCubicKernel3F &other);

        //! Returns kernel function value whichi the r is set to (0,0,0)
        float W_zero() const;

        //! Returns kernel function value at given vector3.
        float W(Vector3F r) const;

        //! Returns kernel function value at given vector3.
        float operator()(Vector3F r) const;

        //! Returns the first derivative at given vector3.
        Vector3F gradW(Vector3F r) const;
    };

} // namespace kiri_math

#include "inl/sph_kernels3-inl.h"

#endif // _KIRI_SPH_KERNELS3_H_
