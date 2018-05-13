#ifndef _NUMERIC_MATRIX_ 
#define _NUMERIC_MATRIX_

#include "num_vector.h"
#pragma warning (disable:4244)

namespace algo {
	template <class _Ty, size_t _Size>
	class NumMatrix {

	private:

		static_assert(std::is_arithmetic<_Ty>::value, "Matrix value type is not arithmetic.");

		static_assert(_Size > 0, "Matrix dimension cannot be zero.");

		NumVector<_Ty, _Size> vec_[_Size];

		static const size_t size_ = _Size;

		template <class _Tp, size_t _Size> friend class NumVector;

		template <class _Tp, size_t _Size> friend class NumMatrix;

	public:

		NumMatrix(const _Ty& a = 0) {
			for (size_t i = 0; i < _Size; i++)
				vec_[i] = NumVector<_Ty, _Size>(a);
		}

		NumMatrix(const std::initializer_list<_Ty>& sl) {
			if (sl.size() != size_ * size_)
				throw m_exception("multiscale::maven", "NumMatrix", "constructor",
					"wrong number of input value arguments", "");
			size_t id = 0;
			for (auto& i : sl) {
				vec_[id / size_][id % size_] = i;
				id++;
			}
		}

		template <class _Tp>
		NumMatrix(const std::initializer_list< NumVector<_Tp, _Size> >& vl) {
			if (vl.size() != size_)
				throw m_exception("multiscale::maven", "NumMatrix", "constructor",
					"wrong number of input vector arguments", "");
			size_t id = 0;
			for (auto& i : vl)
				vec_[id++] = i;
		}

		template <class _Tp>
		NumMatrix(const NumVector<_Ty, _Size>& lv, const NumVector<_Tp, _Size>& rv) {
			for (size_t i = 0; i < _Size; i++)
				for (size_t j = 0; j < _Size; j++)
					vec_[j][i] = lv[i] * rv[j];
		}

		template <class _Tp>
		NumMatrix(const NumMatrix<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] = other.vec_[i];
		}


