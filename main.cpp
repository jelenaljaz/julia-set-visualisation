/// A program that generates a visual presentation of Julia sets
/// based on two complex nubers of our choice.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "bitmap.h"


// constants
#define LIMIT 1.7
#define STEP 2*LIMIT/DIM
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

// input function
void numberInput()
{
    printf("WARNING: CONSTANT MUST BE ENTERED IN FORMAT AS THIS EXAMPLE SHOWS: 5 6\n(SPACE BETWEEN BOTH COMPONENTS IS NECCESSARY)\n\n")
    printf("Enter the constant: ");
    scanf("%lf %lf", &c.x, &c.y);
}

// struct used to add 2 complex numbers from input
struct complexNumber addNumbers(struct complexNumber sum1, struct complexNumber sum2)
{
    struct complexNumber sum;

    sum.x = sum1.x + sum2.x;
    sum.y = sum1.y + sum2.y;

    return sum;
}

// struct used to multiply 2 complex numbers from input
struct complexNumber multiplyNumbers(struct complexNumber mul1, struct complexNumber mul2)
{
    struct complexNumber mul;

    mul.x = mul1.x*mul2.x - mul1.y*mul2.y;
    mul.y = mul1.y*mul2.x + mul1.x*mul2.y;

    return mul;
}

unsigned char picture[DIM][DIM];

// main function - used to calculate the Julia set from input complex numbers
// and output it to a bitmap image.
int main()
{
    int i, j; // loop counters
    double re, im; // re - real component, im - imaginary component
    int n; // counter

    numberInput();

    for (i = 0; i < DIM; i++)
    {
        re = i * STEP - LIMIT;
        for (j = 0; j < DIM; j++)
        {
            im = j * STEP - LIMIT;

            z0.x = re;
            z0.y = im;

            n = 0;
            while(n < DEPTH && (z0.x*z0.x + z0.y*z0.y) < 4)
            {
                // this is the mathematical formula used to calculate
                // a Julia set from a given constant
                z0 = addNumbers(multiplyNumbers(z0, z0), c);
                n++;
            }
            picture[i][j] = (int)((255*n)/DEPTH);
        }
    }

    // output a bitmap image containing a graph of calculated Julia set
    bmpOut(picture, "fractal.bmp");
    return 0;
}
