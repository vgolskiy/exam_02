#!/bin/bash

gcc -Wall -Werror -Wextra main.c get_next_line.c get_next_line.h
./a.out < text > res
diff -y --suppress-common-line res text
rm -f res