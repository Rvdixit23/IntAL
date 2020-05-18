#include"intal.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char* intal_add(const char *intal1, const char *intal2)
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
    const char* bigintal = len1 > len2 ? intal1 : intal2;
    const char* smallintal = len1 > len2 ? intal2 : intal1;
    // The answer
    char *result = (char *)malloc(sizeof(char) * (bigLen + 2));
    int resultIndex = bigLen; // Last index of answer exclude \0
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
        result[bigLen + 1] = '\0';
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
    char *result2 = (char *)malloc(sizeof(int) * (bigLen + 1));
    for (int i = 1; i <= bigLen; i++)
    {
        result2[i - 1] = result[i];
    }
    result2[bigLen] = '\0';
    free(result);
    return result2;
    
}

int intal_compare(const char *intal1, const char *intal2)
{
    /*
    Compare lengths
    If equal compare the digits until they aren't equal
    If all digits are equal, then return 0
    Else return accordingly
    */
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    if (len1 > len2)
    {
        return 1;
    }
    else if (len2 > len1)
    {
        return -1;
    }
    else
    {
        int lenCount = 0;
        while (lenCount < len1)
        {
            if (intal1[lenCount] > intal2[lenCount])
            {
                return 1;
            }
            else if(intal1[lenCount] < intal2[lenCount])
            {
                return -1;
            }
            lenCount++;
        }
        if (lenCount == len1)
        {
            return 0;
        }   
    }
    return 0;

}


char* intal_diff(const char *intal1, const char *intal2)
{
    /*
    Find the larger and smaller number
    Create an array of length of bigger number
    This will manage the carry and borrow
    Initialise to 0
    Go through the smaller number
        if larger than above digit
        then add 10 to borrow arr
        sub 1 from next place in borrow arr
        Add the carry and the digits
    Copy numbers from the big array
    Run a loop to check for trialing zeros
    Reallocate a new memory and copy the digits
    Free the old result
    Free the carry array
    Return the result
    */
    int whichIsLarger = intal_compare(intal1, intal2);
    const char *bigIntal;
    const char *smallIntal;
    if (whichIsLarger == 1)
    {
        bigIntal = intal1;
        smallIntal = intal2;
    }
    else if (whichIsLarger == -1)
    {
        bigIntal = intal2;
        smallIntal = intal1;
    }
    else
    {
        char *result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int bigLen = strlen(bigIntal);
    int smallLen = strlen(smallIntal);
    char *result = (char *)malloc(sizeof(char) * (bigLen + 1));
    result[bigLen] = '\0';
    int *carry = (int *)malloc(sizeof(int) * bigLen);
    for (int i = 0; i < bigLen; i++)
    {
        carry[i] = 0;
    }
    
    int tempCarryIndex;
    int currBig = bigLen - 1;
    // If the bigNo + carry is less than small no
    //  Go to next place, if greater than 0, carry of -1
    //  If equal to 0 then go to next place, until you encounter a non zero
    //  Add a -1 to the first non 0 location
    //  Transfer the carry over until the current point
    for (int currSml = smallLen - 1; currSml > -1; currSml--)
    {
        while (bigIntal[currBig] + carry[currBig]
         < smallIntal[currSml])
        {
            carry[currBig] = carry[currBig] + 10;
            carry[currBig - 1]--;
        }
        result[currBig] = carry[currBig] + bigIntal[currBig]
         - smallIntal[currSml] + 48;
        currBig--;
    }
    
    while (currBig > 0)
    {
        // Copy the result from the bigger number
        // Make sure the carry is handled
        while (bigIntal[currBig] + carry[currBig] <= 48)
        {
            carry[currBig] = carry[currBig] + 10;
            carry[currBig - 1]--;
        }
        result[currBig] = carry[currBig] + bigIntal[currBig];
        currBig--;
    }
    result[0] = carry[0] + bigIntal[0];

    
    // Create a new string
    // Without the trailing zeros of the older string
    int nonZeroIndex = 0;
    while (result[nonZeroIndex] == '0' && nonZeroIndex < bigLen)
    {
        nonZeroIndex++;
    }
    if (nonZeroIndex == 0)
    {
        // printf("Here\n");
        result[bigLen] = '\0';
        free(carry);
        return result;
    }
    
    char *finalRes = (char *)malloc(sizeof(char) * (bigLen - nonZeroIndex + 1));
    finalRes[bigLen - nonZeroIndex] = '\0';
    for (int i = 0; i < bigLen - nonZeroIndex; i++)
    {
        finalRes[i] = result[i + nonZeroIndex];
    }
    
    // printf("Intermediate Res : %s\n", finalRes);
    free(result);
    free(carry);
    return finalRes;

}
char* intal_multiply(const char *intal1, const char *intal2)
{
    return 0;
}
char* intal_mod(const char *intal1, const char *intal2)
{
    return 0;
}
char* intal_pow(const char* intal1, unsigned int n)
{
    return 0;
}
char* intal_gcd(const char *intal1, const char *intal2)
{
    return 0;
}
char* intal_fibonacci(unsigned int n)
{
    return 0;
    // REMOVE THIS LATER
    char *first = (char *)malloc(sizeof(char) * 2);
    first[1] = '\n';
    first[0] = '0';
    char *second = (char *)malloc(sizeof(char) * 2);
    second[1] = '\n';
    second[0] = '1';

    if (n == 1)
    {
        return first;
    }
    if (n == 2)
    {
        return second;
    }
    /*
    Convert first and second to const ints
        This isn't needed as the addition function is read only
        No need to make another const string just for this
    Pass them into the adder and store this pointer
    Make the old second into first
    Make the sum as second and repeat
    */
    for (int i = 3; i < n + 1; i++)
    {
        char *sum = intal_add(first, second);
        free(first);
        first = second;
        second = sum;
    }
    return second;
    
    
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
int intal_search(char **arr, int n, const char* key)
{
    return 0;
}
int intal_binsearch(char **arr, int n, const char* key)
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

