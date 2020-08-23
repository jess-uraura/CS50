#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    char filename[8];   // '#', '#', '#', '.', 'j', 'p', 'g', '\0' --> 8 bytes total
    int counter = 0;   // Create a counter for the increasing number of recovered files
    sprintf(filename, "%03i.jpg", counter);

    BYTE buffer[512];
    FILE *new_file = NULL;
    while ((fread(buffer, 512, 1, file)) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If 'counter' is greater than 0, that means a previous file was already opened. Close it.
            if (counter > 0)
            {
                fclose(new_file);
            }

            // Open a new file
            new_file = fopen(filename, "w");

            // Write the current block (the one with the jpeg signature) to the new file
            fwrite(buffer, 512, 1, new_file);

            // Update counter variable and filename to make it ready for the next file
            counter++;
            sprintf(filename, "%03i.jpg", counter);
        }
        else
        {
            // Keep writing to the previous file if it exists
            if (counter > 0)
            {
                fwrite(buffer, 512, 1, new_file);
            }
        }
    }

    // Close the last file (50th image)
    fclose(new_file);
}