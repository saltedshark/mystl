//myallocator实现
/* 这里的实现分为两种，第一种是简单实现，第二种是模仿stl的实现，分为3部分，对象构造、析构，内存分配、销毁，相关uninitialized算法*/
//先使用简单实现
//用的是全局函数形式实现内存的分配与销毁，对象的构造与析构，直接使用全局的new和delete
//这也是SGI 标准的空间配置器的实现方法，但效率不佳

//一些全局函数
template <typename T>
inline T* _allocate(ptrdiff_t size, T*) {
//用于分配内存
	set_new_handle(0);
	T* tmp = (T*) (::operator new((size_t)(size * sizeof(T))));
	if (tmp == 0) {
		std::cerr << "out of memory" << std::endl;
		exit(1);
	}
	return tmp;
}

template <typename T>
inline void _deallocate(T* buff) {
//用于销毁内存
	::operator delete(buffer);
}

template <typename T1, typename T2>
inline void _construct(T1 *p, const T2& value) {
//从已分配好的内存p处开始构造对象
	new(p) T1(value);
}

template <typename T>
inline void _destroy(T* ptr) {
//析构
	ptr -> ~T();
}

//接着使用这些全局函数实现allocator类成员函数
//注意返回值若使用类内数据类型需要使用关键词typename
//声明allocate<T>::后就相当于进入了类内
template <typename T>
typename allocator<T>::pointer 
allocator<T>::allocate(size_type n) {
	return _allocate((difference_type) n, (pointer) 0);
}

template <typename T>
void allocator<T>::deallocate(pointer p) {
	_deallocate(p);
}

template <typename T>
void allocator<T>::construct(pointer p, const T& value) {
	_construct(p, value);	
}

template <typename T>
void allocator<T>::destroy(pointer p) {
	_destroy(p);
}

template <typename T>
typename allocator<T>::pointer 
allocate<T>::address(reference x) const {
	return (pointer) &x;
}

template <typename T>
typename allocator<T>::const_pointer 
allocate<T>::address(const_reference x) const {
	return (allocator<T>::const_pointer) &x;
}

template <typename T>
typename allocator<T>::size_type 
max_size() const {
	return size_type(UINT_MAX/sizeof(T));
}


//模仿stl的实现，将实现分为3个部分放到不同文件内,分别是myallocator_construct.h,myallocator_allocate.h,myallocator_uninitialized.h现


