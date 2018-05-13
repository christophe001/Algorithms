

#ifndef _NUMERIC_VECTOR_ 
#define _NUMERIC_VECTOR_

#include <iomanip>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#pragma warning (disable:4244)

namespace algo {
	template <class _Ty, size_t _Size>
	class NumVector {

	private:

		static_assert(std::is_arithmetic<_Ty>::value, "Vector value type is not arithmetic.");

		static_assert(_Size > 0, "Vector dimension cannot be zero.");

		_Ty val_[_Size];

		static const size_t size_ = _Size;

		template <class _Tp, size_t _Size> friend class NumVector;

	public:
		//===============================================================================
		//! All kinds of constructors, and dtor                                                 
		//===============================================================================
		NumVector(const _Ty& val = 0) { for (size_t i = 0; i < _Size; i++) val_[i] = val; }

		NumVector(const std::initializer_list<_Ty>& list) {
			if (list.size() != size_)
				throw std::exception("wrong number of input arguments");
			size_t id = 0;
			for (auto& i : list) val_[id++] = i;
		}

		template <class _Tp>
		NumVector(const NumVector<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++) val_[i] = other.val_[i];
		}

		template <class _Tp>
		NumVector<_Ty, _Size>& operator= (const NumVector<_Tp, _Size>& other) {
			for (size_t i = 0; i < _Size; i++) val_[i] = other.val_[i];
			return *this;
		}

		//! Default destructor
		~NumVector() {}

		//===============================================================================
		// static, const members
		//===============================================================================
		//! Static unit vector.
		static NumVector<_Ty, _Size> unit(size_t n) {
			if (n >= _Size)
				throw std::exception("Vector", "unit", "index out of bound");
			NumVector<_Ty, _Size> res; res[n] = 1;
			return res;
		}

		//! Get size
		const size_t size() const { return size_; }


		//===============================================================================
		//! Member access operator
		//===============================================================================
		_Ty& operator[] (size_t n) {
			if (n >= _Size)
				throw std::exception("index out of bound");
			return val_[n];
		}

		const _Ty& operator[] (size_t n) const {
			if (n >= _Size)
				throw std::exception("index out of bound");
			return val_[n];
		}

