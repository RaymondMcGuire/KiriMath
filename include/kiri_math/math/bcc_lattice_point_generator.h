/*
 * @Author: Doyub Kim 
 * @Date: 2020-03-31 19:09:24 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 20:57:13
 */
#ifndef _BBR_BCC_LATTICE_POINT_GENERATOR_H_
#define _BBR_BCC_LATTICE_POINT_GENERATOR_H_

#include <kiri_math/math/point_generator3.h>

namespace kiri_math
{

    //!
    //! \brief Body-centered lattice points generator.
    //!
    //! \see http://en.wikipedia.org/wiki/Cubic_crystal_system
    //!      http://mathworld.wolfram.com/CubicClosePacking.html
    //!
    class BccLatticePointGenerator final : public PointGenerator3
    {
    public:
        //!
        //! \brief Invokes \p callback function for each BCC-lattice points inside
        //! \p boundingBox.
        //!
        //! This function iterates every BCC-lattice points inside \p boundingBox
        //! where \p spacing is the size of the unit cell of BCC structure.
        //!
        void forEachPoint(
            const BoundingBox3D &boundingBox,
            double spacing,
            const std::function<bool(const Vector3D &)> &callback) override;

        void forEachPoint(
            const BoundingBox3F &boundingBox,
            float spacing,
            float layerNum,
            const std::function<bool(const Vector3F &)> &callback) override;

        void forEachPointWithNoOffset(
            const BoundingBox3F &boundingBox,
            float spacing,
            const std::function<bool(const Vector3F &)> &callback) override;
    };

    //! Shared pointer type for the BccLatticePointGenerator.
    typedef std::shared_ptr<BccLatticePointGenerator> BccLatticePointGeneratorPtr;

} // namespace kiri_math

#endif // _BBR_BCC_LATTICE_POINT_GENERATOR_H_
