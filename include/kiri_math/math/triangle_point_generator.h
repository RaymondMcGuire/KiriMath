#ifndef _BBR_TRIANGLE_POINT_GENERATOR_H_
#define _BBR_TRIANGLE_POINT_GENERATOR_H_

#include <kiri_math/math/point_generator2.h>

namespace kiri_math
{

    //!
    //! \brief Right triangle point generator.
    //!
    class TrianglePointGenerator final : public PointGenerator2
    {
    public:
        //!
        //! \brief Invokes \p callback function for each right triangle points
        //! inside \p boundingBox.
        //!
        //! This function iterates every right triangle points inside \p boundingBox
        //! where \p spacing is the size of the right triangle structure.
        //!
        void forEachPoint(
            const BoundingBox2D &boundingBox,
            double spacing,
            const std::function<bool(const Vector2D &)> &callback) const override;
    };

    typedef std::shared_ptr<TrianglePointGenerator> TrianglePointGeneratorPtr;

} // namespace kiri_math

#endif // _BBR_TRIANGLE_POINT_GENERATOR_H_
