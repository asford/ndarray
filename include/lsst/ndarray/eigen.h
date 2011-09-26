// -*- lsst-c++ -*-
/* 
 * LSST Data Management System
 * Copyright 2008, 2009, 2010, 2011 LSST Corporation.
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
#ifndef LSST_NDARRAY_eigen_h_INCLUDED
#define LSST_NDARRAY_eigen_h_INCLUDED

/**
 *  @file lsst/ndarray/eigen.h
 *  @brief Eigen matrix objects that present a view into an lsst::ndarray::Array.
 *
 *  \note This file is not included by the main "lsst/ndarray.h" header file.
 */

#include "Eigen/Core"
#include "lsst/ndarray.h"
#include "lsst/ndarray/eigen_fwd.h"

namespace lsst { namespace ndarray {
namespace detail {

template <int Rows>
struct EigenStrideTraits<1,0,Rows,1> {
    enum {
        InnerStride = Eigen::Dynamic,
        OuterStride = Eigen::Dynamic,
        IsVector = 1,
        Flags = Eigen::LinearAccessBit
    };
    static int getInnerStride(Core<1> const & core) { return core.getStride(); }
    static int getOuterStride(Core<1> const & core) { return core.getSize() * core.getStride(); }
    static int getRowStride(Core<1> const & core) { return core.getStride(); }
    static int getColStride(Core<1> const & core) { return core.getSize() * core.getStride(); }
    static int getRows(Core<1> const & core) { return core.getSize(); }
    static int getCols(Core<1> const & core) { return 1; }
};

template <int Cols>
struct EigenStrideTraits<1,0,1,Cols> {
    enum {
        InnerStride = Eigen::Dynamic,
        OuterStride = Eigen::Dynamic,
        IsVector = 1,
        Flags = Eigen::LinearAccessBit | Eigen::RowMajorBit
    };
    static int getInnerStride(Core<1> const & core) { return core.getStride(); }
    static int getOuterStride(Core<1> const & core) { return core.getSize() * core.getStride(); }
    static int getRowStride(Core<1> const & core) { return core.getSize() * core.getStride(); }
    static int getColStride(Core<1> const & core) { return core.getStride(); }
    static int getRows(Core<1> const & core) { return 1; }
    static int getCols(Core<1> const & core) { return core.getSize(); }
};

template <int C>
struct EigenStrideTraits<1,C,1,1> {
    enum {
        InnerStride = Eigen::Dynamic,
        OuterStride = Eigen::Dynamic,
        IsVector = 1,
        Flags = Eigen::LinearAccessBit
    };
    static int getInnerStride(Core<1> const & core) { return core.getStride(); }
    static int getOuterStride(Core<1> const & core) { return core.getStride(); }
    static int getRowStride(Core<1> const & core) { return core.getStride(); }
    static int getColStride(Core<1> const & core) { return core.getStride(); }
    static int getRows(Core<1> const & core) { return 1; }
    static int getCols(Core<1> const & core) { return 1; }
};

template <int C, int Rows>
struct EigenStrideTraits<1,C,Rows,1> {
    enum {
        InnerStride = 1,
        OuterStride = Eigen::Dynamic,
        IsVector = 1,
        Flags = Eigen::LinearAccessBit | Eigen::PacketAccessBit
    };
    static int getInnerStride(Core<1> const & core) { return 1; }
    static int getOuterStride(Core<1> const & core) { return core.getSize(); }
    static int getRowStride(Core<1> const & core) { return 1; }
    static int getColStride(Core<1> const & core) { return core.getSize(); }
    static int getRows(Core<1> const & core) { return core.getSize(); }
    static int getCols(Core<1> const & core) { return 1;} 
};

template <int C, int Cols>
struct EigenStrideTraits<1,C,1,Cols> {
    enum {
        InnerStride = 1,
        OuterStride = Eigen::Dynamic,
        IsVector = 1,
        Flags = Eigen::LinearAccessBit | Eigen::RowMajorBit | Eigen::PacketAccessBit
    };
    static int getInnerStride(Core<1> const & core) { return 1; }
    static int getOuterStride(Core<1> const & core) { return core.getSize(); }
    static int getRowStride(Core<1> const & core) { return core.getSize(); }
    static int getColStride(Core<1> const & core) { return 1; }
    static int getRows(Core<1> const & core) { return 1; }
    static int getCols(Core<1> const & core) { return core.getSize(); }
};

template <int Rows, int Cols>
struct EigenStrideTraits<2,0,Rows,Cols> {
    enum {
        InnerStride = Eigen::Dynamic,
        OuterStride = Eigen::Dynamic,
        IsVector = 0,
        Flags = 0
    };
    static int getInnerStride(Core<2> const & core) { return core.getStride(); }
    static int getOuterStride(Core<1> const & core) { return core.getStride(); }
    static int getRowStride(Core<2> const & core) { return core.getStride(); }
    static int getColStride(Core<1> const & core) { return core.getStride(); }
    static int getRows(Core<2> const & core) { return core.getSize(); }
    static int getCols(Core<1> const & core) { return core.getSize(); }    
};

template <int Rows, int Cols>
struct EigenStrideTraits<2,1,Rows,Cols> {
    enum {
        InnerStride = 1,
        OuterStride = Eigen::Dynamic,
        IsVector = 0,
        Flags = Eigen::RowMajorBit | Eigen::PacketAccessBit
    };
    static int getInnerStride(Core<1> const & core) { return 1; }
    static int getOuterStride(Core<2> const & core) { return core.getStride(); }
    static int getRowStride(Core<2> const & core) { return core.getStride(); }
    static int getColStride(Core<1> const & core) { return 1; }
    static int getRows(Core<2> const & core) { return core.getSize(); }
    static int getCols(Core<1> const & core) { return core.getSize(); }        
};

template <int Rows, int Cols>
struct EigenStrideTraits<2,2,Rows,Cols> : public EigenStrideTraits<2,1,Rows,Cols> {};

template <int Rows, int Cols>
struct EigenStrideTraits<2,-1,Rows,Cols> {
    enum {
        InnerStride = 1,
        OuterStride = Eigen::Dynamic,
        IsVector = 0,
        Flags = Eigen::PacketAccessBit
    };
    static int getInnerStride(Core<2> const & core) { return 1; }
    static int getOuterStride(Core<1> const & core) { return core.getStride(); }
    static int getRowStride(Core<2> const & core) { return 1; }
    static int getColStride(Core<1> const & core) { return core.getStride(); }
    static int getRows(Core<2> const & core) { return core.getSize(); }
    static int getCols(Core<1> const & core) { return core.getSize(); }        
};

template <int Rows, int Cols>
struct EigenStrideTraits<2,-2,Rows,Cols> : public EigenStrideTraits<2,-1,Rows,Cols> {};

} // namespace detail
}} // namespace lsst::ndarray


