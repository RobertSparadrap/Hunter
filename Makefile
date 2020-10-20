##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## 
##

NAME	=	my_hunter

CC	=	gcc -o

CFLAGS	=	-L ./lib/my -lmy -I./include/

SRC	=	window2.c		\
		lib/my/my_printf.c	\
		lib/my/my_put_nbr_abs.c	\
		lib/my/my_putnbr_base.c	\
		lib/my/my_getnbr.c	\
		lib/my/my_putchar.c	\
		lib/my/my_put_nbr.c	\
		lib/my/my_putstr.c	\
	 	lib/my/my_strlen.c	\
		lib/my/my_wrap_base.c	\
		lib/my/my_wrap.c	\
		lib/my/my_wrap_nbr.c	\


OBJ	=	$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	$(CC) $(NAME) $(SRC) -l csfml-system -l csfml-graphics -l csfml-window -l csfml-audio

clean :
	find -name "*~" -delete , -name "*.o" -delete , -name "#*#" -delete

fclean : clean
	rm -f $(NAME)

re : fclean all
