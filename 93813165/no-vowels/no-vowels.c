// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <stdio.h>
#include <string.h>

// Function to replace vowels with numbers
char *replace(const char *input) {
    static char output[100]; // Assuming a maximum word length of 100 characters
    int i = 0;

    while (input[i] != '\0') {
        switch (input[i]) {
            case 'a':
                output[i] = '6';
                break;
            case 'e':
                output[i] = '3';
                break;
            case 'i':
                output[i] = '1';
                break;
            case 'o':
                output[i] = '0';
                break;
            default:
                output[i] = input[i];
                break;
        }
        i++;
    }
    output[i] = '\0';

    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    char *input_word = argv[1];
    char *converted_word = replace(input_word);

    printf("%s\n", converted_word);

    return 0;
}

