/*
 * @Author: Xu.Wang 
 * @Date: 2020-03-28 01:38:34 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-26 01:55:11
 */
#ifndef _KIRI_MATH_MIN_H_
#define _KIRI_MATH_MIN_H_

#include <kiri_math/compatibility.h>

//  math & array
#include <kiri_math/math/vector.h>
#include <kiri_math/math/vector2.h>
#include <kiri_math/math/vector3.h>
#include <kiri_math/math/vector4.h>
#include <kiri_math/math/matrix2x2.h>
#include <kiri_math/math/matrix3x3.h>
#include <kiri_math/math/matrix4x4.h>

#include <kiri_math/math/vector_field3F.h>
#include <kiri_math/math/constant_vector_field3F.h>

#include <kiri_math/array/array1.h>

#include <kiri_math/math/math_utils.h>

// physics
#include <kiri_math/physics/bounding_box3.h>
#include <kiri_math/physics/collider3.h>
#include <kiri_math/physics/rigid_body_collider3.h>
#include <kiri_math/physics/physics_helpers.h>

// model
#include <kiri_math/model/box3.h>

// point generator
#include <kiri_math/math/point_generator3.h>
#include <kiri_math/math/bcc_lattice_point_generator.h>
#include <kiri_math/math/bbox_surface_point_generator.h>

// nn searcher
#include <kiri_math/search/point_hash_grid_searcher3.h>
#include <kiri_math/search/point_parallel_hash_grid_searcher3.h>

// sph
#include <kiri_math/sph/sph_kernels3.h>

// logging
#include <kiri_math/logging.h>

#endif // _KIRI_MATH_MIN_H_