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
        auto dump_file();
        
        void load_from_script(Script& script);
        void load_from_file(const char* filepath);
        void load_from_buffer(const char* buffer, size_t len);

        void run();
        void run_script(Script& script);
        void run_file(const char* filepath);
        void run_buffer(const char* buffer, size_t len);

        void close();
                

    private:
        lua_State* _state_ptr;
};



}   // end namespace script
}   // end namespace engine

#endif