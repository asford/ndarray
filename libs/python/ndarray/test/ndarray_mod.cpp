#include <boost/python/ndarray.hpp>
#include <boost/python/ndarray/eigen.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

static boost::mt19937 engine;
static boost::uniform_int<> random_int(2, 5);

template <typename T, int N, int C>
ndarray::Array<T,N,C> makeArray(ndarray::Vector<int,N> const & shape) {
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(shape);
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        flat[n] = n;
    }
    return a;
}

template <int N>
ndarray::Vector<int,N> makeShape() {
    ndarray::Vector<int,N> shape;
    for (int n=0; n<N; ++n) {
        shape[n] = random_int(engine);
    }
    return shape;
}

template <typename T, int N, int C>
ndarray::Array<T,N,C> returnArray() {
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(makeShape<N>());
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        flat[n] = n;
    }
    return a;
}

template <typename T, int N, int C>
bool acceptArray(ndarray::Array<T,N,C> const & p) {
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(p.getShape());
    a.deep() = p;
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        if (flat[n] != n) return false;
    }
    return true;
}

template <typename T, int N, int C>
bool extractArray(boost::python::object const & obj) {
    ndarray::Array<T,N,C> p = boost::python::extract< ndarray::Array<T,N,C> >(obj);
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(p.getShape());
    a.deep() = p;
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        if (flat[n] != n) return false;
    }
    return true;
}

template <typename T, int N>
ndarray::Vector<T,N> returnVector() {
    ndarray::Vector<T,N> r;
    for (int n=0; n<N; ++n) {
        r[n] = n;
    }
    return r;
}

template <typename T, int N>
bool acceptVector(ndarray::Vector<T,N> const & p) {
    for (int n=0; n<N; ++n) {
        if (p[n] != T(n)) return false;
    }
    return true;
}

template <typename T, int N>
bool extractVector(boost::python::object const & obj) {
    ndarray::Vector<T,N> p = boost::python::extract< ndarray::Vector<T,N> >(obj);
    for (int n=0; n<N; ++n) {
        if (p[n] != T(n)) return false;
    }
    return true;
}

template <typename T, int N, int C>
ndarray::EigenView<T,N,C> returnEigenView() {
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(makeShape<N>());
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        flat[n] = n;
    }
    return ndarray::EigenView<T,N,C>(a);
}

template <typename T, int N, int C>
ndarray::TransposedEigenView<T,N,C> returnTransposedEigenView() {
    ndarray::Array<typename boost::remove_const<T>::type,N,N> a = ndarray::allocate(makeShape<N>());
    ndarray::Array<typename boost::remove_const<T>::type,1,1> flat = ndarray::flatten<1>(a);
    for (int n=0; n < flat.template getSize<0>(); ++n) {
        flat[n] = n;
    }
    return ndarray::TransposedEigenView<T,N,C>(a);
}

