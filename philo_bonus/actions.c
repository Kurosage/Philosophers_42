/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:32:27 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:53:20 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	func(t_info *info)
{
	info->flag = 0;
	while (1)
	{
		ft_eat(info, info->num_phil);
		info->die = get_time();
		if (info->number_of_times > 0 && ++info->flag == info->number_of_times)
			exit(0);
		ft_sleep(info, info->num_phil);
		ft_think(info, info->num_phil);
	}
}

void	*monitoring(void *all_info)
{
	t_info	*info;

	info = (t_info *)all_info;
	while (1)
	{
		if ((get_time() - info->die > info->time_to_die)
			&& (info->number_of_times < 0 || (info->number_of_times > 0
					&& info->flag != info->count_phil)))
		{
			print_actions(info, 4, info->num_phil);
			exit(1);
		}
		else if ((get_time() - info->die > info->time_to_die)
			&& info->number_of_times > 0 && info->flag == info->count_phil)
			exit(0);
		usleep(100);
	}
	exit(0);
}

void	ft_eat(t_info *info, int num_phil)
{
	sem_wait(info->forks);
	print_actions(info, 1, num_phil);
	sem_wait(info->forks);
	print_actions(info, 1, num_phil);
	print_actions(info, 2, num_phil);
	break_time(info, 1, info->time_to_eat);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	ft_sleep(t_info *info, int num_phil)
{
	print_actions(info, 5, num_phil);
	break_time(info, 1, info->time_to_sleep);
}

void	ft_think(t_info *info, int num_phil)
{
	print_actions(info, 6, num_phil);
}
