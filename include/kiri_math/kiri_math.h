#ifndef _KIRI_MATH_H_
#define _KIRI_MATH_H_
// #include <kiri_math/advection_solver2.h>
// #include <kiri_math/advection_solver3.h>
#include <kiri_math/anime/animation.h>
// #include <kiri_math/anisotropic_points_to_implicit2.h>
// #include <kiri_math/anisotropic_points_to_implicit3.h>
// #include <kiri_math/apic_solver2.h>
// #include <kiri_math/apic_solver3.h>
#include <kiri_math/array/array.h>
#include <kiri_math/array/array1.h>
#include <kiri_math/array/array2.h>
#include <kiri_math/array/array3.h>
#include <kiri_math/array/array_accessor.h>
#include <kiri_math/array/array_accessor1.h>
#include <kiri_math/array/array_accessor2.h>
#include <kiri_math/array/array_accessor3.h>
#include <kiri_math/array/array_samplers.h>
#include <kiri_math/array/array_samplers1.h>
#include <kiri_math/array/array_samplers2.h>
#include <kiri_math/array/array_samplers3.h>
#include <kiri_math/array/array_utils.h>
#include <kiri_math/math/bcc_lattice_point_generator.h>
#include <kiri_math/blas.h>
#include <kiri_math/physics/bounding_box.h>
#include <kiri_math/physics/bounding_box2.h>
#include <kiri_math/physics/bounding_box3.h>
#include <kiri_math/model/box2.h>
#include <kiri_math/model/box3.h>
#include <kiri_math/math/bvh2.h>
#include <kiri_math/math/bvh3.h>
#include <kiri_math/math/cell_centered_scalar_grid2.h>
#include <kiri_math/math/cell_centered_scalar_grid3.h>
#include <kiri_math/math/cell_centered_vector_grid2.h>
#include <kiri_math/math/cell_centered_vector_grid3.h>
// #include <kiri_math/cg.h>
#include <kiri_math/physics/collider2.h>
#include <kiri_math/physics/collider3.h>
// #include <kiri_math/physics/collider_set2.h>
// #include <kiri_math/physics/collider_set3.h>
#include <kiri_math/math/collocated_vector_grid2.h>
#include <kiri_math/math/collocated_vector_grid3.h>
#include <kiri_math/math/constant_scalar_field2.h>
#include <kiri_math/math/constant_scalar_field3.h>
#include <kiri_math/math/constant_vector_field2.h>
#include <kiri_math/math/constant_vector_field3.h>
#include <kiri_math/constants.h>
#include <kiri_math/cpp_utils.h>
// #include <kiri_math/cubic_semi_lagrangian2.h>
// #include <kiri_math/cubic_semi_lagrangian3.h>
// #include <kiri_math/custom_implicit_surface2.h>
// #include <kiri_math/custom_implicit_surface3.h>
// #include <kiri_math/custom_scalar_field2.h>
// #include <kiri_math/custom_scalar_field3.h>
// #include <kiri_math/custom_vector_field2.h>
// #include <kiri_math/custom_vector_field3.h>
#include <kiri_math/model/cylinder3.h>
// #include <kiri_math/eno_level_set_solver2.h>
// #include <kiri_math/eno_level_set_solver3.h>
#include <kiri_math/math/face_centered_grid2.h>
#include <kiri_math/math/face_centered_grid3.h>
// #include <kiri_math/fcc_lattice_point_generator.h>
// #include <kiri_math/fdm_cg_solver2.h>
// #include <kiri_math/fdm_cg_solver3.h>
// #include <kiri_math/fdm_gauss_seidel_solver2.h>
// #include <kiri_math/fdm_gauss_seidel_solver3.h>
// #include <kiri_math/fdm_iccg_solver2.h>
// #include <kiri_math/fdm_iccg_solver3.h>
// #include <kiri_math/fdm_jacobi_solver2.h>
// #include <kiri_math/fdm_jacobi_solver3.h>
// #include <kiri_math/fdm_linear_system2.h>
// #include <kiri_math/fdm_linear_system3.h>
// #include <kiri_math/fdm_linear_system_solver2.h>
// #include <kiri_math/fdm_linear_system_solver3.h>
// #include <kiri_math/fdm_mg_linear_system2.h>
// #include <kiri_math/fdm_mg_linear_system3.h>
// #include <kiri_math/fdm_mg_solver2.h>
// #include <kiri_math/fdm_mg_solver3.h>
// #include <kiri_math/fdm_mgpcg_solver2.h>
// #include <kiri_math/fdm_mgpcg_solver3.h>
#include <kiri_math/fdm_utils.h>
#include <kiri_math/math/field2.h>
#include <kiri_math/math/field3.h>
// #include <kiri_math/flip_solver2.h>
// #include <kiri_math/flip_solver3.h>
#include <kiri_math/level_set/fmm_level_set_solver2.h>
#include <kiri_math/level_set/fmm_level_set_solver3.h>
#include <kiri_math/functors.h>
#include <kiri_math/math/grid2.h>
#include <kiri_math/math/grid3.h>
// #include <kiri_math/grid_backward_euler_diffusion_solver2.h>
// #include <kiri_math/grid_backward_euler_diffusion_solver3.h>
// #include <kiri_math/grid_blocked_boundary_condition_solver2.h>
// #include <kiri_math/grid_blocked_boundary_condition_solver3.h>
// #include <kiri_math/grid_boundary_condition_solver2.h>
// #include <kiri_math/grid_boundary_condition_solver3.h>
// #include <kiri_math/grid_diffusion_solver2.h>
// #include <kiri_math/grid_diffusion_solver3.h>
// #include <kiri_math/grid_emitter2.h>
// #include <kiri_math/grid_emitter3.h>
// #include <kiri_math/grid_emitter_set2.h>
// #include <kiri_math/grid_emitter_set3.h>
// #include <kiri_math/grid_fluid_solver2.h>
// #include <kiri_math/grid_fluid_solver3.h>
// #include <kiri_math/grid_forward_euler_diffusion_solver2.h>
// #include <kiri_math/grid_forward_euler_diffusion_solver3.h>
// #include <kiri_math/grid_fractional_boundary_condition_solver2.h>
// #include <kiri_math/grid_fractional_boundary_condition_solver3.h>
// #include <kiri_math/grid_fractional_single_phase_pressure_solver2.h>
// #include <kiri_math/grid_fractional_single_phase_pressure_solver3.h>
// #include <kiri_math/grid_point_generator2.h>
// #include <kiri_math/grid_point_generator3.h>
// #include <kiri_math/grid_pressure_solver2.h>
// #include <kiri_math/grid_pressure_solver3.h>
// #include <kiri_math/grid_single_phase_pressure_solver2.h>
// #include <kiri_math/grid_single_phase_pressure_solver3.h>
// #include <kiri_math/grid_smoke_solver2.h>
// #include <kiri_math/grid_smoke_solver3.h>
// #include <kiri_math/grid_system_data2.h>
// #include <kiri_math/grid_system_data3.h>
#include <kiri_math/physics/implicit_surface2.h>
#include <kiri_math/physics/implicit_surface3.h>
#include <kiri_math/physics/implicit_surface_set2.h>
#include <kiri_math/physics/implicit_surface_set3.h>
// #include <kiri_math/physics/implicit_triangle_mesh3.h>
#include <kiri_math/query/intersection_query_engine2.h>
#include <kiri_math/query/intersection_query_engine3.h>
// #include <kiri_math/iterative_level_set_solver2.h>
// #include <kiri_math/iterative_level_set_solver3.h>
#include <kiri_math/math/kdtree.h>
// #include <kiri_math/level_set_liquid_solver2.h>
// #include <kiri_math/level_set_liquid_solver3.h>
#include <kiri_math/level_set/level_set_solver2.h>
#include <kiri_math/level_set/level_set_solver3.h>
#include <kiri_math/level_set/level_set_utils.h>
// #include <kiri_math/query/list_query_engine2.h>
// #include <kiri_math/query/list_query_engine3.h>
#include <kiri_math/logging.h>
#include <kiri_math/platform.h>
#include <kiri_math/math/marching_cubes.h>
#include <kiri_math/math/math_utils.h>
#include <kiri_math/math/matrix.h>
#include <kiri_math/math/matrix2x2.h>
#include <kiri_math/math/matrix3x3.h>
#include <kiri_math/math/matrix4x4.h>
#include <kiri_math/math/matrix_csr.h>
#include <kiri_math/math/matrix_expression.h>
#include <kiri_math/math/matrix_mxn.h>
// #include <kiri_math/mg.h>
#include <kiri_math/query/nearest_neighbor_query_engine2.h>
#include <kiri_math/query/nearest_neighbor_query_engine3.h>
// #include <kiri_math/octree.h>
#include <kiri_math/parallel.h>
#include <kiri_math/particle/particle_emitter2.h>
#include <kiri_math/particle/particle_emitter3.h>
#include <kiri_math/particle/particle_emitter_set2.h>
#include <kiri_math/particle/particle_emitter_set3.h>
#include <kiri_math/particle/particle_system_data2.h>
#include <kiri_math/particle/particle_system_data3.h>
#include <kiri_math/particle/particle_system_solver2.h>
#include <kiri_math/particle/particle_system_solver3.h>
#include <kiri_math/sph/pci_sph_solver2.h>
#include <kiri_math/sph/pci_sph_solver3.h>
#include <kiri_math/pde.h>
#include <kiri_math/anime/physics_animation.h>
// #include <kiri_math/pic_solver2.h>
// #include <kiri_math/pic_solver3.h>
#include <kiri_math/model/plane2.h>
#include <kiri_math/model/plane3.h>
#include <kiri_math/math/point.h>
#include <kiri_math/math/point2.h>
#include <kiri_math/math/point3.h>
#include <kiri_math/math/point_generator2.h>
#include <kiri_math/math/point_generator3.h>
#include <kiri_math/search/point_hash_grid_searcher2.h>
#include <kiri_math/search/point_hash_grid_searcher3.h>
#include <kiri_math/search/point_kdtree_searcher2.h>
#include <kiri_math/search/point_kdtree_searcher3.h>
#include <kiri_math/search/point_neighbor_searcher2.h>
#include <kiri_math/search/point_neighbor_searcher3.h>
#include <kiri_math/search/point_parallel_hash_grid_searcher2.h>
#include <kiri_math/search/point_parallel_hash_grid_searcher3.h>
// #include <kiri_math/particle/point_particle_emitter2.h>
// #include <kiri_math/particle/point_particle_emitter3.h>
#include <kiri_math/search/point_simple_list_searcher2.h>
#include <kiri_math/search/point_simple_list_searcher3.h>
#include <kiri_math/p2surf/points_to_implicit2.h>
#include <kiri_math/p2surf/points_to_implicit3.h>
// #include <kiri_math/quadtree.h>
#include <kiri_math/math/quaternion.h>
#include <kiri_math/physics/ray.h>
#include <kiri_math/physics/ray2.h>
#include <kiri_math/physics/ray3.h>
#include <kiri_math/physics/rigid_body_collider2.h>
#include <kiri_math/physics/rigid_body_collider3.h>
#include <kiri_math/math/samplers.h>
#include <kiri_math/math/scalar_field2.h>
#include <kiri_math/math/scalar_field3.h>
#include <kiri_math/math/scalar_grid2.h>
#include <kiri_math/math/scalar_grid3.h>
// #include <kiri_math/semi_lagrangian2.h>
// #include <kiri_math/semi_lagrangian3.h>
#include <kiri_math/serial.h>
#include <kiri_math/serialization.h>
#include <kiri_math/math/size.h>
#include <kiri_math/math/size2.h>
#include <kiri_math/math/size3.h>
#include <kiri_math/sph/sph_kernels2.h>
#include <kiri_math/sph/sph_kernels3.h>
#include <kiri_math/p2surf/sph_points_to_implicit2.h>
#include <kiri_math/p2surf/sph_points_to_implicit3.h>
#include <kiri_math/sph/sph_solver2.h>
#include <kiri_math/sph/sph_solver3.h>
#include <kiri_math/sph/sph_system_data2.h>
#include <kiri_math/sph/sph_system_data3.h>
#include <kiri_math/model/sphere2.h>
#include <kiri_math/model/sphere3.h>
#include <kiri_math/p2surf/spherical_points_to_implicit2.h>
#include <kiri_math/p2surf/spherical_points_to_implicit3.h>
#include <kiri_math/physics/surface2.h>
#include <kiri_math/physics/surface3.h>
// #include <kiri_math/physics/surface_set2.h>
// #include <kiri_math/physics/surface_set3.h>
#include <kiri_math/physics/surface_to_implicit2.h>
#include <kiri_math/physics/surface_to_implicit3.h>
// #include <kiri_math/svd.h>
#include <kiri_math/timer.h>
#include <kiri_math/physics/transform2.h>
#include <kiri_math/physics/transform3.h>
#include <kiri_math/math/triangle3.h>
#include <kiri_math/math/triangle_mesh3.h>
// #include <kiri_math/triangle_mesh_to_sdf.h>
#include <kiri_math/math/triangle_point_generator.h>
#include <kiri_math/type_helpers.h>
// #include <kiri_math/upwind_level_set_solver2.h>
// #include <kiri_math/upwind_level_set_solver3.h>
#include <kiri_math/math/vector.h>
#include <kiri_math/math/vector2.h>
#include <kiri_math/math/vector3.h>
#include <kiri_math/math/vector4.h>
#include <kiri_math/math/vector_expression.h>
#include <kiri_math/math/vector_field2.h>
#include <kiri_math/math/vector_field3.h>
#include <kiri_math/math/vector_grid2.h>
#include <kiri_math/math/vector_grid3.h>
#include <kiri_math/math/vector_n.h>
#include <kiri_math/math/vertex_centered_scalar_grid2.h>
#include <kiri_math/math/vertex_centered_scalar_grid3.h>
#include <kiri_math/math/vertex_centered_vector_grid2.h>
#include <kiri_math/math/vertex_centered_vector_grid3.h>
// #include <kiri_math/volume_grid_emitter2.h>
// #include <kiri_math/volume_grid_emitter3.h>
#include <kiri_math/particle/volume_particle_emitter2.h>
#include <kiri_math/particle/volume_particle_emitter3.h>
// #include <kiri_math/zhu_bridson_points_to_implicit2.h>
// #include <kiri_math/zhu_bridson_points_to_implicit3.h>
#endif // _KIRI_MATH_H_
