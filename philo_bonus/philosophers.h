/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:50:09 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:50:09 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	int				count_phil;
	int				num_phil;
	long			die;
	pid_t			*pid;
	pthread_t		observer;
	sem_t			*forks;
	sem_t			*print;
	long			start;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				number_of_times;
	int				flag;
}	t_info;

//main
void	print_actions(t_info *info, int flag, int num_phil);
void	start_fork(t_info *info);
void	for_exit(char *str, t_info *info);
//init_obj
void	init_check_data(t_info *info, char **argv, int argc);
int		init_fork_sem(t_info *info);
int		ft_atoi(char *str);
long	get_time(void);
void	break_time(t_info *info, int flag, long time_x);
//actions
void	func(t_info *info);
void	*monitoring(void *all_info);
void	ft_eat(t_info *info, int num_phil);
void	ft_sleep(t_info *info, int num_phil);
void	ft_think(t_info *info, int num_phil);
#endif