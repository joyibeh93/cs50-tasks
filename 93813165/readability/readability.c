#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// function prototype
int count_letter(string text);
int count_words(string text);
int count_sentence(string text);

int main(void)
{
    // getting user string

    string text = get_string("Text: ");

    float letters = count_letter(text);
    float words = count_words(text);
    float sentence = count_sentence(text);

    // using index formular index = 0.0588 * L - 0.296 * S - 15.8

    // we need to get our L and S

    float L = (letters / words) * 100;
    float S = (sentence / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int result = round(index);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result == 2)
    {
        printf("Grade 2\n");
    }
    else if (result == 3)
    {
        printf("Grade 3\n");
    }
    else if (result == 4)
    {
        printf("Grade 4\n");
    }
    else if (result == 5)
    {
        printf("Grade 5\n");
    }
    else if (result == 6)
    {
        printf("Grade 6\n");
    }
    else if (result == 7)
    {
        printf("Grade 7\n");
    }
    else if (result == 8)
    {
        printf("Grade 8\n");
    }
    else if (result == 9)
    {
        printf("Grade 9\n");
    }
    else if (result == 10)
    {
        printf("Grade 10\n");
    }
    else if (result == 11)
    {
        printf("Grade 11\n");
    }
    else if (result == 12)
    {
        printf("Grade 12\n");
    }
    else if (result == 13)
    {
        printf("Grade 13\n");
    }
    else if (result == 14)
    {
        printf("Grade 14\n");
    }
    else if (result == 15)
    {
        printf("Grade 15\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letter(string text)
{

    int count = 0;

    int letter_length = strlen(text);

    for (int i = 0; i < letter_length; i++)
    {

        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0, word_length = strlen(text); i < word_length; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_sentence(string text)
{
    int count = 0;
    for (int i = 0, sentence_length = strlen(text); i < sentence_length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}