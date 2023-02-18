#ifndef GAME_INCLUDE_ENGINE_CALLBACK_H
#define GAME_INCLUDE_ENGINE_CALLBACK_H

#include <engine/script/VM.h>

namespace engine {

template<typename R, typename ...TX>
class Callback final {
public:
    using NativeCb = R(*)(TX...);

    enum CB_Type {
        Native,
        Scripted
    };
    
    

    CB_type type() const noexcept {
        return _type;
    }

private:
    CB_Type _type;
    union {
        NativeCB _native;
    }
};

}

#endif