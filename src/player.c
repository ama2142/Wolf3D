/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:39:02 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_player(t_game *game)
{
	t_vec2	pos;
	t_vec2	speed;

	pos.x = 4.5f;
	pos.y = 3.5f;
	speed.x = 1;
	speed.y = 0.5;
	init_object(&(game->player.obj), pos, 0, speed);
	game->player.sec.fov = 90 * M_PI / 180;
	game->player.sec.ang_step = game->player.sec.fov / S_W;
	game->player.ray_depth = 91;
	game->comeback = 0;
	game->level.num = 1;
	game->light = 0;
}
