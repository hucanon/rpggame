/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinding.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hucanon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 03:56:06 by hucanon      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/20 03:56:10 by hucanon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rpg.h"

int ind[map_size_rows][map_size_cols] = 
{
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

t_coord pathfinding(char map[20][20], int start, int end)
{
	int				i, j, k, l, b, cpt_start, cpt_end, found;
	int				p_len = 0;
	int				*path = NULL;
	int				c_len = 0;
	int 			*closed = NULL;
	int				o_len = 1;
	int				*open = (int *)calloc(o_len, sizeof(int));
	double			min, tempg;
	int				current;
	int				s_len = 0;
	struct stop		*stops = NULL;
	int				r_len = 0;
	struct route	*routes = NULL;
	t_coord			final;

	cpt_start = 0;
	cpt_end = 0;
	for (i = 0; i < map_size_rows; i++)
	{
		for (j = 0; j < map_size_cols; j++)
		{
			if (map[i][j] == 0)
			{
				++s_len;
				stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop));
				int t = s_len - 1;
				stops[t].col = j;
				stops[t].row = i;
				stops[t].from = -1;
				stops[t].g = DBL_MAX;
				stops[t].n_len = 0;
				stops[t].n = NULL;
				ind[i][j] = t;
			}
			if (map[i][j] == 1 && cpt_start + s_len < start)
				cpt_start++;
			if (map[i][j] == 1 && cpt_end + s_len < end)
				cpt_end++;
		}
	}
	start -= cpt_start;
	end -= cpt_end;
	for (i = 0; i < s_len; i++)
		stops[i].h = sqrt(pow(stops[end].row - stops[i].row, 2) + pow(stops[end].col - stops[i].col, 2));
	for (i = 0; i < map_size_rows; i++)
		for (j = 0; j < map_size_cols; j++)
			if (ind[i][j] >= 0)
				for (k = i - 1; k <= i + 1; k++)
					for (l = j - 1; l <= j + 1; l++)
					{
						if ((k == i) and (l == j))
							continue;
						if (ind[k][l] >= 0)
						{
							++r_len;
							routes = (struct route *)realloc(routes, r_len * sizeof(struct route));
							int t = r_len - 1;
							routes[t].x = ind[i][j];
							routes[t].y = ind[k][l];
							routes[t].d = sqrt(pow(stops[routes[t].y].row - stops[routes[t].x].row, 2) + pow(stops[routes[t].y].col - stops[routes[t].x].col, 2));
							++stops[routes[t].x].n_len;
							stops[routes[t].x].n = (int*)realloc(stops[routes[t].x].n, stops[routes[t].x].n_len * sizeof(int));
							stops[routes[t].x].n[stops[routes[t].x].n_len - 1] = t;
						}
					}
	open[0] = start;
	stops[start].g = 0;
	stops[start].f = stops[start].g + stops[start].h;
	found = 0;
	while (o_len and not found)
	{
		min = DBL_MAX;
		for (i = 0; i < o_len; i++)
		{
			if (stops[open[i]].f < min)
			{
				current = open[i];
				min = stops[open[i]].f;
			}
		}
		if (current == end) 
		{
			found = 1;
			++p_len;
			path = (int*)realloc(path, p_len * sizeof(int));
			path[p_len - 1] = current;
			while (stops[current].from >= 0)
			{
				current = stops[current].from;
				++p_len;
				path = (int*)realloc(path, p_len * sizeof(int));
				path[p_len - 1] = current;
			}
		}
		for (i = 0; i < o_len; i++)
			if (open[i] == current)
			{
				if (i not_eq (o_len - 1))
					for (j = i; j < (o_len - 1); j++)
						open[j] = open[j + 1];
				--o_len;
				open = (int*)realloc(open, o_len * sizeof(int));
				break;
			}
		++c_len;
		closed = (int*)realloc(closed, c_len * sizeof(int));
		closed[c_len - 1] = current;
		for (i = 0; i < stops[current].n_len; i++)
		{
			b = 0;
			for (j = 0; j < c_len; j++)
				if (routes[stops[current].n[i]].y == closed[j])
					b = 1;
			if (b)
				continue;
			tempg = stops[current].g + routes[stops[current].n[i]].d;
			b = 1;
			if (o_len > 0)
				for (j = 0; j < o_len; j++)
					if (routes[stops[current].n[i]].y == open[j])
						b = 0;
			if (b or (tempg < stops[routes[stops[current].n[i]].y].g))
			{
				stops[routes[stops[current].n[i]].y].from = current;
				stops[routes[stops[current].n[i]].y].g = tempg;
				stops[routes[stops[current].n[i]].y].f = stops[routes[stops[current].n[i]].y].g + stops[routes[stops[current].n[i]].y].h;
				if (b)
				{
					++o_len;
					open = (int*)realloc(open, o_len * sizeof(int));
					open[o_len - 1] = routes[stops[current].n[i]].y;
				}
			}
		}
	}
	final.y = stops[path[p_len - 1]].row;
	final.x = stops[path[p_len - 1]].col;
	if (p_len == 2)
		return (final);
	final.y = stops[path[p_len - 2]].row;
	final.x = stops[path[p_len - 2]].col;
	for (i = 0; i < s_len; ++i)
		free(stops[i].n);
	free(stops);
	free(routes);
	free(path);
	free(open);
	free(closed);
	return (final);
}
