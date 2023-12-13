#include <stdio.h>
#include <stdlib.h>

// Function to check if a block of data matches the start of a JPEG file
int is_jpeg_start(unsigned char buffer[512])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s forensic_image\n", argv[0]);
        return 1;
    }

    // Open the forensic image for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open forensic image %s for reading.\n", argv[1]);
        return 1;
    }

    unsigned char buffer[512];
    int jpeg_count = 0;
    FILE *outfile = NULL;

    while (fread(buffer, 1, 512, infile) == 512)
    {
        // Check if the current block starts a new JPEG
        if (is_jpeg_start(buffer))
        {
            // Close the previous JPEG file (if any)
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03d.jpg", jpeg_count);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 1;
            }

            jpeg_count++;
        }

        // Write the block to the current JPEG file (if any)
        if (outfile != NULL)
        {
            fwrite(buffer, 1, 512, outfile);
        }
    }

    // Close the last JPEG file (if any)
    if (outfile != NULL)
    {
        fclose(outfile);
    }

    // Close the forensic image file
    fclose(infile);

    return 0;
}
