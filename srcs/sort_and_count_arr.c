/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_arr.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:47:42 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:34:21 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_count_files_in_fold(char *str, t_pars *dt)
{
	struct dirent	*d;
	DIR				*dir;
	int				count;

	count = 0;
	if ((dir = opendir(str)) == NULL)
	{
		ft_putstr("ft_ls: ");
		ft_print_troncate_str(str, '/');
		ft_putstr(": ");
		perror("");
		return (0);
	}
	while ((d = readdir(dir)))
		if (!(dt->flag_a == 1 && d->d_name[0] == '.'))
			count++;
	closedir(dir);
	return (count);
}

static void		ft_sort_r_arr(t_pars *dt, t_data_ls ***arr)
{
	int			start;
	int			end;
	t_data_ls	*tmp;

	start = 0;
	end = dt->count - 1;
	while (start < end)
	{
		tmp = arr[0][end];
		arr[0][end] = arr[0][start];
		arr[0][start] = tmp;
		end--;
		start++;
	}
}

static void		ft_sort_t_arr(t_pars *dt, t_data_ls ***arr)
{
	int			i;
	int			j;
	t_data_ls	*tmp;

	i = 0;
	ft_fill_struct_ls_flag_t(arr);
	while (i < dt->count)
	{
		j = 0;
		while (j < dt->count - 1)
		{
			if (arr[0][j]->t_stamp < arr[0][j + 1]->t_stamp)
			{
				tmp = arr[0][j];
				arr[0][j] = arr[0][j + 1];
				arr[0][j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void		ft_sort_alphabetical_arr(t_pars *dt, t_data_ls ***arr)
{
	int			i;
	int			j;
	t_data_ls	*tmp;

	i = 0;
	while (i < dt->count)
	{
		j = 0;
		while (j < dt->count - 1)
		{
			if (ft_strcmp(arr[0][j]->d_name, arr[0][j + 1]->d_name) > 0)
			{
				tmp = arr[0][j];
				arr[0][j] = arr[0][j + 1];
				arr[0][j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void			ft_sort_arr(t_pars *dt, t_data_ls ***arr)
{
	ft_sort_alphabetical_arr(dt, arr);
	if (dt->flag_t == 0)
		ft_sort_t_arr(dt, arr);
	if (dt->flag_r == 0)
		ft_sort_r_arr(dt, arr);
}
