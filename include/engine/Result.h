#ifndef GAME_INCLUDE_ENGINE_RESULT_H
#define GAME_INCLUDE_ENGINE_RESULT_H

namespace engine {

template<typename T, typename E>
class Result {
public:
    Result();

    enum State {
        INVALID,
        OK,
        ERROR
    };

    T unwrap();
    
    T& as_ok();
    T&& as_ok() &&;
    
    E& as_err();
    E&& as_err();
    
    State state() noexcept const {
        return _state;
    };
private:
    State _state;
    union {
        std::nullptr_t _invalid;
        T _ok;
        E _error;
    };
};

};

#endif