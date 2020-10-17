#ifndef _KIRI_MATH_SPH_POINTS_TO_IMPLICIT2_H_
#define _KIRI_MATH_SPH_POINTS_TO_IMPLICIT2_H_

#include <kiri_math/p2surf/points_to_implicit2.h>

namespace kiri_math
{

    //!
    //! \brief 2-D points-to-implicit converter based on standard SPH kernel.
    //!
    //! \see Müller, Matthias, David Charypar, and Markus Gross.
    //!      "Particle-based fluid simulation for interactive applications."
    //!      Proceedings of the 2003 ACM SIGGRAPH/Eurographics symposium on Computer
    //!      animation. Eurographics Association, 2003.
    //!
    class SphPointsToImplicit2 final : public PointsToImplicit2
    {
    public:
        //! Constructs the converter with given kernel radius and cut-off density.
        SphPointsToImplicit2(double kernelRadius = 1.0, double cutOffDensity = 0.5,
                             bool isOutputSdf = true);

        //! Converts the given points to implicit surface scalar field.
        void convert(const ConstArrayAccessor1<Vector2D> &points,
                     ScalarGrid2 *output) const override;

    private:
        double _kernelRadius = 1.0;
        double _cutOffDensity = 0.5;
        bool _isOutputSdf = true;
    };

    //! Shared pointer type for SphPointsToImplicit2 class.
    typedef std::shared_ptr<SphPointsToImplicit2> SphPointsToImplicit2Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_SPH_POINTS_TO_IMPLICIT2_H_
