.PHONY: all clean fclean

NAME	=	libft.a

SRC		=	ft_memset.c			\
			ft_bzero.c			\
			ft_memcpy.c			\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_strrchr.c		\
			ft_strncmp.c		\
			ft_strlen.c			\
			ft_isalpha.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_calloc.c			\
			ft_strchr.c			\
			ft_isdigit.c		\
			ft_tolower.c		\
			ft_toupper.c		\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_atoi.c			\
			ft_strnstr.c		\
			ft_strdup.c			\
			ft_substr.c			\
			ft_strjoin.c		\
			ft_strmapi.c		\
			ft_strtrim.c		\
			ft_split.c			\
			ft_itoa.c			\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c

SRC_B	=	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		

OBJ		= $(SRC:.c=.o)
OBJ_B	= $(SRC_B:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all:  $(NAME)

bonus: $(OBJ) $(OBJ_B)
	ar rc $(NAME) $(OBJ) $(OBJ_B)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ) $(OBJ_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

