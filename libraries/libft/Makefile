CC = cc
CFLAG = -Wextra -Wall -Werror -g
NAME = libft.a
SOURCES = \
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_striteri.c ft_strjoin.c \
		ft_strmapi.c ft_strtrim.c ft_substr.c ft_atol.c \
		ft_strcmp.c ft_strjoin2.c \
		ft_length.c ft_printf.c ft_print_ptr.c \
		ft_print_str.c ft_print_unsigned_int.c \
		ft_length_fd.c ft_printf_fd.c ft_print_ptr_fd.c \
		ft_print_str_fd.c ft_print_unsigned_int_fd.c \
		ft_array_size.c ft_print_array.c ft_strpos.c ft_strldup.c ft_strcmp2.c \
		bonus/ft_list_size.c  bonus/ft_lstadd_back.c  bonus/ft_lstadd_front.c  \
		bonus/ft_lstclear.c  bonus/ft_lstdelone.c  bonus/ft_lstiter.c  bonus/ft_lstlast.c \
		bonus/ft_lstnew.c bonus/ft_lstnew_add_back.c \
		bonus/ft_lsterase_node.c #TODO: make bonus rule

MY_OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(MY_OBJECTS)
	ar -rc $(NAME) $(MY_OBJECTS)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
