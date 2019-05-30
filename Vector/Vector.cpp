#include "Vector.h"

template<class T, class Alloc>
void Vector<T, Alloc>::insert_aux(Iterator pos, const T& x){
	// 表示还有空位
	if (finish != end){
		construct(finish, *(finish - 1));
		
		++finish;
		T x_copy = x;
		copy_backward(pos, finish - 2, finish - 1);
		*pos = x_copy;
	}
	else{
		const size_type old_size = size();
		/*
			1. 原大小为0，则配置1个元素大小
			2. 原大小不为0，则配置原先2倍大小
		*/
		const size_type len = old_size != 0 ? 2 *old_size : 1;

		Iterator new_start = data_allocator::allocate(len); // 实际配置
		Iterator new_finish = new_start;
		try{
			// 将原先内容拷贝到新vector
			new_finish = uninitialized_copy(start, pos, new_start);
			// 为新元素赋初值
			construct(new_finish, x);
			++new_finish;
			// 为处理插入元素情况，将原位置内容拷贝过来
			new_finish = uninitialized_copy(pos, finish, new_finish);
		}
		catch (...){
			destory(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}

		// 析构并释放原vector
		destory(begin(), end());
		deallocate();

		// 调整迭代器，指向新vector
		start = new_start;
		finish = new_finish;
		end = new_start + len;

	}

}	

template<class T, class Alloc>
void Vector<T, Alloc>::insert(Iterator pos, size_type n, const T& x)
{
	if (n != 0){
		// 备用空间与新增元素个数比较
		if (size_type(last - finish) >= n){
			// 足够使用
			T x_copy = x;
			const size_type elems_after = finish - pos;
			Iterator old_finish = finish;
			
			// 插入元素个数大于现有元素个数
			if (elems_after > n){
				uninitialized_copy(finish - n, finish, finish);
				finish += n;
				copy_backward(pos, old_finish - n, old_finish);
				fill(pos, pos + n, x_copy);
			}
			// 插入元素个数小于现有元素个数
			else{
				uninitialized_copy(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				copy_backward(pos, old_finish, finish);
				fill(pos, pold_finish, x_copy);
			}
		}
		else{
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);

			Iterator new_start = data_allocator::allocate(len);
			Iterator new_finish = new_start;
			__STL__TRY{
				new_finish = uninitialized_copy(start, pos, new_start);
				new_finish = uninitialized_fill_n(new_finish, n, x);
				new_finish = uninitialized_copy(pos, finish, new_finish);
			}
		}
#ifdef __STL_USE_EXCEPTIONS
		catch (...){
			destory(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}
#endif
		destory(start, finish);
		deallocate();
		start = new_start;
		finish = new_finish;
		last = new_start + len;
	}
}
