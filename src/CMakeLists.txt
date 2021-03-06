# Parallelism
find_package( OpenMP  REQUIRED )
if( GAUXC_ENABLE_MPI )
  message( STATUS "GauXC Enabling MPI" )
  find_package( MPI REQUIRED )
else()
  message( STATUS "GauXC Disabling MPI" )
endif()

# Required Dependencies
include( gauxc-integratorxx )
include( gauxc-exchcxx      )


add_library( gauxc STATIC 
  grid.cxx 
  grid_impl.cxx 
  molmeta.cxx 
  molgrid.cxx 
  molgrid_impl.cxx 
  molgrid_defaults.cxx 
  atomic_radii.cxx 
  load_balancer_impl.cxx 
  load_balancer.cxx 
  replicated_load_balancer.cxx 
)

target_include_directories( gauxc
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

target_compile_options( gauxc
  PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>: -Wall -Wextra -Wpedantic -Wnon-virtual-dtor>
)



configure_file( 
  ${PROJECT_SOURCE_DIR}/include/gauxc/gauxc_config.hpp.in
  ${PROJECT_BINARY_DIR}/include/gauxc/gauxc_config.hpp
)

target_link_libraries( gauxc PUBLIC 
  ExchCXX::ExchCXX 
  IntegratorXX::IntegratorXX 
  OpenMP::OpenMP_CXX
)

if( GAUXC_ENABLE_MPI )
  target_link_libraries( gauxc PUBLIC MPI::MPI_C )
endif()

add_subdirectory( integrator )


add_library( gauxc::gauxc ALIAS gauxc )

include( GNUInstallDirs )

# TARGETS

install( TARGETS gauxc ${GAUXC_EXPORT_DEPENDENCIES}
  EXPORT gauxc-targets 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties( gauxc PROPERTIES EXPORT_NAME gauxc )

# Export build tree
export(EXPORT gauxc-targets
      NAMESPACE gauxc::
      FILE "${PROJECT_BINARY_DIR}/gauxc-targets.cmake")

# Install staic headers
install( 
  DIRECTORY   ${PROJECT_SOURCE_DIR}/include
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  FILES_MATCHING PATTERN "*.hpp"
)

# Install generated headers
install(
  FILES       ${PROJECT_BINARY_DIR}/include/gauxc/gauxc_config.hpp
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gauxc
)
  
   
# Export target to script
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/gauxc )
install( EXPORT gauxc-targets
  FILE         gauxc-targets.cmake
  NAMESPACE    gauxc::
  DESTINATION  ${INSTALL_CONFIGDIR}
)

# Create config-version.cmake file
include( CMakePackageConfigHelpers )
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/gauxc-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)


# Setup gauxc-config.cmake
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/gauxc-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/gauxc-config.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install CMake files
install( FILES
  ${PROJECT_SOURCE_DIR}/cmake/modules/FindMAGMA.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/gauxc-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/gauxc-config-version.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

# Install Custom Find Modules
include( ${linalg-cmake-modules_SOURCE_DIR}/LinAlgModulesMacros.cmake )
install_linalg_modules( INSTALL_CONFIGDIR )
