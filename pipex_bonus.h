/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:20 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/20 14:30:48 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

typedef struct s_d
{
	int		in_file;
	int		ou_file;
	char	**env;
	char	**path;
	char	*lmt;
	char	***cmds;
}	t_d;

int		check_parms(t_d *data, char **av);
int		ft_strcmp(char *s1, char *s2);
void	puterr(char *str);
char	***get_cmds(int size, int j, char **av);
void	hndl_parms(t_d *data, char **av, int ac);
char	**free_cmds(char ***cmd);
char	*ft_access(char **paths, char *cmd);
void	get_line(t_d data, int fd);
int		here_doc(t_d data);
void	exec_cmds(t_d *data, int status);

#endif
