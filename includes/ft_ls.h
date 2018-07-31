/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:38:38 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:53:44 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <errno.h>
# include <uuid/uuid.h>
# include "libft.h"

/*
*** - Struct contenant toutes les infos des dossiers/ fichiers
*/
typedef struct		s_data_ls
{
	char			d_name[256];
	unsigned char	d_type;
	char			*path;
	unsigned short	d_len;
	time_t			t_stamp;
	mode_t			l_mod;
	nlink_t			l_nlink;
	uid_t			l_uid;
	gid_t			l_gid;
	off_t			l_size;
	time_t			l_mtime;
	dev_t			l_rdev;
	int				sz_uid_arr;
	int				sz_gid_arr;
}					t_data_ls;

/*
*** - Struct contenant les flags du parsing, mais aussi des choses utils pour
*** - l'indentation
*/
typedef struct		s_pars
{
	int				flag_a;
	int				flag_rr;
	int				flag_r;
	int				flag_t;
	int				flag_l;
	int				count;
	int				sz_link;
	long long int	sz_size;
	int				sz_uid;
	int				sz_gid;
	int				sz_maj_rdev;
	int				sz_min_rdev;
	long long int	total_sz_flag_l;
	int				index_files;
	int				nb_file_write_perm;
}					t_pars;

/*
*** - Struct d'aide pour l'affichage des args
*/
typedef struct		s_av_info
{
	int				ct_start;
	int				nb_fold;
	int				nb_files;
	int				nb_total;
	int				tmp;
	int				index_fold;
	int				index_files;
	int				i;
	int				argc;
}					t_av_info;

/*
*** - Feuille : boucherie.c
*/
int					main(int argc, char **argv);
int					ft_ls(char *str, t_pars *dt, int stack);
void				ft_iterate_on_folders(t_data_ls **arr, t_pars *dt,
						int stack);

/*
*** - Feuille : print_dev_l_normal_and_fill_struct_flag_l.c
*/
void				ft_print_size_dev(t_data_ls *arr, t_pars *dt);
void				ft_print_permissions(t_data_ls *arr);
void				ft_print_folder_normal(t_data_ls **arr);
void				ft_fill_struct_ls_flag_t(t_data_ls ***arr);
void				ft_print_dev_indent(int tmp, int limit);

/*
*** - Feuille : sort_and_count_arr.c
*/
int					ft_count_files_in_fold(char *str, t_pars *dt);
void				ft_sort_arr(t_pars *dt, t_data_ls ***arr);

/*
*** - Feuille : print_flag_l.c
*/
void				ft_print_links(t_data_ls *arr, t_pars *dt);
void				ft_print_size(t_data_ls *arr, t_pars *dt, t_data_ls **tab);
void				ft_print_time(t_data_ls *arr);
void				ft_print_symbolic(t_data_ls *arr);
void				ft_print_uid_name(t_data_ls *arr, t_pars *dt);

/*
*** - Feuille : print_folder_flag_l.c
*/
void				ft_size_nb_links(t_data_ls **arr, t_pars *dt);
void				ft_size_groups(t_data_ls **arr, t_pars *dt, int i);
void				ft_print_folder_flag_l(t_data_ls **arr, t_pars *dt);

/*
*** - Feuille : print_l_single_arg.c
*/
void				ft_print_l_file(char *str, t_pars *dt);
void				ft_print_folder(t_data_ls **arr, t_pars *dt);
void				ft_fill_struct_ls_flag_l(t_pars *dt, t_data_ls ***arr);

/*
*** - Feuille : sort_av.c
*/
void				ft_sort_argv(int ct_start_fold, char **argv, int argc,
						t_pars *dt);

/*
*** - Feuille : utils.c
*/
void				ft_putnbr_long(long int n);
void				ft_putstr_i_to_j(char *str, int i, int j);
void				ft_print_troncate_str(char *str, char c);
void				ft_initalize_pars(t_pars *dt);
void				ft_free_arr(t_data_ls **arr);

/*
*** - Feuille : parse_and_utils_av.c
*/
void				ft_count_type_files(t_av_info *av, char **argv, int argc);
void				ft_fill_av(char **argv, int argc);
int					ft_pars_argv(char **argv, t_pars *dt);

/*
*** - Feuille : print_and_print_error_av.c
*/
void				ft_print_everything(t_av_info *av, char **argv, int argc,
						t_pars *dt);
void				ft_print_error(t_av_info *av, char **argv, t_pars *dt);

#endif
