#pragma once

#include "common.hpp"
#include "cursor.hpp"

#include <cppread/read.hpp>

#include <cstdlib>
#include <filesystem>
#include <set>
#include <fstream>

namespace hangman
{
    enum class Difficulty
    {
        Normal,
        Hard,
    };

    enum class GuessKind
    {
        Incorrect,
        Correct,
        Invalid,
    };

    class Hangman
    {
    public:
        Hangman(std::filesystem::path word_list, Difficulty diff)
            : m_word_list{ word_list }
            , m_num_guesses{ 10 }
            , m_diff{ diff }
        {
        }

        void run()
        {
            auto word = get_word();
            m_cursor.erase_screen_to_end().println("{:─^77}", "┤ Hangman Game by mrizaln ├");

            auto unique_letters = std::set<char>{ word.begin(), word.end() };
            auto used_chars     = std::set<char>{};

            print_init_scene();
            m_cursor.move_vert(2).move_horz(14);

            m_cursor.save();

            print_blank_word(word);

            while (true) {
                auto input = get_char();
                if (not input) {
                    m_cursor.restore();
                    print_guess_result_notice(GuessKind::Invalid);
                    continue;
                }

                auto letter       = static_cast<char>(std::tolower(*input));
                auto letter_exist = unique_letters.contains(letter);

                auto [_, is_new_letter] = used_chars.insert(letter);
                if (is_new_letter and not letter_exist) {
                    --m_num_guesses;
                }

                if (letter_exist) {
                    unique_letters.erase(letter);
                    print_guess(word, letter);
                } else {
                    print_hang_scene();
                }

                print_guess_result_notice(letter_exist ? GuessKind::Correct : GuessKind::Incorrect);
                print_used_chars(used_chars);

                if (m_num_guesses == 0 or unique_letters.empty()) {
                    print_game_result(unique_letters.size());
                    auto line = fmt::format("┤ The word is: {} ├", word);
                    m_cursor.move_vert(-2).move_horz(-14).println("{:─^77}", line);
                    break;
                }
            }
        }

    private:
        std::string get_word() const
        {
            auto file  = std::ifstream{ m_word_list };
            auto words = std::vector<std::string>{};

            auto line     = std::string{};
            auto is_alpha = [](char ch) { return std::isalpha(ch); };
            auto lower    = [](std::string_view str) {
                return str | sv::transform([](char ch) { return static_cast<char>(std::tolower(ch)); });
            };

            while (std::getline(file, line)) {
                if (not sr::all_of(line, is_alpha)) {
                    continue;
                }
                if (m_diff == Difficulty::Hard and line.size() < 10) {
                    continue;
                } else if (m_diff == Difficulty::Normal and (line.size() < 5 or line.size() > 10)) {
                    continue;
                }
                words.push_back(lower(line) | sr::to<std::string>());
            }

            auto idx = util::random(0uz, words.size() - 1);
            return words[idx];
        }

        std::optional<char> get_char()
        {
            auto result = cppread::read<char>();
            if (result.is_error()) {
                switch (result.error()) {
                case cppread::Error::InvalidInput: return std::nullopt;
                default: throw std::runtime_error{ "stdin got into an unrecoverable error state" };
                }
            }
            if (not std::isalpha(result.value())) {
                return std::nullopt;
            }
            return result.value();
        }

        // print functions.....
        // --------------------

        void print_init_scene()
        {
            m_cursor    //
                .println("┌───────────────────────────────────────────────────────────────────────────┐")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("│                                                                           │")
                .println("├───────────────────────────────────────────────────────────────────────────┤")
                .println("│ GUESS:                                                                    │")
                .println("├───────────────────────────────────────────────────────────────────────────┤")
                .println("│ Used guesses:                                                             │")
                .println("├───────────────────────────────────────────────────────────────────────────┤")
                .println("│ Your guess:                                                               │")
                .println("└───────────────────────────────────────────────────────────────────────────┘");
        }

        void print_blank_word(std::string_view word)
        {
            m_cursor.move_vert(4).move_horz(-3);
            for (auto c : word) {
                m_cursor.print("{}", c == ' ' ? "  " : "░ ");
            }
            m_cursor.restore();
        }

        void print_guess(std::string_view word, char letter)
        {
            for (auto [offset, ch] : word | sv::enumerate) {
                if (letter == ch) {
                    m_cursor.restore()
                        .move_vert(4)
                        .move_horz(static_cast<isize>(offset * 2) - 3)
                        .print("{}", letter)
                        .restore();
                }
            }
        }

