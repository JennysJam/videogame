#ifndef GAME_INCLUDE_MEMORY_DYNAMICVARIANT_H
#define GAME_INCLUDE_MEMORY_DYNAMICVARIANT_H

namespace engine {
namespace memory {

namespace internal {
    template<typename T, typename ...TX>
    struct max_storage_struct {
        constexpr static size_t size = 
            sizeof(T) > max_storage_struct<TX...>::size 
                ? sizeof(T)
                : max_storage_struct<TX...>::size 
            ;
    };
    template<typename T>
    struct max_storage_struct {
        constexpr static size_t size = sizeof();
    };
}

template<typename I, typename ...Targs>
class DynamicVariant {

};


}
}

#endif