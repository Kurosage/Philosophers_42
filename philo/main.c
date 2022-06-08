/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:26:57 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:26:57 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_actions(t_info *info, int flag, int num_phil)
{
	pthread_mutex_lock(&info->print);
	if (flag == 1)
		printf("%li %i has taken a fork\n", get_time() - info->start,
			num_phil + 1);
	else if (flag == 2)
		printf("%li %i is eating\n", get_time() - info->start, num_phil + 1);
	else if (flag == 4)
		printf("%li %i died\n", get_time() - info->start, num_phil + 1);
	else if (flag == 5)
		printf("%li %i is sleeping\n", get_time() - info->start, num_phil + 1);
	else if (flag == 6)
		printf("%li %i is thinking\n", get_time() - info->start, num_phil + 1);
	else if (flag == 7)
		printf("Failed to create thread\n");
	pthread_mutex_unlock(&info->print);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	break_time(t_info *info, int flag, long time_x)
{
	long	start_time;

	if (flag == 0)
		start_time = info->start;
	else
		start_time = get_time();
	while (get_time() < start_time + time_x)
		usleep(100);
}

void	for_exit(int flag, t_info *info)
{
	if (flag == 1)
		printf("Error: invalid argument\n");
	if (info->forks)
	{
		free(info->forks);
		info->forks = NULL;
	}
	if (info->philo)
	{
		free(info->philo);
		info->philo = NULL;
	}
	if (info->start_die)
	{
		free(info->start_die);
		info->start_die = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	info.flag = 0;
	if (init_all(&info, argc, argv))
		return (1);
	pthread_join(info.observer, NULL);
	pthread_mutex_destroy(&info.print);
	i = -1;
	while (++i < info.count_phil)
		pthread_mutex_destroy(&info.forks[i]);
	for_exit(0, &info);
	return (0);
}