BOOST_PYTHON_MODULE(ndarray_mod) {
    boost::python::numpy::initialize();
    boost::python::def("makeArray_d33", makeArray<double,3,3>);
    boost::python::def("returnArray_d11", returnArray<double,1,1>);
    boost::python::def("returnArray_d10", returnArray<double,1,0>);
    boost::python::def("returnArray_d22", returnArray<double,2,2>);
    boost::python::def("returnArray_d21", returnArray<double,2,1>);
    boost::python::def("returnArray_d20", returnArray<double,2,0>);
    boost::python::def("returnArray_d33", returnArray<double,3,3>);
    boost::python::def("returnArray_d32", returnArray<double,3,2>);
    boost::python::def("returnArray_d31", returnArray<double,3,1>);
    boost::python::def("returnArray_d30", returnArray<double,3,0>);
    boost::python::def("returnArray_dc11", returnArray<double const,1,1>);
    boost::python::def("returnArray_dc10", returnArray<double const,1,0>);
    boost::python::def("returnArray_dc22", returnArray<double const,2,2>);
    boost::python::def("returnArray_dc21", returnArray<double const,2,1>);
    boost::python::def("returnArray_dc20", returnArray<double const,2,0>);
    boost::python::def("returnArray_dc33", returnArray<double const,3,3>);
    boost::python::def("returnArray_dc32", returnArray<double const,3,2>);
    boost::python::def("returnArray_dc31", returnArray<double const,3,1>);
    boost::python::def("returnArray_dc30", returnArray<double const,3,0>);
    boost::python::def("acceptArray_d11", acceptArray<double,1,1>);
    boost::python::def("acceptArray_d10", acceptArray<double,1,0>);
    boost::python::def("acceptArray_d22", acceptArray<double,2,2>);
    boost::python::def("acceptArray_d21", acceptArray<double,2,1>);
    boost::python::def("acceptArray_d20", acceptArray<double,2,0>);
    boost::python::def("acceptArray_d33", acceptArray<double,3,3>);
    boost::python::def("acceptArray_d32", acceptArray<double,3,2>);
    boost::python::def("acceptArray_d31", acceptArray<double,3,1>);
    boost::python::def("acceptArray_d30", acceptArray<double,3,0>);
    boost::python::def("acceptArray_dc11", acceptArray<double const,1,1>);
    boost::python::def("acceptArray_dc10", acceptArray<double const,1,0>);
    boost::python::def("acceptArray_dc22", acceptArray<double const,2,2>);
    boost::python::def("acceptArray_dc21", acceptArray<double const,2,1>);
    boost::python::def("acceptArray_dc20", acceptArray<double const,2,0>);
    boost::python::def("acceptArray_dc33", acceptArray<double const,3,3>);
    boost::python::def("acceptArray_dc32", acceptArray<double const,3,2>);
    boost::python::def("acceptArray_dc31", acceptArray<double const,3,1>);
    boost::python::def("acceptArray_dc30", acceptArray<double const,3,0>);
    boost::python::def("extractArray_d11", extractArray<double,1,1>);
    boost::python::def("extractArray_d10", extractArray<double,1,0>);
    boost::python::def("extractArray_d22", extractArray<double,2,2>);
    boost::python::def("extractArray_d21", extractArray<double,2,1>);
    boost::python::def("extractArray_d20", extractArray<double,2,0>);
    boost::python::def("extractArray_d33", extractArray<double,3,3>);
    boost::python::def("extractArray_d32", extractArray<double,3,2>);
    boost::python::def("extractArray_d31", extractArray<double,3,1>);
    boost::python::def("extractArray_d30", extractArray<double,3,0>);
    boost::python::def("extractArray_dc11", extractArray<double const,1,1>);
    boost::python::def("extractArray_dc10", extractArray<double const,1,0>);
    boost::python::def("extractArray_dc22", extractArray<double const,2,2>);
    boost::python::def("extractArray_dc21", extractArray<double const,2,1>);
    boost::python::def("extractArray_dc20", extractArray<double const,2,0>);
    boost::python::def("extractArray_dc33", extractArray<double const,3,3>);
    boost::python::def("extractArray_dc32", extractArray<double const,3,2>);
    boost::python::def("extractArray_dc31", extractArray<double const,3,1>);
    boost::python::def("extractArray_dc30", extractArray<double const,3,0>);
    boost::python::def("returnVector_d3", returnVector<double,3>);
    boost::python::def("returnVector_d2", returnVector<double,2>);
    boost::python::def("acceptVector_d3", acceptVector<double,3>);
    boost::python::def("acceptVector_d2", acceptVector<double,2>);
    boost::python::def("extractVector_d3", extractVector<double,3>);
    boost::python::def("extractVector_d2", extractVector<double,2>);
    boost::python::def("returnEigenView_d22", returnEigenView<double,2,2>);
    boost::python::def("returnEigenView_d21", returnEigenView<double,2,1>);
    boost::python::def("returnEigenView_d20", returnEigenView<double,2,0>);
    boost::python::def("returnEigenView_d11", returnEigenView<double,1,1>);
    boost::python::def("returnEigenView_d10", returnEigenView<double,1,0>);
    boost::python::def("returnEigenView_dc22", returnEigenView<double const,2,2>);
    boost::python::def("returnEigenView_dc21", returnEigenView<double const,2,1>);
    boost::python::def("returnEigenView_dc20", returnEigenView<double const,2,0>);
    boost::python::def("returnEigenView_dc11", returnEigenView<double const,1,1>);
    boost::python::def("returnEigenView_dc10", returnEigenView<double const,1,0>);
    boost::python::def("returnTransposedEigenView_d22", returnTransposedEigenView<double,2,2>);
    boost::python::def("returnTransposedEigenView_d21", returnTransposedEigenView<double,2,1>);
    boost::python::def("returnTransposedEigenView_d20", returnTransposedEigenView<double,2,0>);
    boost::python::def("returnTransposedEigenView_d11", returnTransposedEigenView<double,1,1>);
    boost::python::def("returnTransposedEigenView_d10", returnTransposedEigenView<double,1,0>);
    boost::python::def("returnTransposedEigenView_dc22", returnTransposedEigenView<double const,2,2>);
    boost::python::def("returnTransposedEigenView_dc21", returnTransposedEigenView<double const,2,1>);
    boost::python::def("returnTransposedEigenView_dc20", returnTransposedEigenView<double const,2,0>);
    boost::python::def("returnTransposedEigenView_dc11", returnTransposedEigenView<double const,1,1>);
    boost::python::def("returnTransposedEigenView_dc10", returnTransposedEigenView<double const,1,0>);
}
