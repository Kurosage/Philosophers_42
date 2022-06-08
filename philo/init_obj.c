/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:26:27 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:26:28 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_check_data(t_info *info, char **argv, int argc)
{
	info->start_die = NULL;
	info->forks = NULL;
	info->philo = NULL;
	if (argc == 5 || argc == 6)
	{
		if (argc == 5)
			info->number_of_times = -2;
		else if (argc == 6 && ft_atoi(argv[5]))
			info->number_of_times = ft_atoi(argv[5]);
		else
			return (1);
		if (ft_atoi(argv[1]) && ft_atoi(argv[2])
			&& ft_atoi(argv[3]) && ft_atoi(argv[4]))
		{
			info->count_phil = ft_atoi(argv[1]);
			info->time_to_die = ft_atoi(argv[2]);
			info->time_to_eat = ft_atoi(argv[3]);
			info->time_to_sleep = ft_atoi(argv[4]);
			return (0);
		}
		else
			return (1);
	}
	else
		return (1);
}

int	init_thread_mutex(t_info *info)
{
	int	i;

	info->start_die = malloc(sizeof(long) * info->count_phil);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->count_phil);
	info->philo = malloc(sizeof(pthread_t) * info->count_phil);
	if (!info->philo || !info->forks || !info->start_die)
	{
		printf("Failed to allocate memory\n");
		return (1);
	}
	pthread_mutex_init (&info->print, NULL);
	i = -1;
	while (++i < info->count_phil)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			printf("Failed to init mutex\n");
			return (1);
		}
	}
	info->start = get_time();
	i = -1;
	while (++i < info->count_phil)
		info->start_die[i] = info->start;
	return (0);
}

int	init_threads(t_info *info, int i)
{
	while (i < info->count_phil)
	{
		info->num_phil = i;
		if (pthread_create (&info->philo[i], NULL, func, (void *)info))
		{
			print_actions(info, 7, 0);
			return (1);
		}
		pthread_detach(info->philo[i]);
		i += 2;
		usleep(100);
	}
	return (0);
}

int	init_all(t_info *info, int argc, char **argv)
{
	if (init_check_data(info, argv, argc))
	{
		for_exit(1, info);
		return (1);
	}
	if (init_thread_mutex(info))
	{
		for_exit(0, info);
		return (1);
	}
	if (pthread_create (&info->observer, NULL, monitoring, (void *)info))
	{
		for_exit(0, info);
		print_actions(info, 7, 0);
		return (1);
	}
	if (init_threads(info, 1))
		return (1);
	if (init_threads(info, 0))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		negativ;
	long	number;

	i = 0;
	negativ = 1;
	number = 0;
	if (str[i] == '-')
		negativ = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (0);
	number = number * negativ;
	if (number <= 0 || number > 2147483647)
		return (0);
	return (number);
}
