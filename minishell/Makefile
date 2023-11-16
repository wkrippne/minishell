# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 12:47:13 by ankinzin          #+#    #+#              #
#    Updated: 2023/07/11 12:36:59 by ankinzin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name:
NAME	= minishell

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address -I $(HOME)/.local/pkg/readline/include
EFLAGS	= -L $(HOME)/.local/pkg/readline/lib -l readline -l history -l curses
RM		= rm -rf

# Sources, objects and dir
SRCDIR	= ./src/
SRC		= create_pipe.c builtin.c free.c free1.c generic.c init_shell.c main.c prompt.c \
			redirect.c redirect1.c signals.c t_env_list.c t_env_list2.c handle_exit.c

PARSERDIR= ./src/parser/
PARSER	= parser.c parser1.c parser2.c parser3.c parser_utils.c

EXPDIR	= ./src/expander/
EXP		= expander.c expander2.c expander3.c

EXECDIR	= ./src/executer/
EXEC	= executer.c access.c


BUILDIR	= ./src/builtins/
BUILT	=	$(BUILDIR)env.c \
 			$(BUILDIR)export.c $(BUILDIR)export_update.c $(BUILDIR)exportenv.c \
 			$(BUILDIR)unset.c $(BUILDIR)unset_update.c\
 			$(BUILDIR)cd.c $(BUILDIR)cd_update.c \
 			$(BUILDIR)exit.c \
 			$(BUILDIR)pwd.c \
 			$(BUILDIR)echo.c

OBJ		=	$(addprefix $(SRCDIR), $(SRC:.c=.o)) \
			$(addprefix $(EXECDIR), $(EXEC:.c=.o)) \
			$(addprefix $(PARSERDIR), $(PARSER:.c=.o)) \
			$(addprefix $(EXPDIR), $(EXP:.c=.o)) \
			$(BUILT:.c=.o)


# Libft
LIBDIR	= ./includes/libft/
LIBAFT	= libft.a

.SILENT: $(OBJ) libft clean fclean re

all: $(NAME)

$(NAME): $(OBJ) libft credit
		@$(CC) $(CFLAGS) $(OBJ) $(LIBAFT) $(EFLAGS) -o $(NAME)

libft:
		@make -C $(LIBDIR)
		@cp $(LIBDIR)$(LIBAFT) .

clean:
		@$(RM) $(OBJ)

fclean: clean
		@make -C $(LIBDIR) fclean
		@$(RM) $(LIBAFT)
		@$(RM) $(NAME)

re: fclean all

credit:
		@echo ""
		@echo "Libft Compiled ✅"
		@echo "Builtins Compiled ✅"
		@echo "expander Compiled ✅"
		@echo "Parsing Compiled ✅"
		@echo "Executer Compiled ✅"
		@echo ""
		@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
		@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
		@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
		@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
		@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
		@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
		@echo ""
