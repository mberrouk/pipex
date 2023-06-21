/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:01:50 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/21 10:06:03 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
		if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
			return (0);
	}
	return (1);
}	

int	check_parms(t_d *data, char **av)
{
	if (ft_strcmp(av[1], "here_doc"))
	{
		data->lmt = av[2];
		return (6);
	}
	data->lmt = NULL;
	return (5);
}

char	***get_cmds(int size, int j, char **av)
{
	int		i;
	char	***cmd;

	cmd = malloc(sizeof(char **) * size);
	if (!cmd)
		puterr(NULL);
	i = 0;
	while (i < size - 1)
	{
		cmd[i] = ft_split(av[j + i], ' ');
		if (!cmd[i])
		{
			free_cmds(cmd);
			puterr(NULL);
		}
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	hndl_parms(t_d *data, char **av, int ac)
{
	if (!data->lmt)
	{
		data->ou_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->ou_file == -1)
			puterr(NULL);
		data->in_file = open(av[1], O_RDONLY);
		if (data->in_file == -1)
			puterr(NULL);
		data->cmds = get_cmds(ac - 2, 2, av);
	}
	else if (data->lmt)
	{
		data->ou_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->ou_file == -1)
			puterr(NULL);
		data->cmds = get_cmds(ac - 3, 3, av);
	}
}
