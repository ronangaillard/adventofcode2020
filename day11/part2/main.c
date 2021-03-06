#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 400
#define MAX_LINE_LENGTH 100

int isThereAnOccupiedSeatInThisDirectionLol(int posX, int posY, int dirX, int dirY, char map[MAX_LINES][MAX_LINE_LENGTH])
{
    while (1)
    {
        posX += dirX;
        posY += dirY;

        if (posX == -1 || posY == -1)
        {
            return 0;
        }

        if (map[posY][posX] == 0)
        {
            return 0;
        }

        if (map[posY][posX] == 'L')
        {
            return 0;
        }

        if (map[posY][posX] == '#')
        {
            return 1;
        }
    }
}
int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char input[MAX_LINES][MAX_LINE_LENGTH];
    char inputTempered[MAX_LINES][MAX_LINE_LENGTH];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    for (int x = 0; x < MAX_LINE_LENGTH; x++)
        for (int y = 0; y < MAX_LINES; y++)
        {
            input[y][x] = 0;
        }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        strcpy(input[i], line);
        i++;
    }

    memcpy(inputTempered, input, MAX_LINES * MAX_LINE_LENGTH);

    while (1)
    {
        int x = 0;
        int y = 0;

        while (1)
        {
            if (input[y][x] == 'L' || input[y][x] == '#')
            {
                int occupiedSeats = 0;

                for (int xOffset = -1; xOffset <= 1; xOffset++)
                    for (int  yOffset = -1; yOffset <= 1; yOffset++)
                    {
                        if (xOffset == 0 && yOffset == 0)
                        {
                            continue;
                        }

                        occupiedSeats += isThereAnOccupiedSeatInThisDirectionLol(x, y, xOffset, yOffset, input);
                    }

                if (input[y][x] == 'L' && occupiedSeats == 0)
                {
                    inputTempered[y][x] = '#';
                }

                if (input[y][x] == '#' && occupiedSeats >= 5)
                {
                    inputTempered[y][x] = 'L';
                }
            }

            x++;

            if (input[y][x] == '\0')
            {
                x = 0;
                y++;
            }

            if (y == i)
            {
                break;
            }
        }

        if (!memcmp(input, inputTempered, MAX_LINES * MAX_LINE_LENGTH))
        {
            break;
        }

        memcpy(input, inputTempered, MAX_LINES * MAX_LINE_LENGTH);
    }

    int occupiedSeats = 0;

    for (int x = 0; x < MAX_LINE_LENGTH; x++)
        for (int y = 0; y < MAX_LINES; y++)
            if (inputTempered[y][x] == '#')
            {
                occupiedSeats++;
            }

    printf("Occupied seats : %d\n", occupiedSeats);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
