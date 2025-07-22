#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void showUsage(char *program_name)
{
    printf("Uso: %s <quantidade_de_itens> <capacidade_da_mochila>\n", program_name);
    printf("  <quantidade_de_itens>: valor inteiro maior que zero\n");
    printf("  <capacidade_de_itens>: valor inteiro maior que zero\n");
}

bool enoughArgs(int argc)
{
    return argc == 3;
}

bool checkArgsValues(char **argv, int *backpack_capacity, int *amount_items)
{
    if(atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0)
        return false;

    *backpack_capacity = atoi(argv[1]);
    *amount_items = atoi(argv[2]);

    return true;
}

void fillFile(FILE *file, int backpack_capacity, int amount_items)
{
    int max_weigh_value = amount_items / 4;
    int max_item_value = 1000;

    srand(time(NULL));

    fprintf(file, "%d", backpack_capacity);

    for(int i = 1 ; i <= amount_items ; i++)
        fprintf(file, "\n%d\t%d", (rand() % max_weigh_value) + 1, (rand() % max_item_value) + 1);
}

int main(int argc, char *argv[])
{
    FILE *output;
    char file_name[50];
    int amount_items;
    int backpack_capacity;

    if(enoughArgs(argc) == false)
    {
        printf("Quantidade errada de argumentos!\n\n");
        showUsage(argv[0]);
        exit(1);
    }

    if(checkArgsValues(argv, &backpack_capacity, &amount_items) == false)
    {
        printf("Algum dos valores passados como entrada ou e nao-numerico ou e igual a zero!\n\n");
        showUsage(argv[0]);
        exit(1);
    }

    sprintf(file_name, "w%d_n%d.txt", backpack_capacity, amount_items);

    output = fopen(file_name, "w");
    
    if(output == NULL)
        exit(1);

    fillFile(output, backpack_capacity, amount_items);

    fclose(output);

    return 0;
}