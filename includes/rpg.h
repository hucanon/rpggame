/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rpg.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 01:52:51 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 04:07:21 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RPG_H
# define RPG_H

# include <pthread.h>
# include <stdio.h>
# include <ncurses.h>
# include <unistd.h>
# include <stdlib.h>

# define ABS(nb) nb < 0 ? -nb : nb

typedef struct	s_struct
{
	int		pv;
	int		pv_max;
	int		force;
	int		intelligence;
	int		mvt;
	int		def;
	int		portee;
	int		kill;
	int		nb_potions;
	int		nb_atk;
	int		nb_mvt;
	char	*nom;
	char	**stats;
}				t_perso;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_coord;

t_coord	ft_make_action(int map[20][20], t_coord pointer, t_perso *list_perso, t_perso *list_enemies, int flag);
t_coord	ft_navigate(int map[20][20], t_coord pointer, t_perso *list_perso, t_perso *list_enemies);
t_perso	*ft_map00(t_perso *list_perso, int nb_map);
t_perso	*init_tab(int sauvegarde);
t_perso	ft_struct_cpy(t_perso perso);
char	**ft_split(char *str, char *charset);
char	*ft_strdup(char *src);
int		menu_maps(char choix[50][500], int nb_choix, int map[20][20], t_perso *list_perso, t_perso *list_enemies);
int		menu_std(char choix[50][500], int nb_choix);
void	ft_print_menu(int input, char choix[50][500], int nb_choix);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_rpg(int sauvegarde);
void	print_map00(int map[20][20], t_perso *list_perso, t_coord pointer, t_perso *list_enemies);
void	print_stats(t_perso *list_perso, int flag);

#endif