namespace Eigen {
namespace internal {

template <typename T, int N, int C, typename XprKind_, int Rows, int Cols>
struct traits< lsst::ndarray::EigenView<T,N,C,XprKind_,Rows,Cols> > {
    typedef int Index;
    typedef Dense StorageKind;
    typedef XprKind_ XprKind;
    typedef typename boost::remove_const<T>::type Scalar;
    enum {
        RowsAtCompileTime = Rows,
        ColsAtCompileTime = Cols,
        MaxRowsAtCompileTime = Rows,
        MaxColsAtCompileTime = Cols,
        InnerStrideAtCompileTime = lsst::ndarray::detail::EigenStrideTraits<N,C,Rows,Cols>::InnerStride,
        OuterStrideAtCompileTime = lsst::ndarray::detail::EigenStrideTraits<N,C,Rows,Cols>::OuterStride,
        IsVectorAtCompileTime = lsst::ndarray::detail::EigenStrideTraits<N,C,Rows,Cols>::IsVector,
        Flags = lsst::ndarray::detail::EigenStrideTraits<N,C,Rows,Cols>::Flags
            | Eigen::NestByRefBit | Eigen::DirectAccessBit
            | (boost::is_const<T>::value ? 0 : Eigen::LvalueBit),
        CoeffReadCost = NumTraits<Scalar>::ReadCost
    };
};

} // namespace internal
} // namespace Eigen

