#ifndef GAME_INCLUDE_SCRIPT_VM_H
#define GAME_INCLUDE_SCRIPT_VM_H

#include "lua.hpp"

namespace engine {
namespace script {

// forward declare

class Script;

class VM final {
    public:
        VM() noexcept = default;
        ~VM();

        void init_default();
        auto dump_buffer(const char* buf, size_t len) -> Script; // TODO: option type?

        void load_from_script(Script& script);
        void load_from_file(const char* filepath);

        void run();

    private:
        lua_State* _state_ptr;
};



}
}

#endif