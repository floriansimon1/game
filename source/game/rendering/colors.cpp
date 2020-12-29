#include <game/rendering/colors.hpp>

#include <cmath>
#include <cassert>
#include <cstdint>

namespace game::rendering {
    sf::Color
    hsvToRgb(
        const float hue,
        const float saturation,
        const float value
    ) {
        const float  chroma  = value * saturation;

        const float hPrime   = fmod(hue / 60.f, 6.f);
        const float m        = value - chroma;

        const float x        = chroma * (1.f - fabs(fmod(hPrime, 2.f) - 1.f));

        const auto adaptColor = [m] (const float red, const float green, const float blue) -> sf::Color {
            return sf::Color(
                static_cast<uint8_t>((red   + m) * 255.f),
                static_cast<uint8_t>((green + m) * 255.f),
                static_cast<uint8_t>((blue  + m) * 255.f),
                255u
            );
        };

        if (hPrime >= 0.f && hPrime < 1.f) {
            return adaptColor(chroma, x, 0.f);
        }
        
        if (hPrime >= 1.f && hPrime < 2.f) {
            return adaptColor(x, chroma, 0.f);
        }
        
        if (hPrime >= 2.f && hPrime < 3.f) {
            return adaptColor(0.f, chroma, x);
        }
        
        if (hPrime >= 3.f && hPrime < 4.f) {
            return adaptColor(0.f, x, chroma);
        }
        
        if (hPrime >= 4.f && hPrime < 5.f) {
            return adaptColor(chroma, 0.f, x);
        }
        
        if (hPrime >= 5.f && hPrime < 6.f) {
            return adaptColor(x, 0.f, chroma);
        }

        return adaptColor(0.f, 0.f, 0.f);
    }
    
    std::vector<sf::Color>
    getDistinctColorsArray(
        const unsigned numberOfColors
    ) {
        assert(numberOfColors <= 360 * 2);

        std::vector<sf::Color> colors;

        for (unsigned colorIndex = 0; colorIndex < numberOfColors; colorIndex++) {
            const double hue = std::min(360.f, colorIndex * (360.f / numberOfColors));

            colors.emplace_back(hsvToRgb(hue, 1.f, colorIndex >= 360.f ? .5f : 1.f));
        }

        return colors;
    }
}
