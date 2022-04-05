#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Could consider creating a struct (or data type) that is like a char, but only allows 0 to 9.
 * There must be *some* way of doing that, so that this data type would be smaller than a string,
 * since, for each char we don't need 8 bits like we do with a string, but only 4. Compared to
 * an int, it'll be smaller for a lot, but then bigger for a lot too. An int is always 4 bytes
 * or 32 bits, but this data type would only reach 4 bytes when it's 8 digits long.
 */

/**
 * TODO: Free variables that have lost their usefulness with `free(var);`
 */

/**
 * This only exists because apparently `strrev` is not available in my version (most versions?) of C.
 */
char* strrev(char *str)
{
	if (!str || ! *str)
		return str;

	char *newstr = malloc(strlen(str));
	int i = strlen(str) - 1;

	while (i >= 0)
	{
		newstr = strncat(newstr, &str[i--], 1);
	}

	return newstr;
}

static int _compare_abs_value(const char *a, const char *b)
{
	int a_size = strlen(a);
	int b_size = strlen(b);

	if (a_size > b_size)
		return 1;
	else if (a_size < b_size)
		return -1;

	// If neither string of characters is greater than the other, then they must be equal in length, and the characters themselves dictate which is larger.
	return strcmp(a, b);
}

/**
 * A function that takes two strings and returns the sum of the two strings.
 * TODO: Expand this to support decimals and integers together.
 */
static char* _add(char* str1, char* str2)
{
	char *a, *b, *c;
	int lengthDiff;

	// Set the longest string to a, and the shortest to b.
	if (strlen(str2) > strlen(str1))
	{
		a = strrev(str2);
		b = strrev(str1);
		lengthDiff = strlen(str2) - strlen(str1);
		c = malloc(strlen(str2) + 1);
	}
	else
	{
		a = strrev(str1);
		b = strrev(str2);
		lengthDiff = strlen(str1) - strlen(str2);
		c = malloc(strlen(str1) + 1);
	}

	// Add the two string integers together.
	int carry = 0;
	int sum, i;
	char *t = malloc(1);
	char ca, cb;
	int ia, ib;
	for (i = 0; i < strlen(b); i++)
	{
		ca = a[i];
		cb = b[i];
		ia = ca - '0'; // Converts the character to an integer.
		ib = cb - '0';
		sum = ia + ib + carry;
		if (sum > 9)
		{
			carry = 1;
			sum = sum - 10;
		}
		else
		{
			carry = 0;
		}

		sprintf(t, "%d", sum);
		strncat(c, t, 1);
	}

	if (carry > 0)
	{
		if (lengthDiff > 0)
		{
			while (carry > 0 && i < strlen(a))
			{
				ca = a[i];
				ia = ca - '0';
				sum = ia + carry;
				if (sum > 9)
				{
					carry = 1;
					sum = sum - 10;
				}
				else
				{
					carry = 0;
				}

				sprintf(t, "%d", sum);
				strncat(c, t, 1);
				i++;
			}

			if (carry > 0)
			{
				sprintf(t, "%d", carry);
				strncat(c, t, 1);
			}

			if (i < strlen(a))
			{
				while (i < strlen(a))
				{
					strncat(c, &a[i++], 1);
				}
			}
		}
		else
		{
			// If there is still something being carried over, but the two strings are the same length,
			// then we simply add the carried value to the end of the string.
			sprintf(t, "%d", carry);
			strncat(c, t, 1);
		}
	}
	else
	{
		// If there is no risidual carry-over, then the rest of the string a is added to the end of c.
		if (lengthDiff > 0)
		{
			while (i < strlen(a))
			{
				strncat(c, &a[i++], 1);
			}
		}
	}

	return strrev(c);
}

/**
 * A function that subtracts str1 (which is always negative) from string str2.
 * TODO: Expand this to support decimals and integers together.
 *
 * @param str1 A negative number as a string (without the negative sign).
 * @param str2 A positive number, as a string, from which the negative number is to be subtracted.
 */
