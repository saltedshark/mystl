//myallocator接口
//该接口实现参考了cppreference
//具有多种实现的，比如仅c++版本不同的情况，仅实现当前c++11还在用的，前后版本的都暂不考虑
#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <cstddef>		//for ptrdiff_t, size_t
namespace mystl {
template< class T >
class allocator {
public:
	//Member types, 算上rebind，共计10个
	typedef T				value_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	//typedef xxx			propagate_on_container_move_assignment
	//typedef xxx			is_always_equal
	
	//rebind
	template< class U >
	struct rebind {
		typedef allocator<U> other;
	};
	
	//Member functions
	
	//ctor
	//noexcept即noexcept(true)表示不会抛出异常,有利于编译器做优化
	allocator() noexcept;
	allocator( const allocator& other ) noexcept;//从同类型的构建
	template< class U >
	allocator( const allocator<U>& other ) noexcept;//从类型U构建
	
	//dtor
	~allocator();

	//普通接口
	pointer address( reference x ) const noexcept;
	const_pointer address( const_reference x ) const noexcept;
	size_type max_size() const noexcept;
	//内存分配释放
	//hint是用于提供局部性的参数，如果支持该功能，将分配接近于hint值的内存
	pointer allocate( size_type n, const void* hint = 0 );
	void deallocate ( T* p, std::size_t n );

	//构造与析构
	template< class U, class... Args >
	void construct ( U* p, Args&&... args );
	template< class U >
	void destroy( U* p);


};

//Non-member functions
//不着急实现，当前还暂时用不到
/*
operator==
operator!=
*/

}
//末尾包含实现文件,且放到namespace之外，若放到namespace之内那么被包含的文件将成为该namespace的一部分，会引发问题
//若按照传统写法在.cpp内包含.h文件，template相关的类会出链接问题，但反过来包含使用的时候就不会有这样问题
#include "allocator.cpp"
#endif
