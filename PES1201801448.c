#include "intal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static char* reverse(char *str, int n)
{
    char temp;
	for(int i=0;i<n/2;i++)
	{
		temp=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=temp;
	}
   	str[n]='\0';
	return str;
}

static char *rem_zero(char *str)
{
    int count = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '0')
            count++;
        else
            break;
    }
    if (strlen(str) == i)
    {
        char *temp = (char *)malloc(sizeof(char) * 2);
        strcpy(temp, "0");
        free(str);
        return temp;
    }
    else
    {
        char *temp = (char *)malloc(sizeof(char) * (strlen(str) - count + 1));
        int j = 0;
        for (i = count; str[i] != '\0'; i++)
            temp[j++] = str[i];
        temp[j] = '\0';
        //free(str);
        return temp;
    }
}

char* intal_add(const char* intal1, const char* intal2)
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
        Reverse the string and insert a null in the right place
        Reverse the string again to obtain a trimmed version
    */
    
    char *a = (char*)malloc(sizeof(char) * 1001);
    char *b = (char*)malloc(sizeof(char) * 1001);
    strcpy(a, intal1);
    strcpy(b, intal2);
    if(strcmp("0", a) == 0)
    {
        free(a);
        return b;
    }
    if(strcmp("0", b) == 0)
    {
        free(b);
        return a;
    }

    if(strlen(a) > strlen(b))
    {
        strcpy(a, intal2);
        strcpy(b, intal1);
    }
    
    int l1 = strlen(a);
    int l2 = strlen(b);
    char *res = (char*)malloc(sizeof(char) * (l2 + 2));
    int carry = 0;
    int i, sum = 0, k = 0;
    for(i = l1 - 1; i >= 0; i--)
    {
        sum = (a[i] - '0') + b[i + l2 - l1] - '0' + carry;
        res[k++] = '0' + (sum % 10);
        carry = sum / 10;
    }
    for(i = l2 - l1 - 1; i >= 0; i--)
    {
        sum = (b[i] - '0') + carry;
        res[k++] = '0' + (sum % 10);
        carry = sum/10;
    }
    if(carry>0)
    {
        res[k++] = '0' + carry;
    }
    res[k] = '\0';
    res = reverse(res, strlen(res));
    free(a);
    free(b);
    return res;
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
            else if (intal1[lenCount] < intal2[lenCount])
            {
                return -1;
            }
            lenCount++;
        }
    }
    return 0;
}

char *intal_diff(const char *intal1, const char *intal2)
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
        while (bigIntal[currBig] + carry[currBig] < smallIntal[currSml])
        {
            carry[currBig] = carry[currBig] + 10;
            carry[currBig - 1]--;
        }
        result[currBig] = carry[currBig] + bigIntal[currBig] - smallIntal[currSml] + 48;
        currBig--;
    }

    if (currBig >= 0)
    {
        while (currBig > 0)
        {
            // Copy the result from the bigger number
            // Make sure the carry is handled
            while (bigIntal[currBig] + carry[currBig] < 48)
            {
                carry[currBig] = carry[currBig] + 10;
                carry[currBig - 1]--;
            }
            result[currBig] = carry[currBig] + bigIntal[currBig];
            currBig--;
        }
        result[0] = carry[0] + bigIntal[0];
    }

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

