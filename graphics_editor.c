/*
Name: Harish Harsha
Project: 2D Graphics Editor in C
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void initializeCanvas()
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;
    printf("\n");

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int r, int c, int h, int w, char ch)
{
    int i, j;

    for (i = r; i < r + h && i < ROWS; i++)
    {
        for (j = c; j < c + w && j < COLS; j++)
        {
            if (i == r || i == r + h - 1 ||
                j == c || j == c + w - 1)
            {
                canvas[i][j] = ch;
            }
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2, char ch)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        if (x1 >= 0 && x1 < ROWS &&
            y1 >= 0 && y1 < COLS)
        {
            canvas[x1][y1] = ch;
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawTriangle(int r, int c, int size, char ch)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (r + i < ROWS)
        {
            if (c - i >= 0)
                canvas[r + i][c - i] = ch;

            if (c + i < COLS)
                canvas[r + i][c + i] = ch;
        }
    }

    for (i = c - size + 1; i <= c + size - 1; i++)
    {
        if (i >= 0 && i < COLS &&
            r + size - 1 < ROWS)
        {
            canvas[r + size - 1][i] = ch;
        }
    }
}

void drawCircle(int xc, int yc, int radius, char ch)
{
    int x, y;

    for(x = 0; x < ROWS; x++)
    {
        for(y = 0; y < COLS; y++)
        {
            int dx = x - xc;
            int dy = y - yc;

            double distance = sqrt(dx * dx + dy * dy);

            if(distance >= radius - 0.5 &&
               distance <= radius + 0.5)
            {
                canvas[x][y] = ch;
            }
        }
    }
}
void clearCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }

    printf("Canvas cleared successfully!\n");
}

void saveCanvas()
{
    FILE *fp = fopen("canvas.txt", "w");

    if(fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            fputc(canvas[i][j], fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
    printf("Canvas saved successfully!\n");
}

void loadCanvas()
{
    FILE *fp = fopen("canvas.txt", "r");

    if(fp == NULL)
    {
        printf("No saved canvas found!\n");
        return;
    }

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = fgetc(fp);
        }
        fgetc(fp);
    }

    fclose(fp);
    printf("Canvas loaded successfully!\n");
}
int main()
{
    int choice;

    initializeCanvas();

    while (1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Rectangle\n");
        printf("6. Modify Rectangle\n");
        printf("7. Display Canvas\n");
        printf("8. Clear Canvas\n");
        printf("9. Save Canvas\n");
        printf("10. Load Canvas\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int r, c, h, w;

            printf("Enter row, column, height, width: ");
            scanf("%d%d%d%d", &r, &c, &h, &w);

            drawRectangle(r, c, h, w, '*');
            break;
        }

        case 2:
        {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2, '*');
            break;
        }

        case 3:
        {
            int r, c, size;

            printf("Enter top row, center column, size: ");
            scanf("%d%d%d", &r, &c, &size);

            drawTriangle(r, c, size, '*');
            break;
        }

        case 4:
        {
            int xc, yc, radius;

            printf("Enter center row, center column, radius: ");
            scanf("%d%d%d", &xc, &yc, &radius);

            drawCircle(xc, yc, radius, '*');
            break;
        }

        case 5:
        {
            int r, c, h, w;

            printf("Enter rectangle row, column, height, width to delete: ");
            scanf("%d%d%d%d", &r, &c, &h, &w);

            drawRectangle(r, c, h, w, '_');
            break;
        }

        case 6:
        {
            int r1, c1, h1, w1;
            int r2, c2, h2, w2;

            printf("Old rectangle row, column, height, width: ");
            scanf("%d%d%d%d", &r1, &c1, &h1, &w1);

            drawRectangle(r1, c1, h1, w1, '_');

            printf("New rectangle row, column, height, width: ");
            scanf("%d%d%d%d", &r2, &c2, &h2, &w2);

            drawRectangle(r2, c2, h2, w2, '*');
            break;
        }

        case 7:
            displayCanvas();
            break;

        case 8:
    clearCanvas();
    break;

case 9:
    saveCanvas();
    break;

case 10:
    loadCanvas();
    break;

case 11:
    printf("Exiting program...\n");
    return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}