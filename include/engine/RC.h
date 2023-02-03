#ifndef GAME_INCLUDE_ENGINE_RC_H
#define GAME_INCLUDE_ENGINE_RC_H


#include <SDL_assert.h>
#include <type_traits>
#include <cstdint>
#include <util>

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

template<typename T>
class RC final {
public:
    static_assert(
        std::is_base_of<RefCounted<T>, T>::value, 
        "type paramter of typename T must implement mixin RefCounted"
    );

    RC() noexcept = default;
    ~RC() noexcept;

    RC(const RC& copee);
    RC& operator=(const RC& copee);
    RC(RC&& movee);
    RC& operator=(RC&& movee);

    RC(T* ptr);
    RC& operator=(T* ptr);
    RC(const T* cptr);
    RC& operator=(const T* cptr);

    T* operator->();
    const T* operator->() const;

    T& operator*();
    const T& operator*() const;

    bool has_valid() const;
    operator bool() const;

private:
    mutable T* _ptr;
}; // end class RC<T>

} // end namesapce engine

#endif