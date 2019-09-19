# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 12:15:31 by rbarbero          #+#    #+#              #
#    Updated: 2019/09/19 10:39:38 by rbarbero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	   ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	   ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	   ft_atoi.c ft_isupper.c ft_islower.c ft_isalpha.c ft_isdigit.c \
	   ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	   ft_isspace.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
	   ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	   ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	   ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c \
	   ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	   ft_lstiter.c ft_lstmap.c ft_strsplittolst.c ft_lstnewnode.c \
	   ft_lstpushback.c ft_lstsize.c get_next_line.c ft_char_encode_utf8.c \
	   ft_char_decode_utf8.c ft_lstsortedinsert.c ft_lstdelnode.c \
	   ft_imtoa_base.c ft_uimtoa_base.c ft_strtoupper.c ft_strtolower.c \
	   ft_wctomb.c ft_wcslen.c ft_absolute.c ft_is_valid_unicode.c \
	   ft_lstrsortedinsert.c ft_lstaddback.c ft_getfilename.c ft_lstdelif.c \
	   ft_nbrlen.c ft_lstselect.c ft_strarrtolist.c ft_strnarrtolist.c \
	   ft_strnclr.c ft_strsplitstr.c ft_strpushback.c ft_buf_flush.c \
	   ft_buf_add_char.c ft_buf_init.c ft_buf_destroy.c ft_buf_extend.c \
	   ft_buf_insert_char.c ft_buf_delete_char.c ft_isstrdigit.c \
	   ft_btreenew.c ft_btreedelone.c ft_btreedel.c ft_strarrdel.c \
	   ft_lsttoarrstr.c ft_strarrchr.c ft_buf_add_str.c ft_strndup.c \
	   ft_strmove.c ft_lstdup.c ft_buf_add_nstr.c ft_lstpush.c ft_strarrtostr.c
DIR_FT_VSDPRINTF = ft_vsdprintf
SRCS_FT_VSDPRINTF = ft_vsdprintf.c parse.c parse_format.c parse_width.c \
				 parse_precision.c int_arg.c int_conv.c conv_tools.c \
				 buf_tools.c int_mod_width.c percent_conv.c \
				 int_mod_precision.c int_mod_flags.c hex_conv.c octal_conv.c \
				 uint_conv.c hex_mod_width.c char_arg.c char_conv.c \
				 str_arg.c str_conv.c default_conv.c bin_conv.c \
				 bin_mod_width.c n_conv.c n_arg.c arg_tools.c print_color.c \
				 arg_tools_del.c ft_dprintf.c ft_printf.c ft_sprintf.c
OBJS = $(SRCS:%.c=%.o)
OBJS += $(SRCS_FT_VSDPRINTF:%.c=$(DIR_FT_VSDPRINTF)/%.o)
HEADERS_DIR = includes/
HEADERS = libft.h get_next_line.h ft_vsdprintf.h
LHEADERS = $(HEADERS:%.h=$(HEADERS_DIR)%.h)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $^

$(OBJS): %.o: %.c $(LHEADERS)
	$(CC) $(CFLAGS) -o $@ -I $(HEADERS_DIR) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
