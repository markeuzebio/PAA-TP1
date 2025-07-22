#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers/i_o.h"
#include "headers/structures.h"

bool hasEnoughArguments(int argc)
{
    return argc == 2;
}

int main(int argc, char *argv[])
{
    FILE *file;
    Backpack backpack;
    unsigned int lines_amount;

    if(hasEnoughArguments(argc) == false)
    {
        exit(1);
    }

    file = openFile(argv[1], "r");

    // If error on opening the file passed by argument
    if(file == NULL)
    {
        exit(2);
    }

    lines_amount = countLines(file);

    // It takes off the first line, since it defines the backpack weigh
    backpack.items = allocItems(lines_amount - 1);

    // Read backpack data and put it in backpack variable
    readBackpackDataFile(file, lines_amount, &backpack);

    freeItems(&(backpack.items));

    closeFile(file);
    
    return 0;
}
