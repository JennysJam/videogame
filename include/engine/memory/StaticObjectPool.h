#ifndef GAME_INCLUDE_ENGINE_MEMORY_STATICOBJECTPOOL_H
#define GAME_INCLUDE_ENGINE_MEMORY_STATICOBJECTPOOL_H

#include <SDL_assert.h>

#include <exception>
#include <new>
#include <memory>
#include <cstddef>
#include <iterator>

namespace engine {
namespace memory {

// forward declares

class StaticObjectPoolIterGaurd final{};

template<typename T, std::size_t N, std::size_t A> class StaticObjectPoolIter;

/// @brief Fixed size pool allocator for provided type.
/// @tparam T the type the object pool stores 
/// @tparam N The number of objects in the pool
/// @tparam A Alignment of objects (default to alignof(T))
template<typename T, std::size_t N, std::size_t A = alignof(T)>
class StaticObjectPool final {
public:

    // iterator types

    StaticObjectPool() noexcept;
    ~StaticObjectPool() noexcept;

    auto reset() -> void;
    auto allocate() -> T*;
    auto deallocate(T* ptr) -> void;
    auto begin() -> StaticObjectPoolIter<T, N, A>;
    auto end() -> StaticObjectPoolIterGaurd;

private:
    union Node {
        Node() noexcept: next(nullptr) {};
        ~Node() noexcept {};
        T data;
        Node* next;
    };
    bool active_index[N];
    Node* next_free;
    Node node_array[N];
}; // end class StaticObjectPool



/// @brief Class that provides iteration over a StaticObjectPool
/// @tparam T Type of StaticObjectPool
/// @tparam N Size of object pool
/// @tparam A Alignment of object in allocator pool
template<typename T, std::size_t N, std::size_t A=alignof(T)> 
class StaticObjectPoolIter final {
public:

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;

    // TODO: const version of iterator stuff

    StaticObjectPoolIter(StaticObjectPool<T,N,A>& object_pool) noexcept;

    auto operator*() -> reference;
    auto operator->() -> pointer; 
    auto operator++() -> StaticObjectPoolIter<T,N,A>&;
    auto operator++(int)-> StaticObjectPoolIter<T,N,A>&;

    friend bool operator==(const StaticObjectPoolIter& lhs, const StaticObjectPoolIterGaurd& rhs) noexcept;
    friend bool operator!=(const StaticObjectPoolIter& lhs, const StaticObjectPoolIterGaurd& rhs) noexcept;

private:
    void move_next();

    size_t index;
    StaticObjectPool<T,N,A>* object_pool;
}; // end class StaticObjectPoolIter


// StaticObjectPool's implementation

/// @brief Default constructor initializes all members 
template<typename T, std::size_t N, std::size_t A>
StaticObjectPool<T, N, A>::StaticObjectPool() noexcept {
        for (size_t i = 0; i < N; i++) {
        active_index[i] = false;
        node_array[i].next = node_array + i + 1;
    }
    next_free = node_array;
    node_array[N - 1].next == nullptr;

}

/// @brief Destructor calls destructors on each active object
template<typename T, std::size_t N, std::size_t A>
StaticObjectPool<T, N, A>::~StaticObjectPool() noexcept {
    for (size_t i = 0; i < N; i++) {
        if (active_index[i]) {
            node_array[i].data.~T();
        }
    }
} 

/// @brief Reset the object pool and call each child's destructors. 
/// @return 
template<typename T, std::size_t N, std::size_t A>
auto StaticObjectPool<T, N, A>::reset() -> void {
    for (size_t i = 0; i < N; i++) {
        if (active_index[i]) {
            node_array[i].data.~T();
            node_array[i].next = node_array + i + 1;
        }
        next_free = node_array;
        node_array[N - 1].next == nullptr;

    }
}

/// @brief Allocate memory for a new T to be allocated by placement new
/// @return A poitner to a non initialized instance of T (from inside of a union)
template<typename T, std::size_t N, std::size_t A>
auto StaticObjectPool<T, N, A>::allocate() -> T* {
    if (next_free == nullptr) {
        throw std::bad_alloc();
    }

    Node* result_node = next_free;
    size_t index = (node_array - result_node) / sizeof(Node);
    active_index[index] = true;

    next_free = next_free->next;
    return &(result_node->data);
}


/// @brief Free ptr from node and call destructor
template<typename T, std::size_t N, std::size_t A>
auto StaticObjectPool<T, N, A>::deallocate(T* ptr) -> void {
    // cast ptr to
    Node* nodeptr = reinterpret_cast<Node*>(ptr); 
    // get index of node array
    size_t index = (node_array - nodeptr) / sizeof(Node);

    // perform destructor
    nodeptr->~T();
    
    // next, add element to free list and free `active` ptr
    Node* old_free = next_free;
    nodeptr->next = old_free;
    next_free = nodeptr;
    active_index[index] = false;
}



// static object pool iterator implementation

template<typename T, std::size_t N, std::size_t A>
StaticObjectPoolIter<T,N,A>::StaticObjectPoolIter(StaticObjectPool<T,N,A>& object_pool) noexcept {
    this->object_pool = std::addressof(object_pool);
}

} //end namespace memory
} //end namespace engine

#endif