        // print hang scene according to remaining guess trial
        void print_hang_scene()
        {
            m_cursor.restore();

            switch (m_num_guesses) {
            case 9: {
                m_cursor.move_vert(7).move_horz(-12).println("###########################");
                break;
            }

            case 8: {
                m_cursor.move_vert(26).move_horz(1);
                for (int i{ 0 }; i < 19; i++) {
                    m_cursor.print("#");
                    m_cursor.move_vert(-1).move_horz(-1);
                }
                m_cursor.println("");
                break;
            }

            case 7: {
                m_cursor.move_vert(27).move_horz(1).println("########################################");
                break;
            }

            case 6: {
                // clang-format off
                m_cursor
                    .move_vert(23) .move_horz(36) .print(" .$$$. ")
                    .move_vert(-1) .move_horz(-7) .print("$'   '$")
                    .move_vert(-1) .move_horz(-7) .print("$.   .$")
                    .move_vert(-1) .move_horz(-7) .println(" *$$$* ");
                // clang-format on
                break;
            }

            case 5: {
                m_cursor.move_vert(19).move_horz(39);
                for (int i{ 0 }; i < 6; i++) {
                    m_cursor.print("$");
                    m_cursor.move_vert(-1).move_horz(-1);
                }
                m_cursor.println("^");
                break;
            }

            case 4: {
                m_cursor.move_vert(19).move_horz(40).print("_");
                for (int i{ 0 }; i < 3; i++) {
                    m_cursor.move_vert(-1).move_horz(-1).print("^$.");
                }
                m_cursor.println("");
                break;
            }

            case 3: {
                m_cursor.move_vert(19).move_horz(38).print("_").move_horz(-2).move_vert(-1);
                for (int i{ 0 }; i < 3; i++) {
                    m_cursor.print(".$^");
                    m_cursor.move_vert(-1).move_horz(-5);
                }
                m_cursor.println("");
                break;
            }

            case 2: {
                m_cursor.move_vert(13).move_horz(40).print("$");
                for (int i{ 0 }; i < 4; i++) {
                    m_cursor.move_vert(-1).move_horz(-1).print("`$");
                }
                m_cursor.println("");
                break;
            }

            case 1: {
                m_cursor.move_vert(13).move_horz(38).print("$").move_vert(-1).move_horz(-2);
                for (int i{ 0 }; i < 4; i++) {
                    m_cursor.print("$`");
                    m_cursor.move_vert(-1).move_horz(-3);
                }
                m_cursor.println("");
                break;
            }

            case 0: {
                m_cursor.move_vert(26).move_horz(39);
                for (int i{ 0 }; i < 3; i++) {
                    m_cursor.print("|");
                    m_cursor.move_vert(-1).move_horz(-1);
                }
                m_cursor.println("");
                break;
            }

            default: return;
            }

            m_cursor.restore();
        }

        void print_guess_result_notice(GuessKind kind)
        {
            m_cursor.restore();

            auto guesses = m_num_guesses;
            switch (kind) {

            case GuessKind::Incorrect:
                m_cursor.println("                                               INCORRECT │ {} ", guesses);
                break;
            case GuessKind::Correct:
                m_cursor.println("                                                 CORRECT │ {} ", guesses);
                break;
            case GuessKind::Invalid:
                m_cursor.println("                                                 INVALID │ {} ", guesses);
                break;
            }

            m_cursor.restore();
        }

        void print_used_chars(const std::set<char>& used_chars)
        {
            m_cursor.restore();

            m_cursor.move_vert(2).move_horz(2);
            for (auto c : used_chars) {
                m_cursor.print("{} ", c);
            }

            m_cursor.restore();
        }

        void print_game_result(usize remaining_letters)
        {
            m_cursor.restore().move_horz(-14).move_vert(21);

            if (m_num_guesses == 0) {
                m_cursor    //
                    .println("┌───────────────────────────────────────────────────────────────────────────┐")
                    .println("│                                                                           │")
                    .println("│         #     #   ####   #    #      #      ####    ####   #####          │")
                    .println("│          #   #   #    #  #    #      #     #    #  #       #              │")
                    .println("│           # #    #    #  #    #      #     #    #  #       #              │")
                    .println("│            #     #    #  #    #      #     #    #   ####   #####          │")
                    .println("│            #     #    #  #    #      #     #    #       #  #              │")
                    .println("│            #     #    #  #    #      #     #    #       #  #              │")
                    .println("│            #      ####    ####       #####  ####    ####   #####          │")
                    .println("│                                                                           │")
                    .println("└───────────────────────────────────────────────────────────────────────────┘");
            } else if (remaining_letters == 0) {
                m_cursor    //
                    .println("┌───────────────────────────────────────────────────────────────────────────┐")
                    .println("│                                                                           │")
                    .println("│        #     #   ####   #    #      #.         .#   ###   #$    #         │")
                    .println("│         #   #   #    #  #    #      ^#         #^    #    #^#   #         │")
                    .println("│          # #    #    #  #    #       #.       .#     #    # *:  #         │")
                    .println("│           #     #    #  #    #       ^#. ,#, .#^     #    #  #  #         │")
                    .println("│           #     #    #  #    #        #. # # .#      #    #  !: #         │")
                    .println("│           #     #    #  #    #        ^# # # #^      #    #   #.#         │")
                    .println("│           #      ####    ####          ##' '##      ###   #    $#         │")
                    .println("│                                                                           │")
                    .println("└───────────────────────────────────────────────────────────────────────────┘");
            }

            m_cursor.restore();
        }

        // --------------------

        std::filesystem::path m_word_list;
        Cursor                m_cursor;
        usize                 m_num_guesses;
        Difficulty            m_diff;
    };
}