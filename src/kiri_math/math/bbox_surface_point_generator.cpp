/*
 * @Author: Xu.Wang 
 * @Date: 2020-04-26 00:55:23 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-05-29 23:23:17
 */

#include <kiri_math/pch.h>
#include <kiri_math/math/bbox_surface_point_generator.h>

namespace kiri_math
{
    void BboxSurfacePointGenerator::forEachPlane(
        const Vector3D &p1,
        const Vector3D &p2,
        double spacing,
        const std::function<bool(const Vector3D &)> &callback)
    {
        Vector3D minCorner;
        Vector3D maxCorner;
        minCorner.x = std::min(p1.x, p2.x);
        minCorner.y = std::min(p1.y, p2.y);
        minCorner.z = std::min(p1.z, p2.z);
        maxCorner.x = std::max(p1.x, p2.x);
        maxCorner.y = std::max(p1.y, p2.y);
        maxCorner.z = std::max(p1.z, p2.z);
        const Vector3D diff = maxCorner - minCorner;
        const size_t stepsX = static_cast<size_t>(diff.x / spacing) + 1;
        const size_t stepsY = static_cast<size_t>(diff.y / spacing) + 1;
        const size_t stepsZ = static_cast<size_t>(diff.z / spacing) + 1;

        bool shouldQuit = false;
        for (size_t x = 0; x < stepsX; x++)
        {
            for (size_t y = 0; y < stepsY; y++)
            {
                for (size_t z = 0; z < stepsZ; z++)
                {
                    const Vector3D position = minCorner + Vector3D(x * spacing, y * spacing, z * spacing);
                    if (!callback(position))
                    {
                        shouldQuit = true;
                        break;
                    }
                }
            }
        }
    }

    void BboxSurfacePointGenerator::forEachPlane(
        const Vector3F &p1,
        const Vector3F &p2,
        float spacing,
        const std::function<bool(const Vector3F &)> &callback)
    {
        Vector3F diff = p2 - p1;
        diff = diff / spacing;
        float stepsX = std::round(diff.x + 1);
        float stepsY = std::round(diff.y + 1);
        float stepsZ = std::round(diff.z + 1);
        KIRI_INFO << "diff/spacing:" << diff.x << "," << diff.y << "," << diff.z;
        KIRI_INFO << "Generate Boundary Panel:" << stepsX << "," << stepsY << "," << stepsZ;
        bool shouldQuit = false;
        for (int x = 0; x < (int)stepsX; x++)
        {
            for (int y = 0; y < (int)stepsY; y++)
            {
                for (int z = 0; z < (int)stepsZ; z++)
                {
                    float xPos = x * spacing;
                    float yPos = y * spacing;
                    float zPos = z * spacing;

                    const Vector3F position = p1 + Vector3F(xPos, yPos, zPos);
                    if (!callback(position))
                    {
                        shouldQuit = true;
                        break;
                    }
                }
            }
        }
    }

    void BboxSurfacePointGenerator::forEachPoint(
        const BoundingBox3D &boundingBox,
        double spacing,
        const std::function<bool(const Vector3D &)> &callback)
    {
        // bottom
        Vector3D v1 = boundingBox.corner(1);
        Vector3D v4 = boundingBox.corner(4);
        forEachPlane(v1, v4, spacing, callback);

        // left
        Vector3D v0 = boundingBox.corner(0);
        Vector3D v6 = boundingBox.corner(6);
        forEachPlane(v0, v6, spacing, callback);

        // right
        Vector3D v3 = boundingBox.corner(3);
        Vector3D v5 = boundingBox.corner(5);
        forEachPlane(v3, v5, spacing, callback);

        // front
        Vector3D v7 = boundingBox.corner(7);
        forEachPlane(v4, v7, spacing, callback);

        // back
        forEachPlane(v0, v3, spacing, callback);

        // top
        forEachPlane(v3, v6, spacing, callback);
    }

    void BboxSurfacePointGenerator::offsetNormDir(Vector3F &p1, Vector3F &p2, float spacing, float layerNum, float sign, bool sketch, bool onlyX, bool onlyY, bool onlyZ)
    {
        const Vector3F diff = p2 - p1;
        float radius = spacing / 2.0f;

        if (diff.x == 0.f)
        {
            p1.x += sign * radius;
            p2.x += (layerNum * 2 + 1) * sign * radius;

            if (sketch)
            {
                if (!onlyZ)
                {
                    if (p1.y > p2.y)
                    {
                        p1.y += layerNum * 2 * radius;
                        p2.y -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.y -= layerNum * 2 * radius;
                        p2.y += layerNum * 2 * radius;
                    }
                }

                if (!onlyY)
                {
                    if (p1.z > p2.z)
                    {
                        p1.z += layerNum * 2 * radius;
                        p2.z -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.z -= layerNum * 2 * radius;
                        p2.z += layerNum * 2 * radius;
                    }
                }
            }
        }
        else if (diff.y == 0.f)
        {

            p1.y += sign * radius;
            p2.y += (layerNum * 2 + 1) * sign * radius;

            if (sketch)
            {
                if (!onlyZ)
                {
                    if (p1.x > p2.x)
                    {
                        p1.x += layerNum * 2 * radius;
                        p2.x -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.x -= layerNum * 2 * radius;
                        p2.x += layerNum * 2 * radius;
                    }
                }

                if (!onlyX)
                {
                    if (p1.z > p2.z)
                    {
                        p1.z += layerNum * 2 * radius;
                        p2.z -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.z -= layerNum * 2 * radius;
                        p2.z += layerNum * 2 * radius;
                    }
                }
            }
        }
        else if (diff.z == 0.f)
        {
            p1.z += sign * radius;
            p2.z += (layerNum * 2 + 1) * sign * radius;

            if (sketch)
            {
                if (!onlyY)
                {
                    if (p1.x > p2.x)
                    {
                        p1.x += layerNum * 2 * radius;
                        p2.x -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.x -= layerNum * 2 * radius;
                        p2.x += layerNum * 2 * radius;
                    }
                }

                if (!onlyX)
                {
                    if (p1.y > p2.y)
                    {
                        p1.y += layerNum * 2 * radius;
                        p2.y -= layerNum * 2 * radius;
                    }
                    else
                    {
                        p1.y -= layerNum * 2 * radius;
                        p2.y += layerNum * 2 * radius;
                    }
                }
            }
        }

        Vector3F minCorner;
        Vector3F maxCorner;
        minCorner.x = std::min(p1.x, p2.x);
        minCorner.y = std::min(p1.y, p2.y);
        minCorner.z = std::min(p1.z, p2.z);
        maxCorner.x = std::max(p1.x, p2.x);
        maxCorner.y = std::max(p1.y, p2.y);
        maxCorner.z = std::max(p1.z, p2.z);

        // KIRI_INFO << "max-min:" << (maxCorner.y - minCorner.y);
        // KIRI_INFO << "spacing:" << spacing;
        // KIRI_INFO << "max-min/spacing:" << (maxCorner.y - minCorner.y) / spacing;

        p1 = minCorner;
        p2 = maxCorner;
    }

