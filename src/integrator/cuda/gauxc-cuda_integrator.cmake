add_library( gauxc_device_integrator OBJECT 
  integrator/cuda/collocation/gaueval_kernels.cu
  integrator/cuda/collocation/gaueval_device.cu
  #cuda_integrator/collocation/.cxx
)
target_compile_features( gauxc_device_integrator PUBLIC cuda_std_14 cxx_std_14 )
target_link_libraries( gauxc_device_integrator PUBLIC ExchCXX::exchcxx )

target_include_directories( gauxc_device_integrator
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_compile_options( gauxc_device_integrator 
  PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>: -Wall -Wextra -Wpedantic -Wnon-virtual-dtor>
    $<$<COMPILE_LANGUAGE:CUDA>: -Xcudafe --diag_suppress=partial_override -Xptxas -v > 
)
