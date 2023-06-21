/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:33:29 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/20 14:28:48 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmds(t_data *data, char **env, int sta)
{
	if (pipe(data->pip) == -1)
		puterrs(NULL, data);
	data->pid1 = fork();
	if (data->pid1 == 0)
		first_child_pro(data->pip, data, env);
	else if (data->pid1 > 0)
	{
		data->pid2 = fork();
		if (data->pid2 == 0)
			second_child_pro(data->pip, data, env);
		else if (data->pid2 < 0)
			puterrs(NULL, data);
		close(data->pip[1]);
		close(data->pip[0]);
		if (waitpid(data->pid1, NULL, 0) == -1)
			puterrs(NULL, data);
		if (waitpid(data->pid2, &sta, 0) == -1)
			puterrs(NULL, data);
		free_all(data);
		sta = WEXITSTATUS(sta);
		exit(sta);
	}
	else
		puterrs(NULL, data);
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	if (ac != 5)
		puterrs("Usage: ./pipex file1 cmd1 cmd2 file2\n", NULL);
	data.ou_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.ou_file == -1)
		puterrs(NULL, NULL);
	data.in_file = open(av[1], O_RDONLY);
	if (data.in_file == -1)
		puterrs(NULL, NULL);
	data.paths = find_path(env);
	if (!data.paths)
		puterrs("Cannot find the PATH\n", NULL);
	data.cmd1 = ft_split(av[2], ' ');
	data.cmd2 = ft_split(av[3], ' ');
	if (dup2(data.in_file, STDIN_FILENO) == -1)
		puterrs(NULL, &data);
	if (dup2(data.ou_file, STDOUT_FILENO) == -1)
		puterrs(NULL, &data);
	execute_cmds(&data, env, 0);
	return (0);
}
