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
 * Adds two positive integers together.
 * TODO: Expand this to allow both integers and decimal numbers to be added together.
 */
static char* _add(char* str1, char* str2)
{
  char *a, *b, *c;
  int lengthDiff;

  if (strlen(str2) > strlen(str1))
  {
    a = str2;
    b = str1;
    lengthDiff = strlen(b) - strlen(a);
  }
  else
  {
    a = str1;
    b = str2;
    lengthDiff = strlen(a) - strlen(b);
  }

  int carry = 0;
  int sum;
  char *temp[strlen(a)];
  for (int i = strlen(a)-1; i >= lengthDiff; i--)
  {
    // TODO: This DOESN'T WORK. If a is longer than b, then this just adds the first strlen(b) digits of a to b. Not good math.
    sum = atoi(a[i]) + atoi(b[i-lengthDiff]) + carry;
    carry = 0;
    if (sum > 9)
    {
      carry = 1;
      sum -= 10;
    }
    sprintf(t,"%d",sum);
    temp[i] = t[0];
  }
  // TODO: Handle when i == lengthDiff is reached (i.e. only the carryOver and digits of a that are greater than the length of b remain).

  if (lengthDiff > 0)
  {
    char *c;
    if (carry > 0)
    {
    }
    else
    {
      for (int i = 0; i < lengthDiff; i++)
      {
        c[i] = a[i];
      }
    }
    strcat(c,temp);
  }
  else if (carry > 0)
  {
//    char* c = (char*) malloc(strlen(a) + 1);
    char c[0] = '1';
    strcat(c,temp);
  }

  //
  return c;
}

/**
 * Subtracts positive integer b from positive integer a.
 * TODO: Expand this to enable subtracting either a positive decimal or integer from another.
 */
static char* _subtract(char* a, char* b)
{
  //
  return "123456789";
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
