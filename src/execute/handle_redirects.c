/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:17:41 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_prev_redirect(t_token *token)
{
	while (token && token->type != CMD)
	{
		if (token->type == TRUNC || token->type == APPEND)
			return (true);
		token = token->prev;
	}
	return (false);
}

void	ft_handle_redirections(t_shell *shell, t_token *token)
{
	char	*ts;

	ts = ft_strtrim(token->str, " ");
	if (ts == NULL)
		error(ERROR_MALLOC);
	if (!errno && shell->f_out != -1 && close(shell->f_out) == -1)
		error(ERROR_CLOSE);
	if (token->prev->type == TRUNC)
		shell->f_out = open(ts, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		shell->f_out = open(ts, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (shell->f_out == -1)
		error(ERROR_OPEN);
	if (!errno && dup2(shell->f_out, STDOUT_FILENO) == -1)
		error(ERROR_DUP);
	if (!errno && close(shell->f_out) == -1)
		error(ERROR_CLOSE);
	else
		shell->f_out = -1;
	free(ts);
}

void	ft_handle_input(t_shell *shell, t_token *token, t_envs_lst *env)
{
	char	*ts;

	ts = ft_strtrim(token->str, " ");
	if (ts == NULL)
		error(ERROR_MALLOC);
	if (!errno && shell->f_in != -1 && close(shell->f_in) == -1)
		return ;
	shell->f_in = open(ts, O_RDONLY, 0777);
	if (shell->f_in == -1)
		ft_print_errno_error(shell, ts, &env);
	if (!errno && dup2(shell->f_in, STDIN_FILENO) == -1)
		error(ERROR_DUP);
	if (!errno && close(shell->f_in) == -1)
		error(ERROR_CLOSE);
	else
		shell->f_in = -1;
	free(ts);
}

void	ft_handle_dobinp(t_shell *shell, t_token *token, t_envs_lst *env)
{
	int		fd;
	pid_t	pid;
	char	*eof;

	if (dup2(shell->std_in, STDIN_FILENO) == -1
		|| dup2(shell->std_out, STDOUT_FILENO) == -1)
		error(ERROR_DUP);
	fd = open(shell->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		error(ERROR_OPEN);
	eof = ft_strjoin(token->str, "\n");
	if (eof == NULL)
		error(ERROR_MALLOC);
	signal(SIGINT, ft_sig_empty);
	pid = fork();
	if (pid == 0)
		ft_handle_child_dobinp(fd, eof);
	else if (pid > 0)
	{
		ft_handle_parent_dobinp(shell, fd, pid, env);
		free(eof);
	}
	else
		error(ERROR_FORK);
}

int	ft_handle_pipe(t_shell *shell)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(ERROR_PIPE);
	pid = fork();
	if (pid == 0)
		return (ft_handle_child_pipe(shell, fd));
	else if (pid > 0)
		return (ft_handle_parent_pipe(shell, fd, pid));
	else
	{
		error(ERROR_FORK);
		return (DEFAULT);
	}
}
