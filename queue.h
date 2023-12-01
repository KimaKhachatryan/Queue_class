namespace my {
template<typename T>
class Queue {
private:
	size_t m_size;
	size_t m_capacity;
	size_t m_index;
	T* m_ptr;

public:

//constructors
	Queue();
	Queue(const my::Queue<T>& obj);
	Queue(my::Queue<T>&& obj);

//destructor
	~Queue();
//my::Queue class methods
//functions for allocating new space
	void allocator(size_t new_capacity = 2);
	void reallocator(size_t new_capacity = 0);
//functions that return information about sizes
	size_t size();
	size_t max_size();
	size_t capacity();	
//inserts element at the end
	void push(T value);
//removes the first element
	void pop();
//access the first element
	T& front();
//access the last element
	T& back();
//checks whether the container is empty
	bool empty(); 
//swaps the contents of 2 objects
	void swap(my::Queue<T>& obj);

//helper functions
	void mover(T* ptr = nullptr);
	void print();

//oerator overloading
	void operator=(const my::Queue<T>& obj);
	void operator=(my::Queue<T>&& obj);
	bool operator==(const my::Queue<T>& obj);
	bool operator!=(const my::Queue<T>& obj);
};

#include "queue.hpp"
}
