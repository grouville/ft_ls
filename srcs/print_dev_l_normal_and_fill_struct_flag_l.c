/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_dev__l_and_normal.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:42:44 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:22:12 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_fill_struct_ls_flag_t(t_data_ls ***arr)
{
	int			i;
	struct stat	buf;

	i = 0;
	while (arr[0][i])
	{
		lstat(arr[0][i]->path, &buf);
		arr[0][i]->t_stamp = buf.st_mtime;
		i++;
	}
}

void		ft_print_folder_normal(t_data_ls **arr)
{
	int			i;
	struct stat buf;

	i = 0;
	while (arr[i])
	{
		if (!lstat(arr[i]->path, &buf)
			|| ft_strcmp(arr[i]->path, "/dev/fd") == 47)
		{
			ft_putstr(arr[i]->d_name);
			ft_putchar('\n');
		}
		i++;
	}
}

void		ft_print_permissions(t_data_ls *arr)
{
	if (S_ISDIR(arr->l_mod))
		ft_putchar('d');
	else if (S_ISLNK(arr->l_mod))
		ft_putchar('l');
	else if (S_ISBLK(arr->l_mod))
		ft_putchar('b');
	else if (S_ISFIFO(arr->l_mod))
		ft_putchar('p');
	else if (S_ISSOCK(arr->l_mod))
		ft_putchar('s');
	else
		ft_putchar((S_ISCHR(arr->l_mod)) ? 'c' : '-');
	ft_putchar((arr->l_mod & S_IRUSR) ? 'r' : '-');
	ft_putchar((arr->l_mod & S_IWUSR) ? 'w' : '-');
	ft_putchar((arr->l_mod & S_IXUSR) ? 'x' : '-');
	ft_putchar((arr->l_mod & S_IRGRP) ? 'r' : '-');
	ft_putchar((arr->l_mod & S_IWGRP) ? 'w' : '-');
	ft_putchar((arr->l_mod & S_IXGRP) ? 'x' : '-');
	ft_putchar((arr->l_mod & S_IROTH) ? 'r' : '-');
	ft_putchar((arr->l_mod & S_IWOTH) ? 'w' : '-');
	ft_putchar((arr->l_mod & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}

void		ft_print_dev_indent(int tmp, int limit)
{
	int		len;

	len = 0;
	while (tmp /= 10)
		len++;
	len = len + 1;
	while (len < limit)
	{
		ft_putchar(' ');
		len++;
	}
}

void		ft_print_size_dev(t_data_ls *arr, t_pars *dt)
{
	int		tmp;

	if (arr->l_rdev || S_ISCHR(arr->l_mod))
	{
		tmp = major(arr->l_rdev);
		ft_print_dev_indent(tmp, dt->sz_maj_rdev);
		ft_putnbr_long(major(arr->l_rdev));
		ft_putstr(", ");
		tmp = minor(arr->l_rdev);
		ft_print_dev_indent(tmp, dt->sz_min_rdev);
		ft_putnbr_long(minor(arr->l_rdev));
		ft_putchar(' ');
	}
	else
	{
		tmp = arr->l_size;
		ft_print_dev_indent(tmp, dt->sz_maj_rdev);
		ft_putstr("   ");
		tmp = arr->l_size;
		ft_print_dev_indent(tmp, dt->sz_min_rdev);
		ft_putnbr_long(arr->l_size);
	}
}
