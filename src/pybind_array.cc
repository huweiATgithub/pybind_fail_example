#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <vector>
#include <Eigen/Eigen>

namespace py = pybind11;


class ArrayDynamic {
 using Vector =Eigen::VectorXd;

 private:
  Vector data_;

 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ArrayDynamic() = default;
  virtual ~ArrayDynamic() = default;

  explicit ArrayDynamic(size_t dim) { data_.resize(dim); }
  auto data() const -> const Vector& { return data_; }
  auto data() -> Vector& { return data_; }
};


PYBIND11_MODULE(promote, m)
{
    auto math = m.def_submodule("math");
    py::class_<ArrayDynamic>(math, "ArrayDynamic")
        .def(py::init<size_t>(), "Create an array of given size.", py::arg("dim"))
        .def("data", py::overload_cast<>(&ArrayDynamic::data), py::return_value_policy::reference_internal, "internal")
        .def( "set_data",
            [](ArrayDynamic& array,
               const Eigen::VectorXd& data)
            {
                array.data() = data;
            },
            "Set data.");
}
