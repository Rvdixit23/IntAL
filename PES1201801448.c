#include"intal.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char *intal_add(char *intal1, char *intal2)
{
    /*
    Find the length of each intal
    Distinguish the bigger and smaller intals
    The length of the sum intal is at most
    The greater length among the two + 1
    Start from the units place of smaller intal
        Add the corresponding place until the smaller length
        Carry generated if digit total greater than 10
        Digit total is total % 10
        Convert to string and add to the last place of result
    Execute addition until the carry is zero or capacity is exceeded
    Then copy from the biggerintal as it
    Remove the trailing zeros
    */
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    // The length of the bigger intal
    int bigLen = len1 > len2 ? len1 : len2;
    int smallLen = len1 > len2 ? len2 : len1;
    // The intals with big and small determined
    char* bigintal = len1 > len2 ? intal1 : intal2;
    char* smallintal = len1 > len2 ? intal2 : intal1;
    // The answer
    char *result = (char *)malloc(sizeof(char) * (bigLen + 1));
    int resultIndex = bigLen; // Last index of answer
    // Variables for step by step addition
    int carry = 0;
    int digitTotal;
    int digit1;
    int digit2;
    for (int i = smallLen - 1; i >= 0; i--)
    {
        digit1 = smallintal[i] - 48;
        digit2 = bigintal[resultIndex - 1] - 48;
        digitTotal = digit1 + digit2 + carry;
        carry = digitTotal >= 10 ? 1 : 0;
        // Converting to interger by adding ascii value of 0
        result[resultIndex--] = (digitTotal % 10) + 48;
    }
    while (resultIndex > 0 && carry == 1) //Until carry is cleared
    {
        // Result index remains > 0 as long as 
        digitTotal = bigintal[resultIndex - 1] - 48 + carry;
        carry = digitTotal >= 10 ? 1 : 0;

        result[resultIndex] = carry + bigintal[(resultIndex) - 1] + 48;
        resultIndex--;
    }

    /*
    Scenario 1
    There is no carry into last place no trailing digit
    Scenario 2 
    Make the last digit 1 if there is carry at the end
    */

    if (carry == 1 && resultIndex == 0)
    {
        result[0] = 49;
        return result;
    }
    else if (carry == 0)
    {
        while (resultIndex > 0)
        {
            result[resultIndex] = bigintal[(resultIndex) - 1];
            resultIndex--;
        }
    }
    // To return a valid freeable pointer
    char *result2 = (char *)malloc(sizeof(int) * bigLen);
    for (int i = 1; i <= bigLen; i++)
    {
        result2[i - 1] = result[i];
    }
    free(result);
    return result2;
    
}

int intal_compare(char *intal1, char *intal2)
{
    return 0;
}
char* intal_diff(char* intal1, char* intal2)
{
    return 0;
}
char* intal_multiply(char* intal1, char* intal2)
{
    return 0;
}
char* intal_mod(char* intal1, char* intal2)
{
    return 0;
}
char* intal_pow(char* intal1, unsigned int n)
{
    return 0;
}
char* intal_gcd(char* intal1, char* intal2)
{
    return 0;
}
char* intal_fibonacci(unsigned int n)
{
    char *first = "0";
    char *second = "1";
    if (n == 0)
    {
        return first;
    }
    if (n == 1)
    {
        return second;
    }
    return '1';
    
}
char* intal_factorial(unsigned int n)
{
    return 0;
}
char* intal_bincoeff(unsigned int n, unsigned int k)
{
    return 0;
}
int intal_max(char **arr, int n)
{
    return 0;
}
int intal_min(char **arr, int n)
{
    return 0;
}
int intal_search(char **arr, int n, char* key)
{
    return 0;
}
int intal_binsearch(char **arr, int n, char* key)
{
    return 0;
}
void intal_sort(char **arr, int n)
{
    // return 0;
    ;
}
char* coin_row_problem(char **arr, int n)
{
    return 0;
}
