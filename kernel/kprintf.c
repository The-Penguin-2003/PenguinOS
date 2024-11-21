#include <vga.h>
#include <kprintf.h>

#define args_list uint8_t*
#define _arg_stack_size(type) (((sizeof(type) - 1) / sizeof(int)+1) * sizeof(int))
#define args_start(ap, fmt) do { ap = (uint8_t*)((uint32_t)&fmt + _arg_stack_size(&fmt)); } while (0)
#define args_end(ap)
#define args_next(ap, type) (((type*)(ap += _arg_stack_size(type)))[-1])

static uint8_t buf[1024] = {-1};
static int32_t ptr = -1;

static void parse_num(int32_t value, uint32_t base) {
    uint8_t tmp_buf[32];
    int32_t tmp_ptr = 0;
    bool is_negative = FALSE;

    if (value < 0) {
        is_negative = TRUE;

        if (value == INT32_MIN) {
            value = -(value + 1);
            tmp_buf[tmp_ptr++] = ((value % base) + 1) + '0';
            value /= base;
        }
        else {
            value = -value;
        }
    }

    do {
        tmp_buf[tmp_ptr++] = (value % base) + '0';
        value /= base;
    } while (value > 0);

    if (is_negative)
        buf[ptr++] = '-';

    while (tmp_ptr > 0)
        buf[ptr++] = tmp_buf[--tmp_ptr];
}

static void parse_hex(uint32_t value) {
    int32_t i = 8;

    while (i-- > 0)
        buf[ptr++] = "0123456789ABCDEF"[(value >> (i * 4)) & 0xF];
}

void kprintf(const uint8_t* fmt, ...) {
    int32_t i = 0;
    uint8_t* s;
    args_list args;
    args_start(args, fmt);
    ptr = 0;

    for (; fmt[i]; ++i) {
        if ((fmt[i] != '%') && (fmt[i] != '\\')) {
            buf[ptr++] = fmt[i];
            continue;
        }
        else if (fmt[i] == '\\') {
            switch (fmt[++i]) {
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

        switch (fmt[++i]) {
            case 's':
                s = (uint8_t*)args_next(args, uint8_t*);
                while (*s) {
                    buf[ptr++] = *s++;
                }
                break;
            case 'c':
                buf[ptr++] = (uint8_t)args_next(args, uint32_t);
                break;
            case 'x':
                parse_hex((unsigned long)args_next(args, unsigned long));
                break;
            case 'd':
                parse_num((long)args_next(args, long), 10);
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
