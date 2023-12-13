#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Allocate memory for the license plate and copy the contents of buffer
        plates[idx] = malloc(7 * sizeof(char));
        if (plates[idx]==NULL)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);

        // Don't forget to free the memory allocated for each license plate
        free(plates[i]);
    }

    // Close the input file
    fclose(infile);

    return 0;
}

