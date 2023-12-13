#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int binary[9]);
void convert_to_binary(int decimal, int binary[9]);

int main(void)
{

    string message = get_string("Message: ");

    // iterating through each character
    for (int i = 0, message_length = strlen(message); i < message_length; i++)
    {
        char character = message[i];

        // converting to Ascii equivalent
        int ascii_value = (int) character;

        // dividing the values of the ascii code to get the remainder and the whole number
        // Convert the ASCII value to an 8-bit binary representation
        int binary[9];
        convert_to_binary(ascii_value, binary);

        // call the print bulbs function
        print_bulb(binary);
    }

    return 0;
}

void print_bulb(int binary[9])

{
    for (int i = 0; i < 8; i++)
    {

        if (binary[i] == 0)
        {
            // Dark emoji
            printf("\U000026AB");
        }
        else if (binary[i] == 1)
        {
            // Light emoji
            printf("\U0001F7E1");
        }
    }

    printf("\n");
}

void convert_to_binary(int decimal, int binary[9])
{
    for (int i = 7; i >= 0; i--)
    {
        binary[i] = (decimal % 2) + 0; // Convert the remainder to a 0 and 1
        decimal = decimal / 2;         // Divide by 2 to move to the next int
    }
    binary[BITS_IN_BYTE] = '\0'; // Null-terminate the string
}
