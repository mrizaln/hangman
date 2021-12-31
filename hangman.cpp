#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>

using namespace std;

string category_name[4] = {"foods", "places", "animals", "colors"};

string category[4][12] = {
    {"egg", "soup",  "meat",    "salad",  "candy",      "spaghetti", "pasta",  "pudding",     "rice",      "burger",    "pizza",  "noodle"},
    {"bar", "park",  "library", "school", "dormitory",  "office",    "house",  "pool",        "mall",      "cafe",      "forest", "restaurant"},
    {"cat", "dog",   "girrafe", "seal",   "orca",       "shark",     "owl",    "caterpillar", "butterfly", "dragonfly", "lizard", "cockroach"},
    {"red", "green", "blue",    "teal",   "aquamarine", "cream",     "orange", "maroon",      "azure",     "violet",    "blue",   "jade"},
};

// return number of unique chars
int unique_char_num(char c_arr[], int w_size){
    int temp_size = 1;
    for (int i = 1; i < w_size; i++){
        bool same_letter = 0;
        for (int j = 0; j < temp_size; j++){
            if (c_arr[j] == c_arr[i]){ 
                same_letter = 1;
                break;
            }
        }
        if (!same_letter){
            temp_size += 1;
        }
    }
    return temp_size;
}

// generate random number between 1 - 12
int rand_num(){
    srand(time(0));
    return rand() % 12 + 1;
}

