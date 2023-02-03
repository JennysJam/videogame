#ifndef GAME_INCLUDE_ENGINE_OPTION_H
#define GAME_INCLUDE_ENGINE_OPTION_H

namespace engine {

class None;

template<typename T>
class Option final {
public:
    Option() noexcept;
    Option(None) noexcept;

    ~Option() noexcept;

    Option(const Option&);
    Option& operator=(Option&) &;
    Option(Option&&);
    Option& operator=(Option&&) &;

    Option(const T&);
    Option& operator=(const T&);
    Option(T&&);
    Option& operator=(T&&);

    auto unwrap() -> T;
    auto unwrap_or(T fallback) -> T;

    T& operator*() &;
    const T& operator*() const&;

    T&& operator*() &&;
    const T&& operator*() const&&;

    T* operator->();

    bool has_value();
    operator bool() noexcept;
private:
    T* ptr;
    char backing[sizeof(T)];
};

template<typename T>
auto Some(T) -> Option<T>;

class None final {};

} // end namespace game

#endif