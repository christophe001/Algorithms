#ifndef _MEM_SHARED_PTR_
#define _MEM_SHARED_PTR_

namespace memory {

	template <class _Type>
	class UniquePtr;
	template <class _Type>
	class SharedPtr;
	template <class _Type>
	class WeakPtr;

	class _Base_Ref_Count {
	private:
		unsigned long m_cnt;
		unsigned long m_weaks;
		virtual void _destroy() noexcept = 0;
		virtual void _delete_this() noexcept = 0;
	protected:
		_Base_Ref_Count() 
			: m_cnt(1), m_weaks(1) {}
	public:
		virtual ~_Base_Ref_Count() {}
		bool _add_ref() {}
		bool _dec_ref() {}

	};

	template <class _Type>
	class _Base_Ptr {
	private:
		_Type *m_ptr;

		template <class _Ty2>
		friend class _Base_Ptr;

	public:
		typedef _Type	element_type;
		typedef _Base_Ptr<_Type>	_Myt;

		constexpr _Base_Ptr() noexcept
		:{}


	};
}

#endif // !_MEM_SHARED_PTR_

