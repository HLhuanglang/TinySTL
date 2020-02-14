/************************************************************
���ƣ�vector.h
���ã�vector�������洢���ݣ��ṩ����������Ԫ�ص�һЩ����
note:		
		vector��������ķ�ʽ��
		vector<T> v1;
		vector<T> v2(10); //10��Ĭ��T
		vector<T> v3(10,T()); //10��T���͵�ֵ
		vector<T> v4 = v1; //=��ֵ
		vector<T> v5(v2); //����
		
		array<string, 5> words {"one", "two","three", "four", "five"};
		vector<string> v6 {begin(words) , end(words)}; ����һ�Ե��������д���
*************************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include"../fundation/allocator.h"
#include"../fundation/iterator.h"
#include"../fundation/utility.h"
#include"../algorithm/algorithm.h"
namespace TinySTL {
	template<typename T, typename Alloc = allocator<T>>
	class vector {
	public:
		//���Ͳ���������ֱ��ʹ�õģ���vector<Test>::pointer A; A ����һ��ָ��
		typedef T						value_type;
		typedef T*					iterator; //vector�ĵ���������ָͨ��
		typedef const T*			const_iterator;
		typedef TinySTL::reverse_iterator<iterator> reverse_iterator;
		typedef TinySTL::reverse_iterator<const iterator> const_reverse_iterator;
		typedef T*					pointer;
		typedef T&					reference;
		typedef const T&		const_reference;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
	private:
		iterator first_;
		iterator last_;
		iterator end_;
		typedef Alloc data_allocator;

	public:
		/********************************************************************************/
		//�����졢�������
		vector();
		explicit vector(const size_type n);
		vector(const size_type n, const value_type& value);
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last);

		vector(const vector& v);
		vector(vector &&v);
		vector &operator=(const vector &v);
		vector &operator=(vector&& v);
		~vector();
		/********************************************************************************/
		//���������
		iterator begin() { return first_; }
		iterator end() { return last_; }
		const_iterator begin() const { return first_; }
		const_iterator end() const { return last_; }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		const_iterator cbegin() const { return begin(); }
		const_iterator cend() const { return end(); }
		const_reverse_iterator crbegin() const { return rbegin(); }
		const_reverse_iterator crend() const { return rend(); }
		/********************************************************************************/
		//Ԫ�ط������
		reference operator[](const difference_type i) { return *(first_ + i); }
		const_reference operator[](const difference_type i)const { return *(first_ + i); }
		reference front() { return *(first_); }
		reference back() { return *(last_ - 1); }
		reference at(); //TO DO
		/********************************************************************************/
		//�������
		difference_type size() const { return last_ - first_; }
		difference_type capacity() const { return end_ - first_; }
		bool empty() { return first_ == last_; }
		void resize(size_type n, value_type val = value_type()); //����������С
		void reserve(size_type n); //Ԥ���ռ��С����n>capacity()ʱ�����·���
		void shrink_to_fit(); //��������
		/********************************************************************************/
		//�޸�����Ԫ�����
		void clear();
		void swap(vector &v);
		void push_back(const value_type& val);
		void pop_back();
		iterator insert(iterator position, const value_type& val); //��positionλ��ǰ����һ��Ԫ��
		void insert(iterator position, size_type n, const value_type& val); //��position֮ǰ������n��Ԫ��

		//����Χ[first��last��֮�ڵ�һ��Ԫ�ز���position
		//�ú����빹�캯��һ������first��last����int���͵Ļ����ǻ�ƥ�䵽�����Ǹ�������
		template<typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		/********************************************************************************/
		//�Ƚϲ���
		bool operator==(const vector &v) const;
		bool operator!=(const vector &v) const;
		/********************************************************************************/
		//�����Ŀռ����������
		Alloc get_allocator() { return data_allocator; }
	private:
		/********************************************************************************/
		//helper functions
				//ֻ�ܰѸ������е����ݸ��Ƶ��������ڴ����λ�ã��������е�󡣡���������һ����������Ŀ�ĵ�
		void allocate_and_fill_n(const size_type n, const value_type& value);
		template<typename InputIterator>
		void allocate_and_copy(InputIterator first, InputIterator last);

		void destory_and_deallocate();
		template<typename Integer>
		void vector_aux(Integer n, Integer value, __true_type);
		template<typename InputIterator>
		void vector_aux(InputIterator first, InputIterator last, __false_type);

		void insert_aux(iterator position, size_type n, const value_type& val, __true_type);
		template<typename InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, __false_type);

		void reallocate_and_fill_n(iterator position, size_type n, const value_type&val);
		template<typename InputIterator>
		void reallocate_and_copy(iterator position, InputIterator first, InputIterator last);
		size_type get_newsize(size_type n);
	}; //end of class vector

	/********************************************************************************/
	//helper functions
	template<typename T, typename Alloc>
	void vector<T, Alloc>::allocate_and_fill_n(const size_type n, const value_type& value) {
		first_ = data_allocator::allocate(n);
		uninitialized_fill_n(first_, n, value);
		last_ = end_ = first_ + n;
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last) {
		this->first_ = data_allocator::allocate(last - first); //�Լ����һ�� (last-first)/sizeof(InputIterator),��ָ������Զ����ȥ���͵�λ
		uninitialized_copy(first, last, this->first_);
		this->last_ = this->end_ =this->first_ + (last - first);
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::destory_and_deallocate() {
		if (capacity() != 0) {
			data_allocator::destory(first_, last_);
			data_allocator::deallocate(first_, capacity());
		}
	}

	template<typename T, typename Alloc>
	template<typename Integer>
	void vector<T, Alloc>::vector_aux(Integer n, Integer value, __true_type) {
		allocate_and_fill_n(n, value); 
	}
	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, __false_type) {
		allocate_and_copy(first, last);
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::insert_aux(iterator position, size_type n, const value_type &val, __true_type) {
		assert(n != 0);
		difference_type locationLeft =end_ - last_; // the size of left storage
		difference_type locationNeed = n;

		if (locationLeft >= locationNeed) {
			auto tempPtr = end() - 1;
			for (; tempPtr - position >= 0; --tempPtr) {//move the [position, finish_) back
				//*(tempPtr + locationNeed) = *tempPtr;//bug
				construct(tempPtr + locationNeed, *tempPtr);
			}
			TinySTL::uninitialized_fill_n(position, n, val);
			last_ += locationNeed;
		}
		else {
			reallocate_and_fill_n(position, n, val);
		}
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, __false_type) {
		difference_type locationLeft = end_ - last_; // the size of left storage
		difference_type locationNeed = std::distance(first, last);

		if (locationLeft >= locationNeed) {
			if (last_ - position > locationNeed) {
				TinySTL::uninitialized_copy(last_ - locationNeed, last_, last_);
				std::copy_backward(position, last_ - locationNeed, last_);
				std::copy(first, last, position);
			}
			else {
				iterator temp = TinySTL::uninitialized_copy(first + (last_ - position), last, last_);
				TinySTL::uninitialized_copy(position, last_, temp);
				std::copy(first, first + (last_ - position), position);
			}
			last_ += locationNeed;
		}
		else {
			reallocate_and_copy(position, first, last);
		}
	}


	template<typename T, typename Alloc>
	void vector<T, Alloc>::reallocate_and_fill_n(iterator position, size_type n, const value_type&val) {
		difference_type new_size = get_newsize(n);
		
		T* new_first_ = data_allocator::allocate(new_size);
		T* new_end_ = new_first_ + new_size;
		T* new_last_ = TinySTL::uninitialized_copy(begin(), position, new_first_);
		new_last_ = TinySTL::uninitialized_fill_n(new_last_, n, val);
		new_last_ = TinySTL::uninitialized_copy(position, end(), new_last_);

		destory_and_deallocate();
		first_ = new_first_;
		last_ = new_last_;
		end_ = new_end_;
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::reallocate_and_copy(iterator position, InputIterator first, InputIterator last) {
		
		difference_type need_size = last - first;
		size_type new_size = get_newsize(need_size);

		T* new_first_ = data_allocator::allocate(new_size);
		T* new_end_ = new_first_ + new_size;
		T* new_last_ = TinySTL::uninitialized_copy(begin(), position, new_first_);
		new_last_ = TinySTL::uninitialized_copy(first, last, new_first_);
		new_last_ = TinySTL::uninitialized_copy(position, end(), new_last_);

		destory_and_deallocate();
		first_ = new_first_;
		last_ = new_last_;
		end_ = new_end_;
	}

	template<typename T, typename Alloc>
	typename vector<T,Alloc>::size_type vector<T, Alloc>::get_newsize(size_type n) {
		//���push_back��insert �����ײ���
		//push_back (ÿ�ζ�ֻ����һ��Ԫ��,���Բ���ʱ���������������2*capacity())
		if (capacity() != 0) {
			if (n == 1)
				return (2 * capacity());
			else
				return (capacity() + 2 * n);
		}
		return n;
	}
	/********************************************************************************/
	//���졢���������ƵȺ���ʵ��
	template<typename T, typename Alloc>
	vector<T, Alloc>::~vector() {
		data_allocator::destory(first_, last_);
		data_allocator::deallocate(first_, end_ - first_);
	}
	template<typename T, typename Alloc>
	vector<T, Alloc>::vector() {
		first_ = data_allocator::allocate();
		last_ = end_ = first_;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const size_type n) {
		allocate_and_fill_n(n, value_type());
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type &value) {
		//�����Ƕ���vector<T>ʱ�����TֻӰ��value_type, size_type��T �޹أ����Ǹ�size_t
		allocate_and_fill_n(n, value);
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last) {
		typedef typename __is_integer<InputIterator>::is_integer INTEGER;
		vector_aux(first, last, INTEGER());
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector& v) {
		//copy���죬���
		allocate_and_copy(v.begin(), v.end());
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(vector&&v) {
		//��ֵ���ã�v��һ����ʱ����
		first_ = v.first_;
		last_ = v.last_;
		end_ = v.end_;
		v.first_ = v.last_ = v.end_ = nullptr;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>	&vector<T, Alloc>::operator=(const vector& v) {
		if (this != v) {
			allocate_and_copy(v.first_, v.last_);
		}
		return *this;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(vector&&v) {
		if (this != v)
			allocate_and_copy(v.first_, v.first_);
		v.first_ = v.last_ = v.end_ = nullptr;
	}
	/********************************************************************************/
	//Ԫ�ط���
	/*
	����ʵ��Ҫд�Ĳ�������̫���ˣ����Է������ڲ�ʵ����
	*/
	
	/********************************************************************************/
	//�������
	template<typename T, typename Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val){
		if (n < size()) {
			data_allocator::destory(first_ + n, last_);
			last_ = first_ + n;
		}
		else if (n > size() && n < capacity()) {
			auto insert_length = n - size();
			last_ = TinySTL::uninitialized_fill_n(last_, insert_length, val);
		}
		else if (n >= capacity()) {
			size_type insert_length = n - size();
			iterator new_first_ = data_allocator::allocate(n);
			iterator new_last_ = TinySTL::uninitialized_copy(begin(), end(), new_first_);
			new_last_ = TinySTL::uninitialized_fill_n(new_last_, insert_length, val);

			destory_and_deallocate(); //���ɵ���Դ�ͷ�
			first_ = new_first_;
			last_ = new_last_;
			end_ = new_first_ + n;
		}
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::reserve(size_type n) {
		if (n > capacity()) {
			iterator new_first_ = data_allocator::allocate(n); //�������ڴ�Ϊ�λ��Ƿ���first_�ĵ�ַ
			iterator new_last_ = TinySTL::uninitialized_copy(begin(), end(), new_first_);

			destory_and_deallocate(); //���ɵ���Դ�ͷ�
			first_ = new_first_;
			last_ = new_last_;
			end_ = new_first_ + n;
		}
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::shrink_to_fit() {
		//����������size()��С
		if (last_ == end_)
			return;
		data_allocator::deallocate(last_, end_ - last_); //����Ҫ��������Ϊlast_ ~ end_�������û�й������
		end_ = last_;
	}

	/********************************************************************************/
	//�޸��������
	template<typename T, typename Alloc>
	void vector<T, Alloc>::clear() {
		data_allocator::destory(first_, last_);
		last_ = first_;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::swap( vector& v) {
		if (*this != v) {
			TinySTL::swap(this->first_, v.first_);
			TinySTL::swap(this->last_, v.last_);
			TinySTL::swap(this->end_, v.end_);
		}
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::push_back(const value_type& val) {
		insert(end(), val);
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::pop_back() {
		//last-ָ�����һ��Ԫ�ص���һ��λ��
		last_--;
		data_allocator::destory(last_);
	}
	
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& val) {
		insert(position, 1, val);
		return position;
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) {
		typedef typename __is_integer<InputIterator>::is_integer IS_INTEGER;
		insert_aux(position, first, last, IS_INTEGER());
	}
	/*
	�������������뺯��˵���ҵ����
	*/
	template<typename T, typename Alloc>
	void vector<T,Alloc>::insert(iterator position, size_type n, const value_type& val){
		typedef typename __is_integer<size_type>::is_integer  IS_INTEGER;
		insert_aux(position, n, val, IS_INTEGER());
	}

	/********************************************************************************/
	//�Ƚϲ���
	template<typename T, typename Alloc>
	bool vector<T, Alloc>::operator==(const vector &v) const {
		if (size() != v.size())
			return false;
		auto self = first_;
		auto other = v.first_;
		for (; self != last_ && other != v.last_; ++self, ++other) {
			if (*self != *other)
				return false;
		}
		return true;
	}

	template<typename T, typename Alloc>
	bool vector<T, Alloc>::operator!=(const vector &v) const {
		return (!(*this == v));
	}

}//namaspace TinySTL
#endif // !VECTOR_H
