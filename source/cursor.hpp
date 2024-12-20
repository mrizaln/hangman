#pragma once

#include "common.hpp"

#include <fmt/core.h>

namespace hangman
{
    struct Cursor
    {
        template <typename... Args>
        const Cursor& print(fmt::format_string<Args...> fmt, Args&&... args) const
        {
            fmt::print(fmt, std::forward<Args>(args)...);
            return *this;
        }

        template <typename... Args>
        const Cursor& println(fmt::format_string<Args...> fmt, Args&&... args) const
        {
            fmt::println(fmt, std::forward<Args>(args)...);
            return *this;
        }

        const Cursor& newline_flush() const
        {
            fmt::println("");
            return *this;
        }

        const Cursor& save() const
        {
            fmt::print("\033[s");
            return *this;
        }

        const Cursor& restore() const
        {
            fmt::print("\033[u");
            return *this;
        }

        const Cursor& home() const
        {
            fmt::print("\033[H");
            return *this;
        }

        const Cursor& move_vert(isize n) const
        {
            if (n > 0) {
                fmt::print("\033[{}A", n);
            } else if (n < 0) {
                fmt::print("\033[{}B", -n);
            }
            return *this;
        }

        const Cursor& move_horz(isize n) const
        {
            if (n > 0) {
                fmt::print("\033[{}C", n);
            } else if (n < 0) {
                fmt::print("\033[{}D", -n);
            }
            return *this;
        }

        const Cursor& erase_line_to_end() const
        {
            fmt::print("\033[K");
            return *this;
        }

        const Cursor& erase_line_to_cursor() const
        {
            fmt::print("\033[1K");
            return *this;
        }

        const Cursor& erase_entire_line() const
        {
            fmt::print("\033[2K");
            return *this;
        }

        const Cursor& erase_screen_to_end() const
        {
            fmt::print("\033[J");
            return *this;
        }

        const Cursor& erase_screen_to_cursor() const
        {
            fmt::print("\033[1J");
            return *this;
        }

        const Cursor& erase_entire_screen() const
        {
            fmt::print("\033[2J");
            return *this;
        }
    };
}
