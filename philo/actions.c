/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:26:19 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:26:21 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*func(void *all_info)
{
	int		num_phil;
	t_info	*info;
	int		i;

	info = (t_info *)all_info;
	num_phil = info->num_phil;
	if (num_phil % 2 == 0)
		break_time(info, 0, 20);
	i = 0;
	while (1)
	{
		ft_eat(info, num_phil);
		info->start_die[num_phil] = get_time();
		if (info->number_of_times > 0)
		{
			if (++i == info->number_of_times)
			{
				info->flag++;
				return (NULL);
			}
		}
		ft_sleep(info, num_phil);
		ft_think(info, num_phil);
	}
	return (NULL);
}

void	*monitoring(void *all_info)
{
	t_info	*info;
	int		i;

	info = (t_info *)all_info;
	while (1)
	{
		i = 0;
		while (i < info->count_phil)
		{
			if ((get_time() - *(info->start_die + i) > info->time_to_die)
				&& (info->number_of_times < 0 || (info->number_of_times > 0
						&& info->flag != info->count_phil)))
			{
				print_actions(info, 4, i);
				return (NULL);
			}
			else if ((get_time() - *(info->start_die + i) > info->time_to_die)
				&& info->number_of_times > 0 && info->flag == info->count_phil)
				return (NULL);
			usleep(100);
			i++;
		}
	}
	return (NULL);
}

void	ft_eat(t_info *info, int num_phil)
{
	if (num_phil == 0)
	{
		pthread_mutex_lock(&info->forks[num_phil]);
		print_actions(info, 1, num_phil);
		pthread_mutex_lock(&info->forks[info->count_phil - 1]);
		print_actions(info, 1, num_phil);
		print_actions(info, 2, num_phil);
		break_time(info, 1, info->time_to_eat);
		pthread_mutex_unlock(&info->forks[num_phil]);
		pthread_mutex_unlock(&info->forks[info->count_phil - 1]);
	}
	else
	{
		pthread_mutex_lock(&info->forks[num_phil]);
		print_actions(info, 1, num_phil);
		pthread_mutex_lock(&info->forks[num_phil - 1]);
		print_actions(info, 1, num_phil);
		print_actions(info, 2, num_phil);
		break_time(info, 1, info->time_to_eat);
		pthread_mutex_unlock(&info->forks[num_phil]);
		pthread_mutex_unlock(&info->forks[num_phil - 1]);
	}
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
