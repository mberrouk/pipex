/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/21 10:05:56 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char *av[], char *env[])
{
	t_d	data;

	if (ac == 1 || ac < check_parms(&data, av))
		puterr("Error parms\n");
	data.env = env;
	hndl_parms(&data, av, ac);
	if (!data.lmt)
		if (dup2(data.in_file, STDIN_FILENO) == -1)
			puterr(NULL);
	if (dup2(data.ou_file, STDOUT_FILENO) == -1)
		puterr(NULL);
	data.path = find_path(data.env);
	if (!data.cmds || !data.path)
	{
		close(data.in_file);
		close(data.ou_file);
		if (!data.path)
			puterr("Cannot find the PATH\n");
		puterr(NULL);
	}
	exec_cmds(&data, 0);
	return (0);
}
