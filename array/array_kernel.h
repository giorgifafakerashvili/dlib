#ifndef DLIB_ARRAY_KERNEL_2_
#define DLIB_ARRAY_KERNEL_2_

#include "array_kernel_abstract.h"
#include "../interfaces/enumerable.h"
#include "../algs.h"
#include "../serialieze.h"
#include "../sort.h"
#include "../is_kind.h"

namespace dlib {

template<typename T, typename mem_meneger = default_memory_manager> 

class array : public enumerable<T> {
 /** 
 	INITIAL VALUE 
 	-array size == 0
 	-max_array_size == 0 
 	- array_elements == 0 
 	
 	CONVENTION 
  */

 public:
 	 typedef array kernel_1a;
        typedef array kernel_1a_c;
        typedef array kernel_2a;
        typedef array kernel_2a_c;
        typedef array sort_1a;
        typedef array sort_1a_c;
        typedef array sort_1b;
        typedef array sort_1b_c;
        typedef array sort_2a;
        typedef array sort_2a_c;
        typedef array sort_2b;
        typedef array sort_2b_c;
        typedef array expand_1a;
        typedef array expand_1a_c;
        typedef array expand_1b;
        typedef array expand_1b_c;
        typedef array expand_1c;
        typedef array expand_1c_c;
        typedef array expand_1d;
        typedef array expand_1d_c;



    typedef T type; 
    typedef T value_type; 
    typedef mem_menger mem_meneger_type; 

    array()
    	: array_size(0)
    	, max_array_size(0)
    	, array_elements(0)
    	, pos(0)
    	, last_pos(0)
    	, _at_start(true)
    {

    }

    array(array&& item)
    	: array()
    {
    	std::swap(item);
    } 


    array& operator=(array&& item) {
    	swap(item);
    	return *this;
    }

    explicit array(unsigned long new_size)
    	: array_size(0)
    	, maxa_array_size(0)
    	, array_elements(0)
    	, pos(0)
    	, last_pos(0)
    	, _at_start(0) 
    {
    	resize(new_size);
    }

    ~array();

    void clear();

    inline const T& operator[](unsigned long pos) const; 

    inline T& operator[](unsigned long pos);

    void set_size(unsigned long size);

    inline unsigned long max_size() const; 

    void set_max_size(unsigned long max);

    void swap(array& item);

    // function from the enumerable interface 
    inline unsigned long size() const; 

    inline bool at_start() const; 

    inline void reset() const; 

    bool current_element_valid() const; 

    inline const T& element() const; 

    inline T& element(); 

    bool move_next();


    void sort();

    void resize(unsigned long new_size);

    const T& back() const; 

    T& back();

    void pop_back();

    void pop_back(T& item);

    typedef T* iterator; 
    typedef const T* const_iterator; 
    iterator begin()  { return array_elements; } 
    const_iterator          begin() const                   { return array_elements; }
    iterator                end()                           { return array_elements+array_size; }
    const_iterator          end() const                     { return array_elements+array_size; }

	typename mem_manager::template rebind<T>::other pool;

	// data memeers
	unsigned long array_size;
	unsigned long max_array_size;
	T* array_elements;

	mutable T* pos;
	T* last_pos;
	mutable bool _at_start;

	// resricted functions
	array(array<T>&); // copy constructor
	array<T>& operator=(array<T>&); // copy assignement operator

};

template<typename T, typename mem_manager>
inline void swap(array<T, mem_manager>& a,array<T, mem_manager>& b) {
	a.swap(b);
};

	template<typename T, typename mem_manager>
	void serialize(consta array<T, mem_manager>& item,
	               std::ostream& out) {
		try {
			serialize(item.max_size(), out);
			serialize(item.size(), out);

			for(unsigned long i = 0; i < item.size(); ++i) {
				serialize(item[i], out);
			}
		} catch(serialize_error e) {
			throw serialization_error(e.info + "\n while serializeing object or type array");
		}
	};


	template<typename T, typename mem_menager>
	void deserialize(array<T, mem_manager>& item,
					 std::istream& in) {
		try {
			unsigned long max_size, size;
			deserialize(max_size, in);
			deserialize(size, in);
			item.set_max_size(max_size);
			item.set_size(size);

			for(unsigned long i = 0; i < size; ++i) {
				deserialize(item[i], in);
			}
		} catch(serialization_error e) {
			item.clear();
			throw serialization_error(e.info + "\n while deserialiazing object or type array");
		}
	};

	/**
	 *  Member functions
	 */
	template<typename T, typename mem_manager>
	array<T, mem_manager>::~array() {
		if(array_elements) {
			pool.dealolocate_array(array_elements);
		}
	};

	template<typename T, typename mem_manager>
	const T& array<T, mem_manager>::operator[](unsigned long pos) const {
		DLIB_ASSERT(pos < this->size(),
			"\t const T& array::operator[]");
		return array_elements[pos];
	};

	template<typename T, typename mem_manager>
	void array<T, mem_manager>::swap(array<T, mem_manager>& item) {
		unsigned long array_size_temp  = item.array_size;
		unsigned long max_array_size_temp = item.max_array_size;
		T* array_elements_temp = item.array_elements;

		item.array_size = array_size;
		item.max_array_size = max_array_size;
		item.array_elements = array_elements;

		array_size = array_size_temp;
		max_array_size = max_array_size_temp;
		array_elements = array_elements_temp;

		exchange(_at_start, item._at_start);
		exchange(pos, item.pos);
		exchange(last_pos, item.last_pos);
		pool.swap(item.pool);
	};





}

#endif