static char* _subtract(char* str1, char* str2)
{
	// If the values are the same, then subtracting one from the other will result in 0.
	if (str1 == str2)
	{
		return "0";
	}

	char *a, *b, *c;
	int lengthDiff;
	bool str1_was_longest = false;

	if (_compare_abs_value(str1, str2) > 0)
	{
		a = strrev(str1);
		b = strrev(str2);
		c = malloc(strlen(str1) + 1);
		lengthDiff = strlen(str1) - strlen(str2);
		str1_was_longest = true;
	}
	else
	{
		a = strrev(str2);
		b = strrev(str1);
		c = malloc(strlen(str2));
		lengthDiff = strlen(str2) - strlen(str1);
	}

	// Section: The subtracting part.
	int borrow = 0;
	int sum, i;
	char *t = malloc(1);
	char ca, cb;
	int ia, ib;
	for (i = 0; i < strlen(b); i++)
	{
		ca = a[i];
		cb = b[i];
		ia = ca - '0';
		ib = cb - '0';
		sum = ia - ib - borrow;
		if (sum < 0)
		{
			sum = sum + 10;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}
		sprintf(t, "%d", sum);
		strncat(c, t, 1);
	}
	if (borrow > 0)
	{
		// Fortunately, with how we've laid this out, the borrow will not be > 0 while lengthDiff is /> 0
		while (borrow > 0)
		{
			ca = a[i++];
			ia = ca - '0';
			sum = ia - borrow;
			if (sum < 0)
			{
				sum = sum + 10;
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
			sprintf(t, "%d", sum);
			strncat(c, t, 1);
		}

		while (i < strlen(a) - 1)
		{
			strncat(c, &a[i++], 1);
		}
	}
	else
	{
		// If there was no risidual borrow-over, then the rest of the string a is added to the end of c.
		if (lengthDiff > 0)
		{
			while (i < strlen(a))
			{
				strncat(c, &a[i++], 1);
			}
		}
	}
	// END Section: The subtracting part.

	// Remove leading zeros.
	c = strrev(c);
	i = 0;
	while (c[i] == '0')
	{
		i++;
	}
	if (i > 0)
	{
		c = &c[i];
	}

	if (str1_was_longest)
	{
		// Add a '-' to the begining of the string (by adding it to the end before reversing the string).
		c = strrev(c);
		strncat(c, "-", 1);
		c = strrev(c);
	}

	return c;
}

char* strmath_sum(char* a, char* b)
{
	if (a[0] == '-' && b[0] == '-')
	{
		// If both numbers are negative, this is easy because it's still addition.
		char* unsignedA = a + 1; // This sets unsignedA[0] = a[1], and so on (ex. if a is -23, unsignedA is 23).
		char* unsignedB = b + 1;
		char* sum = _add(unsignedA, unsignedB);
		char* c = (char*) malloc(strlen(sum) + 1);
		c[0] = '-';
		strcat(c,sum);

		return c;
	}
	else if (a[0] == '-')
	{
		// This is less easy because it's actual subtraction. Let's pass it off.
		// But not without inverting `a`, which is negative, to positive.
		// TODO: Figure out a more abstracted/universal way of doing this.
		char* unsignedA = a + 1;
		return _subtract(unsignedA, b);
	}
	else if (b[0] == '-')
	{
		// This is also easy because I'm assuming I've solved the previous case.
		return strmath_sum(b, a);
	}

	return _add(a, b);
}


// Contemplate having an all-encompasing string math function. Where you submit a string of math, like "-5^3+4*9^(1/2)" and it returns the correct answer as a string (in this example, "-113").

int main(int argc, char *argv[])
{
	char *a, *b, *c;

	printf("test sum of two positive integers\n");
	a = "1000";
	b = "-477";
	c = strmath_sum(a, b);
	printf("%s + (%s) = %s\n", a, b, c);

	return 0;
}
