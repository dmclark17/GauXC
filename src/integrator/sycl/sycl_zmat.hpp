#pragma once
#include <SYCL/sycl.hpp>
#include <gauxc/xc_task.hpp>

namespace GauXC      {
namespace integrator {
namespace sycl       {

using namespace GauXC::sycl;

template <typename T>
void zmat_lda_sycl(size_t ntasks, int32_t max_nbf, int32_t max_npts,
                   XCTaskDevice<T> *tasks_device, sycl::queue *stream);

template <typename T>
void zmat_gga_sycl(size_t ntasks, int32_t max_nbf, int32_t max_npts,
                   XCTaskDevice<T> *tasks_device, sycl::queue *stream);
}
}
}
