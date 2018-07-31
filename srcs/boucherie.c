/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   boucherie.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 04:40:49 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:26:39 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static t_data_ls	*ft_copy_in_struct(t_data_ls *arr, struct dirent *e,
						char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!(arr = (t_data_ls *)malloc(sizeof(t_data_ls))))
		return (NULL);
	while (++i < 256)
		arr->d_name[i] = e->d_name[i];
	arr->d_len = e->d_reclen;
	arr->d_type = e->d_type;
	i = 0;
	if (ft_strcmp(str, "/") != 0)
	{
		tmp = ft_strjoin(str, "/");
		arr->path = ft_strjoin(tmp, e->d_name);
		free(tmp);
	}
	else
		arr->path = ft_strjoin(str, e->d_name);
	return (arr);
}

static void			ft_fill_arr(t_pars *dt, char *str, t_data_ls ***arr)
{
	struct dirent	*e;
	int				i;
	DIR				*first;

	i = 0;
	if (!(first = opendir(str)))
		return ;
	if (!(arr[0] = (t_data_ls **)malloc(sizeof(t_data_ls *) * (dt->count + 1))))
		return ;
	while ((e = readdir(first)))
		if (!(dt->flag_a == 1 && e->d_name[0] == '.'))
		{
			arr[0][i] = ft_copy_in_struct(arr[0][i], e, str);
			i++;
		}
	arr[0][i] = NULL;
	ft_sort_arr(dt, arr);
	closedir(first);
}

void				ft_iterate_on_folders(t_data_ls **arr, t_pars *dt,
						int stack)
{
	int				i;
	struct stat		buf;

	i = 0;
	while (arr[i])
	{
		lstat(arr[i]->path, &buf);
		if (!((arr[i]->d_name)[0] == '.' && ft_strlen(arr[i]->d_name) == 1)
				&& (ft_strcmp(arr[i]->d_name, "..\0")) != 0
				&& (S_ISDIR(buf.st_mode)))
		{
			ft_putchar('\n');
			ft_putstr(arr[i]->path);
			ft_putstr(":\n");
			ft_ls(arr[i]->path, dt, stack + 1);
		}
		i++;
	}
}

int					ft_ls(char *str, t_pars *dt, int stack)
{
	t_data_ls		**arr;
	struct stat		buf;

	if (stack == 0)
		if (lstat(str, &buf) == -1)
			return (-1);
	if ((stack == 0 ? S_ISDIR(buf.st_mode) : 1))
	{
		if ((dt->count = ft_count_files_in_fold(str, dt)) == 0)
			return (-1);
		ft_fill_arr(dt, str, &arr);
		ft_print_folder(arr, dt);
		if (dt->flag_rr == 0)
			ft_iterate_on_folders(arr, dt, stack);
		ft_free_arr(arr);
	}
	else if (dt->flag_l == 0 && stack == 0)
		ft_print_l_file(str, dt);
	else
	{
		ft_putstr(str);
		ft_putchar('\n');
	}
	return (0);
}

int					main(int argc, char **argv)
{
	t_pars		dt;
	t_av_info	av;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	ft_initalize_pars(&dt);
	av.ct_start = ft_pars_argv(argv, &dt) + 1;
	if (av.ct_start == argc)
	{
		ft_fill_av(argv, argc);
		argc = argc + 1;
		ret = 1;
	}
	ft_sort_argv(av.ct_start, argv, argc, &dt);
	ft_count_type_files(&av, argv, argc);
	ft_print_error(&av, argv, &dt);
	ft_print_everything(&av, argv, argc, &dt);
	if (ret == 1)
		free(argv[argc - 1]);
	return (0);
}
