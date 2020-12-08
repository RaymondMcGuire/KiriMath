/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-18 20:16:42 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 20:57:31
 */
#include <kiri_math/pch.h>
#include <kiri_math/math/bcc_lattice_point_generator.h>

namespace kiri_math
{

    void BccLatticePointGenerator::forEachPoint(
        const BoundingBox3D &boundingBox,
        double spacing,
        const std::function<bool(const Vector3D &)> &callback)
    {
        double halfSpacing = spacing / 2.0;
        double boxWidth = boundingBox.width();
        double boxHeight = boundingBox.height();
        double boxDepth = boundingBox.depth();

        Vector3D position;
        bool hasOffset = false;
        bool shouldQuit = false;
        for (int k = 0; k * halfSpacing <= boxDepth && !shouldQuit; ++k)
        {
            position.z = k * halfSpacing + boundingBox.LowestPoint.z;

            double offset = (hasOffset) ? halfSpacing : 0.0;

            for (int j = 0; j * spacing + offset <= boxHeight && !shouldQuit; ++j)
            {
                position.y = j * spacing + offset + boundingBox.LowestPoint.y;

                for (int i = 0; i * spacing + offset <= boxWidth; ++i)
                {
                    position.x = i * spacing + offset + boundingBox.LowestPoint.x;
                    if (!callback(position))
                    {
                        shouldQuit = true;
                        break;
                    }
                }
            }

            hasOffset = !hasOffset;
        }
    }

    void BccLatticePointGenerator::forEachPoint(
        const BoundingBox3F &boundingBox,
        float spacing,
        float layerNum,
        const std::function<bool(const Vector3F &)> &callback)
    {
        float halfSpacing = spacing / 2.0f;
        float boxWidth = boundingBox.width();
        float boxHeight = boundingBox.height();
        float boxDepth = boundingBox.depth();

        Vector3F position;
        bool hasOffset = false;
        bool shouldQuit = false;
        for (int k = 0; k * halfSpacing <= boxDepth && !shouldQuit; ++k)
        {
            position.z = k * halfSpacing + boundingBox.LowestPoint.z;

            float offset = (hasOffset) ? halfSpacing : 0.0f;

            for (int j = 0; j * spacing + offset <= boxHeight && !shouldQuit; ++j)
            {
                position.y = j * spacing + offset + boundingBox.LowestPoint.y;

                for (int i = 0; i * spacing + offset <= boxWidth; ++i)
                {
                    position.x = i * spacing + offset + boundingBox.LowestPoint.x;
                    if (!callback(position))
                    {
                        shouldQuit = true;
                        break;
                    }
                }
            }

            hasOffset = !hasOffset;
        }
    }

    void BccLatticePointGenerator::forEachPointWithNoOffset(
        const BoundingBox3F &boundingBox,
        float spacing,
        const std::function<bool(const Vector3F &)> &callback)
    {
        float boxWidth = boundingBox.width();
        float boxHeight = boundingBox.height();
        float boxDepth = boundingBox.depth();

        Vector3F position;
        bool shouldQuit = false;
        for (int k = 0; k * spacing <= boxDepth && !shouldQuit; ++k)
        {
            position.z = k * spacing + boundingBox.LowestPoint.z;

            for (int j = 0; j * spacing <= boxHeight && !shouldQuit; ++j)
            {
                position.y = j * spacing + boundingBox.LowestPoint.y;

                for (int i = 0; i * spacing <= boxWidth; ++i)
                {
                    position.x = i * spacing + boundingBox.LowestPoint.x;
                    if (!callback(position))
                    {
                        shouldQuit = true;
                        break;
                    }
                }
            }
        }
    }
} // namespace kiri_math
