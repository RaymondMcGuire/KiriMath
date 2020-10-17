#ifndef SRC_BBR_FACTORY_H_
#define SRC_BBR_FACTORY_H_

#include <kiri_math/math/scalar_grid2.h>
#include <kiri_math/math/scalar_grid3.h>
#include <kiri_math/math/vector_grid2.h>
#include <kiri_math/math/vector_grid3.h>
#include <kiri_math/search/point_neighbor_searcher2.h>
#include <kiri_math/search/point_neighbor_searcher3.h>
#include <string>

namespace kiri_math
{

    class Factory
    {
    public:
        static ScalarGrid2Ptr buildScalarGrid2(const std::string &name);

        static ScalarGrid3Ptr buildScalarGrid3(const std::string &name);

        static VectorGrid2Ptr buildVectorGrid2(const std::string &name);

        static VectorGrid3Ptr buildVectorGrid3(const std::string &name);

        static PointNeighborSearcher2Ptr buildPointNeighborSearcher2(
            const std::string &name);

        static PointNeighborSearcher3Ptr buildPointNeighborSearcher3(
            const std::string &name);
    };

} // namespace kiri_math

#endif // SRC_BBR_FACTORY_H_
