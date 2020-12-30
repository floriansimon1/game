#pragma once

#include <type_traits>

namespace game::base {
    template <typename... Tail>
    struct ParameterPackTypeUnicityStruct;

    template <typename Head>
    struct ParameterPackTypeUnicityStruct<Head> {
        static constexpr bool value = true;   
    };

    template <typename Head, typename Second, typename... Tail>
    struct ParameterPackTypeUnicityStruct<Head, Second, Tail ...> {
        static constexpr bool value = (
            ParameterPackTypeUnicityStruct<Head, Second>::value
            && ParameterPackTypeUnicityStruct<Head, Tail...>::value
            && ParameterPackTypeUnicityStruct<Second, Tail...>::value
        );
    };

    template <class Head, class Second>
    struct ParameterPackTypeUnicityStruct<Head, Second> {
        static constexpr bool value = !std::is_same_v<Head, Second>;
    };

    template <typename... Types>
    concept ParameterPackTypeUnicity = ParameterPackTypeUnicityStruct<Types...>::value;
}
