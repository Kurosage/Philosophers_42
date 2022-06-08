/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:01:15 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 10:01:35 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_check_data(t_info *info, char **argv, int argc)
{
	if (argc == 5 || argc == 6)
	{
		if (argc == 5)
			info->number_of_times = -2;
		else if (argc == 6 && ft_atoi(argv[5]))
			info->number_of_times = ft_atoi(argv[5]);
		else
			for_exit("Error: invalid argument\n", info);
		if (ft_atoi(argv[1]) && ft_atoi(argv[2])
			&& ft_atoi(argv[3]) && ft_atoi(argv[4]))
		{
			info->count_phil = ft_atoi(argv[1]);
			info->time_to_die = ft_atoi(argv[2]);
			info->time_to_eat = ft_atoi(argv[3]);
			info->time_to_sleep = ft_atoi(argv[4]);
		}
		else
			for_exit("Error: invalid argument\n", info);
	}
	else
		for_exit("Error: invalid argument\n", info);
}

int	init_fork_sem(t_info *info)
{
	int	i;

	info->pid = malloc(sizeof(pid_t) * info->count_phil);
	if (!info->pid)
		for_exit("Failed to allocate memory\n", info);
	i = -1;
	while (++i < info->count_phil)
		info->pid[i] = 0;
	sem_unlink("/info_printer");
	sem_unlink("/all_fork");
	info->print = sem_open("/info_printer", O_CREAT, 0644, 1);
	info->forks = sem_open("/all_fork", O_CREAT, 0644, info->count_phil);
	if (info->print <= 0 || info->forks <= 0)
		for_exit("Failed to allocate memory\n", info);
	info->start = get_time();
	info->die = info->start;
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