    void BboxSurfacePointGenerator::forEachPointInBottom(
        const BoundingBox3F &boundingBox,
        float spacing,
        float layerNum,
        const std::function<bool(const Vector3F &)> &callback)
    {
        // bottom
        Vector3F v1 = boundingBox.corner(1);
        Vector3F v4 = boundingBox.corner(4);
        offsetNormDir(v1, v4, spacing, layerNum - 1, -1.f, false);
        forEachPlane(v1, v4, spacing, callback);
    }

    void BboxSurfacePointGenerator::forEachPointNoTop(
        const BoundingBox3F &boundingBox,
        float spacing,
        float layerNum,
        const std::function<bool(const Vector3F &)> &callback)
    {
        // bottom
        Vector3F v1 = boundingBox.corner(1);
        Vector3F v4 = boundingBox.corner(4);
        offsetNormDir(v1, v4, spacing, layerNum - 1, -1.f, true);
        forEachPlane(v1, v4, spacing, callback);

        // left
        Vector3F v0 = boundingBox.corner(0);
        Vector3F v6 = boundingBox.corner(6);
        offsetNormDir(v0, v6, spacing, layerNum - 1, -1.f, true, false, false, true);
        forEachPlane(v0, v6, spacing, callback);

        // right
        Vector3F v3 = boundingBox.corner(3);
        Vector3F v5 = boundingBox.corner(5);
        offsetNormDir(v3, v5, spacing, layerNum - 1, 1.f, true, false, false, true);
        forEachPlane(v3, v5, spacing, callback);

        // front
        Vector3F v4f = boundingBox.corner(4);
        Vector3F v7 = boundingBox.corner(7);
        offsetNormDir(v4f, v7, spacing, layerNum - 1, 1.f);
        forEachPlane(v4f, v7, spacing, callback);

        // back
        Vector3F v0b = boundingBox.corner(0);
        Vector3F v3b = boundingBox.corner(3);
        offsetNormDir(v0b, v3b, spacing, layerNum - 1, -1.f);
        forEachPlane(v0b, v3b, spacing, callback);
    }

    void BboxSurfacePointGenerator::forEachPoint(
        const BoundingBox3F &boundingBox,
        float spacing,
        float layerNum,
        const std::function<bool(const Vector3F &)> &callback)
    {
        // bottom
        Vector3F v1 = boundingBox.corner(1);
        Vector3F v4 = boundingBox.corner(4);
        offsetNormDir(v1, v4, spacing, layerNum - 1, -1.f);
        forEachPlane(v1, v4, spacing, callback);

        // left
        Vector3F v0 = boundingBox.corner(0);
        Vector3F v6 = boundingBox.corner(6);
        offsetNormDir(v0, v6, spacing, layerNum - 1, -1.f);
        forEachPlane(v0, v6, spacing, callback);

        // right
        Vector3F v3 = boundingBox.corner(3);
        Vector3F v5 = boundingBox.corner(5);
        offsetNormDir(v3, v5, spacing, layerNum - 1, 1.f);
        forEachPlane(v3, v5, spacing, callback);

        // front
        Vector3F v4f = boundingBox.corner(4);
        Vector3F v7 = boundingBox.corner(7);
        offsetNormDir(v4f, v7, spacing, layerNum - 1, 1.f);
        forEachPlane(v4f, v7, spacing, callback);

        // back
        Vector3F v0b = boundingBox.corner(0);
        Vector3F v3b = boundingBox.corner(3);
        offsetNormDir(v0b, v3b, spacing, layerNum - 1, -1.f);
        forEachPlane(v0b, v3b, spacing, callback);

        // top
        Vector3F v3t = boundingBox.corner(3);
        Vector3F v6t = boundingBox.corner(6);
        offsetNormDir(v3t, v6t, spacing, layerNum - 1, 1.f);
        forEachPlane(v3t, v6t, spacing, callback);
    }

    void BboxSurfacePointGenerator::forEachPointWithNoOffset(
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
