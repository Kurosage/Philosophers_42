/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:27:10 by rmaren            #+#    #+#             */
/*   Updated: 2022/04/12 09:27:10 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int				count_phil;
	int				num_phil;
	long			*start_die;
	pthread_t		*philo;
	pthread_t		observer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	long			start;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				number_of_times;
	int				flag;
}	t_info;

//init_obj
int		init_check_data(t_info *info, char **argv, int argc);
int		init_thread_mutex(t_info *info);
int		init_threads(t_info *info, int i);
int		init_all(t_info *info, int argc, char **argv);
int		ft_atoi(char *str);
//actions.c
void	*func(void *all_info);
void	*monitoring(void *all_info);
void	ft_eat(t_info *info, int num_phil);
void	ft_sleep(t_info *info, int num_phil);
void	ft_think(t_info *info, int num_phil);
//main.c
void	print_actions(t_info *info, int flag, int num_phil);
long	get_time(void);
void	break_time(t_info *info, int flag, long time_x);
void	for_exit(int flag, t_info *info);

#endif