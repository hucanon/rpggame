/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 01:59:43 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/18 23:45:10 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

void	ft_print_menu(int input, char choix[50][500], int nb_choix)
{
	int		i;

	write(1, "____________________________\n", 29);
	i = -1;
	while (++i < nb_choix)
	{
		if (input == i)
			write(1, "--> ", 4);
		else
			write(1, "    ", 4);
		ft_putstr(choix[i]);
		write(1, "\n___________________________\n", 30);
	}
}

int		menu_std(char choix[50][500], int nb_choix)
{
	char		c;
	int			pos_pointer;

	pos_pointer = 0;
	ft_print_menu(pos_pointer, choix, nb_choix);
	while (1)
	{
		c = '0';
		system("/bin/stty raw");
		c = getchar();
		system("/bin/stty cooked");
		switch (c)
		{
			case 'w':
				if (pos_pointer > 0)
				{
					ft_putstr("\e[1;1H\e[2J");
					ft_print_menu(--pos_pointer, choix, nb_choix);
				}
				break ;
			case 's':
				if (pos_pointer < nb_choix - 1)
				{
					ft_putstr("\e[1;1H\e[2J");
					ft_print_menu(++pos_pointer, choix, nb_choix);
				}
				break ;
			case ' ':
				return (pos_pointer);
		}
	}
}

int		menu_maps(char choix[50][500], int nb_choix, int map[20][20], t_perso *list_perso, t_perso *list_enemies)
{
	t_coord		pointer;
	char		c;
	int			pos_pointer;

	pointer.x = -1;
	pointer.y = -1;
	pos_pointer = 0;
	print_map00(map, list_perso, pointer, list_enemies);
	ft_print_menu(pos_pointer, choix, nb_choix);
	while (1)
	{
		c = '0';
		system("/bin/stty raw");
		c = getchar();
		system("/bin/stty cooked");
		switch (c)
		{
			case 'w':
				if (pos_pointer > 0)
				{
					print_map00(map, list_perso, pointer ,list_enemies);
					ft_print_menu(--pos_pointer, choix, nb_choix);
				}
				break ;
			case 's':
				if (pos_pointer < nb_choix - 1)
				{
					print_map00(map, list_perso, pointer, list_enemies);
					ft_print_menu(++pos_pointer, choix, nb_choix);
				}
				break ;
			case ' ':
				return (pos_pointer);
		}
	}
}
