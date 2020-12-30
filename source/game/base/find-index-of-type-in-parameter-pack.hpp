#pragma once

#include <game/base/parameter-pack-has-type.hpp>

#include <cstddef>
#include <type_traits>

namespace game::base {
    template <typename Type, typename... Tail>
    struct ParameterPackTypeIndexStruct;

    template <typename Type, typename Head, typename... Types>
    requires std::is_same_v<Type, Head>
    struct ParameterPackTypeIndexStruct<Type, Head, Types...> {
        static constexpr bool   exists   = true;
        static constexpr size_t position = 0;
    };

    template <typename Type, typename Head, typename Second, typename... Types>
    requires ParameterPackContainingType<Type, Head, Second, Types...>
    struct ParameterPackTypeIndexStruct<Type, Head, Second, Types...> {
        static constexpr bool   exists   = true;
        static constexpr size_t position = 1 + ParameterPackTypeIndexStruct<Type, Second, Types...>::position;
    };

    template <typename Type, typename... Types>
    constexpr size_t positionOfTypeInParameterPack = ParameterPackTypeIndexStruct<Type, Types...>::position;
}