		//===============================================================================
		//! bool comparison of vectors
		//===============================================================================
		template <class _Tp>
		bool operator== (const NumVector<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->val_[i] != rhs.val_[i]) return false;
			}
			return true;
		}

		template <class _Tp>
		bool operator!= (const NumVector<_Tp, _Size>& rhs) const { return !(*this == rhs); }

		template <class _Tp>
		bool operator< (const NumVector<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->val_[i] >= rhs.val_[i]) return false;
			}
			return true;
		}

		template <class _Tp>
		bool operator<= (const NumVector<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->val_[i] > rhs.val_[i]) return false;
			}
			return true;
		}

		template <class _Tp>
		bool operator> (const NumVector<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->val_[i] <= rhs.val_[i]) return false;
			}
			return true;
		}

		template <class _Tp>
		bool operator>= (const NumVector<_Tp, _Size>& rhs) const {
			for (size_t i = 0; i < _Size; i++) {
				if (this->val_[i] < rhs.val_[i]) return false;
			}
			return true;
		}

		//===============================================================================
		//! Numeric operations
		//===============================================================================

		//-------------------------------------------------------------------------------
		//! operation +
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumVector<_Ty, _Size> operator+ (const NumVector<_Tp, _Size>& other) const;

		template <class _Tp>
		NumVector<_Ty, _Size>& operator+= (const NumVector<_Tp, _Size>& rhs);

		//-------------------------------------------------------------------------------
		//! operation -
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumVector<_Ty, _Size> operator- (const NumVector<_Tp, _Size>& other) const;

		template <class _Tp>
		NumVector<_Ty, _Size>& operator-= (const NumVector<_Tp, _Size>& rhs);

		//-------------------------------------------------------------------------------
		//! operation * (with scalar)
		//-------------------------------------------------------------------------------
		NumVector<_Ty, _Size> operator* (const _Ty& val) const;

		NumVector<_Ty, _Size>& operator*= (const _Ty& val);

		//-------------------------------------------------------------------------------
		//! operation / (with scalar)
		//-------------------------------------------------------------------------------
		NumVector<_Ty, _Size> operator/ (const _Ty& val) const;

		NumVector<_Ty, _Size>& operator/= (const _Ty& val);

		//-------------------------------------------------------------------------------
		//! operation * (with vector)
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumVector<_Ty, _Size> operator* (const NumVector<_Tp, _Size>& vec) const;

		template <class _Tp>
		NumVector<_Ty, _Size>& operator*= (const NumVector<_Tp, _Size>& rhs);

		//-------------------------------------------------------------------------------
		//! operation / (with vector)
		//-------------------------------------------------------------------------------
		template <class _Tp>
		NumVector<_Ty, _Size> operator/ (const NumVector<_Tp, _Size>& vec) const;

		template <class _Tp>
		NumVector<_Ty, _Size>& operator/= (const NumVector<_Tp, _Size>& rhs);

		//-------------------------------------------------------------------------------
		//! Linear algebra operations
		//-------------------------------------------------------------------------------
		template <class _Tp>
		const _Ty dot(const NumVector<_Tp, _Size>& other) const;

		const double norm() const;

		//===============================================================================
		//! External functions
		//===============================================================================
		template <class _Ty, size_t _Size>
		friend std::ostream& operator<< (std::ostream& os, const NumVector<_Ty, _Size>& vec);

		template <class _Ty, size_t _Size, class _Tp>
		friend NumVector<_Ty, _Size> operator* (const _Tp& scalar, const NumVector<_Ty, _Size>& vec);

		template <class _Ty, size_t _Size, class _Tp>
		friend NumVector<_Ty, _Size> min_val(const NumVector<_Ty, _Size>& fv, const NumVector<_Tp, _Size>& sv);

		template <class _Ty, size_t _Size, class _Tp>
		friend NumVector<_Ty, _Size> max_val(const NumVector<_Ty, _Size>& fv, const NumVector<_Tp, _Size>& sv);

	};

	//===================================================================================
	//! Numerical operations
	//===================================================================================

	//-----------------------------------------------------------------------------------
	//! operator +
	//-----------------------------------------------------------------------------------
	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator+ (const NumVector<_Tp, _Size>& other) const {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] + other.val_[i];
		return res;
	}

	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator+= (const NumVector<_Tp, _Size>& other) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] += other.val_[i];
		return *this;
	}

	//------------------------------------------------------------------------------------
	//! operator -
	//------------------------------------------------------------------------------------
	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator- (const NumVector<_Tp, _Size>& other) const {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] - other.val_[i];
		return res;
	}

	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator-= (const NumVector<_Tp, _Size>& other) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] -= other.val_[i];
		return *this;
	}

	//------------------------------------------------------------------------------------
	//! operator * (scalar)
	//------------------------------------------------------------------------------------
	template<class _Ty, size_t _Size>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator* (const _Ty& val) const {
		NumVector<_Ty, _Size> res;
		for (int i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] * val;
		return res;
	}

	template<class _Ty, size_t _Size>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator*= (const _Ty& val) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] *= val;
		return *this;
	}

	//------------------------------------------------------------------------------------
	//! operator / (scalar)
	//------------------------------------------------------------------------------------
	template <class _Ty, size_t _Size>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator/(const _Ty& val) const {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] / val;
		return res;
	}

	template <class _Ty, size_t _Size>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator/=(const _Ty& val) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] /= val;
		return *this;
	}

	//------------------------------------------------------------------------------------
	//! operator * (vector)
	//------------------------------------------------------------------------------------
	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator* (const NumVector<_Tp, _Size>& other) const {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] * other.val_[i];
		return res;
	}

	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator*= (const NumVector<_Tp, _Size>& other) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] *= other.val_[i];
		return *this;
	}

	//------------------------------------------------------------------------------------
	//! operator / (vector)
	//------------------------------------------------------------------------------------
	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size> NumVector<_Ty, _Size>::operator/ (const NumVector<_Tp, _Size>& other) const {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = this->val_[i] / other.val_[i];
		return res;
	}

	template <class _Ty, size_t _Size> template <class _Tp>
	inline NumVector<_Ty, _Size>& NumVector<_Ty, _Size>::operator/= (const NumVector<_Tp, _Size>& other) {
		for (size_t i = 0; i < _Size; i++)
			this->val_[i] /= other.val_[i];
		return *this;
	}

	//-------------------------------------------------------------------------------
	//! Linear algebra operations
	//-------------------------------------------------------------------------------
	template<class _Ty, size_t _Size> template<class _Tp>
	inline const _Ty NumVector<_Ty, _Size>::dot(const NumVector<_Tp, _Size>& other) const {
		_Ty prod = 0;
		for (size_t i = 0; i < _Size; i++)
			prod += this->val_[i] * other.val_[i];
		return prod;
	}

	template<class _Ty, size_t _Size>
	inline const double NumVector<_Ty, _Size>::norm() const {
		double res = 0.0;
		for (size_t i = 0; i < _Size; i++)
			res += val_[i] * val_[i];
		return sqrt(res);
	}

	//-------------------------------------------------------------------------------
	//! External operations
	//-------------------------------------------------------------------------------
	template<class _Ty, size_t _Size>
	std::ostream & operator << (std::ostream& os, const NumVector<_Ty, _Size>& vec) {
		os << "[" << _Size << "]: " << "(";
		for (size_t i = 0; i < _Size - 1; i++)
			os << vec[i] << ",";
		os << vec[_Size - 1] << ")\n";
		return os;
	}

	template<class _Ty, size_t _Size, class _Tp>
	inline NumVector<_Ty, _Size> min_val(const NumVector<_Ty, _Size>& fv, const NumVector<_Tp, _Size>& sv) {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = fv.val_[i] < sv.val_[i] ? fv.val_[i] : sv.val_[i];
		return res;
	}

	template<class _Ty, size_t _Size, class _Tp>
	inline NumVector<_Ty, _Size> max_val(const NumVector<_Ty, _Size>& fv, const NumVector<_Tp, _Size>& sv) {
		NumVector<_Ty, _Size> res;
		for (size_t i = 0; i < _Size; i++)
			res.val_[i] = fv.val_[i] > sv.val_[i] ? fv.val_[i] : sv.val_[i];
		return res;
	}

	template<class _Ty, size_t _Size, class _Tp>
	inline NumVector<_Ty, _Size> operator*(const _Tp & scalar, const NumVector<_Ty, _Size>& vec) {
		return vec * scalar;
	}
}
#endif // !_M4_NUMERIC_VECTOR_ 


