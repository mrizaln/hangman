#include <iostream>
#include <ctime>
#include <cstring>
#include <limits>

// configuration
//---------------------------------------------------------------------------------------
constexpr int MAX_GUESS { 10 };

const std::string category_name[4] = {"foods", "places", "animals", "colors"};

const std::string category[4][12] = {
    {"egg", "soup",  "meat",     "salad",  "candy",      "spaghetti", "pasta",  "pudding",     "rice",      "burger",    "pizza",  "noodle"    },
    {"bar", "park",  "library",  "school", "dormitory",  "office",    "house",  "pool",        "mall",      "cafe",      "forest", "restaurant"},
    {"cat", "dog",   "girraffe", "seal",   "orca",       "shark",     "owl",    "caterpillar", "butterfly", "dragonfly", "lizard", "cockroach" },
    {"red", "green", "blue",     "teal",   "aquamarine", "cream",     "orange", "maroon",      "azure",     "violet",    "blue",   "jade"      },
};

//---------------------------------------------------------------------------------------

// return number of unique chars
int unique_char_num(char c_arr[], int w_size)
{
    int temp_size{ 1 };
    for (int i{ 1 }; i < w_size; i++)
    {
        bool same_letter = 0;
        for (int j{ 0 }; j < temp_size; j++)
        {
            if (c_arr[j] == c_arr[i])
            { 
                same_letter = 1;
                break;
            }
        }
        if (!same_letter)
        {
            temp_size += 1;
        }
    }
    return temp_size;
}

// generate random number between 1 - 12
int rand_num()
{
    srand(time(0));
    int num{ rand() % 12 + 1 };
    return num;
}

// take only numeric input
int enter_category()
{
    int x{ 0 };
    while(!(std::cin >> x))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again: ";
    }
    return x;
}

// print a notice whether your guess is right or not
void print_guess_result_notice(bool flag)
{
    std::cout << "\033[u";
    if (flag)
        std::cout << "                                                       CORRECT";
    else
        std::cout << "                                                     INCORRECT";
    std::cout << "\033[u";
}

// print initial scene
void init_scene()
{
    std::cout <<
    " ___________________________________________________________________________\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|                                                                           |\n"
    "|___________________________________________________________________________|\n"
    "|                                                                           |\n"
    "| GUESS:                                                                    |\n"
    "|---------------------------------------------------------------------------|\n"
    "| Used guesses:                                                             |\n"
    "|---------------------------------------------------------------------------|\n"
    "| Your guess:                                                               |\n"
    "|___________________________________________________________________________|\n";
}

// print hang scene according to remaining guess trial
void hang_scene(int num)
{
    std::cout << "\033[u";
    switch (num)
    {
        case 9:
            std::cout << "\033[7A\033[12D";
            std::cout << "###########################";
            break;

        case 8:
            std::cout << "\033[26A\033[1C";
            for (int i{ 0 }; i < 19; i++)
            {
                std::cout << "#";
                std::cout << "\033[1B\033[1D";
            }
            break;

        case 7:
            std::cout << "\033[27A\033[1C";
            std::cout << "########################################"; 
            break;

        case 6:
            std::cout << "\033[23A\033[36C"; std::cout << " .$$$. ";
            std::cout << "\033[1B\033[7D";   std::cout << "$'   '$";
            std::cout << "\033[1B\033[7D";   std::cout << "$.   .$";
            std::cout << "\033[1B\033[7D";   std::cout << " *$$$* ";
            break;

        case 5:
            std::cout << "\033[19A\033[39C";
            for (int i{ 0 }; i < 6; i++)
            {
                std::cout << "$";
                std::cout << "\033[1B\033[1D";
            }
            std::cout << "^";
            break;

        case 4:
            std::cout << "\033[19A\033[40C"; std::cout << "_";
            for (int i{ 0 }; i < 3; i++)
            {
                std::cout << "\033[1B\033[1D"; std::cout << "^$.";
            }
            break;

        case 3:
            std::cout << "\033[19A\033[38C";
            std::cout << "_";
            std::cout << "\033[2D\033[1B";
            for (int i{ 0 }; i < 3; i++)
            {
                std::cout << ".$^"; std::cout << "\033[1B\033[5D";
            }
            break;
            
        case 2:
            std::cout << "\033[13A\033[40C"; std::cout << "$";
            for (int i{ 0 }; i < 4; i++)
            {
                std::cout << "\033[1B\033[1D"; std::cout << "`$";
            }
            break;

        case 1:
            std::cout << "\033[13A\033[38C"; std::cout << "$";
            std::cout << "\033[1B\033[2D";
            for (int i{ 0 }; i < 4; i++)
            {
                std::cout << "$`"; std::cout << "\033[1B\033[3D";
            }
            break;

        case 0:
            std::cout << "\033[26A\033[39C";
            for (int i{ 0 }; i < 3; i++)
            {
                std::cout << "|"; std::cout << "\033[1B\033[1D";
            }
            break;

        default:
            return;
    }
    std::cout << "\033[u";
}

// print guessed char
void print_guess(char c, int char_off)
{
    std::cout << "\033[u";
    int col{ char_off * 2 + 1 };
    printf("\033[4D\033[4A\033[%dC", col);
    std::cout << c;
    // std::cout << "\033[4B\033[14C";
    std::cout << "\033[u";
}

