/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:18:49 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/21 09:47:25 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	not_found(char *parm)
{
	write(STDERR_FILENO, "pipex: ", 8);
	if (parm && *parm)
		write(STDERR_FILENO, parm, ft_strlen(parm));
	write(STDERR_FILENO, ": command not found\n", 21);
	exit(127);
}

void	puterr(char *str)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		exit(1);
	}
	else
	{
		perror("Error");
		exit(errno);
	}
}

char	**handle_error(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	handle_error(data->cmd1);
	handle_error(data->cmd2);
	handle_error(data->paths);
}

char	**free_cmds(char ***cmd)
{
	int	i;
	int	j;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (NULL);
}
