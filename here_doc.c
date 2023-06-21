/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:04 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/20 13:38:08 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_line(t_d data, int fd)
{
	char	*buff;
	int		n;

	buff = malloc(sizeof(char) * 1024);
	if (!buff)
		puterr(NULL);
	while (1)
	{
		n = read(STDIN_FILENO, buff, 1023);
		if (n == -1)
		{
			free(buff);
			puterr(NULL);
		}
		else if (n)
		{	
			buff[n] = '\0';
			if (ft_strcmp(buff, data.lmt))
				break ;
			write(fd, buff, ft_strlen(buff));
		}
		else if (!n)
			break ;
	}
	free(buff);
}

int	here_doc(t_d data)
{
	int	pid;
	int	fd[20];

	if (pipe(fd) == -1)
		puterr(NULL);
	pid = fork();
	if (pid == 0)
	{
		data.lmt = ft_strjoin(data.lmt, "\n");
		close(fd[0]);
		get_line(data, fd[1]);
		close(fd[1]);
		free(data.lmt);
		exit(0);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		wait(NULL);
		return (fd[0]);
	}
	else if (pid < 0)
		puterr(NULL);
	return (0);
}
