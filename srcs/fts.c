/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fts.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 03:47:09 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/19 00:44:04 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;
	
	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar('c');
		i++;
	}
	return (i);
}

int		is_charset(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*newline(char *str, int *i, char *charset)
{
	char	*newline;
	int		j;

	j = 0;
	if (!(newline = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	while (is_charset(str[*i], charset) == 0 && str[*i])
	{
		newline[j] = str[*i];
		j++;
		(*i)++;
	}
	newline[j] = 0;
	return (newline);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	char	**strs;
	int		j;

	j = 0;
	i = 0;
	if (!(strs = (char**)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	while (str[i])
	{
		while (is_charset(str[i], charset) == 1)
			i++;
		if (str[i] == 0)
			return (strs);
		if (!(strs[j] = newline(str, &i, charset)))
			return (0);
		j++;
	}
	strs[j] = 0;
	return (strs);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char *str;

	str = (char*)malloc(ft_strlen(src) + 1);
	ft_strcpy(str, src);
	return (str);
}

t_perso	ft_struct_cpy(t_perso perso)
{
	t_perso	enemy;

	enemy.pv = perso.pv;
	enemy.pv_max = perso.pv_max;
	enemy.force = perso.force;
	enemy.intelligence = perso.intelligence;
	enemy.mvt = perso.mvt;
	enemy.def = perso.def;
	enemy.portee = perso.portee;
	enemy.kill = perso.kill;
	enemy.nb_potions = perso.nb_potions;
	enemy.nb_atk = perso.nb_atk;
	enemy.nb_mvt = perso.nb_mvt;
	enemy.nom = ft_strdup(perso.nom);
	printf(" %s\n", enemy.nom);
	enemy.stats = ft_split("Name\nHP\nStrength\nSpirit\nMobility\nDefense\nRange\nTalent points\nNumber of potions", "\n");
	return (enemy);
}