		template <class _Tp>
		NumMatrix<_Ty, _Size>& operator= (const NumMatrix<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] = other.vec_[i];
			return *this;
		}

		//! Default destructor
		~NumMatrix() {}

		//===============================================================================
		// static, const members
		//===============================================================================
		//! Static unit vector.
		static NumMatrix<_Ty, _Size> identity() {
			NumMatrix<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res.vec_[i] = NumVector<_Ty, _Size>::unit(i);
			return res;
		}

		//! Get size
		const size_t size() const { return size_; }

		//===============================================================================
		//! Member access operator
		//===============================================================================
		NumVector<_Ty, _Size>& operator[] (size_t n) {
			if (n >= _Size)
				throw m_exception("multiscale::maven", "NumMatrix", "operator[]", "index out of bound", "");
			return vec_[n];
		}

		const NumVector<_Ty, _Size>& operator[] (size_t n) const {
			if (n >= _Size)
				throw m_exception("multiscale::maven", "NumMatrix", "operator[]", "index out of bound", "");
			return vec_[n];
		}

		const NumVector<_Ty, _Size> row(size_t n) const {
			if (n >= _Size)
				throw m_exception("multiscale::maven", "NumMatrix", "row", "index out of bound", "");
			NumVector<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res[i] = this->vec_[i][n];
			return res;
		}

		const NumVector<_Ty, _Size> col(size_t n) const {
			if (n >= _Size)
				throw m_exception("multiscale::maven", "NumMatrix", "col", "index out of bound", "");
			return vec_[n];
		}
		//===============================================================================
		//! bool comparison of vectors
		//===============================================================================
		template <class _Tp>
		bool operator== (const NumMatrix<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->vec_[i] != rhs.vec_[i]) return false;
			}
			return true;
		}

		template <class _Tp>
		bool operator!= (const NumMatrix<_Tp, _Size>& rhs) const { return !(*this == rhs); }

		//===============================================================================
		//! Numeric operations
		//===============================================================================

		//-------------------------------------------------------------------------------
		//! operation +
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumMatrix<_Ty, _Size> operator+ (const NumMatrix<_Tp, _Size>& other) const {
			NumMatrix<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res.vec_[i] = this->vec_[i] + other.vec_[i];
			return res;
		}

		template <class _Tp>
		NumMatrix<_Ty, _Size>& operator+= (const NumMatrix<_Tp, _Size>& rhs) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] += rhs.vec_[i];
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! operation -
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumMatrix<_Ty, _Size> operator- (const NumMatrix<_Tp, _Size>& other) const {
			NumMatrix<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res.vec_[i] = this->vec_[i] - other.vec_[i];
			return res;
		}

		template <class _Tp>
		NumMatrix<_Ty, _Size>& operator-= (const NumMatrix<_Tp, _Size>& rhs) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] -= rhs.vec_[i];
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! operation * (with scalar)
		//-------------------------------------------------------------------------------
		NumMatrix<_Ty, _Size> operator* (const _Ty& val) const {
			NumMatrix<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res.vec_[i] = this->vec_[i] * val;
			return res;
		}

		NumMatrix<_Ty, _Size>& operator*= (const _Ty& val) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] *= val;
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! operation / (with scalar)
		//-------------------------------------------------------------------------------
		NumMatrix<_Ty, _Size> operator/ (const _Ty& val) const {
			NumMatrix<_Ty, _Size> res;
			for (size_t i = 0; i < _Size; i++)
				res.vec_[i] = this->vec_[i] / val;
			return res;
		}

		NumMatrix<_Ty, _Size>& operator/= (const _Ty& val) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] /= val;
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! Mul (element wise) with matrix in place
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumMatrix<_Ty, _Size>& mul(const NumMatrix<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] *= other.vec_[i];
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! div (element wise) with matrix in place
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumMatrix<_Ty, _Size>& div(const NumMatrix<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++)
				this->vec_[i] /= other.vec_[i];
			return *this;
		}

		//-------------------------------------------------------------------------------
		//! Linear algebra
		//-------------------------------------------------------------------------------
		const _Ty trace() const {
			_Ty tc = 0;
			for (size_t i = 0; i < _Size; i++)
				tc += this->vec_[i][i];
			return tc;
		}

		const NumMatrix<_Ty, _Size> transpose() const;

		NumMatrix<_Ty, _Size>& make_transpose();


		//-------------------------------------------------------------------------------
		//! Matrix operations * with matrix
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumMatrix<_Ty, _Size> operator* (const NumMatrix<_Tp, _Size>& other) const;

		template <class _Tp>
		NumMatrix<_Ty, _Size>& operator*= (const NumMatrix<_Tp, _Size>& rhs);

		//-------------------------------------------------------------------------------
		//! Matrix operations * with vector
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumVector<_Ty, _Size> operator* (const NumVector<_Tp, _Size>& other) const;

		//-------------------------------------------------------------------------------
		//! External operations
		//-------------------------------------------------------------------------------
		template <class _Ty, size_t _Size, class _Tp>
		friend NumMatrix<_Ty, _Size> operator* (const _Tp& scalar, const NumMatrix<_Ty, _Size>& mat);

		template <class _Ty, size_t _Size, class _Tp>
		friend NumVector<_Ty, _Size> operator* (const NumVector<_Tp, _Size>& vec,
			const NumMatrix<_Ty, _Size>& mat);

		template <class _Ty, size_t _Size>
		friend std::ostream& operator<< (std::ostream& os, const NumMatrix<_Ty, _Size>& mat);
	};


	template<class _Ty, size_t _Size>
	inline const NumMatrix<_Ty, _Size> NumMatrix<_Ty, _Size>::transpose() const {
		NumMatrix<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			for (size_t j = 0; j < _Size; j++)
				res.vec_[i][j] = this->vec_[j][i];
		return res;
	}

	template<class _Ty, size_t _Size>
	inline NumMatrix<_Ty, _Size>& NumMatrix<_Ty, _Size>::make_transpose() {
		for (size_t i = 1; i < _Size; i++) {
			for (size_t j = 0; j < i; j++) {
				_Ty temp = this->vec_[i][j];
				this->vec_[i][j] = this->vec_[j][i];
				this->vec_[j][i] = temp;
			}
		}
		return *this;
	}

	template<class _Ty, size_t _Size> template<class _Tp>
	inline NumMatrix<_Ty, _Size> NumMatrix<_Ty, _Size>::operator*(const NumMatrix<_Tp, _Size>& other) const {
		NumMatrix<_Ty, _Size> lhs = this->transpose(), res;
		for (size_t i = 0; i < _Size; i++)
			for (size_t j = 0; j < _Size; j++)
				res.vec_[j][i] = lhs[i].dot(other[j]);
		return res;
	}

	template<class _Ty, size_t _Size> template<class _Tp>
	inline NumMatrix<_Ty, _Size>& NumMatrix<_Ty, _Size>::operator*=(const NumMatrix<_Tp, _Size>& rhs) {
		NumMatrix<_Ty, _Size> lhs = this->transpose();
		NumMatrix<_Tp, _Size> rh(rhs);
		for (size_t i = 0; i < _Size; i++)
			for (size_t j = 0; j < _Size; j++)
				this->vec_[j][i] = lhs[i].dot(rh[j]);
		return *this;
	}

	template<class _Ty, size_t _Size> template<class _Tp>
	inline NumVector<_Ty, _Size> NumMatrix<_Ty, _Size>::operator*(const NumVector<_Tp, _Size>& other) const {
		NumMatrix<_Ty, _Size> tp = this->transpose();
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res[i] = tp[i].dot(other);
		return res;
	}

	template<class _Ty, size_t _Size, class _Tp>
	inline NumMatrix<_Ty, _Size> operator*(const _Tp & scalar, const NumMatrix<_Ty, _Size>& mat) {
		return mat * scalar;
	}

	template<class _Ty, size_t _Size, class _Tp>
	inline NumVector<_Ty, _Size> operator*(const NumVector<_Tp, _Size>& vec, const NumMatrix<_Ty, _Size>& mat) {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res[i] = vec.dot(mat[i]);
		return res;
	}

	template<class _Ty, size_t _Size>
	std::ostream & operator<<(std::ostream & os, const NumMatrix<_Ty, _Size>& mat)
	{
		os << "[" << _Size << "]: ";
		for (size_t i = 0; i < _Size; i++) {
			os << "\t";
			for (size_t j = 0; j < _Size; j++)
				os << std::setw(6) << mat[j][i] << ",";
			os << "\n";
		}
		os << "\n";
		return os;
	}

}

#endif
