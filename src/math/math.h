#pragma once

namespace Math {
    // Clamps the value between lower and upper bounds.
    template<class T>
    const T& clamp(const T& value, const T& lower, const T& upper) {
        if(value > upper) return upper;
        else if(value < lower) return lower;
        else return value;
    }
}