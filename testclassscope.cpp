#include <iostream>
using std::cout;
using std::endl;


template <typename T>
class A{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	//使用默认构造、析构等	
	
	//普通接口
	void set_data(const value_type& x);
	value_type get_data() const;
private:
	T data;
};


template<typename T>
typename A<T>::value_type 
//下面的是错误写法，找不到value_type
//value_type A<T>::get_data() const {
A<T>::get_data() const {
	return data;	
}

//A<T>::之后就进入了类内了,名字不用再担心
template <typename T>
void A<T>::set_data(const value_type& x){
	data = x;	
}

int main() {
	cout << "test scope of class A: " << endl;
	A<int> a;
	cout << "set data x = 10" << endl;
	a.set_data(10);
	cout << "data of class A : " << endl;
	int value = a.get_data();
	cout << value << endl;
	return 0;
}
