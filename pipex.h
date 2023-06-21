/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:33:26 by mberrouk          #+#    #+#             */
/*   Updated: 2023/06/21 09:59:09 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

//#include <sys/_types/_pid_t.h>
//#include <sys/wait.h>

typedef struct s_data
{
	int		in_file;
	char	**cmd1;
	char	**cmd2;
	int		ou_file;
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	int		pip[2];
}	t_data;

int		ft_strlen(char *str);
int		ft_strlcpy(char *dest, const char *src, int dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	**find_path(char **env);
char	**ft_split(char *s, char c);
int		ft_printf(const char *str, ...);
int		ft_putstr(char *str);

void	first_child_pro(int *pip, t_data *data, char **env);
void	second_child_pro(int *pip, t_data *data, char **env);
void	puterrs(char *str, t_data *data);
void	free_all(t_data *data);
char	**handle_error(char **ptr);
void	not_found(char *parm);

#endif
