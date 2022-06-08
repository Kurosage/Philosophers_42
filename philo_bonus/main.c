/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:33:17 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:33:17 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_actions(t_info *info, int flag, int num_phil)
{
	sem_wait(info->print);
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
	sem_post(info->print);
}

void	start_fork(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->count_phil)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			for_exit("Error: fork mistake\n", info);
		else if (info->pid[i] == 0)
		{
			info->num_phil = i;
			if (pthread_create (&info->observer, NULL, monitoring,
					(void *)info))
				for_exit("Failed to create thread\n", info);
			func(info);
		}
	}
}

void	for_exit(char *str, t_info *info)
{
	printf("%s\n", str);
	if (info->pid)
		free(info->pid);
	info->pid = NULL;
	exit(1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		stat;
	int		i;

	init_check_data(&info, argv, argc);
	init_fork_sem(&info);
	start_fork(&info);
	i = -1;
	while (++i < info.count_phil)
	{
		waitpid(-1, &stat, 0);
		if (stat)
		{
			i = -1;
			while (++i < info.count_phil)
				kill (info.pid[i], SIGTERM);
			break ;
		}
	}
	sem_unlink("/info_printer");
	sem_unlink("/all_fork");
	if (info.pid)
		free(info.pid);
	return (0);
}
