#include "../header/minishell.h"
#include <signal.h>

void handler()
{
	write(1, "nope\n", 5);
}


int	main(int argc, char** argv, char **envp) {
	(void)argc;
	(void) argv;
	char *cmd;
	t_listenv *listenv;

	listenv = ft_env(envp);
	while (listenv != NULL)
	{
		printf("%s", listenv->key);
		printf("%s\n", listenv->content);
		listenv = listenv->next;
	}
	while (1)
	{
		cmd = readline(">>");
		if (ft_strlen(cmd) > 0)
			add_history(cmd);
		printf("%s\n", cmd);
		if (ft_strncmp(cmd, "clear", 5) == 0)
			rl_clear_history();
		
	}
	return 0;
}