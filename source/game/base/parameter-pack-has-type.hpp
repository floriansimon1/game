#pragma once

#include <type_traits>

namespace game::base {
    template<typename Type, typename... Types>
    struct ParameterPackHasTypeStruct {
        static constexpr bool value = (std::is_same_v<Type, Types> || ...);
    };

    template <typename Type, typename... Types>
    concept ParameterPackContainingType = ParameterPackHasTypeStruct<Type, Types...>::value;

    template <typename Type, typename... Types>
    concept ParameterPackWithoutType = !ParameterPackContainingType<Type, Types...>;

    template <typename Type, typename... Types>
    constexpr bool parameterPackHasType = ParameterPackHasTypeStruct<Type, Types...>::value;
}
