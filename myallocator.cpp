//myallocator实现
/* 这里的实现分为两种，第一种是简单实现，第二种是模仿stl的实现，分为3部分，对象构造、析构，内存分配、销毁，相关uninitialized算法*/

//先使用简单实现
//用的是全局函数形式实现内存的分配与销毁，对象的构造与析构，直接使用全局的new和delete
//这也是SGI 标准的空间配置器的实现方法，但效率不佳

#include <new> //for placement new
#include <iostream> //for cerr
#include <cstdlib> //for exit
#include <climits>	//for UINT_MAX