int used_pos{ 0 };
char used_chars[40];        // this selection of number is arbitrary, but, at least this should have a capacity that equals to the number of letters (lowercase only) in alphabet
// print used char
void print_used_guess(char c)
{
    std::cout << "\033[u";
    for (int i{ 0 }; i < 40; i++)
    {
        if (used_chars[i] == c){ return; }
    }
    
    int col{ 2 + used_pos };
    printf("\033[2A\033[%dC", col);
    std::cout << c;
    used_pos += 2;
    used_chars[used_pos / 2] = c;
    std::cout << "\033[u";
}

// print blank guess word
void print_blank_word(int word_size)
{
    std::cout << "\033[4A\033[3D";
    for (int i{ 0 }; i < word_size; i++)
    {
        std::cout << "_ ";
    }
    std::cout << "\033[u";
}

// print game result; win/lose
void game_result(int rem_guess, int rem_letter)
{
    std::cout << "\033[u\033[14D\033[21A";
    if (rem_guess == 0)
    {
        std::cout << 
        "|---------------------------------------------------------------------------|\n"
        "|                                                                           |\n"
        "|         #     #   ####   #    #      #      ####    ####   #####          |\n"
        "|          #   #   #    #  #    #      #     #    #  #       #              |\n"
        "|           # #    #    #  #    #      #     #    #  #       #              |\n"
        "|            #     #    #  #    #      #     #    #   ####   #####          |\n"
        "|            #     #    #  #    #      #     #    #       #  #              |\n"
        "|            #     #    #  #    #      #     #    #       #  #              |\n"
        "|            #      ####    ####       #####  ####    ####   #####          |\n"
        "|                                                                           |\n"
        "|---------------------------------------------------------------------------|\n";
    }
    else if (rem_letter == 0)
    {
        std::cout << 
        "|---------------------------------------------------------------------------|\n"
        "|                                                                           |\n"
        "|        #     #   ####   #    #      #.         .#   ###   #$    #         |\n"
        "|         #   #   #    #  #    #      ^#         #^    #    #^#   #         |\n"
        "|          # #    #    #  #    #       #.       .#     #    # *:  #         |\n"
        "|           #     #    #  #    #       ^#. ,#, .#^     #    #  #  #         |\n"
        "|           #     #    #  #    #        #. # # .#      #    #  !: #         |\n"
        "|           #     #    #  #    #        ^# # # #^      #    #   #.#         |\n"
        "|           #      ####    ####          ##' '##      ###   #    $#         |\n"
        "|                                                                           |\n"
        "|---------------------------------------------------------------------------|\n";
    }
    std::cout << "\033[u";
}

//---------------------------------------------------------------------------------------

// main function
int main()
{
    int remaining_guess { MAX_GUESS };

    std::cout << "=========================<[ Hangman Game by mrizaln ]>========================" << '\n';
    std::cout << "Category: 1) foods\n\t  2) places\n\t  3) animals\n\t  4) colors\n";
    
    // take input
    std::cout << "Which category you plan to play (input number): ";
    int cat {};
    while (true)
    {
        cat = enter_category();
        if (cat >= 1 && cat <= 4)
            break;
        else
            std::cout << "Please input 1 to 4: ";
    }

    std::cout << "\033[2J";
    std::cout << "=========================<[ Hangman Game by mrizaln ]>========================" << '\n';
    std::cout << "Category: " << category_name[cat - 1] << '\n';

    init_scene();
    std::cout << "\033[2A\033[14C";
    std::cout << "\033[s";
    
    // game loop
    while (true)
    {
        // preparing word
        std::string word { category[cat - 1][rand_num()] };
        int word_size { (int)word.length() };
        char c_arr[word_size + 1];
        strcpy(c_arr, word.c_str());

        int remaining_letter { unique_char_num(c_arr, word_size) };

        print_blank_word(word_size);

        while (true)
        {
            std::string dummy {};
            getline(std::cin, dummy);
            if (dummy.empty())
            {
                std::cout << "\033[u";
                continue;
            }

            // std::cout << "\033[1A\033[14C \033[1D";
            std::cout << "\033[u";
            char letter {};
            letter = dummy[0];

            // check if letter is an uppercase, then convert it into lowercase
            if (letter >= 65 && letter <= 90)
                letter += 32;

            bool letter_exist { false };
            for (int i { 0 }; i < word_size; i++)
            {
                if (c_arr[i] == letter)
                { 
                    letter_exist = true;
                    print_guess(letter, i); 
                }
            }

            bool letter_already_used = 0;
            for (int i = 0; i < 40; i++)
            {
                if (used_chars[i] == letter)
                    letter_already_used = true;
            }

            if (!letter_exist && !letter_already_used)
            { 
                --remaining_guess;
                hang_scene(remaining_guess);
            }

            if (letter_exist && !letter_already_used)
                --remaining_letter;

            print_guess_result_notice(letter_exist);
            print_used_guess(letter);

            game_result(remaining_guess, remaining_letter);
            if (remaining_guess == 0 || remaining_letter == 0)
            { 
                std::cout << "\033[2B\033[14D";
                std::cout << "The word is: " << word << '\n';
                return 0;
            }
        }
    }
}
