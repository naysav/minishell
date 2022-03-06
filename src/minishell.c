/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:36:47 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:57:56 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_shell(t_shell *shell)
{
	shell->pid = 0;
	shell->f_in = -1;
	shell->f_out = -1;
	shell->process_level = DEFAULT;
}

static void	run_shell(t_shell *shell, t_envs_lst *envs)
{
	char		*username;
	char		*prompt;
	char		*buf;

	username = find_env_variable(&envs, "USER");
	if (username)
		prompt = ft_strjoin(username, "$ ");
	else
		prompt = ft_strjoin("", "$ ");
	if (prompt == NULL)
	{
		printf("\033[A%sexit\n", prompt);
		error(ERROR_MALLOC);
	}
	buf = readline(prompt);
	if (buf == NULL)
	{
		printf("\033[A%sexit\n", prompt);
		exit(ERROR_MALLOC);
	}
	add_history(buf);
	ft_parse(shell, envs, buf, prompt);
	free(buf);
	free(prompt);
}

static void	start_shell(t_envs_lst *envs, t_shell *shell)
{
	shell->is_running = true;
	shell->exit_status = ERROR_NON;
	while (shell->is_running)
	{
		ft_tty_mask();
		start_signals();
		init_shell(shell);
		run_shell(shell, envs);
		start_signals();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_envs_lst	*envs;
	t_shell		shell;

	(void) argc;
	(void) argv;
	envs = NULL;
	ft_parse_envs_to_lst(&envs, env);
	if (find_env_variable(&envs, "SHLVL"))
		shell.shlvl = ft_atoi(find_env_variable(&envs, "SHLVL"));
	else
		shell.shlvl = SHLVL_DEFAULT;
	shell.tmpfile = ft_strjoin(TMP_PATH, TMP_FILE);
	if (shell.tmpfile == NULL)
		error(ERROR_MALLOC);
	shell.std_in = dup(0);
	shell.std_out = dup(1);
	if (shell.std_in == -1 || shell.std_out == -1)
		exit(ERROR_DUP);
	start_shell(envs, &shell);
	if (close(shell.std_in) == -1 || close(shell.std_out) == -1)
		error(ERROR_CLOSE);
	return (shell.exit_status);
}
