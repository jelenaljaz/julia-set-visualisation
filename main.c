#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "bitmap.h"

#define LIMIT 1.7
#define STEP 2 * LIMIT / DIM
#define DEPTH 256

/// struct for complex number representation
/// x is a real component of the number
/// y is an imaginary component of the number
struct complexNumber
{
    double x;
    double y;
};

struct complexNumber z0;
struct complexNumber z;
struct complexNumber c;
struct complexNumber tmp;

void numberInput()
{
    printf("Enter the constant: ");
    scanf_s("%lf %lf", &c.x, &c.y);
}

struct complexNumber addNumbers(struct complexNumber sum1, struct complexNumber sum2)
{
    struct complexNumber sum;

    sum.x = sum1.x + sum2.x;
    sum.y = sum1.y + sum2.y;

    return sum;
}

struct complexNumber multiplyNumbers(struct complexNumber mul1, struct complexNumber mul2)
{
    struct complexNumber mul;

    mul.x = mul1.x * mul2.x - mul1.y * mul2.y;
    mul.y = mul1.y * mul2.x + mul1.x * mul2.y;

    return mul;
}

unsigned char picture[DIM][DIM];

int main()
{
    int i, j;
    double re, im;
    int n;

    //c.x = CONST_X;
    //c.y = CONST_Y;

    numberInput();

    for (i = 0; i < DIM; i++) {
        re = i * STEP - LIMIT;

        for (j = 0; j < DIM; j++) {
            im = j * STEP - LIMIT;

            z0.x = re;
            z0.y = im;

            n = 0;
            while (n < DEPTH && (z0.x * z0.x + z0.y * z0.y) < 4) {
                z0 = addNumbers(multiplyNumbers(z0, z0), c);
                n++;
            }
            picture[i][j] = (int)((255 * n) / DEPTH);
        }
    }

    bmpOut(picture, "fractal.bmp");

    return 0;
}