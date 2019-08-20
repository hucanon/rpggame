/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map00.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 12:43:08 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 04:32:32 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

t_perso	*init_map00(int map[20][20], t_perso *list_perso)
{
	t_coord	pos_team[3];
	t_perso	*list_enemies;
	int		i;
	int		j;
	int		n;
	int		k;

	pos_team[0].x = 3;
	pos_team[0].y = 5;
	pos_team[1].x = 1;
	pos_team[1].y = 4;
	pos_team[2].x = 2;
	pos_team[2].y = 3;
	if (!(list_enemies = malloc(sizeof(t_perso) * 6)))
		return (0);
	i = -1;
	k = 0;
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
		{
			n = -1;
			map[i][j] = 0;
			while (++n < 3)
				if (pos_team[n].x == j && pos_team[n].y == i)
					map[i][j] = n + 1;
			if ((i == 5 && j == 12) || (i == 8 && j == 12) || (i == 9 && j == 15))
			{
				map[i][j] = -(k + 1);
				list_enemies[k++] = ft_struct_cpy(list_perso[3]);
			}
			else if ((i == 7 && j == 13) || (i == 13 && j == 14))
			{
				map[i][j] = -(k + 1);
				list_enemies[k++] = ft_struct_cpy(list_perso[4]);
			}
			else if (i == 11 && j == 18)
			{
				map[i][j] = -(k + 1);
				list_enemies[k++] = ft_struct_cpy(list_perso[5]);
			}
			else if (((i > 10 || j > 16) && (j - i > 10 || j - i < 0)) || (i < 2))
				map[i][j] = -10;
		}
	}
	return (list_enemies);
}

void	create_obstacles_map(char mappy[20][20], int map[20][20], int n)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
		{
			if (map[i][j] == 0 || map[i][j] == -n || map[i][j] == 1)
				mappy[i][j] = 0;
			else
				mappy[i][j] = 1;
		}
	}
}

void	ft_new_turn(int map[20][20], t_perso *list_perso, t_perso *list_enemies, int nb_enemies)
{
	t_coord	end;
	t_coord	start;
	t_coord	tmp;
	int		n;
	int		mvt;
	char	mappy[20][20];

	n = -1;
	(void)list_perso;
	while (++n < nb_enemies)
	{
		if (list_enemies[n].pv > 0)
		{
			//ft_find_closest_enemy();
			mvt = list_enemies[n].mvt;
			while (mvt > 0)
			{
				create_obstacles_map(mappy, map, n);
				start.y = -1;
				while (++start.y < 20)
				{
					start.x = -1;
					while (++start.x < 20)
						if (map[start.y][start.x] == -(n + 1))
							tmp = start;
				}
				start = tmp;
				end.y = -1;
				while (++end.y < 20)
				{
					end.x = -1;
					while (++end.x < 20)
						if (map[end.y][end.x] == 1)
							tmp = end;
				}
				end = tmp;
				tmp = pathfinding(mappy, (start.x + start.y * 20), (end.x + end.y * 20));
				if (tmp.x == start.x && tmp.y == start.y)
				{
					list_perso[0].pv -= (list_enemies[n].portee > 1) ? (list_enemies[n].intelligence - list_perso[0].intelligence) : (list_enemies[n].force - list_perso[0].def);
					break ;
				}
				if (tmp.y != start.y && tmp.x != start.x)
				{
					if (mvt > 1)
					{
						map[tmp.y][tmp.x] = -(n + 1);
						map[start.y][start.x] = 0;
						mvt -= 2;
					}
					else
					{
						if (tmp.y > start.y && map[start.y + 1][start.x] == 0)
						{
							map[start.y + 1][start.x] = -(n + 1);
							map[start.y][start.x] = 0;
						}
						else if (tmp.y < start.y && map[start.y - 1][start.x] == 0)
						{
							map[start.y - 1][start.x] = -(n + 1);
							map[start.y][start.x] = 0;
						}
						else if (tmp.x > start.x && map[start.y][start.x + 1] == 0)
						{
							map[start.y][start.x + 1] = -(n + 1);
							map[start.y][start.x] = 0;
						}
						else if (tmp.x < start.x && map[start.y][start.x - 1] == 0)
						{
							map[start.y][start.x - 1] = -(n + 1);
							map[start.y][start.x] = 0;
						}
						mvt--;
						if (map[tmp.y][tmp.x] == 1)
						{
							list_perso[0].pv -= (list_enemies[n].portee > 1) ? (list_enemies[n].intelligence - list_perso[0].intelligence) : (list_enemies[n].force - list_perso[0].def);
							break ;
						}
					}
				}
				else
				{
					map[tmp.y][tmp.x] = -(n + 1);
					map[start.y][start.x] = 0;
					mvt--;
				}
				print_map00(map, list_perso, tmp, tmp, list_enemies, -1000);
				usleep(200000);
			}
		}
	}
	print_map00(map, list_perso, tmp, tmp, list_enemies, -1000);
}

