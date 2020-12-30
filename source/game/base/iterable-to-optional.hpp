#pragma once

#include <optional>

namespace game::base {
    class ToOptionalRangeConverter {
        public:
            friend auto
            operator|(
                auto&&                   range,
                ToOptionalRangeConverter
            ) {
                using WrappedType = std::decay_t<decltype(*range.begin())>;

                for (auto&& value: range) {
                    return std::make_optional(value);
                }

                return std::optional<WrappedType>(std::nullopt);
            }
    };

    ToOptionalRangeConverter
    toOptional();
}
