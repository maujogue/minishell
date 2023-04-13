.PHONY:     			all $(NAME) clear mkbuild lib clear clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/

HEADER_DIR				= header/

HEADER_FILE				= minishell.h pipex.h

DIR						= src/

SRC			 			=	ms_main.c	ms_utils_free.c	ms_utils_print.c	ms_utils_pars_arg.c		ms_utils_libft.c\
							builtins/export.c	builtins/export_print.c	\
							builtins/env.c	builtins/unset.c	builtins/builtins.c	\
							builtins/cd.c	builtins/exit.c		builtins/pwd.c	\
							builtins/echo.c builtins/echo_var.c	\
							builtins/ft_strncmpbuil.c \
              				parsing/parsing.c parsing/parsarg.c	\
							pipex/pp_main.c pipex/pp_utils.c pipex/pp_exec.c pipex/pp_free_utils.c\
							pipex/pp_get_env_cmds.c pipex/pp_cmds_to_pip.c \
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)

LIBFT					= libft.a
LIB_DIR					= libft/
	
CC						= cc
CFLAGS					= -Wall -Wextra -Werror
SANITIZE				= $(CFLAGS) -fsanitize=address

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR) ${LIB_DIR}*.c ${LIB_DIR}/${LIB_HEADER} ${LIB_DIR} Makefile 
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -c $< -o $@

all: 					clear lib mkbuild  $(HEADER_DIR) $(NAME)
	
mkbuild:	
						@mkdir -p ${BUILD_DIR}

clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(CC) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline

sanitize :				$(OBJECTS)
						$(CC) $(SANITIZE) $(OBJECTS) -o $(NAME) ${LIB_DIR} -lreadline

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