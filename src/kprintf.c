/* PenguinOS printf() Implementation */

#include <vga.h>
#include <kprintf.h>

#define args_list char *
#define _arg_stack_size(type) (((sizeof(type)-1)/sizeof(int)+1)*sizeof(int))
#define args_start(ap, fmt) do { ap = (char*)((unsigned int)&fmt + _arg_stack_size(&fmt)); } while (0)
#define args_end(ap)
#define args_next(ap, type) (((type*)(ap+=_arg_stack_size(type)))[-1])

static int8_t buf[1024] = {-1};
static int32_t ptr = -1;

static void parse_num(uint32_t value, uint32_t base)
{
	uint32_t n = value / base;
	int32_t r = value % base;

	if (r < 0)
	{
		r += base;
		--n;
	}

	if (value >= base)
		parse_num(n, base);

	buf[ptr++] = (r + '0');
}

static void parse_hex(uint32_t value)
{
	int32_t i = 8;

	while (i-- > 0)
		buf[ptr++] = "0123456789ABCDEF"[(value>>(i*4))&0xF];
}

void kprintf(const int8_t* fmt, ...)
{
	int32_t i = 0;
	int8_t* s;
	args_list args;
	args_start(args, fmt);
	ptr = 0;

	for (; fmt[i]; ++i)
	{
		if ((fmt[i] != '%') && (fmt[i] != '\\'))
		{
			buf[ptr++] = fmt[i];
			continue;
		}
		else if (fmt[i] == '\\')
		{
			switch (fmt[++i])
			{
				case 'a':
					buf[ptr++] = '\a';
					break;
				case 'b':
					buf[ptr++] = '\b';
					break;
				case 't':
					buf[ptr++] = '\t';
					break;
				case 'n':
					buf[ptr++] = '\n';
					break;
				case 'r':
					buf[ptr++] = '\r';
					break;
				case '\\':
					buf[ptr++] = '\\';
					break;
			}

			continue;
		}

		switch (fmt[++i])
		{
			case 's':
				s = (int8_t*)args_next(args, int8_t*);
				while (*s)
					buf[ptr++] = *s++;
				break;
			case 'c':
				buf[ptr++] = (int8_t)args_next(args, int32_t);
				break;
			case 'x':
				parse_hex((unsigned long)args_next(args, unsigned long));
				break;
			case 'd':
				parse_num((unsigned long)args_next(args, unsigned long), 10);
				break;
			case '%':
				buf[ptr++] = '%';
				break;
			default:
				buf[ptr++] = fmt[i];
				break;
		}
	}

	buf[ptr] = '\0';
	args_end(args);
	puts(buf);
}
