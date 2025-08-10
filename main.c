#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/i_o.h"
#include "headers/dynamic.h"
#include "headers/structures.h"
#include "headers/backtracking.h"

bool hasEnoughArguments(int argc)
{
    return argc == 3;
}

/*
    argv[1]: input file to feeding the program.
    argv[2]: method desired to use to solve the knapsack 0-1 problem.

    argv[2] can be: "dynamic", "bnb" and "backtracking".

    Note: "bnb" stands for "Branch-And-Bound". 
*/
int main(int argc, char *argv[])
{
    FILE *file;
    Backpack backpack;
    unsigned int lines_amount;

    if(hasEnoughArguments(argc) == false)
    {
        printf("Quantidade errada de argumentos!\n\n");
        printf("Uso: %s <nome_arquivo> <dynamic | backtracking | bnb>\n", argv[0]);
        exit(1);
    }

    file = openFile(argv[1], "r");

    // If error on opening the file passed by argument
    if(file == NULL)
    {
        printf("Falha ao abrir o arquivo!\n");
        exit(2);
    }

    lines_amount = countLines(file);

    // It takes off the first line, since it defines the backpack weigh
    backpack.items = allocItems(lines_amount - 1);

    // Read backpack data and put it in backpack variable
    readBackpackDataFile(file, lines_amount, &backpack);

    {
        if(!strcmp(argv[2], "dynamic"))
            dynamicApproch(&backpack);
        else if(!strcmp(argv[2], "backtracking"))
            executarBacktracking(&backpack);
        else if(!strcmp(argv[2], "bnb"))
            branchAndBoundApproach(&backpack);
        else
            printf("Metodo especificado nao e valido!\n");
    }

    freeItems(&(backpack.items));

    closeFile(file);
    
    return 0;
}
