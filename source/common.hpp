#pragma once

#include <concepts>
#include <cstdint>
#include <random>
#include <ranges>

namespace hangman::inline aliases
{
    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;

    using f32 = float;
    using f64 = double;

    namespace sr = std::ranges;
    namespace sv = std::ranges::views;
}

namespace hangman::util
{
    template <typename T>
        requires std::integral<T> or std::floating_point<T>
    T random(T min, T max)
    {
        thread_local static auto rng = std::mt19937{ std::random_device{}() };
        if constexpr (std::integral<T>) {
            auto dist = std::uniform_int_distribution{ min, max };
            return dist(rng);
        } else if (std::floating_point<T>) {
            auto dist = std::uniform_real_distribution{ min, max };
            return dist(rng);
        }
    }
}
