#include "main.h"

/**
 * print_unsigned - Prints an unsigned number.
 * @types: List of arguments containing the format specifier and data.
 * @buffer: Buffer array to handle print output.
 * @flags: Integer representing active formatting flags.
 * @width: Width of the unsigned number.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation.
 * @types: List of arguments containing the format specifier and data.
 * @buffer: Buffer array to handle print output.
 * @flags: Integer representing active formatting flags.
 * @width: Width of the octal number.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation.
 * @types: List of arguments containing the format specifier and data.
 * @buffer: Buffer array to handle print output.
 * @flags: Integer representing active formatting flags.
 * @width: Width of the hexadecimal number.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in uppercase hexadecimal format.
 * @types: List of arguments containing the format specifier and data.
 * @buffer: Buffer array for print output.
 * @flags: Integer representing active formatting flags.
 * @width: Width of the hexadecimal number.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper case.
 * @types: Arguments containing the format specifier and data.
 * @map_to: Array of values to map the number to (either lower or upper case).
 * @buffer: Buffer array for print output.
 * @flags: Integer representing active formatting flags.
 * @flag_ch: Calculates active flags.
 * @width: Width of the hexadecimal number.
 * @precision: Precision specification.
 * @size: Size specifier (not used for this function).
 * Return: Number of characters printed.
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
