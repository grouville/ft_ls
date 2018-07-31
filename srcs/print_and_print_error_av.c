/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_error_av.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:10:26 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:32:45 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_total(t_av_info *av, char **argv)
{
	if (av->nb_fold >= 1 && av->nb_total > 1)
	{
		ft_putstr(argv[av->tmp]);
		ft_putstr(":\n");
	}
	else if (errno == 13 && av->nb_fold >= 1 && av->index_fold != 1)
	{
		ft_putstr(argv[av->tmp]);
		ft_putstr(":\n");
	}
}

void			ft_print_everything(t_av_info *av, char **argv, int argc,
					t_pars *dt)
{
	DIR				*dir;
	extern int		errno;
	struct stat		buf;

	av->tmp = av->ct_start - 1;
	while (++av->tmp < argc)
	{
		errno = 0;
		dir = opendir(argv[av->tmp]);
		if (!lstat(argv[av->tmp], &buf) && (errno == 0 || errno == 13)
			&& !S_ISLNK(buf.st_mode))
		{
			av->index_fold++;
			if ((av->index_fold != 1 && av->nb_fold > 1)
				|| (av->index_fold == 1 && dt->index_files >= 0
					&& av->nb_files != 0))
				ft_putchar('\n');
			ft_print_total(av, argv);
		}
		dt->index_files = ((av->i == 0 && errno != 0)
			|| S_ISLNK(buf.st_mode)) ? 0 : dt->index_files + 1;
		if (errno == 0 || errno == 13)
			ft_ls(argv[av->tmp], dt, 0);
		dir != NULL ? closedir(dir) : (void)0;
	}
}

static void		ft_file_inexistant(t_av_info *av, char **argv, int i)
{
	DIR				*dir;
	extern int		errno;
	struct stat		buf;

	while (++i < av->argc)
	{
		errno = 0;
		dir = opendir(argv[i]);
		if (errno == 2)
		{
			ft_putstr("ft_ls: ");
			ft_print_troncate_str(argv[i], '/');
			ft_putstr(": ");
			perror("");
		}
		else if (errno == 13 && lstat(argv[i], &buf))
		{
			ft_putstr("ft_ls: ");
			ft_putstr(argv[i]);
			ft_putstr(": ");
			perror("");
		}
		if (dir != NULL)
			closedir(dir);
	}
}

static void		ft_single_file(t_av_info *av, char **argv, t_pars *dt)
{
	int				i;
	DIR				*dir;
	extern int		errno;

	i = av->ct_start - 1;
	while (++i < av->argc)
	{
		errno = 0;
		dir = opendir(argv[i]);
		if (errno == 20)
			ft_ls(argv[i], dt, 0);
		if (dir != NULL)
			closedir(dir);
	}
}

void			ft_print_error(t_av_info *av, char **argv, t_pars *dt)
{
	int i;

	i = av->ct_start - 1;
	ft_file_inexistant(av, argv, i);
	ft_single_file(av, argv, dt);
}
