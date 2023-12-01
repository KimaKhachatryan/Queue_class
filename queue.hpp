//default constructor
template<typename T>
Queue<T>::Queue()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_index = 0;
	this->m_ptr = nullptr;
}
//copy constructor
template<typename T>
Queue<T>::Queue(const my::Queue<T>& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_index = obj.m_index;
		this->m_ptr = new T[obj.m_capacity];

		for (size_t i = 0; i < obj.m_size; ++i) {
			this->m_ptr[i] = obj.m_ptr[i];
		}
	}
} 

//move constructor
template<typename T>
Queue<T>::Queue(my::Queue<T>&& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_index = obj.m_index;
		this->m_ptr = obj.m_ptr;
		obj.m_ptr = nullptr;
	}
}
//destructor
template<typename T>
Queue<T>::~Queue()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_index = 0;

	if (this->m_ptr) {
		delete[] this->m_ptr;
		this->m_ptr = nullptr;
	}
}

//allocator works only when pointer is nullptr
template<typename T>
void Queue<T>::allocator(size_t new_capacity)
{
	if (!this->m_ptr) {
		this->m_ptr = new T[new_capacity];
		this->m_capacity = new_capacity;
	}
}

//reallocator function allocates new space when pointer isn't nullptr
template<typename T>
void Queue<T>::reallocator(size_t new_capacity)
{
	if (new_capacity == 0) {
		this->m_capacity *= 1.5;
	} else {
		this->m_capacity = new_capacity;
	}

	T* tmp_ptr = new T[this->m_capacity];
	this->mover(tmp_ptr);
	

	delete[] this->m_ptr;
	this->m_ptr = tmp_ptr;
	tmp_ptr = nullptr;
}

//functions wich return size and capacity
template<typename T>
size_t Queue<T>::size()
{
	return this->m_size;
}

template <typename T>
size_t Queue<T>::max_size()
{
	return 1073741823;
}

template<typename T>
size_t Queue<T>::capacity()
{
	if (!this->m_ptr) {
		std::cout << "Out of range." << std::endl;
		exit(0);
	}
	return this->m_capacity;
	
}

//inserts the element at the end
template<typename T>
void Queue<T>::push(T value)
{
	if(!this->m_ptr){
		this->allocator();
	} else if(this->m_size + this->m_index + 1 > this->m_capacity) {
		if (this->m_index < this->m_capacity / 2) {
			this->reallocator();
		} else {
			this->mover();
		}
	}

	this->m_ptr[this->m_index + this->m_size] = value;
	++this->m_size;
}

//removes the first element
template<typename T>
void Queue<T>::pop()
{
	if (this->m_size) {
		--this->m_size;
		++this->m_index;
	 } else {
		std::cout << "Out of range." << std::endl;
		exit(0);
	 }
}

//access the first element
template<typename T>
T& Queue<T>::front()
{
	if(this->m_size) {
		return this->m_ptr[this->m_index];
	}else {
		std::cout << "Out of range." << std::endl;
		exit(0);
	}
}

//access the last element
template<typename T>
T& Queue<T>::back()
{
	if(this->m_size) {
		return this->m_ptr[this->m_index + this->m_size - 1];
	} else {
		std::cout << "Out of range." << std::endl;
		exit(0);
	}
}

//checks whether the container is empty
template<typename T>
bool Queue<T>::empty() 
{
	return this->m_size;
}

//swaps the contents of 2 objects
template<typename T>
void Queue<T>::swap(my::Queue<T>& obj) 
{
	std::swap(this->m_size, obj.m_size);
	std::swap(this->m_capacity, obj.m_capacity);
	std::swap(this->m_index, obj.m_index);
	std::swap(this->m_ptr, obj.m_ptr);
}
//helper functions
//
//moves the elements to the beginning
template<typename T>
void Queue<T>::mover(T* ptr)
{
	size_t i = 0;
	size_t j = this->m_index;
	
	if(!ptr) { 
		for(; i < this->m_size; ++i, ++j) {
			this->m_ptr[i] = this->m_ptr[j];
		}
	} else {
		for(; i < this->m_size; ++i, ++j) {
			ptr[i] = this->m_ptr[j];
		}	
	}

	this->m_index = 0;
}
//print the element of queue
template<typename T>
void Queue<T>::print()
{
	for (size_t i = this->m_index; i < this->m_index + this->m_size; ++i) {
		std::cout << this->m_ptr[i] << " ";
	}

	std::cout << std::endl;
}

//operator overloading
//
//assignment operator
template<typename T>
void Queue<T>::operator=(const my::Queue<T>& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		if(this->m_ptr) {
			delete[] this->m_ptr;
		}

		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_index = obj.m_index;
		this->m_ptr = new T[obj.m_capacity];

		for (size_t i = 0; i < obj.m_size; ++i) {
			this->m_ptr[i] = obj.m_ptr[i];
		}
	}
}

template<typename T>
void Queue<T>::operator=(my::Queue<T>&& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		if (this->m_ptr) {
			delete[] this->m_ptr;
		}

		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_index = obj.m_index;
		this->m_ptr = obj.m_ptr;
		obj.m_ptr = nullptr;
	}
}

//operator== return true if 2 object have the same contents
template<typename T>
bool Queue<T>::operator==(const my::Queue<T>& obj)
{
	if (this->m_size != obj.m_size) {
		return false;
	}

	for (size_t i = this->m_index; i < this->m_size + this->m_index; ++i) {
		if (this->m_ptr[i] != obj.m_ptr[i]) {
			return false;
		}
	}

	return true;
}

//operator!= return true if 2 object have not the same contents
template<typename T>
bool Queue<T>::operator!=(const my::Queue<T>& obj)
{
	if (this->m_size != obj.m_size) {
		return true;
	}

	for (size_t i = this->m_index; i < this->m_size + this->m_index; ++i) {
		if (this->m_ptr[i] != obj.m_ptr[i]) {
			return true;
		}
	}

	return false;
}
