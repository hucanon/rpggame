/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 05:01:00 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 21:29:51 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

t_perso	*init_tab(int sauvegarde)
{
	t_perso	*list_perso;
	int		i;
//	if (sauvegarde == 1)
//		return (parsing_perso());
	i = -1;
	(void)sauvegarde;
	list_perso = (t_perso *)malloc(sizeof(t_perso) * 7);
	while (++i < 7)
	{
		list_perso[i].stats = ft_split("Name\nHP\nStrength\nSpirit\nMobility\nDefense\nRange\nTalent points\nNumber of potions", "\n");
		list_perso[i].portee = 1;
		if (i == 0)
		{
			list_perso[i].pv_max = 20;
			list_perso[i].force = 7;
			list_perso[i].intelligence = 3;
			list_perso[i].mvt = 4;
			list_perso[i].def = 4;
			list_perso[i].nom = ft_strdup("Chrom");
		}
		else if (i == 1)
		{
			list_perso[i].pv_max = 12;
			list_perso[i].force = 2;
			list_perso[i].intelligence = 12;
			list_perso[i].mvt = 3;
			list_perso[i].def = 1;
			list_perso[i].portee = 2;
			list_perso[i].nom = ft_strdup("Rizel");
		}
		else if (i == 2)
		{
			list_perso[i].pv_max = 22;
			list_perso[i].force = 10;
			list_perso[i].intelligence = 1;
			list_perso[i].mvt = 3;
			list_perso[i].def = 2;
			list_perso[i].nom = ft_strdup("Uldur");
		}
		else if (i == 3)
		{
			list_perso[i].pv_max = 9;
			list_perso[i].force = 7;
			list_perso[i].intelligence = 1;
			list_perso[i].mvt = 3;
			list_perso[i].def = 3;
			list_perso[i].nom = ft_strdup(" Orc ");
		}
		else if (i == 4)
		{
			list_perso[i].pv_max = 7;
			list_perso[i].force = 2;
			list_perso[i].intelligence = 7;
			list_perso[i].mvt = 3;
			list_perso[i].def = 1;
			list_perso[i].portee = 2;
			list_perso[i].nom = ft_strdup("Necro");
		}
		else if (i == 5)
		{
			list_perso[i].pv_max = 14;
			list_perso[i].force = 6;
			list_perso[i].intelligence = 2;
			list_perso[i].mvt = 3;
			list_perso[i].def = 4;
			list_perso[i].nom = ft_strdup("Gnoll");
		}
		else
		{
			list_perso[i].pv_max = 4;
			list_perso[i].force = 12;
			list_perso[i].intelligence = 5;
			list_perso[i].mvt = 3;
			list_perso[i].def = 1;
			list_perso[i].nom = ft_strdup("Rogue");
		}
		list_perso[i].pv = list_perso[i].pv_max;
		list_perso[i].kill = 0;
		list_perso[i].nb_atk = 1;
		list_perso[i].nb_mvt = 1;
		list_perso[i].nb_potions = 3;
	}
	return (list_perso);
}
