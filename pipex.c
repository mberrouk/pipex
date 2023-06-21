/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:37:19 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/21 09:59:02 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	puterrs(char *str, t_data *data)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		exit(1);
	}
	else
	{
		perror("Error");
		free_all(data);
		exit(errno);
	}
}

char	*ft_access(char **paths, char *cmd)
{
	char	*new;
	char	*v_cmd;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!new)
		return (NULL);
	new[0] = '/';
	ft_strlcpy(&new[1], cmd, ft_strlen(cmd) + 1);
	while (paths[i])
	{
		v_cmd = ft_strjoin(paths[i], new);
		if (!access(v_cmd, X_OK))
		{
			free(new);
			return (v_cmd);
		}
		free(v_cmd);
		i++;
	}
	free(new);
	return (NULL);
}

void	first_child_pro(int *pip, t_data *data, char **env)
{
	char	*cmd;

	if (close(pip[0]) == -1)
		puterrs(NULL, data);
	if (dup2(pip[1], STDOUT_FILENO) == -1)
		puterrs(NULL, data);
	if (close(pip[1]) == -1)
		puterrs(NULL, data);
	if (data->cmd1 && data->cmd1[0] && data->cmd1[0][0] == '/')
		cmd = data->cmd1[0];
	else
		cmd = ft_access(data->paths, data->cmd1[0]);
	if (!cmd)
	{
		handle_error(data->paths);
		not_found(data->cmd1[0]);
	}
	if (execve(cmd, data->cmd1, env) == -1)
		puterrs(NULL, data);
}

void	second_child_pro(int *pip, t_data *data, char **env)
{
	char	*cmd;

	if (close(pip[1]) == -1)
		puterrs(NULL, data);
	if (dup2(pip[0], STDIN_FILENO) == -1)
		puterrs(NULL, data);
	if (close(pip[0]) == -1)
		puterrs(NULL, data);
	if (data->cmd2 && data->cmd2[0] && data->cmd2[0][0] == '/')
		cmd = data->cmd2[0];
	else
		cmd = ft_access(data->paths, data->cmd2[0]);
	if (!cmd)
	{
		handle_error(data->paths);
		not_found(data->cmd2[0]);
	}
	if (execve(cmd, data->cmd2, env) == -1)
		puterrs(NULL, data);
}
