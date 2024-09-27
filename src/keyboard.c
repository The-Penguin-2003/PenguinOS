#include <keyboard.h>
#include <io.h>
#include <irq.h>
#include <kprintf.h>

uint8_t us_kbd[128] =
{
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
	'`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*',
	0,
	' ',
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'-',
	0, 0, 0,
	'+',
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t us_kbd_shift[128] =
{
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',
	'~', 0,
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
	'*',
	0,
	' ',
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'-',
	0, 0, 0,
	'+',
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static int8_t kb_buffer[KEYBOARD_BUFFER_SIZE];
static uint32_t kb_buffer_start = 0;
static uint32_t kb_buffer_end = 0;
static int32_t shift_pressed = 0;

void keyboard_handler()
{
	uint8_t scancode;
	scancode = inb(0x60);

	if (scancode & 0x80)
	{
		if (scancode == LEFT_SHIFT_RELEASED || scancode == RIGHT_SHIFT_RELEASED)
			shift_pressed = 0;
	}
	else
	{
		if (scancode == LEFT_SHIFT_PRESSED || scancode == RIGHT_SHIFT_PRESSED)
			shift_pressed = 1;
		else
		{
			int8_t c;

			if (shift_pressed)
				c = us_kbd_shift[scancode];
			else
				c = us_kbd[scancode];

			if (c)
			{
				kb_buffer[kb_buffer_end] = c;
				kb_buffer_end = (kb_buffer_end + 1) % KEYBOARD_BUFFER_SIZE;
			}
		}
	}
}

void init_keyboard()
{
	irq_install_handler(1, keyboard_handler);
	kprintf("[KERNEL] Installed Keyboard IRQ Handler\r\n");
}

int8_t kb_getchar()
{
	while (kb_buffer_start == kb_buffer_end);

	int8_t c = kb_buffer[kb_buffer_start];
	kb_buffer_start = (kb_buffer_start + 1) % KEYBOARD_BUFFER_SIZE;
	return c;
}

int32_t kb_has_input()
{
	return kb_buffer_start != kb_buffer_end;
}

int8_t kb_getchar_non_blocking()
{
	if (kb_has_input())
	{
		int8_t c = kb_buffer[kb_buffer_start];
		kb_buffer_start = (kb_buffer_start + 1) % KEYBOARD_BUFFER_SIZE;
		return c;
	}

	return 0;
}
