/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 17:06:56 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:33:43 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_putnbr_long(long int n)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_long(n / 10);
		n %= 10;
	}
	ft_putchar_fd('0' + n, 1);
}

void		ft_putstr_i_to_j(char *str, int i, int j)
{
	while (i < j)
	{
		ft_putchar(str[i]);
		i++;
	}
}

void		ft_print_troncate_str(char *str, char c)
{
	int		begin;
	int		end;

	begin = 0;
	while (str[begin])
		begin++;
	end = begin;
	while (str[begin] != c && begin > -1)
		begin--;
	ft_putstr_i_to_j(str, begin + 1, end);
}

void		ft_initalize_pars(t_pars *dt)
{
	dt->flag_a = 1;
	dt->flag_rr = 1;
	dt->flag_r = 1;
	dt->flag_t = 1;
	dt->flag_l = 1;
	dt->count = 0;
	dt->total_sz_flag_l = 0;
	dt->sz_link = 0;
	dt->sz_size = 0;
	dt->sz_maj_rdev = 0;
	dt->sz_min_rdev = 0;
	dt->index_files = 0;
}

void		ft_free_arr(t_data_ls **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]->path);
		free(arr[i]);
		i++;
	}
	free(arr);
}
