#ifndef GAME_INCLIUDE_ENGINE_SCRIPT_RESULT_H
#define GAME_INCLIUDE_ENGINE_SCRIPT_RESULT_H

#include <engine/script/VM.h>
#include <lua.hpp>

namespace engine {
namespace script {

template<typename T>
class Result {
public:
    
private:
    bool _is_valid;
    union {
        // todo?
        
    };
};

}
}


#endif