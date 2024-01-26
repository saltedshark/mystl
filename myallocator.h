//myallocator接口
#ifndef _MYALLOCATOR_
#define _MYALLOCATOR_

#ifndef _NEW_
#define _NEW_
#include <new> 			//for placement new
#endif
#include <cstddef>		//for ptrdiff_t, size_t
#include <iostream>		//for cerr
#include <cstdlib>		//for exit
#include <climits>		//for UINT_MAX
template <typename T>
class allocator {
public:
	//类型定义
	typedef T				value_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	
	//rebind
	template <typename U>
	struct rebind {
		typedef allocator<U> other;
	};
	//构造函数相关
	allocator();						//default contor
	allocator(const allocator&);		//copy contor
	template <class U> allocator(const allocator<U>&);//泛化的copy contor
	~allocator();

	//普通接口
	pointer address(reference x) const;
	const_pointer address(const_reference x) const;
	size_type max_size() const;
	//内存分配释放
	pointer allocate(size_type n);
	void deallocate(pointer p);
	//构造与析构
	void construct(pointer p, const T& x);
	void destroy(pointer p);


};

//末尾包含实现文件
#include "allocator.cpp"

#endif
