#include <stdlib.h>
#include <stdbool.h>

#include "../headers/i_o.h"

// It uses 2^16 bytes as buffer
#define  BUFFER_SIZE 65536

FILE *openFile(char *filename, char *mode)
{
    FILE *file = fopen(filename, mode);

    return file;
}

void closeFile(FILE *file)
{
    fclose(file);
}

int countLines(FILE *file)
{
    char buffer[BUFFER_SIZE];
    int lines_counter;

    lines_counter = 0;

    while(true)
    {
        size_t bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file);

        for(size_t i = 0 ; i < bytes_read ; i++)
            if(buffer[i] == '\n')
                lines_counter++;
        
        if(feof(file))
            break;
    }

    // It moves the file pointer to its beginning
    fseek(file, 0, SEEK_SET);

    return lines_counter;
}

void readBackpackDataFile(FILE *file, int lines_amount, Backpack *backpack)
{
    Item *p_item;
    char buffer[BUFFER_SIZE];

    // Because the first line specifies the backpack weigh
    int items_amount = lines_amount - 1;

    fgets(buffer, BUFFER_SIZE, file);

    backpack->items_amount = items_amount;
    backpack->weigh = atoi(buffer);

    for(int i = 0 ; i < items_amount ; i++)
    {
        p_item = &(backpack->items[i]);
        fgets(buffer, BUFFER_SIZE, file);
        sscanf(buffer, "%u\t%d", &(p_item->weigh), &(p_item->value));
    }
}