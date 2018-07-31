/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_l_single_arg.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:30:10 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:33:26 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_copy_l_file_dname(char *str, t_data_ls *cas)
{
	int			begin;
	int			i;

	begin = 0;
	i = 0;
	while (str[begin] && begin < 256)
	{
		cas->d_name[i] = str[begin];
		begin++;
		i++;
	}
	cas->d_name[i] = '\0';
}

void			ft_print_l_file(char *str, t_pars *dt)
{
	t_data_ls	**cas;

	if (!(cas = (t_data_ls **)malloc(sizeof(t_data_ls *) * 2)))
		return ;
	if (!(cas[0] = (t_data_ls *)malloc(sizeof(t_data_ls))))
		return ;
	cas[1] = NULL;
	cas[0]->path = ft_strdup(str);
	ft_copy_l_file_dname(str, cas[0]);
	ft_fill_struct_ls_flag_l(dt, &cas);
	ft_print_folder_flag_l(cas, dt);
	ft_free_arr(cas);
}

void			ft_fill_struct_ls_flag_l(t_pars *dt, t_data_ls ***arr)
{
	int			i;
	struct stat	buf;

	i = -1;
	dt->nb_file_write_perm = 0;
	dt->total_sz_flag_l = 0;
	while (arr[0][++i])
	{
		if (!lstat(arr[0][i]->path, &buf)
			|| ft_strcmp(arr[0][i]->path, "/dev/fd") == 47)
		{
			arr[0][i]->l_mod = buf.st_mode;
			arr[0][i]->l_nlink = buf.st_nlink;
			arr[0][i]->l_uid = buf.st_uid;
			arr[0][i]->l_gid = buf.st_gid;
			arr[0][i]->l_size = buf.st_size;
			arr[0][i]->l_mtime = buf.st_mtime;
			arr[0][i]->l_rdev = buf.st_rdev;
			dt->total_sz_flag_l = dt->total_sz_flag_l + buf.st_blocks;
		}
		else
			dt->nb_file_write_perm++;
	}
}

void			ft_print_folder(t_data_ls **arr, t_pars *dt)
{
	if (dt->flag_l == 0)
	{
		ft_fill_struct_ls_flag_l(dt, &arr);
		ft_print_folder_flag_l(arr, dt);
	}
	else
		ft_print_folder_normal(arr);
}
