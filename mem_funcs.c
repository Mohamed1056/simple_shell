#include "shell.h"

/**
 * re_allocate - function to reallocate the memory
 * @mtr: the pointer to the function
 * @num: takes the old size
 * @bum: takes the new size
 * Return: void
*/

void *re_allocate(void *mtr, unsigned int num, unsigned int bum)
{
	char *ret;
	/*after decleration of the onlyy variable*/
	if (!mtr)
		return (malloc(bum));
	/*checking if bum exist or not*/
	if (!bum)
		return (free(mtr), NULL);
	/*checking if num is equal to bum or not*/
	if (bum == num)
		return (mtr);
	/*allocating the variable that we declared*/
	ret = malloc(bum);
	if(!ret)
		return (NULL);
	num = num < bum ? num : bum;
	while (num--)
		p[num] = ((char *)mtr)[num];
	free(mtr);
	return (ret);
}

/**
 * mem_set - function to find a charater in a string
 * @str: takes the input of the function
 * @d: takes the 2nd input for the function
 * @m: takes the 3rd input for the functio
 * Return: str
*/

char *mem_set(char *str, char d, unsigned int m)
{
	unsigned int x = 0;
	/*after decleration*/
	while (x < m)
	{
		str[x] = d;
		x++;
	}
	return (str);
}
