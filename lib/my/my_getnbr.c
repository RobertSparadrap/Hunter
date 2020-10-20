/*
** EPITECH PROJECT, 2019
** my_getnbr
** File description:
** 
*/

#include "../../include/my.h"

int limit(int ret, int neg, int r)
{
    if (ret > 0 && (2147483647 / ret < 10)) {
        return (0);
    }
    if (ret > 0 && (neg % 2) && (-2147483648 + ret * 10 > r)) {
        return(0);
    }
    if (ret > 0 && !(neg % 2) && (2147483647 - ret * 10 < r)) {
        return (0);
    }
}

int my_getnbr(char const *str)
{
    int ret = 0, neg = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') neg++;
        if ((str[i] < '0' || str[i] > '9') && (str[i] != '+' || str[i] != '-')) {
            if (ret != '0')
                break;
            else
                continue;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            int r = str[i] - '0';
            limit(ret, neg, r);
            ret = ret * 10 + r;
        }
    }
    if (neg % 2)
        ret *= -1;
    return (ret);
}
