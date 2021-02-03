/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:50:04 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_forward(t_game *game, t_game_obj *obj, t_map *map, double koeff)
{
	t_vec2	test;
	float	step;
	move_shift(game);
	koeff *= (obj->speed * game->shift_k);
	test.x = obj->pos.x;
	test.y = obj->pos.y;
	step = obj->border;
	while (koeff > 0)
	{
		if (step > koeff)
			step = koeff;
		test.x += step * obj->dir.x;
		test.y += step * obj->dir.y;
		check_step(obj, map, &(test));
		koeff -= step;
	}
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_back(t_game *game, t_game_obj *obj, t_map *map, double koeff)
{
	t_vec2	test;
	move_shift(game);
	koeff *= (obj->speed * game->shift_k);
	test.x = obj->pos.x - koeff * obj->dir.x;
	test.y = obj->pos.y - koeff * obj->dir.y;
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_left(t_game_obj *obj, t_map *map, double koeff)
{
	float	rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot + M_PI_2);
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_right(t_game_obj *obj, t_map *map, double koeff)
{
	float	rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot - M_PI_2);
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	put_out_the_light_1(t_game *game)
{
	SDL_Point	pos;
	int			y_index;
	Uint32		col;
	SDL_Color	sc;
	
	pos.y = -1;
	while (++pos.y < S_H)
	{
		y_index = pos.y * S_W;
		pos.x = -1;
		while (++pos.x < S_W)
		{
			col = game->data[y_index + pos.x];
				sc.r = ((col & 0xFF0000) >> 16) / game->light_k;
				sc.g = ((col & 0xFF00) >> 8) / game->light_k;
				sc.b = (col & 0xFF) / game->light_k;
			game->data[y_index + pos.x] = (sc.r << 16) | (sc.g << 8) | sc.b;
		}
	}
}

void	put_out_the_light(t_game *game)
{
	if (game->light == 1)
	{
		game->light_k = 1.5;
		put_out_the_light_1(game);
	}
	else if (game->light == 2)
	{
		game->light_k = 2.5;
		put_out_the_light_1(game);
	}
	else if (game->light == 3)
	{
		game->light_k = 3.5;
		put_out_the_light_1(game);
	}
	else if (game->light == 0)
	{
		game->light_k = 1.0;
		put_out_the_light_1(game);
	}			
}