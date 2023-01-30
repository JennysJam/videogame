#ifndef GAME_INCLUDE_ENGINE_MEMORY_STATICOBJECTPOOL_H
#define GAME_INCLUDE_ENGINE_MEMORY_STATICOBJECTPOOL_H

#include <SDL_assert.h>

#include <cstddef>
#include <iterator>

namespace game {

class StaticObjectPoolIterGaurd final{};

template<typename T, std::size_t N, std::size_t A=alignof(T)> class StaticObjectPoolIter;

/// @brief Fixed size pool allocator for provided type.
/// @tparam T the type the object pool stores 
/// @tparam N The number of objects in the pool
/// @tparam A Alignment of objects (default to alignof(T))
template<typename T, std::size_t N, std::size_t A = alignof(T)>
class StaticObjectPool final {
public:

    // iterator types

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;

    StaticObjectPool() noexcept = default;
    ~StaticObjectPool() noexcept;

    auto init() -> void;
    auto clear() -> void;
    auto allocate() -> void*;
    auto deallocate(T* ptr) -> void*;
    auto begin() -> StaticObjectPoolIter<T, N, A>;
    auto end() -> StaticObjectPoolIterGaurd;

private:
    Node* first_node_address();
    Node* last_node_address();
    Node* pointer_to_node(T* ptr);

    union Node {
        Node() noexcept: next(nullptr) {};
        ~Node() noexcept {};
        T data;
        Node* next;
    };

    T* pointers[N];
    Node* next_node;
    Node  node_array[N];
};

template<typename T, std::size_t N, std::size_t A>
auto StaticObjectPool<T,N,A>::init() -> void {
    using std::size_t;
    for (size_t n = 0; n < N; n++) {
        this->pointers[n] = nullptr;
        this->node_array[n].next = node_array + n + 1;
    }
    this->node_array[n].next = nullptr;
    this->next_node = nullptr;
}

template<typename T, std::size_t N, std::size_t A>
auto StaticObjectPool<T,N,A>::clear() -> void {
    for (std::size_t n = 0; n < N; n++) {
        if (pointers[n] != nullptr) 
            pointers[n]->~T();
    }
    this->init();
}

}
#endif