// take only numeric input
int enter_category(){
    int x = 0;
    while(!(cin >> x)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    return x;
}

// print a notice whether your guess is right or not
void print_guess_result_notice(bool flag){
    printf("\033[u");
    if (flag){ printf("                                                       CORRECT"); }
    else {     printf("                                                     INCORRECT"); }
    printf("\033[u");
}

// print initial scene
void init_scene(){
    cout <<"\
 ___________________________________________________________________________\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|                                                                           |\n\
|___________________________________________________________________________|\n\
|                                                                           |\n\
| GUESS:                                                                    |\n\
|---------------------------------------------------------------------------|\n\
| Used guesses:                                                             |\n\
|---------------------------------------------------------------------------|\n\
| Your guess:                                                               |\n\
|___________________________________________________________________________|\n";
}

// print hang scene according to remaining guess trial
void hang_scene(int num){
    printf("\033[u");
    switch (num){
        case 9:
            printf("\033[7A\033[12D");
            cout << "###########################";
            break;
        case 8:
            printf("\033[26A\033[1C");
            for (int i = 0; i < 19; i++){
                cout << "#"; printf("\033[1B\033[1D");
            }
            break;
        case 7:
            printf("\033[27A\033[1C");
            cout << "########################################"; 
            break;
        case 6:
            printf("\033[23A\033[36C"); cout << " .$$$. ";
            printf("\033[1B\033[7D");   cout << "$'   '$";
            printf("\033[1B\033[7D");   cout << "$.   .$";
            printf("\033[1B\033[7D");   cout << " *$$$* ";
            break;
        case 5:
            printf("\033[19A\033[39C");
            for (int i = 0; i < 6; i++){
                cout << "$"; printf("\033[1B\033[1D");
            }
            cout << "^";
            break;
        case 4:
            printf("\033[19A\033[40C"); cout << "_";
            for (int i = 0; i < 3; i++){
                printf("\033[1B\033[1D"); cout << "^$.";
            }
            break;
        case 3:
            printf("\033[19A\033[38C"); cout << "_"; printf("\033[2D\033[1B");
            for (int i = 0; i < 3; i++){
                cout << ".$^"; printf("\033[1B\033[5D");
            }
            break;
        case 2:
            printf("\033[13A\033[40C"); cout << "$";
            for (int i = 0; i < 4; i++){
                printf("\033[1B\033[1D"); cout << "`$";
            }
            break;
        case 1:
            printf("\033[13A\033[38C"); cout << "$"; printf("\033[1B\033[2D");
            for (int i = 0; i < 4; i++){
                cout << "$`"; printf("\033[1B\033[3D");
            }
            break;
        case 0:
            printf("\033[26A\033[39C");
            for (int i = 0; i < 3; i++){
                cout << "|"; printf("\033[1B\033[1D");
            }
            break;
        default:
            return;
    }
    printf("\033[u");
}

// print guessed char
void print_guess(char c, int char_off){
    printf("\033[u");
    int col = char_off * 2 + 1;
    printf("\033[4D\033[4A\033[%dC", col);
    cout << c;
    // printf("\033[4B\033[14C");
    printf("\033[u");
}

int used_pos = 0;
char used_chars[40];
// print used char
void print_used_guess(char c){
    printf("\033[u");
    for (int i = 0; i < 40; i++){
        if (used_chars[i] == c){ return; }
    }
    int col = 2 + used_pos;
    printf("\033[2A\033[%dC", col);
    cout << c;
    used_pos += 2;
    used_chars[used_pos / 2] = c;
    printf("\033[u");
}

// print blank guess word
void print_blank_word(int word_size){
    printf("\033[4A\033[3D");
    for (int i = 0; i < word_size; i++){
        cout << "_ ";
    }
    printf("\033[u");
}

// print game result; win/lose
void game_result(int rem_guess, int rem_letter){
    printf("\033[u\033[14D\033[21A");
    if (rem_guess == 0){
        cout << "\
|---------------------------------------------------------------------------|\n\
|                                                                           |\n\
|         #     #   ####   #    #      #      ####    ####   #####          |\n\
|          #   #   #    #  #    #      #     #    #  #       #              |\n\
|           # #    #    #  #    #      #     #    #  #       #              |\n\
|            #     #    #  #    #      #     #    #   ####   #####          |\n\
|            #     #    #  #    #      #     #    #       #  #              |\n\
|            #     #    #  #    #      #     #    #       #  #              |\n\
|            #      ####    ####       #####  ####    ####   #####          |\n\
|                                                                           |\n\
|---------------------------------------------------------------------------|\n";
    } else if (rem_letter == 0){
        cout << "\
|---------------------------------------------------------------------------|\n\
|                                                                           |\n\
|        #     #   ####   #    #      #.         .#   ####   #$    #        |\n\
|         #   #   #    #  #    #      ^#         #^  #    #  #^#   #        |\n\
|          # #    #    #  #    #       #.       .#   #    #  # *:  #        |\n\
|           #     #    #  #    #       ^#. ,#, .#^   #    #  #  #  #        |\n\
|           #     #    #  #    #        #. # # .#    #    #  #  !: #        |\n\
|           #     #    #  #    #        ^# # # #^    #    #  #   #.#        |\n\
|           #      ####    ####          ##' '##      ####   #    $#        |\n\
|                                                                           |\n\
|---------------------------------------------------------------------------|\n";
    }
    printf("\033[u");
}

// main function
int main(){
    char letter;
    string dummy = "dummy";
    int cat;
    int remaining_guess = 10;
    int remaining_letter;
    cout << "=========================<[ Hangman Game by Maiuna ]>========================" << endl;
    cout << "Category: 1) foods\n\t  2) places\n\t  3) animals\n\t  4) colors\n";
    
    // take input
    cout << "Which category you plan to play (input number): ";
    while (true){
        cat = enter_category();
        if (cat >= 1 && cat <= 4){
            break;
        } else {
            cout << "Please input 1 to 4: ";
        }
    }

    printf("\033[2J");
    cout << "=========================<[ Hangman Game by Maiuna ]>========================" << endl;
    cout << "Category: " << category_name[cat-1] << endl;

    init_scene();
    printf("\033[2A\033[14C");
    printf("\033[s");
    
    // game runtime
    while (true){
        // preparing word
        // string word = "apple";
        string word = category[cat-1][rand_num()];
        int word_size = word.length();
        char c_arr[word_size + 1];
        strcpy(c_arr, word.c_str());

        int remaining_letter = unique_char_num(c_arr, word_size);

        print_blank_word(word_size);

        while (true){
            getline(cin, dummy);
            if (dummy.empty()){ printf("\033[u"); continue; }

            // printf("\033[1A\033[14C \033[1D");
            printf("\033[u");
            letter = dummy[0];

            bool letter_exist = 0;
            for (int i = 0; i < word_size; i++){
                if (c_arr[i] == letter){ 
                    letter_exist = 1;
                    print_guess(letter, i); 
                }
            }

            bool letter_already_used = 0;
            for (int i = 0; i < 40; i++){
                if (used_chars[i] == letter){ 
                    letter_already_used = 1;
                }
            }

            if (!letter_exist && !letter_already_used){ 
                remaining_guess -= 1;
                hang_scene(remaining_guess);
            } else if (letter_exist && !letter_already_used){
                remaining_letter -= 1;
            }

            print_guess_result_notice(letter_exist);
            print_used_guess(letter);

            game_result(remaining_guess, remaining_letter);
            if (remaining_guess == 0 || remaining_letter == 0) { 
                printf("\033[2B\033[14D");
                return 0;
            }
        }
    }
}