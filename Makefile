.PHONY:     			all $(NAME) clear mkbuild lib clear clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/

HEADER_DIR				= header/

HEADER_FILE				= minishell.h

DIR						= src/

SRC			 			=	ms_main.c	builtins/env.c	ms_utils_free.c
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)

LIBFT					= libft.a
LIB_DIR					= libft/
	
CC						= cc
CFLAGS					= -Wall -Wextra -Werror
SANITIZE				= $(CFLAGS) -fsanitize=address

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)/$(HEADER_FILE) ${LIB_DIR}*.c ${LIB_DIR}/${LIB_HEADER} ${LIB_DIR} Makefile 
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -c $< -o $@

all: 					clear lib mkbuild  $(HEADER_DIR) $(NAME)
	
mkbuild:	
						@mkdir -p ${BUILD_DIR}

clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(CC) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline

sanitize :				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(CC) $(SANITIZE) $(OBJECTS) -o $(NAME) $(LIB_DIR) $(LIBFT) -lreadline

lib:
						@make -C $(LIB_DIR) --no-print-directory
						
clean:					
						@${RM} $(OBJECTS)
						@make clean -C $(LIB_DIR) --no-print-directory
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}
						@make fclean -C $(LIB_DIR) --no-print-directory

re:						fclean all
						$(MAKE) all