namespace lsst { namespace ndarray {

/**
 *  @brief Eigen3 view into an lsst::ndarray::Array.
 *
 *  EigenView provides an Eigen DenseBase-derived object based on an lsst::ndarray::Array internally.
 *  Any one or two dimensional Array can be viewed as an Eigen object.
 *
 *  Assignment to an EigenView is deep, and uses the Eigen assignment operators, but construction
 *  from an lsst::ndarray::Array or ArrayRef is shallow with reference counting.  Block and transpose
 *  operations use the standard Eigen Block and Transpose classes, and do not do reference counting
 *  (in fact, they hold a plain C++ reference to the EigenView, so they should be considered extremely
 *  temporary).
 *
 *  @todo Add reference-counted share and transpose operations that return EigenViews.
 *  
 *  @ingroup EigenGroup
 */
template <typename T, int N, int C, typename XprKind_, int Rows_, int Cols_>
class EigenView
    : public Eigen::internal::dense_xpr_base< EigenView<T,N,C,XprKind_,Rows_,Cols_> >::type 
{
    typedef detail::EigenStrideTraits<N,C,Rows_,Cols_> ST;
    typedef detail::ArrayAccess< Array<T,N,C> > Access;

    void checkDimensions() {
        LSST_NDARRAY_ASSERT( Rows_ == Eigen::Dynamic || Rows_ == rows() );
        LSST_NDARRAY_ASSERT( Cols_ == Eigen::Dynamic || Cols_ == cols() );
    }

public:
    
    typedef typename Eigen::internal::dense_xpr_base< EigenView<T,N,C,XprKind_,Rows_,Cols_> >::type Base;

    EIGEN_DENSE_PUBLIC_INTERFACE(EigenView)

    typedef T * PointerType;

    EigenView() : _array() {}
    
    EigenView(EigenView const & other) : _array(other._array) {}

    explicit EigenView(Array<T,N,C> const & array) : _array(array) { checkDimensions(); }

    explicit EigenView(ArrayRef<T,N,C> const & array) : _array(array) { checkDimensions(); }

    EIGEN_INHERIT_ASSIGNMENT_OPERATORS(EigenView)

    EigenView & operator=(EigenView const & other) {
        // Weird behavior to please SWIG: if we're default-constructed, do shallow assignment;
        // otherwise all assignment is deep.
        if (_array.getData() == 0) {
            _array = other._array;
        } else {
            Base::operator=(other);
        }
        return *this;
    }

    inline Index innerStride() const { return ST::getInnerStride(*Access::getCore(_array)); }
    inline Index outerStride() const { return ST::getOuterStride(*Access::getCore(_array)); }

    inline Index rowStride() const { return ST::getRowStride(*Access::getCore(_array)); }
    inline Index colStride() const { return ST::getColStride(*Access::getCore(_array)); }

    inline Index rows() const { return ST::getRows(*Access::getCore(_array)); }
    inline Index cols() const { return ST::getCols(*Access::getCore(_array)); }

    inline T* data() const { return _array.getData(); }

    inline T* data() { return _array.getData(); }

    inline T& coeff(Index row, Index col) const {
        return _array.getData()[row * rowStride() + col * colStride()];
    }

    inline T& coeff(Index index) const {
        return _array.getData()[index * innerStride()];
    }

    inline T& coeffRef(Index row, Index col) const {
      return _array.getData()[row * rowStride() + col * colStride()];
    }

    inline T& coeffRef(Index row, Index col) {
      return _array.getData()[row * rowStride() + col * colStride()];
    }

    inline T& coeffRef(Index index) const {
        return _array.getData()[index * innerStride()];
    }

    inline T& coeffRef(Index index) {
        return _array.getData()[index * innerStride()];
    }

    template <int LoadMode>
    inline PacketScalar packet(Index row, Index col) const {
        return Eigen::internal::ploadt<PacketScalar, LoadMode>(
            _array.getData() + (col * colStride() + row * rowStride())
        );
    }

    template<int LoadMode>
    inline PacketScalar packet(Index index) const {
        BOOST_STATIC_ASSERT( N == 1 );
        return Eigen::internal::ploadt<PacketScalar, LoadMode>(
            _array.getData() + index * innerStride()
        );
    }

    template<int StoreMode>
    inline void writePacket(Index row, Index col, const PacketScalar& x) {
        BOOST_STATIC_ASSERT( !boost::is_const<T>::value );
        Eigen::internal::pstoret<Scalar, PacketScalar, StoreMode>(
            _array.getData() + (col * colStride() + row * rowStride()), x
        );
    }

    template<int StoreMode>
    inline void writePacket(Index index, const PacketScalar& x) {
        BOOST_STATIC_ASSERT( !boost::is_const<T>::value );
        BOOST_STATIC_ASSERT( N == 1 );
        Eigen::internal::pstoret<Scalar, PacketScalar, StoreMode>(
            _array.getData() + index * innerStride(), x
        );
    }

    Array<T,N,C> const & shallow() const { return _array; }
    ArrayRef<T,N,C> deep() const { return _array.deep(); }

    void reset(Array<T,N,C> const & array) { _array = array; checkDimensions(); }
    void reset(ArrayRef<T,N,C> const & array) { reset(array.shallow()); }

private:
    Array<T,N,C> _array;
};

/// @brief A metafunction that computes the EigenView instantiation that most closely matches an Eigen type.
template <typename T>
struct SelectEigenView {
    typedef Eigen::internal::traits<T> Traits;
    typedef typename Traits::Scalar Scalar;
    typedef typename Traits::XprKind XprKind;
    enum {
        N = 2,
        C = ((Traits::Flags & Eigen::RowMajorBit) ? 2 : -2),
        Rows = Traits::RowsAtCompileTime,
        Cols = Traits::ColsAtCompileTime
    };
    typedef Array<Scalar,N,C> Shallow;
    typedef ArrayRef<Scalar,N,C> Deep;
    typedef EigenView<Scalar,N,C,XprKind,Rows,Cols> Type;
};

/// @brief Copy an arbitrary Eigen expression into a new EigenView.
template <typename T>
inline typename SelectEigenView<T>::Type copy(Eigen::EigenBase<T> const & other) {
    typename SelectEigenView<T>::Type result(
        typename SelectEigenView<T>::Shallow(allocate(other.rows(), other.cols()))
    );
    result = other.derived();
    return result;
}

template <typename Derived>
template <typename XprKind, int Rows, int Cols>
inline EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
                 ArrayBase<Derived>::RMC::value, XprKind, Rows, Cols
                 >
ArrayBase<Derived>::asEigen() const {
    return EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
        ArrayBase<Derived>::RMC::value, XprKind, Rows, Cols>(this->getSelf());
}

template <typename Derived>
template <typename XprKind>
inline EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
                 ArrayBase<Derived>::RMC::value, XprKind>
ArrayBase<Derived>::asEigen() const {
    return EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
        ArrayBase<Derived>::RMC::value, XprKind>(this->getSelf());
}

template <typename Derived>
template <int Rows, int Cols>
inline EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
                 ArrayBase<Derived>::RMC::value, Eigen::MatrixXpr, Rows, Cols>
ArrayBase<Derived>::asEigen() const {
    return EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
        ArrayBase<Derived>::RMC::value, Eigen::MatrixXpr, Rows, Cols>(this->getSelf());
}
    
template <typename Derived>
inline EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
                 ArrayBase<Derived>::RMC::value, Eigen::MatrixXpr>
ArrayBase<Derived>::asEigen() const {
    return EigenView<typename ArrayBase<Derived>::Element, ArrayBase<Derived>::ND::value,
        ArrayBase<Derived>::RMC::value>(this->getSelf());
}

}} // namespace lsst::ndarray

#endif // !LSST_NDARRAY_eigen_h_INCLUDED
