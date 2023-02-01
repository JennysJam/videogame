#include <engine/sample.h>
#include <engine/memory/StaticObjectPool.h>

#include <SDL.h>

#include <cstdio>
#include <string>

static engine::memory::StaticObjectPool<std::string, 16> string_pool{};

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    printf("%d\n", foo());

    for (int i = 0; i < 16; i++) {
        char buffer[256];
        snprintf(buffer, sizeof buffer, "string #%d", i);

        auto* sptr = new(string_pool.allocate()) std::string();
        printf("%s\n", sptr->c_str());

    }

    string_pool.reset();

    auto* s2 = new(string_pool.allocate()) std::string("hello world!");
    printf("%s\n", s2->c_str());

    return 0;
}