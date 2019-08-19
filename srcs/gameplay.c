/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gameplay.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 00:07:59 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 23:47:11 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

void	test_navigation(int	map[20][20], t_coord pointer, t_perso *list_perso, t_perso *list_enemies)
{
	if (map[pointer.y][pointer.x] > 0)
	{
		if (list_perso[map[pointer.y][pointer.x] - 1].nb_mvt > 0)
			ft_putstr("\033[01;33mThis unit can still move during this turn !\n\033[0m");
		if (list_perso[map[pointer.y][pointer.x] - 1].nb_atk > 0)
			ft_putstr("\033[01;33mThis unit has an action left to do !\n\033[0m");
		print_stats(list_perso, map[pointer.y][pointer.x] - 1);
	}	
	else if (map[pointer.y][pointer.x] < 0 && map[pointer.y][pointer.x] > -10)
		print_stats(list_enemies, -(map[pointer.y][pointer.x] + 1));
}

t_coord ft_navigate(int map[20][20], t_coord pointer, t_perso *list_perso, t_perso *list_enemies)
{
	char		c;

	while (1)
	{
		print_map00(map, list_perso, pointer, list_enemies);
		test_navigation(map, pointer, list_perso, list_enemies);
		usleep(500);
		c = '0';
		system("/bin/stty raw");
		c = getchar();
		system("/bin/stty cooked");
		switch (c)
		{
			case 'w':
				if (pointer.y > 0)
					pointer.y--;
				break ;
			case 's':
				if (pointer.y < 19)
					pointer.y++;
				break ;
			case 'a':
				if (pointer.x > 0)
					pointer.x--;
				break ;
			case 'd':
				if (pointer.x < 19)
					pointer.x++;
				break ;
			case ' ':
				return (pointer);
		}
	}
	return (pointer);
}

t_coord	ft_make_action(int map[20][20], t_coord pointer, t_perso *list_perso, t_perso *list_enemies, int flag)
{
	char	c;
	int		range;
	t_coord	sub_pointer;

	c = '0';
	sub_pointer.x = pointer.x;
	sub_pointer.y = pointer.y;
	range = (flag == 1) ? list_perso[abs(map[pointer.y][pointer.x]) - 1].mvt : list_perso[abs(map[pointer.y][pointer.x]) - 1].portee;
	while (c != ' ')
	{
		print_map00(map, list_perso, pointer, list_enemies);
		usleep(500);
		c = '0';
		system("/bin/stty raw");
		c = getchar();
		system("/bin/stty cooked");
		switch (c)
		{
			case 'w':
				if (sub_pointer.y > 0 && abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) <= range)
				{
					sub_pointer.y--;
					if (abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) > range)
						sub_pointer.y++;
				}
				break ;
			case 's':
				if (sub_pointer.y < 19 && abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) <= range)
				{
					sub_pointer.y++;
					if (abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) > range)
						sub_pointer.y--;
				}
				break ;
			case 'a':
				if (sub_pointer.x > 0 && abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) <= range)
				{
					sub_pointer.x--;
					if (abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) > range)
						sub_pointer.x++;
				}
				break ;
			case 'd':
				if (sub_pointer.x < 19 && abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) <= range)
				{
					sub_pointer.x++;
					if (abs(pointer.y - sub_pointer.y) + abs(pointer.x - sub_pointer.x) > range)
						sub_pointer.x--;
				}
				break ;
		}
	}
	if (flag == 1)
	{
		if (map[sub_pointer.y][sub_pointer.x] != 0)
		{
			ft_putstr("Impossible move\n");
			sleep(1);
		}
		else
		{
			map[sub_pointer.y][sub_pointer.x] = map[pointer.y][pointer.x];
			map[pointer.y][pointer.x] = 0;
			list_perso[abs(map[sub_pointer.y][sub_pointer.x]) - 1].nb_mvt--;
		}
	}
	else
	{
		if (map[sub_pointer.y][sub_pointer.x] < 0 && map[sub_pointer.y][sub_pointer.x] > -10)
		{
		list_enemies[abs(map[sub_pointer.y][sub_pointer.x]) - 1].pv -= (list_perso[abs(map[pointer.y][pointer.x]) - 1].portee == 1) ? list_perso[abs(map[pointer.y][pointer.x]) - 1].force - list_enemies[abs(map[sub_pointer.y][sub_pointer.x]) - 1].def : list_perso[abs(map[pointer.y][pointer.x]) - 1].intelligence - list_enemies[abs(map[sub_pointer.y][sub_pointer.x]) - 1].intelligence;
		list_perso[abs(map[pointer.y][pointer.x]) - 1].nb_atk--;
		}
		else
		{
			ft_putstr("Unvalid target");
			sleep(1);
		}
	}
	return (sub_pointer);
}
