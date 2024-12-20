#include "hangman.hpp"

#include <CLI/CLI.hpp>

#include <csignal>

int main(int argc, char** argv)
{
    // I don't know cleaner way to handle interrupt signal other than this
    std::signal(SIGINT, [](int) { std::fclose(stdin); });

    auto app = CLI::App{ "Hangman game" };

    auto hard      = false;
    auto word_list = std::filesystem::path{ "/usr/share/dict/words" };

    app.add_flag("--hard", hard, "Use hard difficulty");
    app.add_option("--word-list", word_list, "Path to word list")->default_val(word_list);

    CLI11_PARSE(app, argc, argv);

    if (not std::filesystem::exists(word_list)) {
        fmt::println(stderr, "No such file: {}", word_list.c_str());
        return 1;
    }
    if (not std::filesystem::is_regular_file(word_list)) {
        fmt::println(stderr, "Not a regular file: {}", word_list.c_str());
        return 1;
    }

    auto diff    = hard ? hangman::Difficulty::Hard : hangman::Difficulty::Normal;
    auto hangman = hangman::Hangman{ word_list, diff };

    try {
        hangman.run();
    } catch (const hangman::error::NotEnoughWords& e) {
        fmt::println("Error: {}", e.what());
        return 1;
    } catch (const hangman::error::Error& e) {
        hangman.fix_cursor();
        fmt::println("Error: {}", e.what());
        return 1;
    }
}
