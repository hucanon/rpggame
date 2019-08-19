/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 06:17:14 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 21:32:59 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

void	print_stats(t_perso *list_perso, int flag)
{
	ft_putchar('\n');
	ft_putstr(list_perso[flag].stats[0]);
	printf(" : %s\n\n", list_perso[flag].nom);
	ft_putstr(list_perso[flag].stats[1]);
	printf(" : %d / %d\n", list_perso[flag].pv, list_perso[flag].pv_max);
	ft_putstr(list_perso[flag].stats[2]);
	printf(" : %d\n", list_perso[flag].force);
	ft_putstr(list_perso[flag].stats[3]);
	printf(" : %d\n", list_perso[flag].intelligence);
	ft_putstr(list_perso[flag].stats[4]);
	printf(" : %d\n", list_perso[flag].mvt);
	ft_putstr(list_perso[flag].stats[5]);
	printf(" : %d\n", list_perso[flag].def);
	ft_putstr(list_perso[flag].stats[6]);
	printf(" : %d\n", list_perso[flag].portee);
	ft_putstr(list_perso[flag].stats[7]);
	printf(" : %d\n", list_perso[flag].kill);
	ft_putstr(list_perso[flag].stats[8]);
	printf(" : %d\n\n", list_perso[flag].nb_potions);
}

void	ft_print_names(int map[20][20], int line, int col, t_perso *list_perso, t_coord pointer, t_perso *list_enemies)
{
	if (map[line][col] > 0)
	{
		ft_putstr("\033[1;34m");
		ft_putstr(list_perso[map[line][col] - 1].nom);
	}
	else if (map[line][col] < 0)
	{
		if (map[line][col] == -10)
			ft_putstr("/////");
		else
		{
			ft_putstr("\033[1;31m");
			ft_putstr(list_enemies[-(map[line][col] + 1)].nom);
		}
	}
	else
	{
		if (line == pointer.y && col == pointer.x)
			ft_putstr("\033[01;33m \\ / ");
		else
			(line + col) % 2 == 0 ? ft_putstr(" . . ") : ft_putstr("     ");
	}
	ft_putstr("\033[0m | ");
}

void	ft_print_health(int map[20][20], int line, int col, t_perso *list_perso, t_coord pointer, t_perso *list_enemies)
{
	int		hp;

	if (map[line][col] !=  0 && map[line][col] != -10)
	{
		if (map[line][col] > 0)
			hp = list_perso[map[line][col] - 1].pv * 100 / list_perso[map[line][col] - 1].pv_max;
		else
			hp = list_enemies[-(map[line][col] + 1)].pv * 100 / list_enemies[-(map[line][col] + 1)].pv_max;
		if (hp / 75 >= 1)
			ft_putstr("\033[1;34m ");
		else if (hp / 50 >= 1)
			ft_putstr("\033[0;32m ");
		else if (hp / 25 >= 1)
			ft_putstr("\033[0;33m ");
		else
			ft_putstr("\033[0;31m ");
		if (line == pointer.y && col == pointer.x)
			ft_putstr("\033[01;33m");
		ft_putchar((char)(hp / 100 + 48));
		ft_putchar((char)(hp / 10 % 10 + 48));
		ft_putchar((char)(hp % 10 + 48));
		ft_putchar('%');
	}
	else if (line == pointer.y && col == pointer.x)
		ft_putstr("\033[01;33m / \\ ");
	else if (map[line][col] == -10)
		ft_putstr("/////");
	else
		(line + col) % 2 == 0 ? ft_putstr(" . . ") : ft_putstr("     ");
	ft_putstr("\033[0m | ");
}

void	print_map00(int map[20][20], t_perso *list_perso, t_coord pointer, t_perso *list_enemies)
{
	int		line;
	int		col;

	line = -1;
	ft_putstr("\e[1;1H\e[2J");
	while (++line < 20)
	{
		col = -1;
		ft_putstr("   _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ \n  | ");
		while (++col < 20)
			ft_print_names(map, line, col, list_perso, pointer, list_enemies);
		ft_putstr("\n  | ");
		col = -1;
		while (++col < 20)
			ft_print_health(map, line, col, list_perso, pointer, list_enemies);
		ft_putchar('\n');
	}
	ft_putstr("   _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______ _______  \n\n");
}
