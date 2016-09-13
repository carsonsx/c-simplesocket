//
// Created by 姚双喜 on 9/13/16.
//

#include <stdio.h>
#include <stdarg.h>

#include "print.h"

int println(const char *fmt, ...) {
    char println_buf[1024];
    va_list args;
    int printed;
    va_start(args, fmt);
    printed = vsprintf(println_buf, fmt, args);
    va_end(args);
    puts(println_buf);
    return printed;
}