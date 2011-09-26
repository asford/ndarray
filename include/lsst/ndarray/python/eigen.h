// -*- lsst-c++ -*-
/* 
 * LSST Data Management System
 * Copyright 2008, 2009, 2010 LSST Corporation.
 * 
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the LSST License Statement and 
 * the GNU General Public License along with this program.  If not, 
 * see <http://www.lsstcorp.org/LegalNotices/>.
 */

#ifndef LSST_NDARRAY_PYTHON_eigen_hpp_INCLUDED
#define LSST_NDARRAY_PYTHON_eigen_hpp_INCLUDED

/**
 *  @file lsst/ndarray/python/eigen.hpp
 *  @brief Python C-API conversions for Eigen matrices.
 *
 *  \note This file is not included by the main "lsst/ndarray/python.h" header file.
 */

#include "lsst/ndarray/python.h"
#include "lsst/ndarray/eigen.h"

namespace lsst { namespace ndarray {

/**
 *  @ingroup PythonGroup
 *  @brief Specialization of PyConverter for EigenView.
 */
template <typename T, int N, int C, typename XprKind_, int Rows_, int Cols_>
struct PyConverter< EigenView<T,N,C,XprKind_,Rows_,Cols_> > {
    
    static bool fromPythonStage1(PyPtr & p) {
        // add or remove dimensions with size one so we have the right number of dimensions
        if (PyArray_Check(p)) {
            if ((Rows_ == 1 || Cols_ == 1) && N == 2) {
                npy_intp shape[2] = { -1, -1 };
                if (Rows_ == 1) {
                    shape[0] = 1;
                } else {
                    shape[1] = 1;
                }
                PyArray_Dims dims = { shape, 2 };
                PyPtr r(PyArray_NewShape(reinterpret_cast<PyArrayObject*>(p.get()), &dims));
                if (!r) return false;
                p.swap(r);
            } else if (N == 1) {
                PyPtr r(PyArray_Squeeze(reinterpret_cast<PyArrayObject*>(p.get())));
                if (!r) return false;
                p.swap(r);
            }
        } // else let the Array converter raise the exception
        if (!PyConverter< Array<T,N,C> >::fromPythonStage1(p)) return false;
        // check whether the size is correct if it's static
        if (N == 2) {
            if (Rows_ != Eigen::Dynamic && PyArray_DIM(p.get(), 0) != Rows_) {
                PyErr_SetString(PyExc_ValueError, "incorrect number of rows for matrix");
                return false;
            }
            if (Cols_ != Eigen::Dynamic && PyArray_DIM(p.get(), 1) != Cols_) {
                PyErr_SetString(PyExc_ValueError, "incorrect number of columns for matrix");
                return false;
            }
        } else {
            int requiredSize = Rows_ * Cols_;
            if (requiredSize != Eigen::Dynamic && PyArray_SIZE(p.get()) != requiredSize) {
                PyErr_SetString(PyExc_ValueError, "incorrect number of elements for vector");
                return false;
            }
        }
    }

    static bool fromPythonStage2(
        PyPtr const & input,
        EigenView<T,N,C,XprKind_,Rows_,Cols_> & output
    ) {
        Array<T,N,C> array;
        if (!PyConverter< Array<T,N,C> >::fromPythonStage2(input, array)) return false;
        output.reset(array);
        return true;
    }

    static PyObject * toPython(EigenView<T,N,C> const & m, PyObject * owner=NULL) {
        PyPtr r(PyConverter< Array<T,N,C> >::toPython(m.shallow(), owner));
        if (!r) return r;
        PyPtr p(PyArray_Squeeze(reinterpret_cast<PyArrayObject*>(r.get())));
        return p;
    }
        
    )
};

namespace detail {

/**
 *  @internal @ingroup PythonInternalGroup
 *  @brief Implementations for PyConverter for Eigen objects.
 */
template <typename Matrix>
class EigenPyConverter : public detail::PyConverterBase<Matrix> {
    typedef typename SelectEigenView<Matrix>::Type View;
public:

    static PyObject * toPython(Matrix const & input, PyObject * owner = NULL) {
        return PyConverter<View>::toPython(ndarray::copy(input, owner));
    }

    static PyTypeObject const * getPyType() {
        return reinterpret_cast<PyTypeObject*>(getNumpyMatrixType().get());
    }

    static bool fromPythonStage1(PyPtr & p) {
        return PyConverter<View>::fromPythonStage1(p);
    }

    static bool fromPythonStage2(PyPtr const & p, Matrix & output) {
        View v;
        if (!PyConverter<View>::fromPythonStage2(p, v)) return false;
        output = v;
        return true;
    }

};

} // namespace detail

/**
 *  @ingroup PythonGroup
 *  @brief Specialization of PyConverter for Eigen::Matrix.
 */
template <typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
struct PyConverter< Eigen::Matrix<Scalar,Rows,Cols,Options,MaxRows,MaxCols> >
    : public detail::EigenPyConverter< Eigen::Matrix<Scalar,Rows,Cols,Options,MaxRows,MaxCols> > 
{};

/**
 *  @ingroup PythonGroup
 *  @brief Specialization of PyConverter for Eigen::Array.
 */
template <typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
struct PyConverter< Eigen::Array<Scalar,Rows,Cols,Options,MaxRows,MaxCols> >
    : public detail::EigenPyConverter< Eigen::Array<Scalar,Rows,Cols,Options,MaxRows,MaxCols> > 
{};

}} // namespace lsst::ndarray

#endif // !LSST_NDARRAY_PYTHON_eigen_hpp_INCLUDED