t_perso	*ft_map00(t_perso *list_perso, int nb_map)
{
	t_perso	*list_enemies;
	t_coord	pointer;
	char	choix_perso[50][500] = { "Movement", "Attack", "Drink potion", "Go back" };
	char	choix_turn[50][500] = { "Continue", "End your turn", "Finish game" };
	char	choix_verif[50][500] = { "I am sure", "I changed my mind" };
	int		map[20][20];
	int		a;
	int		b;

	pointer.x = 0;
	pointer.y = 0;
	(void)nb_map;
	//	if (nb_map == 0)
	list_enemies = init_map00(map, list_perso);
	//	else if (map == 1)
	//		init_map01(map);
	//	else
	//		init_map02(map);
	while (1)
	{
		pointer = ft_navigate(map, pointer, list_perso, list_enemies);
		if (map[pointer.y][pointer.x] > 0)
		{
			a = -1;
			while (a < 3)
			{
				a = menu_maps(choix_perso, 4, map, pointer, list_perso, list_enemies);
				if (a == 0)
				{
					if (list_perso[map[pointer.y][pointer.x] - 1].nb_mvt > 0)
						pointer = ft_make_action(map, pointer, list_perso, list_enemies, 1);
					else
					{
						ft_putstr("This character has already moved.\n");
						sleep(1);
					}
				}
				else if (a == 1)
				{
					if (list_perso[map[pointer.y][pointer.x] - 1].nb_atk > 0)
						pointer = ft_make_action(map, pointer, list_perso, list_enemies, 2);
					else
					{
						ft_putstr("This character has already made an action.\n");
						sleep(1);
					}
				}
				else if (a == 2)
				{
					if (list_perso[map[pointer.y][pointer.x] - 1].nb_potions > 0 && list_perso[map[pointer.y][pointer.x] - 1].nb_atk > 0)
					{
						if (menu_maps(choix_verif, 2, map, pointer, list_perso, list_enemies) == 0)
						{
							list_perso[map[pointer.y][pointer.x] - 1].nb_potions--;
							list_perso[map[pointer.y][pointer.x] - 1].nb_atk--;
							list_perso[map[pointer.y][pointer.x] - 1].pv = (list_perso[map[pointer.y][pointer.x] - 1].pv + 15 > list_perso[map[pointer.y][pointer.x] - 1].pv_max) ? list_perso[map[pointer.y][pointer.x] - 1].pv_max : list_perso[map[pointer.y][pointer.x] - 1].pv + 15;
							ft_putstr("\nPotion drunk.\n15 HP restored.\n");
							sleep(2);
						}
					}
					else if (list_perso[map[pointer.y][pointer.x] - 1].nb_atk == 0)
					{
						ft_putstr("This character has already made an action.\n");
						sleep(1);
					}
					else
					{
						ft_putstr("This character has no potion left.\n");
						sleep(1);
					}
				}
			}
		}
		else
		{
			b = menu_maps(choix_turn, 3, map, pointer, list_perso, list_enemies);
			if (b == 1)
			{
				if (menu_maps(choix_verif, 2, map, pointer, list_perso, list_enemies) == 0)
				{
					b = -1;
					while (++b < 3)
					{
						list_perso[b].nb_atk = 1;
						list_perso[b].nb_mvt = 1;
					}
					ft_new_turn(map, list_perso, list_enemies, 6);
					ft_putstr("\nNew turn !\n");
					sleep(1);
				}
			}
			else if (b == 2)
				if (menu_maps(choix_verif, 2, map, pointer, list_perso, list_enemies) == 0)
					return (list_perso);
		}
	}
}
