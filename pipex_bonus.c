/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:16 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/20 14:31:15 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(int ifd, int ofd, t_d *data, char **cmds)
{
	pid_t	pid;
	char	*cmd;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(ifd, STDIN_FILENO) == -1 || dup2(ofd, STDOUT_FILENO) == -1)
			puterr("Error dup2\n");
		close(ifd);
		close(ofd);
		if (cmds && cmds[0] && cmds[0][0] == '/')
			cmd = cmds[0];
		else
			cmd = ft_access(data->path, cmds[0]);
		if (!cmd)
			not_found(cmds[0]);
		if (execve(cmd, cmds, data->env) == -1)
			puterr(NULL);
	}
	else if (pid < 0)
		puterr(NULL);
}

void	cmds(t_d data, int fdi)
{
	int	pip_fds[2];
	int	i;

	i = 0;
	while (data.cmds[i])
	{
		if (data.cmds[i + 1])
		{	
			if (pipe(pip_fds) == -1)
				puterr(NULL);
		}
		else
		{
			close(pip_fds[1]);
			pip_fds[1] = data.ou_file;
		}
		execute_command(fdi, pip_fds[1], &data, data.cmds[i]);
		if (fdi != data.in_file)
			close(fdi);
		close(pip_fds[1]);
		fdi = pip_fds[0];
		i++;
	}
}

void	exec_cmds(t_d *data, int status)
{
	int	fdi;

	if (!data->lmt)
		fdi = data->in_file;
	else
	{
		fdi = here_doc(*data);
		data->in_file = fdi;
	}
	cmds(*data, fdi);
	while (wait(&status) > 0)
		;
	status = WEXITSTATUS(status);
	if (data->cmds)
		free_cmds(data->cmds);
	handle_error(data->path);
	exit(status);
}
