#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_matrix(int rows, int matrix[20][60], const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return -1;
    }
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < 60; ++j)
        {
            fscanf(fp, "%d%*c", &matrix[i][j]);
        }
    }
    fclose(fp);
    printf("before out");
    return 0;
}