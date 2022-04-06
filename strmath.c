#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * TODO: consider creating a struct (or data type) that is like a char, but only allows 0 to 9.
 * There must be *some* way of doing that, so that this data type would be smaller than a string,
 * since, for each char we don't need 8 bits like we do with a string, but only 4. Compared to
 * an int, it'll be smaller for a lot, but then bigger for a lot too. An int is always 4 bytes
 * or 32 bits, but this data type would only reach 4 bytes when it's 8 digits long.
 */

/**
 * TODO: Contemplate having an all-encompasing string math function. Where you submit a string of math, like "-5^3+4*9^(1/2)" and it returns the correct answer as a string (in this example, "-113").
 */

/**
 * TODO: Free variables that have lost their usefulness with `free(var);`
 */

static char* _abs(char* a) {
	if (a[0] == '-')
		return a + 1;

	return a;
}

static char* _negate(char* a)
{
	if (a[0] == '-')
	{
		return a + 1;
	}
	else
	{
		a = _rev(a);
		strncat(a, "-", 1);
		a = _rev(a);
	}
}

/**
 * This only exists because apparently `strrev` is not available in my version (most versions?) of C.
 */
static char* _rev(char *str)
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

static int _char_to_int(char a)
{
	return a - '0';
}

/**
 * Determine whether a is greater than, equal to, or less than b.
 *
 * @param a The first number to compare.
 * @param b The second number to compare.
 * @return 1 if abs(a) > abs(b), 0 if abs(a) == abs(b), and -1 if abs(a) < abs(b).
 */
static int _compare_abs_value(char* a, char* b)
{
	int a_size = strlen(_abs(a));
	int b_size = strlen(_abs(b));

	if (a_size > b_size)
		return 1;
	else if (a_size < b_size)
		return -1;

	// If neither string of characters is greater than the other, then they must be equal in length, and the characters themselves dictate which is larger.
	return strcmp(_abs(a), _abs(b));
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
		a = _rev(str2);
		b = _rev(str1);
		lengthDiff = strlen(str2) - strlen(str1);
		c = malloc(strlen(str2) + 1);
	}
	else
	{
		a = _rev(str1);
		b = _rev(str2);
		lengthDiff = strlen(str1) - strlen(str2);
		c = malloc(strlen(str1) + 1);
	}

	// Add the two string integers together.
	int carry = 0;
	int sum, i;
	char *t = malloc(1);
	for (i = 0; i < strlen(b); i++)
	{
		sum = _char_to_int(a[i]) + _char_to_int(b[i]) + carry;
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
				sum = _char_to_int(a[i]) + carry;
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

	return _rev(c);
}

/**
 * A function that subtracts str1 (which is always negative) from string str2.
 * TODO: Expand this to support decimals and integers together.
 *
 * @param str1 A negative number as a string (without the negative sign).
 * @param str2 A positive number, as a string, from which the negative number is to be subtracted.
 */
static char* _subtract_a_from_b(char* str1, char* str2)
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
		a = _rev(str1);
		b = _rev(str2);
		c = malloc(strlen(str1) + 1);
		lengthDiff = strlen(str1) - strlen(str2);
		str1_was_longest = true;
	}
	else
	{
		a = _rev(str2);
		b = _rev(str1);
		c = malloc(strlen(str2));
		lengthDiff = strlen(str2) - strlen(str1);
	}

	// Section: The subtracting part.
	int borrow = 0;
	int sum, i;
	char *t = malloc(1);
	for (i = 0; i < strlen(b); i++)
	{
		sum = _char_to_int(a[i]) - _char_to_int(b[i]) - borrow;
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
			sum = _char_to_int(a[i++]) - borrow;
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

		while (i < strlen(a))
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
	c = _rev(c);
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
		c = _negate(c);
	}

	return c;
}

static char* _multiply(char* a, char* b)
{
	// TODO: Impelement.
}

/**
 * A function that multiplies two numbers.
 *
 * @param char* a A number as a string.
 * @param char* b A number as a string.
 * @return char* The sum of the two numbers as a string.
 */
char* str_sum(char* a, char* b)
{
	if (a[0] == '-' && b[0] == '-')
	{
		// Remove the negative sign from both strings.
		char* sum = _add(_abs(a), _abs(b));
		char* c = (char*) malloc(strlen(sum) + 1);
		c[0] = '-';
		strcat(c,sum);

		return c;
	}
	else if (a[0] == '-')
	{
		return _subtract_a_from_b(_abs(a), b);
	}
	else if (b[0] == '-')
	{
		return _subtract_a_from_b(_abs(b), a);
	}

	return _add(a, b);
}

char* str_multiply(char* a, char* b)
{
	char* c = _multiply(_abs(a), _abs(b));

	if ((a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-'))
	{
		return _negate(c);
	}

	return c;
}

char* str_calculate(char* str)
{
	// Step 1: Extract substrings within parentheses, and run str_calculate on them.
	// Step 2: Calculate Exponents
	// Step 3: Calculate Multiplication and Division
	// Step 4: Calculate Addition and Subtraction
	return "not implemented";
}

int main(int argc, char *argv[])
{
	printf("(-4) + 202 = %s\n", str_sum("-4", "202"));
	printf("(-4) + (-208) = %s\n", str_sum("-4", "-208"));
	printf("4 + (-202) = %s\n", str_sum("4", "-202"));
	printf("4 + 208 = %s\n", str_sum("4", "208"));
	printf("%s\n", str_calculate("4+3/2*(2+3)"));
	return 0;
}
