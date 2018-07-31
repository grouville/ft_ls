/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_av.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:17:27 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:35:29 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_sort_r_av(int start, char **argv, int argc)
{
	int			end;
	char		*tmp;

	end = argc - 1;
	while (start < end)
	{
		tmp = argv[end];
		argv[end] = argv[start];
		argv[start] = tmp;
		end--;
		start++;
	}
}

static void		ft_sort_t_av(int start, char **argv, int argc)
{
	int			i;
	int			j;
	char		*tmp;
	struct stat	buf;
	struct stat	buf2;

	i = start - 1;
	while (++i < argc)
	{
		j = start - 1;
		while (++j < argc - 1)
		{
			lstat(argv[j], &buf);
			lstat(argv[j + 1], &buf2);
			if (buf.st_mtime < buf2.st_mtime)
			{
				tmp = argv[j];
				argv[j] = argv[j + 1];
				argv[j + 1] = tmp;
			}
		}
	}
}

static void		ft_sort_alphabetical_av(int start, char **argv, int argc)
{
	int				i;
	int				j;
	char			*tmp;

	i = start - 1;
	while (++i < argc)
	{
		j = start - 1;
		while (++j < argc - 1)
		{
			if (ft_strcmp(argv[j], argv[j + 1]) > 0)
			{
				tmp = argv[j];
				argv[j] = argv[j + 1];
				argv[j + 1] = tmp;
			}
		}
	}
}

static void		ft_resort_properly_errors(int start, char **argv, int argc,
					int nb)
{
	int				i;
	int				j;
	char			*tmp;
	struct stat		buf;

	i = start - 1;
	while (++i < argc)
	{
		j = start - 1;
		while (++j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) < 0 && lstat(argv[i], &buf)
				&& lstat(argv[j], &buf) && nb == 0)
			{
				tmp = argv[i];
				argv[i] = argv[j];
				argv[j] = tmp;
			}
		}
	}
}

void			ft_sort_argv(int ct_start_fold, char **argv, int argc,
					t_pars *dt)
{
	extern int		errno;
	int				i;

	i = ct_start_fold - 1;
	ft_sort_alphabetical_av(ct_start_fold, argv, argc);
	if (dt->flag_t == 0)
	{
		ft_sort_t_av(ct_start_fold, argv, argc);
		ft_resort_properly_errors(ct_start_fold, argv, argc, dt->flag_t);
	}
	if (dt->flag_r == 0)
	{
		ft_sort_r_av(ct_start_fold, argv, argc);
		ft_resort_properly_errors(ct_start_fold, argv, argc, dt->flag_r);
	}
}
