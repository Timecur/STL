#include <iostream>

template<class T, class Alloc>
class simple_alloc{
public:
	static T *alloc(size_t n){ return 0 = n ? 0 : (T*)Alloc::allocate(n*sizeof(T)); }
	static T *allocate(void){ return (T*)Alloc::allocate(sizeof(T)); }
	static void deallocate(T *p, size_t n){
		if (0 != n)
			Alloc::deallocate(p, n*sizeof(T));
	}
	static void deallocate(T *p){ Alloc::deallocate(p, sizeof(T)); }
};

template<class T, class Alloc = alloc> // alloc是STL空间配置器
class Vector{
public:
	typedef T value_type;
	typedef value_type* point;
	typedef value_type* Iterator; // vector的迭代器是普通指针
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

protected:
	typedef simple_alloc<value_type, Alloc> data_allocator; // simple_alloc空间配置器,以元素大学为分配单位
	Iterator start;  // 表示目前使用空间的头 
	Iterator finish; // 表示目前使用空间的尾
	Iterator last;    // 表示可用空间的尾

	void insert_aux(Iterator pos, const T& x);
	void deallocate(){
		if (start)
			data_allocator::deallocate(start, last - start);
	}

	// 初始化所有可用空间
	void fill_initialize(size_type n, const T& value){
		start = allocate_and_fill(n, value);
		finish = start + n;
		last = finish;
	}

public:
	Vector()
		:start(0)
		, finish(0)
		, last(0)
	{}

	Vector(size_type n, const T& value){ fill_initialize(n, value); }
	Vector(int n, const T& value){ fill_initialize(n, value); }
	Vector(long n, const T& value){ fill_initialize(n, value); }
	explicit Vector(size_type n){ fill_initialize(n, T()); }

	~Vector(){
		destory(start, last);
		deallocate();
	}

	Iterator begin(){ return start; }
	Iterator end(){ return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const { return size_type(last - begin()); }
	bool empty() const { return begin() == end(); }
	reference operator[](size_type n){ return *(begin() + n); }
	reference front(){ return *begin(); }  // 第一个元素
	reference back(){ return *(end() - 1); } // 最后一个元素

	void push(const T& x){
		if (finish != last){
			construct(finish, x);
			++finish;
		}
		else{
			insert_aux(end(), x);
		}
	}

	void pop(){
		--finish;
		destory(finish);
	}

	Iterator erase(Iterator pos){
		if (pos + 1 != end()) // 判断之后是否还有元素
			copy(pos + 1, finish, pos); // 从删除位置后一位开始，每位向前挪一位
		--finish;
		destory(finish);
		return pos;
	}

	void resize(size_type new_size, const T& x = T()){
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - fize(), x);
	}

	void clear(){ erase(begin(), end()); }

	void insert(Iterator pos, size_type n, const T& x);

protected:
	// 配置空间并填满内容
	Iterator allocate_and_fill(size_type n, const T& x){
		Iterator result = data_allocator::allocate(n); // 以元素大小为单位，配置n个元素空间
		uninitialized_fill_n(result, n, x);
		return result;
	}

};
