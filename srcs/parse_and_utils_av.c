/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_av.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:14:14 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:21:31 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_count_type_files(t_av_info *av, char **argv, int argc)
{
	struct stat	buf;

	av->tmp = av->ct_start;
	av->nb_fold = 0;
	av->nb_files = 0;
	while (av->tmp < argc)
	{
		lstat(argv[av->tmp], &buf);
		if (S_ISDIR(buf.st_mode))
			av->nb_fold++;
		else if (!S_ISDIR(buf.st_mode))
			av->nb_files++;
		av->tmp++;
	}
	av->tmp = av->ct_start;
	av->index_fold = 0;
	av->argc = argc;
	av->nb_total = av->nb_fold + av->nb_files;
}

void			ft_fill_av(char **argv, int argc)
{
	if (!(argv[argc] = (char*)malloc(sizeof(char) * 2)))
		return ;
	argv[argc][0] = '.';
	argv[argc][1] = '\0';
}

static void		ft_comp_fill_flag(char c, t_pars *dt, char *str)
{
	if (c == 'R')
		dt->flag_rr = 0;
	else if (c == 'a')
		dt->flag_a = 0;
	else if (c == 'r')
		dt->flag_r = 0;
	else if (c == 't')
		dt->flag_t = 0;
	else if (c == 'l')
		dt->flag_l = 0;
	else if (str[0] == '-' && str[1] == '-' && !str[2])
		(void)0;
	else
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(c);
		ft_putchar('\n');
		ft_putstr("usage: ft_ls [-Ralrt] [file ...]\n");
		exit(0);
	}
}

int				ft_pars_argv(char **argv, t_pars *dt)
{
	int	i;
	int	count;
	int	j;

	i = 1;
	count = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		count++;
		if (!(argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2]))
		{
			while (argv[i][j])
			{
				ft_comp_fill_flag(argv[i][j], dt, argv[i]);
				j++;
			}
		}
		else
			break ;
		i++;
	}
	return (count);
}
