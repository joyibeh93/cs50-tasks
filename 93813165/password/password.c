// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{

    bool lower_case = false;
    bool uppercase = false;
    bool contain_digit = false;
    bool contain_symbol = false;

    // checking the length of the password
    int passwordLength = strlen(password);

    for (int i = 0; i < passwordLength; i++)
    {
        char current_char = password[i];
        // printf("%c\n", current_char);

        if (islower(current_char))
        {
            lower_case = true;
        }
        else if (isupper(current_char))
        {
            uppercase = true;
        }
        else if (isdigit(current_char))
        {
            contain_digit = true;
        }
        else
        {
            contain_symbol = true;
        }
    }

    return lower_case && uppercase && contain_digit && contain_symbol;
}
