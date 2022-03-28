#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Could consider creating a struct (or data type) that is like a char, but only allows 0 to 9.
 * There must be *some* way of doing that, so that this data type would be smaller than a string,
 * since, for each char we don't need 8 bits like we do with a string, but only 4. Compared to
 * an int, it'll be smaller for a lot, but then bigger for a lot too. An int is always 4 bytes
 * or 32 bits, but this data type would only reach 4 bytes when it's 8 digits long.
 */


/**
 * A function that takes two strings and returns the sum of the two strings.
 */
static char* _add(char* str1, char* str2)
{
  char *a, *b, *c;

  // Set the longest string to a, and the shortest to b.
  if (strlen(str2) > strlen(str1))
  {
    char* a = strrev(str2);
    char* b = strrev(str1);
  }
  else
  {
    char* a = strrev(str1);
    char* b = strrev(str2);
  }

  // Get the difference in length between the two strings.
  int lengthDiff = strlen(a) - strlen(b);

  // Add the two string integers together.
  int carry = 0;
  int sum, i;
  char *t;
  for (i = 0; i < strlen(b); i++)
  {
    sum = atoi(a[i]) + atoi(b[i]) + carry;
    if (sum > 9)
    {
      carry = 1;
      sum = sum - 10;
    }
    else
    {
      carry = 0;
    }

    sprintf(t, "%c", sum);
    strncat(c, &t, 1);
  }

  if (carry > 0)
  {
    if (lengthDiff > 0)
    {
      while (carry > 0 && i < strlen(a))
      {
        sum = atoi(a[i]) + carry;
        if (sum > 9)
        {
          carry = 1;
          sum = sum - 10;
        }
        else
        {
          carry = 0;
        }

        sprintf(t, "%c", sum);
        strncat(c, &t, 1);
        i++;
      }

      if (carry > 0)
      {
        sprintf(t, "%c", carry);
        strncat(c, &t, 1);
      }

      if (i < strlen(a))
      {
        while (i < strlen(a))
        {
          strncat(c, a[i++], 1);
        }
      }
    }
    else
    {
      // If there is still something being carried over, but the two strings are the same length,
      // then we simply add the carried vallue to the end of the string.

      sprintf(t, "%c", carry);
      strncat(c, &t, 1);
    }
  }

  return strrev(c);
}

/**
 * TODO: A function that takes two positive integer strings and subtracts string b from string a.
 * TODO: Expand this to enable subtracting either a positive decimal or integer from another.
 */
static char* _subtract(char* a, char* b)
{
  return "...";
}

char* strmath_sum(char* a, char* b)
{
  if (a[0] == '-' && b[0] == '-')
  {
    char* unsignedA = a + 1; // This sets unsignedA[0] = a[1], and so on;
    char* unsignedB = b + 1;
    char* sum = _add(unsignedA, unsignedB);
    char* c = (char*) malloc(strlen(sum) + 1);
    c[0] = '-';
    strcat(c,sum);

    return c;
  }
  else if (a[0] == '-')
  {
    //
  }
  else if (b[0] == '-')
  {
    //
  }
  else
  {
    //
  }

  return "fish";
}



// Contemplate having an all-encompasing string math function. Where you submit a string of math, like "-5^3+4*9^(1/2)" and it returns the correct answer as a string (in this example, "-113").

int main(int argc, char *argv[])
{
  char *a, *b, *c;

  printf("test sum of two negative integers\n");
  a = "-4";
  b = "-5";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  printf("test sum of two positive integers\n");
  a = "7";
  b = "5";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  printf("test sum of a positive integer with a negative integer of lesser absolute value, with the negative integer first\n");
  a = "-4";
  b = "5";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  printf("test sum of a positive integer with a negative integer of greater absolute value, with the negative integer first\n");
  a = "-4";
  b = "3";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  printf("test sum of a positive integer with a negative integer of lesser absolute value, with the positive integer first\n");
  a = "4";
  b = "-3";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  printf("test sum of a positive integer with a negative integer of greater absolute value, with the positive integer first\n");
  a = "4";
  b = "-5";
  c = strmath_sum(a, b);
  printf("(%s) + (%s) = %s\n", a, b, c);

  return 0;
}
