#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

#include "../headers/structures.h"

FILE *openFile(char *filename, char *mode);
void closeFile(FILE *file);
void readBackpackDataFile(FILE *file, int lines_amount, Backpack *backpack);
int countLines(FILE *file);

#endif