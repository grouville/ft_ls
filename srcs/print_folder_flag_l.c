/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_folder_flag_l.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:35:47 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:37:20 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_gid_name(t_data_ls *arr, t_pars *dt)
{
	if (getgrgid(arr->l_gid))
		ft_putstr(getgrgid(arr->l_gid)->gr_name);
	else
		ft_putstr("wheel");
	while (arr->sz_gid_arr < dt->sz_gid)
	{
		ft_putchar(' ');
		arr->sz_gid_arr++;
	}
	ft_putstr("  ");
}

static void		ft_size_nb_links_device(t_data_ls *arr, t_pars *dt)
{
	int	tmp;
	int	tmp2;
	int	i;
	int	j;

	i = 0;
	tmp = major(arr->l_rdev);
	while (tmp /= 10)
		i++;
	dt->sz_maj_rdev = (dt->sz_maj_rdev > i + 1 ? dt->sz_maj_rdev : i + 1);
	tmp2 = minor(arr->l_rdev);
	j = 0;
	while (tmp2 /= 10)
		j++;
	dt->sz_min_rdev = (dt->sz_min_rdev > j + 1 ? dt->sz_min_rdev : j + 1);
}

void			ft_size_nb_links(t_data_ls **arr, t_pars *dt)
{
	int				i;
	int				tmp;
	int				j;
	long long int	tmp2;
	int				k;

	i = 0;
	while (arr[i])
	{
		j = 0;
		k = 0;
		tmp = arr[i]->l_nlink;
		while (tmp /= 10)
			j++;
		dt->sz_link = (dt->sz_link > j + 1 ? dt->sz_link : j + 1);
		tmp2 = arr[i]->l_size;
		while (tmp2 /= 10)
			k++;
		dt->sz_size = (dt->sz_size > k + 1 ? dt->sz_size : k + 1);
		ft_size_nb_links_device(arr[i], dt);
		i++;
	}
}

void			ft_size_groups(t_data_ls **arr, t_pars *dt, int i)
{
	dt->sz_uid = 0;
	dt->sz_gid = 0;
	while (arr[++i])
	{
		if (getgrgid(arr[i]->l_gid) != NULL)
			if ((arr[i]->sz_gid_arr =
			ft_strlen(getgrgid(arr[i]->l_gid)->gr_name)) > dt->sz_gid)
				dt->sz_gid = arr[i]->sz_gid_arr;
		if (getpwuid(arr[i]->l_uid) != NULL)
		{
			if ((arr[i]->sz_uid_arr =
					ft_strlen(getpwuid(arr[i]->l_uid)->pw_name)) > dt->sz_uid)
				dt->sz_uid = arr[i]->sz_uid_arr;
		}
		else
		{
			arr[i]->sz_uid_arr = 0;
			while (arr[i]->l_uid /= 10)
				arr[i]->sz_uid_arr++;
			if (arr[i]->sz_uid_arr > dt->sz_uid)
				dt->sz_uid = arr[i]->sz_uid_arr;
		}
	}
}

void			ft_print_folder_flag_l(t_data_ls **arr, t_pars *dt)
{
	int	i;

	i = -1;
	if (dt->nb_file_write_perm == 0)
	{
		ft_size_groups(arr, dt, i);
		ft_size_nb_links(arr, dt);
		if (dt->index_files != 0)
		{
			ft_putstr("total ");
			ft_putnbr_long(dt->total_sz_flag_l);
			ft_putchar('\n');
		}
		while (arr[++i])
		{
			ft_print_permissions(arr[i]);
			ft_print_links(arr[i], dt);
			ft_print_uid_name(arr[i], dt);
			ft_print_gid_name(arr[i], dt);
			ft_print_size(arr[i], dt, arr);
			ft_print_time(arr[i]);
			ft_putstr(arr[i]->d_name);
			ft_print_symbolic(arr[i]);
		}
	}
}
