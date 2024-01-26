#ifndef _MYALLOCATOR_CONSTRUCT_
#define _MYALLOCATOR_CONSTRUCT_

#ifndef _NEW_
#define _NEW_
#include <new>			//for placement new
#endif
//这个头文件内容都是写为全局函数形式
//都是inline函数，就直接实现了

template <typename T1, typename T2>
inline void construct(T1* p, const T2& value) {
	new(p) T1(value);	
}

//两个版本的destroy函数，第一个接受单指针析构单个对象，第二个接受迭代器析构一组对象
template <typename T>
inline void destroy(T* p) {
	p -> ~T();	
}

template <typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
	//接受两个迭代器，然后利用type_traits采用合适方法
	_destroy(first, last, value_type(first));//value_type需要包含头文件吧，不然都看不到?
}

//该函数用于判断当前数值类型是否有trivial destructor
template <typename ForwardIeterator, typename T>
inline void _destroy(ForwardIterator first, ForwardIterator last, T*){
	typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor;
	_destroy_aux(first, last, trivial_destructor());
}

//该函数用于判断当前value_type是否有non-trivial destructor
template <typename ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type) {
	for( ; first < last; ++ first)
		destroy(&(*first));	//调用的是单指针版本
}

//该函数判断当前value_type是否有trivial destructor
template <typename ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _true_type) {}


//针对char*,wchar_t*的就不特化了


#endif
