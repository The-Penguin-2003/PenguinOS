/* PenguinOS String Manipulation Functions */

#include <string.h>

int32_t strlen(int8_t* str)
{
	int32_t len = 0;

	while (*str++)
	{
		len++;
	}

	return len;
}
