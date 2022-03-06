/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:17:48 by ralena            #+#    #+#             */
/*   Updated: 2022/01/22 15:30:43 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redirect_type(t_shell *shell, t_token *token, t_token *prev,
		t_envs_lst *env)
{
	int	lvl;

	lvl = DEFAULT;
	if (prev && (prev->type == TRUNC || prev->type == APPEND))
		ft_handle_redirections(shell, token);
	else if (prev && (prev->type == INPUT))
		ft_handle_input(shell, token, env);
	else if (prev && (prev->type == DOBINP))
		ft_handle_dobinp(shell, token, env);
	else if (prev && (prev->type == PIPE))
		lvl = ft_check_pipe_io(shell, prev);
	return (lvl);
}

void	ft_handle_child_dobinp(int fd, char *eof)
{
	char	*line;

	errno = 0;
	signal(SIGINT, ft_sig_heredoc);
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		ft_putstr_fd("> ", STDOUT_FILENO);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	exit(ERROR_NON);
}

void	ft_handle_parent_dobinp(t_shell *shell, int fd, pid_t pid,
			t_envs_lst *env)
{
	int		status;
	t_token	new_token;

	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
	if (close(fd) == -1)
		error(ERROR_CLOSE);
	new_token.str = shell->tmpfile;
	ft_handle_input(shell, &new_token, env);
}

int	ft_handle_child_pipe(t_shell *shell, int *fd)
{
	errno = 0;
	if (close(fd[1]) == -1)
		error(ERROR_CLOSE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error(ERROR_DUP);
	if (close(fd[0]) == -1)
		error(ERROR_CLOSE);
	shell->process_level = CHILD;
	return (CHILD);
}

int	ft_handle_parent_pipe(t_shell *shell, int *fd, pid_t pid)
{
	shell->pid = pid;
	if (close(fd[0]) == -1)
		error(ERROR_CLOSE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error(ERROR_DUP);
	if (close(fd[1]) == -1)
		error(ERROR_CLOSE);
	return (PARENT);
}
