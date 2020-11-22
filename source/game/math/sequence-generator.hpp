#pragma once

#include <game/base/non-copyable.hpp>

namespace game::math {
    template <typename NumericType>
    class SequenceGenerator: private game::base::NonCopyable {
        private:
            NumericType myNumber = static_cast<NumericType>(0);

        public:
            NumericType next() {
                const auto returnedValue = myNumber;

                myNumber++;

                return returnedValue;
            }
    };
}
