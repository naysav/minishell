/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:17:22 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_tmpfile(t_shell *shell)
{
	pid_t	pid;
	char	**argv;

	argv = malloc(sizeof(char *) * 3);
	if (argv == NULL)
		error(ERROR_MALLOC);
	argv[0] = "/bin/rm";
	argv[1] = shell->tmpfile;
	argv[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		execve("/bin/rm", argv, NULL);
	}
	else if (pid > 0)
		free(argv);
	else
		error(ERROR_FORK);
}

static void	proceed_to_cmd(t_shell *shell, t_token *token, t_token *next,
	t_envs_lst *env)
{
	if (token)
		ft_execute_cmd(shell, token, env);
	if (next && next->type == DOBINP)
		delete_tmpfile(shell);
}

static void	process_next_cmd(t_shell *shell, t_token *token, t_envs_lst *env)
{
	t_token	*prev;
	t_token	*next;
	int		lvl;

	prev = ft_get_prev_token(token);
	next = ft_get_next_token(token);
	if (!prev && token && token->type != CMD)
		process_next_cmd(shell, token->next, env);
	lvl = ft_check_redirect_type(shell, token, prev, env);
	if (next && lvl != PARENT)
		process_next_cmd(shell, next->next, env);
	if (lvl != PARENT && !shell->executed && (!prev || prev->type == PIPE)
		&& token->type == CMD && !errno)
	{
		if (lvl == CHILD)
			shell->executed = true;
		proceed_to_cmd(shell, token, next, env);
	}
}

int	ft_check_pipe_io(t_shell *shell, t_token *prev)
{
	int		lvl;
	pid_t	pid;

	lvl = DEFAULT;
	if (prev && ft_prev_redirect(prev->prev))
	{
		pid = fork();
		if (pid == 0)
		{
			errno = 0;
			shell->process_level = CHILD;
			dup2(shell->std_out, STDOUT_FILENO);
			lvl = CHILD;
		}
		else if (pid > 0)
		{
			shell->pid = pid;
			lvl = PARENT;
		}
		else
			error(ERROR_FORK);
	}
	else
		lvl = ft_handle_pipe(shell);
	return (lvl);
}

bool	ft_execute_token(t_shell *shell, t_token *token, t_envs_lst *env)
{
	errno = 0;
	shell->process_level = PARENT;
	shell->executed = false;
	if (token)
		process_next_cmd(shell, token, env);
	if (shell->f_in != -1 && close(shell->f_in) == -1)
		error(ERROR_CLOSE);
	if (shell->f_out != -1 && close(shell->f_out) == -1)
		error(ERROR_CLOSE);
	if (dup2(shell->std_in, STDIN_FILENO) == -1)
		error(ERROR_DUP);
	if (dup2(shell->std_out, STDOUT_FILENO) == -1)
		error(ERROR_DUP);
	while (wait(NULL) > 0)
		;
	if (shell->process_level == CHILD)
		exit(shell->exit_status);
	return (true);
}
