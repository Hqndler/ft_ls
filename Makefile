NAME	=	ft_ls
CC		=	gcc
FLAG	=	-Wall -Wextra -Werror -g3

SRC_DIR	=	src/
OBJ_DIR	=	obj/

#Source
FILES	=	main
SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

INCLUDE	=	-I ./include
HNAME	=	ft_ls
HEADER	=	$(addsuffix .h, $(HNAME))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

vpath %.c $(SRC_DIR)
vpath %.h include/

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAG) $(OBJS) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)Compiled!$(DEF_COLOR)"
	@echo "Launch the program with $(RED)./${NAME} $(DEF_COLOR)"

$(OBJ_DIR)%.o : %.c $(HEADER) Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;91m
GREEN 		= \033[0;92m