#include "../header/minishell.h"

int	main(int argc, char** argv) {
	(void)argc;
	(void) argv;
	char *cmd;

	while (1)
	{
		cmd = readline(">>");
		if (ft_strlen(cmd) > 0)
			add_history(cmd);
		printf("%s\n", cmd);
	}
	return 0;
}