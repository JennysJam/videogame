#ifndef GAME_INCLUDE_ENGINE_RC_H
#define GAME_INCLUDE_ENGINE_RC_H


#include <SDL_assert.h>
#include <type_traits>
#include <cstdint>
#include <utility>

namespace engine {

/**
 * @brief Mixin type to implement a refcounted typed pointed to by RC<T>
 * @details To implement this code perform something like this
 * 
 * @code{.cpp}
 * class IntNode: RefCounted<IntNode> {
 *    void refcounted_release() {
 *       delete this;
 *    }
 * }
 * @endcode
 * 
 * @tparam T A type that implements this mixin, must implement void refcounted_release().
 */
template<typename T>
class RefCounted {
public:
    static_assert(
        noexcept(T::refcounted_release()),
        "Type must implement noexcept refcounted_release to appease the linter gods"
        )

    int32_t get_refcount() const noexcept {
        return _refcounted_rc;
    }

    void refcounted_increment() {
        SDL_assert(_refcounted_rc != INT32_MAX);
        _refcounted_rc++;
    }

    void refcounted_decrement() {
        SDL_assert(_refcounted_rc > 0);
        _refcounted_rc--;
        if (_refcounted_rc == 0) {
            downcast()->refcounted_release();
        }
    }

protected:
    // TODO: needs implementation

    mutable int32_t _refcounted_rc;
private:
    T* downcast() noexcept {
        return static_cast<T>(this);
    }
}; // end class RefCounted<T>

/**
 * @brief This type impelements a shared_ptr likereference pointer to a type
 *  that must implement mixin Refcounted<T>.
 * 
 * @details This is a smart pointer that, in lieue of doing memory allocation, expects a value to implement the mixin
 * (via the curiously recursive template pattern) that exposes a function to handle releasing itself. This allows 
 * stuff like an object pool that expects an eventual GC-esque sleep to occur that checks some variable that
 * RefCounted can handle deincrmeneting.
 * Otherwise it should mostly act as shared_ptr does -- you can use it as the value of a conditinal,
 * perform * and -> on it, and so on. SDL Asserts are added to all deref points, so in theory this
 * should be easier to debug and be more explicit.
 * 
 * @tparam T Type to Refc count pointer to
 */
template<typename T>
class RC final {
public:
    static_assert(
        std::is_base_of<RefCounted<T>, T>::value, 
        "type paramter of typename T must implement mixin RefCounted"
    );
    RC() noexcept = default;
    ~RC() noexcept {

    }

    RC(const RC& copee) {
        this->_ptr = copee->_ptr;
        this->_ptr->refcounted_increment();
    }
    RC& operator=(const RC& copee) {
        if (this->_ptr) this->_ptr->recounted_decrement();
        this->_ptr = copee->_ptr;
        this->_ptr->refcounted_increment();
    }

    RC(RC&& movee) noexcept {
        this->_ptr = movee->_ptr;
    }
    // TODO: we don't know if refcounted_decrement() is noexcept
    RC& operator=(RC&& movee) {
        if (this->_ptr) this->_ptr->recounted_decrement();
        this->_ptr = movee._ptr;
    }

    RC(T& ref) {
        this->_ptr = std::addressof(ref);
    }

    T* operator->() noexcept {
        SDL_assert(this->_ptr != nullptr);
        return this->_ptr;
    }
    const T* operator->() const {
        SDL_assert(this->_ptr != nullptr);
        return this->_ptr;
    }

    T& operator*() {
        SDL_assert(this->_ptr != nullptr);
        return *this->_ptr;        
    }
    const T& operator*() const {
        SDL_assert(this->_ptr != nullptr);
        return this->_ptr;
    }

    bool is_valid() const noexcept {
        return this->_ptr != nullptr;
    }
    operator bool() const noexcept {
        return this->_ptr != nullptr;
    }

private:
    mutable T* _ptr;
}; // end class RC<T>

} // end namesapce engine

#endif