char *intal_multiply(const char *intal1, const char *intal2)
{
    if (intal1 == NULL || intal2 == NULL)
        return NULL;
    if (strcmp("0", intal1) == 0 || strcmp("0", intal2) == 0)
    {
        char *result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    char *a = (char *)malloc(1001 * sizeof(char));
    char *b = (char *)malloc(1001 * sizeof(char));
    strcpy(a, intal1);
    strcpy(b, intal2);
    a = rem_zero(a);
    b = rem_zero(b);

    if (strcmp("1", a) == 0)
        return b;
    if (strcmp("1", b) == 0)
        return a;
    int l = l1 + l2;
    int r = l - 1;
    char *ans = malloc(sizeof(char) * (l + 1));
    int i, j, sum;
    for (i = 0; i < l; i++)
        ans[i] = '0';
    ans[i] = '\0';
    for (i = l2 - 1; i >= 0; i--)
    {
        int carry = 0;
        int offset = 0;
        for (j = l1 - 1; j >= 0; j--)
        {
            sum = (a[j] - '0') * (b[i] - '0') + carry + (ans[r - offset] - '0');
            carry = sum / 10;
            ans[r - offset] = sum % 10 + '0';
            offset++;
        }
        if (carry > 0)
            ans[r - offset] = '0' + carry;
        r--;
    }
    ans = rem_zero(ans);
    free(a);
    free(b);
    return ans;
}

char *intal_mod(const char *intal1, const char *intal2)
{
    /*
    If numbers are equal return 0
    If the second number is greater, return a copy of the small number
    If the second number is smaller, then calculate the value
        Add as many zeros as possible to the end of the divisor
        Subtract from the dividend ,until the value left over
            is lesser than the divisor
    */
    int comparison = intal_compare(intal1, intal2);
    if (comparison == 0)
    {
        char *result = (char *)malloc(sizeof(char) * 2);
        strcpy(result, "0");
        return result;
    }
    else if (comparison == -1)
    {
        char *result = (char *)malloc(sizeof(char) * (strlen(intal1) + 1));
        strcpy(result, intal1);
        return result;
    }
    else
    {
        int dividendLenCurrent = strlen(intal1);
        int divisorLen = strlen(intal2);
        char *current = (char *)malloc(sizeof(char) * (dividendLenCurrent + 1));
        char *tempDivisor = (char *)malloc(sizeof(char) * (dividendLenCurrent + 1));
        char *tempResult;
        strcpy(current, intal1);
        int i;
        while (intal_compare(current, intal2) == 1)
        {
            // printf("Current : %s", current);
            dividendLenCurrent = strlen(current);
            strcpy(tempDivisor, intal2);
            if (dividendLenCurrent - divisorLen >= 1)
            {
                int i = 0;
                for (i = 0; i < dividendLenCurrent - divisorLen - 1; i++)
                {
                    tempDivisor[divisorLen + i] = '0';
                }
                tempDivisor[divisorLen + i] = '\0';
                tempResult = intal_multiply(tempDivisor, "10");
                if (intal_compare(tempResult, current) == -1)
                {
                    tempDivisor[divisorLen + i] = '0';
                    i++;
                    tempDivisor[divisorLen + i] = '\0';
                }
                free(tempResult);
            }
            tempResult = intal_diff(current, tempDivisor);
            free(current);
            current = tempResult;
        }
        if (intal_compare(current, intal2) == 0)
        {
            strcpy(current, "0");
        }
        
        free(tempDivisor);
        return current;
    }

    // Add the zeros here
    // for (i = 0; i < dividendLenCurrent - divisorLen; i++)
    // {
    //     tempDivisor[i + divisorLen] = '0';
    // }
    // // Check if adding another zero will make it exceed
    // // if (intal_compare(intal_multiply(tempDivisor, "10"), current) < 1)
    // // {
    // //     tempDivisor[i++] = '0';
    // // }
    // tempDivisor[i] = '\0';
    // tempResult = intal_diff(current, tempDivisor);
    // free(current);
    // current = tempResult;
    // int p = strlen(intal2);
    // int stop = strlen(intal1);
    // char *current = (char *)malloc(sizeof(char) * (strlen(intal2) + 2));
    // for (int i = 0; i < p; i++)
    // {
    //     current[i] = intal1[i];
    // }
    // current[p] = '\0';

    // do
    // {
    //     if (intal_compare(current, intal2) == -1 && p < stop)
    //     {
    //         int len = strlen(current);
    //         if (strcmp(current, "0") == 0)
    //         {
    //             len = 0;
    //         }
    //         current[len] = intal1[p];
    //         current[len + 1] = '\0';
    //         p++;
    //     }

    //     if (intal_compare(current, intal2) != -1)
    //     {
    //         char *result = intal_diff(current, intal2);
    //         while (intal_compare(result, intal2) > -1)
    //         {
    //             char *temp = result;
    //             result = intal_diff(result, intal2);
    //             free(temp);
    //         }
    //         strcpy(current, result);
    //         free(result);
    //     }

    // } while (p < stop);
    // current = realloc(current, (strlen(current) + 1) * sizeof(char));
    // current[strlen(current) + 1] = '\0';
    // return current;
}

char *intal_pow(const char *intal1, unsigned int n)
{
    if (n == 0 || intal_compare(intal1, "0") == 0)
    {
        char *zeroAns = (char *)malloc(sizeof(char) * 2);
        zeroAns[0] = '1';
        zeroAns[1] = '\0';
        return zeroAns;
    }
    else if (n == 1)
    {
        return intal_multiply("1", intal1);
    }
    int totalPower = 0;
    int currentInnerLoopPower = 0;
    char *innerLoopValue;
    char *resultHolder;
    char *totalValue = intal_multiply("1", "1");
    while (totalPower != n)
    {
        innerLoopValue = intal_multiply(intal1, "1");
        currentInnerLoopPower = 1;

        while (currentInnerLoopPower * 2 <= n - totalPower)
        {
            resultHolder = intal_multiply(innerLoopValue,
                                          innerLoopValue);
            currentInnerLoopPower = currentInnerLoopPower * 2;
            free(innerLoopValue);
            innerLoopValue = resultHolder;
        }
        resultHolder = intal_multiply(totalValue, innerLoopValue);
        free(totalValue);
        free(innerLoopValue);
        totalValue = resultHolder;

        totalPower = totalPower + currentInnerLoopPower;
        // printf("After inner loop %s\nCurrent Power is %d\nInner Loop power is %d", totalValue, totalPower, currentInnerLoopPower);
    }

    return totalValue;
}

char *intal_gcd(const char *intal1, const char *intal2)
{


    if (intal2[0] == 48)
    {
        char *newRes = (char *)malloc(sizeof(char) * (strlen(intal1) + 1));
        strcpy(newRes, intal1);
        return newRes;
    }

    if (intal1[0] == 48)
    {
        char *newRes = (char *)malloc(sizeof(char) * (strlen(intal1) + 1));
        strcpy(newRes, intal2);
        return newRes;
    }
    

    else
    {
        char *tempRes = intal_mod(intal1, intal2);
        char *finalRes = intal_gcd(intal2, tempRes);
        free(tempRes);
        return finalRes;
    }
}

char *intal_fibonacci(unsigned int n)
{
    char *first = (char *)malloc(sizeof(char) * 2);
    first[1] = '\0';
    first[0] = '0';
    char *second = (char *)malloc(sizeof(char) * 2);
    second[1] = '\0';
    second[0] = '1';

    if (n == 0)
    {
        return first;
    }
    if (n == 1)
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
    for (int i = 2; i < n + 1; i++)
    {
        char *sum = intal_add(first, second);
        free(first);
        // printf("%s\n", sum);
        first = second;
        second = sum;
    }
    free(first);
    return second;
}

char *intal_factorial(unsigned int n)
{
    char *result = (char *)malloc(sizeof(char) * 2);
    char *multiplier = (char *)malloc(sizeof(char) * 1001);
    strcpy(result, "1");

    if (n <= 1)
    {
        return result;
    }
    else
    {
        char *tempResult;
        for (int i = 2; i < n + 1; i++)
        {
            sprintf(multiplier, "%d", i);
            tempResult = intal_multiply(result, multiplier);
            free(result);
            result = tempResult;
        }
        free(multiplier);
        return result;
    }
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
  int r = k > n - k ? n - k : k;
  char **c = (char **)malloc((r + 1) * sizeof(char *));
  for (int i = 0; i < r + 1; ++i)
  {
        c[i] = (char *)malloc(2 * sizeof(char));
        // c[i][0] = '0';
        // c[i][1] = '\0';
        strcpy(c[i], "0");
  }

  c[0][0] = '1';
  

  for (int i = 1; i < n + 1; ++i)
    {
        int j = (i > r) ? r : i;
        while (j > 0)
        {
            char *tmp = c[j];
            c[j] = intal_add(c[j], c[j - 1]);
            free(tmp);
            --j;
        }
    }   
    char *result = (char *)malloc((strlen(c[r]) + 1) * sizeof(char));
    strcpy(result, c[r]);

    for (int i = 0; i < r + 1; ++i)
    {
        free(c[i]);
    }
    free(c);
    return result;

}

int intal_max(char **arr, int n)
    {
        int maxIndex = 0;
        for (int i = 1; i < n; i++)
        {
            if (intal_compare(arr[maxIndex], arr[i]) == -1)
            {
                maxIndex = i;
            }
        }
        return maxIndex;
    }

int intal_min(char **arr, int n)
    {
        int minIndex = 0;
        for (int i = 1; i < n; i++)
        {
            if (intal_compare(arr[minIndex], arr[i]) == 1)
            {
                minIndex = i;
            }
        }
        return minIndex;
    }

int intal_search(char **arr, int n, const char *key)
    {
        int index;
        for (index = 0; index < n; index++)
        {
            if (intal_compare(arr[index], key) == 0)
            {
                return index;
            }
        }
        return -1;
    }

static int partition(char **arr, int low, int high)
    {
        char *pivot = (char *)malloc(sizeof(char) * 1001);
        strcpy(pivot, arr[high]);
        int i = low - 1;
        char *temp;
        for (int j = low; j < high; j++)
        {
            if (intal_compare(arr[j], pivot) == -1)
            {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        free(pivot);
        return i + 1;
    }

static void quickSort(char **arr, int low, int high)
    {
        if (low < high)
        {
            int part = partition(arr, low, high);
            quickSort(arr, low, part - 1);
            quickSort(arr, part + 1, high);
        }
    }

void intal_sort(char **arr, int n)
    {
        if (n == 1)
        {
            return;
        }
        quickSort(arr, 0, n - 1);
    }

int intal_binsearch(char **arr, int n, const char *key)
    {
        intal_sort(arr, n);
        int low = 0;
        int high = n - 1;
        int result = -1;
        int mid;
        int comparison;
        while (high >= low)
        {
            mid = (high + low) / 2;
            comparison = intal_compare(arr[mid], key);
            if (comparison == 0)
            {
                result = mid;
                high = mid - 1;
            }
            else if (comparison == 1)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return result;
    }

char *coin_row_problem(char **arr, int n)
    {
        /*
    Dynamic programming using a sliding window
    Bottom up approach
    Maintain highest value for n coins and n - 1 coins
    If the sum of the n + 1 th coin and n - 1th coin
    Is greater than the best value of the nth coin
    Soln(n + 1) = sum
    Soln(n) Remains as is
    If less than best value of nth coin
    Soln(n + 1) = Soln(n)
    Soln(n)  remains as is
    Now n + 1 becomes n and n becomes n - 1
    Process is repeated until the entire array is covered
    */
        char *ppval = (char *)malloc(sizeof(char) * 2);
        ppval[0] = '0';
        ppval[1] = '\0';

        if (n == 0)
        {
            return ppval;
        }

        char *pval = (char *)malloc(sizeof(char) * strlen(arr[0]));
        strcpy(pval, arr[0]);

        if (n == 1)
        {
            free(ppval);
            return pval;
        }

        char *tempRes;
        int index = 1;
        int compare;
        while (index < n)
        {
            tempRes = intal_add(ppval, arr[index]);
            compare = intal_compare(tempRes, pval);
            free(ppval);
            if (compare == 1)
            {
                ppval = pval;
                pval = tempRes;
            }
            else if (compare == -1)
            {
                free(tempRes);
                ppval = intal_multiply(pval, "1");
            }
            else
            {
                ppval = pval;
                pval = tempRes;
            }

            index++;
        }
        free(ppval);
        return pval;
    }
