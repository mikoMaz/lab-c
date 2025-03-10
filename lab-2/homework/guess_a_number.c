/*
random.o:
                 U _GLOBAL_OFFSET_TABLE_
                 U __stack_chk_fail
0000000000000058 T get_input_from_the_user
0000000000000000 T random_number
                 U scanf
0000000000000000 D seed
*/

#include <stdio.h>

extern int random_number(int max);
extern int get_input_from_the_user();

void guess_the_number() {
    printf("Let's play a game!\nType a number: ");

    int max_value = get_input_from_the_user();
    printf("You have to guess the numebr from 0 to %d\n", max_value);

    int number_to_guess = random_number(max_value);

    int number_of_guesses = 0;
    int user_guess;

    for (;;) {
        number_of_guesses++;
        printf("Type your guess: ");
        user_guess = get_input_from_the_user();

        if (user_guess < number_to_guess)
            printf("too small\n");
        else if (user_guess > number_to_guess)
            printf("too big\n");
        else {
            printf("you guessed correctly in %d rounds\n", number_of_guesses);
            break;
        }
    }
}

int main()
{
    guess_the_number();

	return 0;
}
