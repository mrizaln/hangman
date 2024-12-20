#include <hangman.hpp>

int main()
{
    auto word_list = std::filesystem::path{ "/usr/share/dict/words" };
    auto hangman   = hangman::Hangman{ word_list, hangman::Difficulty::Hard };
    hangman.run();
}
