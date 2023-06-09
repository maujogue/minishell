.PHONY:     			all $(NAME) clear mkbuild lib clear clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/

HEADER_DIR				= header/

HEADER_FILE				= minishell.h pipex.h

DIR						= src/

SRC			 			=	ms_main.c	ms_signals.c	ms_utils_pars.c		ms_utils_split.c	ms_utils_print_list.c 	ms_utils_free.c		ms_utils_libft.c 	ms_is_double_char_spe.c \
							builtins/export.c	builtins/export_fill.c	builtins/export_lstutils.c\
							builtins/env.c	builtins/env_utils.c builtins/unset.c	builtins/builtins.c	\
							builtins/cd.c	builtins/cd_utils.c	builtins/exit.c		builtins/pwd.c	\
							builtins/echo.c builtins/echo_var.c	\
              				parsing/parsing.c parsing/parsarg.c	parsing/parsopt.c 	parsing/parsfile.c	parsing/pars.c	parsing/parsvar.c	parsing/parsquote.c		parsing/utilsparsquote.c	parsing/parsimplequote.c 	parsing/parspace.c \
							parsing/utilsparsarg.c 		parsing/fillpars.c		parsing/utilsfillpars.c \
							pipex/pp_main.c	pipex/pp_here_doc.c pipex/pp_free.c pipex/pp_dupes.c	pipex/pp_init_files.c	pipex/pp_utils.c pipex/pp_exec.c pipex/pp_free_utils.c\
							pipex/pp_get_env_cmds.c pipex/pp_cmds_to_pip.c \
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)

LIBFT					= libft.a
LIB_DIR					= libft/
	
CC						= cc
CFLAGS					= -Wall -Wextra -Werror
SANITIZE				= $(CFLAGS) -fsanitize=address

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)* ${LIB_DIR}*.c ${LIB_DIR}/${LIB_HEADER} ${LIB_DIR} Makefile 
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
						$(CC) $(SANITIZE) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline

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