/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#ifndef MY_H
#define MY_H

typedef struct flag
{
    char c;
    int (*f)(va_list*);
} flag;

int my_putchar(int c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
int my_printf(char *str, ...);
int my_put_nbr_abs(int nb);
int my_putnbr_base(int nbr, char const *base);
int my_putstr_wrap(va_list *arg);
int my_putchar_wrap(va_list *arg);
int my_putnbr_b_wrap(va_list *arg);
int my_putnbr_o_wrap(va_list *arg);
int my_putnbr_x_wrap(va_list *arg);
int my_putnbr_big_x_wrap(va_list *arg);
int my_put_nbr_wrap(va_list *arg);
int my_put_nbr_abs_wrap(va_list *arg);
int my_put_percent(va_list *arg);

#endif
