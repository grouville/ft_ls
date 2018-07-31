/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_flag_l.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:40:10 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:33:08 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_links(t_data_ls *arr, t_pars *dt)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	j = 0;
	tmp = arr->l_nlink;
	while (tmp /= 10)
		i++;
	i = i + 1;
	while (i < dt->sz_link)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr_long(arr->l_nlink);
	ft_putchar(' ');
}

void		ft_print_size(t_data_ls *arr, t_pars *dt, t_data_ls **tab)
{
	int		tmp;

	if (tab[0]->l_rdev)
		ft_print_size_dev(arr, dt);
	else
	{
		tmp = arr->l_size;
		ft_print_dev_indent(tmp, dt->sz_size);
		ft_putnbr_long(arr->l_size);
		ft_putchar(' ');
	}
}

void		ft_print_time(t_data_ls *arr)
{
	ft_putstr_i_to_j(ctime(&arr->l_mtime), 8, 11);
	ft_putstr_i_to_j(ctime(&arr->l_mtime), 4, 8);
	ft_putstr_i_to_j(ctime(&arr->l_mtime), 11, 16);
	ft_putchar(' ');
}

void		ft_print_symbolic(t_data_ls *arr)
{
	size_t	ret;
	int		i;
	char	buf[1000];

	i = -1;
	while (i++ < 100)
		buf[i] = 0;
	if (!(ret = readlink(arr->path, buf, 1000)))
		return ;
	buf[ret] = '\0';
	if (buf[0] != 0)
	{
		ft_putstr(" -> ");
		ft_putstr(buf);
	}
	ft_putchar('\n');
}

void		ft_print_uid_name(t_data_ls *arr, t_pars *dt)
{
	if (getpwuid(arr->l_uid) == NULL)
		ft_putnbr_long(arr->l_uid);
	else
		ft_putstr(getpwuid(arr->l_uid)->pw_name);
	while (arr->sz_uid_arr < dt->sz_uid)
	{
		ft_putchar(' ');
		arr->sz_uid_arr++;
	}
	ft_putstr("  ");
}
