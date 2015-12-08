#-------------------------------------------------
#
# Project created by QtCreator 2015-11-28T22:45:22
#
#-------------------------------------------------

QT       += core gui opengl concurrent
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Haporres
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    Mesh/mesh.cpp \
    Mesh/meshglbuffercreator.cpp \
    Mesh/meshloader.cpp \
    Utils/utils.cpp \
    Viewer3D/camera.cpp \
    Viewer3D/glwrap.cpp \
    Settings/settings.cpp \
    Viewer3D/meshviewer.cpp \
    Utils/bbox.cpp

HEADERS  += mainwindow.h \
    libs/glm/common.hpp \
    libs/glm/exponential.hpp \
    libs/glm/ext.hpp \
    libs/glm/fwd.hpp \
    libs/glm/geometric.hpp \
    libs/glm/glm.hpp \
    libs/glm/integer.hpp \
    libs/glm/mat2x2.hpp \
    libs/glm/mat2x3.hpp \
    libs/glm/mat2x4.hpp \
    libs/glm/mat3x2.hpp \
    libs/glm/mat3x3.hpp \
    libs/glm/mat3x4.hpp \
    libs/glm/mat4x2.hpp \
    libs/glm/mat4x3.hpp \
    libs/glm/mat4x4.hpp \
    libs/glm/matrix.hpp \
    libs/glm/packing.hpp \
    libs/glm/trigonometric.hpp \
    libs/glm/vec2.hpp \
    libs/glm/vec3.hpp \
    libs/glm/vec4.hpp \
    libs/glm/vector_relational.hpp \
    libs/glm/detail/_features.hpp \
    libs/glm/detail/_fixes.hpp \
    libs/glm/detail/_noise.hpp \
    libs/glm/detail/_swizzle.hpp \
    libs/glm/detail/_swizzle_func.hpp \
    libs/glm/detail/_vectorize.hpp \
    libs/glm/detail/func_common.hpp \
    libs/glm/detail/func_exponential.hpp \
    libs/glm/detail/func_geometric.hpp \
    libs/glm/detail/func_integer.hpp \
    libs/glm/detail/func_matrix.hpp \
    libs/glm/detail/func_noise.hpp \
    libs/glm/detail/func_packing.hpp \
    libs/glm/detail/func_trigonometric.hpp \
    libs/glm/detail/func_vector_relational.hpp \
    libs/glm/detail/intrinsic_common.hpp \
    libs/glm/detail/intrinsic_exponential.hpp \
    libs/glm/detail/intrinsic_geometric.hpp \
    libs/glm/detail/intrinsic_integer.hpp \
    libs/glm/detail/intrinsic_matrix.hpp \
    libs/glm/detail/intrinsic_trigonometric.hpp \
    libs/glm/detail/intrinsic_vector_relational.hpp \
    libs/glm/detail/precision.hpp \
    libs/glm/detail/setup.hpp \
    libs/glm/detail/type_float.hpp \
    libs/glm/detail/type_gentype.hpp \
    libs/glm/detail/type_half.hpp \
    libs/glm/detail/type_int.hpp \
    libs/glm/detail/type_mat.hpp \
    libs/glm/detail/type_mat2x2.hpp \
    libs/glm/detail/type_mat2x3.hpp \
    libs/glm/detail/type_mat2x4.hpp \
    libs/glm/detail/type_mat3x2.hpp \
    libs/glm/detail/type_mat3x3.hpp \
    libs/glm/detail/type_mat3x4.hpp \
    libs/glm/detail/type_mat4x2.hpp \
    libs/glm/detail/type_mat4x3.hpp \
    libs/glm/detail/type_mat4x4.hpp \
    libs/glm/detail/type_vec.hpp \
    libs/glm/detail/type_vec1.hpp \
    libs/glm/detail/type_vec2.hpp \
    libs/glm/detail/type_vec3.hpp \
    libs/glm/detail/type_vec4.hpp \
    libs/glm/gtc/bitfield.hpp \
    libs/glm/gtc/constants.hpp \
    libs/glm/gtc/epsilon.hpp \
    libs/glm/gtc/integer.hpp \
    libs/glm/gtc/matrix_access.hpp \
    libs/glm/gtc/matrix_integer.hpp \
    libs/glm/gtc/matrix_inverse.hpp \
    libs/glm/gtc/matrix_transform.hpp \
    libs/glm/gtc/noise.hpp \
    libs/glm/gtc/packing.hpp \
    libs/glm/gtc/quaternion.hpp \
    libs/glm/gtc/random.hpp \
    libs/glm/gtc/reciprocal.hpp \
    libs/glm/gtc/round.hpp \
    libs/glm/gtc/type_precision.hpp \
    libs/glm/gtc/type_ptr.hpp \
    libs/glm/gtc/ulp.hpp \
    libs/glm/gtc/vec1.hpp \
    libs/glm/gtx/associated_min_max.hpp \
    libs/glm/gtx/bit.hpp \
    libs/glm/gtx/closest_point.hpp \
    libs/glm/gtx/color_space.hpp \
    libs/glm/gtx/color_space_YCoCg.hpp \
    libs/glm/gtx/common.hpp \
    libs/glm/gtx/compatibility.hpp \
    libs/glm/gtx/component_wise.hpp \
    libs/glm/gtx/dual_quaternion.hpp \
    libs/glm/gtx/euler_angles.hpp \
    libs/glm/gtx/extend.hpp \
    libs/glm/gtx/extented_min_max.hpp \
    libs/glm/gtx/fast_exponential.hpp \
    libs/glm/gtx/fast_square_root.hpp \
    libs/glm/gtx/fast_trigonometry.hpp \
    libs/glm/gtx/gradient_paint.hpp \
    libs/glm/gtx/handed_coordinate_space.hpp \
    libs/glm/gtx/integer.hpp \
    libs/glm/gtx/intersect.hpp \
    libs/glm/gtx/io.hpp \
    libs/glm/gtx/log_base.hpp \
    libs/glm/gtx/matrix_cross_product.hpp \
    libs/glm/gtx/matrix_decompose.hpp \
    libs/glm/gtx/matrix_interpolation.hpp \
    libs/glm/gtx/matrix_major_storage.hpp \
    libs/glm/gtx/matrix_operation.hpp \
    libs/glm/gtx/matrix_query.hpp \
    libs/glm/gtx/matrix_transform_2d.hpp \
    libs/glm/gtx/mixed_product.hpp \
    libs/glm/gtx/multiple.hpp \
    libs/glm/gtx/norm.hpp \
    libs/glm/gtx/normal.hpp \
    libs/glm/gtx/normalize_dot.hpp \
    libs/glm/gtx/number_precision.hpp \
    libs/glm/gtx/optimum_pow.hpp \
    libs/glm/gtx/orthonormalize.hpp \
    libs/glm/gtx/perpendicular.hpp \
    libs/glm/gtx/polar_coordinates.hpp \
    libs/glm/gtx/projection.hpp \
    libs/glm/gtx/quaternion.hpp \
    libs/glm/gtx/range.hpp \
    libs/glm/gtx/raw_data.hpp \
    libs/glm/gtx/rotate_normalized_axis.hpp \
    libs/glm/gtx/rotate_vector.hpp \
    libs/glm/gtx/scalar_multiplication.hpp \
    libs/glm/gtx/scalar_relational.hpp \
    libs/glm/gtx/simd_mat4.hpp \
    libs/glm/gtx/simd_quat.hpp \
    libs/glm/gtx/simd_vec4.hpp \
    libs/glm/gtx/spline.hpp \
    libs/glm/gtx/std_based_type.hpp \
    libs/glm/gtx/string_cast.hpp \
    libs/glm/gtx/transform.hpp \
    libs/glm/gtx/transform2.hpp \
    libs/glm/gtx/type_aligned.hpp \
    libs/glm/gtx/vector_angle.hpp \
    libs/glm/gtx/vector_query.hpp \
    libs/glm/gtx/wrap.hpp \
    Mesh/mesh.h \
    Mesh/meshcommon.h \
    Mesh/meshglbuffercreator.h \
    Mesh/meshloader.h \
    Utils/utils.h \
    Viewer3D/camera.h \
    Viewer3D/glwrap.h \
    Settings/settings.h \
    Viewer3D/meshviewer.h \
    Utils/bbox.h

FORMS    += mainwindow.ui
INCLUDEPATH += libs libs/glm/detail libs/glm/gtc libs/glm/gtx
INCLUDEPATH += mesh mmodel slicer toolpath utils viewer3d settings


RESOURCES += \
    resources.qrc
