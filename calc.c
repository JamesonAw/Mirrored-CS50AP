// includes
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //checks for correct argc
    if (argc != 4) {
        printf("usage: ./calc <number> <operand> <number>\n");
        return 1;
    }

    //check if argv[2] is appropriate operand
    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != '/' && argv[2][0] != '%') {
        printf("Invalid Operand inputted. Re-enter input.");
        return 1;
    }

    //get nums from argv
    float firstNum = atof(argv[1]);
    float secondNum = atof(argv[3]);

    //get operand from argv
    string operandString = argv[2];
    char operandChar = operandString[0];

    //initialize result
    float result;
    int bigNum;

    //perform operation
    switch(operandChar) {
        case '+' :
            result = firstNum + secondNum;
            break;
        case '-' :
            result = firstNum - secondNum;
            break;
        case 'x' :
            result = firstNum * secondNum;
            break;
        case '/' :
            result = firstNum / secondNum;
            break;
        case '%':
            bigNum = (int)(firstNum / secondNum);
            result = firstNum - (secondNum * bigNum);
    }

    //print result
    printf("%.6f\n", result);
}