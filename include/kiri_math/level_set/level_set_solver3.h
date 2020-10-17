#ifndef _KIRI_LEVEL_SET_SOLVER3_H_
#define _KIRI_LEVEL_SET_SOLVER3_H_

#include <kiri_math/math/collocated_vector_grid3.h>
#include <kiri_math/math/face_centered_grid3.h>
#include <kiri_math/math/scalar_grid3.h>
#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-D level set solver.
    class LevelSetSolver3
    {
    public:
        //! Default constructor.
        LevelSetSolver3();

        //! Default destructor.
        virtual ~LevelSetSolver3();

        //!
        //! Reinitializes given scalar field to signed-distance field.
        //!
        //! \param inputSdf Input signed-distance field which can be distorted.
        //! \param maxDistance Max range of reinitialization.
        //! \param outputSdf Output signed-distance field.
        //!
        virtual void reinitialize(
            const ScalarGrid3 &inputSdf,
            double maxDistance,
            ScalarGrid3 *outputSdf) = 0;

        //!
        //! Extrapolates given scalar field from negative to positive SDF region.
        //!
        //! \param input Input scalar field to be extrapolated.
        //! \param sdf Reference signed-distance field.
        //! \param maxDistance Max range of extrapolation.
        //! \param output Output scalar field.
        //!
        virtual void extrapolate(
            const ScalarGrid3 &input,
            const ScalarField3 &sdf,
            double maxDistance,
            ScalarGrid3 *output) = 0;

        //!
        //! Extrapolates given collocated vector field from negative to positive SDF
        //! region.
        //!
        //! \param input Input collocated vector field to be extrapolated.
        //! \param sdf Reference signed-distance field.
        //! \param maxDistance Max range of extrapolation.
        //! \param output Output collocated vector field.
        //!
        virtual void extrapolate(
            const CollocatedVectorGrid3 &input,
            const ScalarField3 &sdf,
            double maxDistance,
            CollocatedVectorGrid3 *output) = 0;

        //!
        //! Extrapolates given face-centered vector field from negative to positive
        //! SDF region.
        //!
        //! \param input Input face-centered field to be extrapolated.
        //! \param sdf Reference signed-distance field.
        //! \param maxDistance Max range of extrapolation.
        //! \param output Output face-centered vector field.
        //!
        virtual void extrapolate(
            const FaceCenteredGrid3 &input,
            const ScalarField3 &sdf,
            double maxDistance,
            FaceCenteredGrid3 *output) = 0;
    };

    //! Shared pointer type for the LevelSetSolver3.
    typedef std::shared_ptr<LevelSetSolver3> LevelSetSolver3Ptr;

} // namespace kiri_math

#endif // INCLUDE_KIRI_LEVEL_SET_SOLVER3_H_
