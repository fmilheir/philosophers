/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:03:24 by fmilheir         #+#    #+#             */
/*   Updated: 2022/10/30 13:03:24 by fmilheir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

int	thread_create_pair(t_philo *philo)
{
	int		i;
	long	time;

	time = get_time(0);
	i = 0;
	while (i < philo->utils->n_philo)
	{
		philo[i].start = time;
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (1);
		if (pthread_detach(philo[i].thread) != 0)
			return (1);
		i += 2;
	}
	usleep(25 * philo->utils->n_philo);
	thread_create_unpair(philo, time);
	return (0);
}

int	thread_create_unpair(t_philo *philo, long time)
{
	int	i;

	i = 1;
	while (i < philo->utils->n_philo)
	{
		philo[i].start = time;
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (1);
		if (pthread_detach(philo[i].thread) != 0)
			return (1);
		i += 2;
	}
	return (0);
}

void	deal_pair(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->fork[philo->left_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->fork[philo->right_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->time);
	philo->last_eaten = get_time(philo->start);
	pthread_mutex_unlock(&philo->utils->time);
	mini_print(philo, "is eating\n", get_time(philo->start));
	sleeper(philo->utils->time_to_eat);
	pthread_mutex_unlock(&philo->utils->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->utils->fork[philo->right_fork]);
}

void	deal_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->fork[philo->right_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->fork[philo->left_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->time);
	philo->last_eaten = get_time(philo->start);
	pthread_mutex_unlock(&philo->utils->time);
	mini_print(philo, "is eating\n", get_time(philo->start));
	sleeper(philo->utils->time_to_eat);
	pthread_mutex_unlock(&philo->utils->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->utils->fork[philo->right_fork]);
}

int	monitoring(t_philo *philo, t_ph_utils *utils)
{
	int		i;
	long	time;

	i = 0;
	while (i < philo->utils->n_philo)
	{
		pthread_mutex_lock(&philo->utils->time);
		time = get_time(philo[i].start + philo[i].last_eaten);
		pthread_mutex_unlock(&philo->utils->time);
		if (time >= philo[i].utils->time_to_die)
			return (prompt_death(&philo[i]));
		pthread_mutex_lock(&philo->utils->looper);
		if (utils->loop == utils->n_philo && utils->meals != -1)
			return (EXIT);
		pthread_mutex_unlock(&philo->utils->looper);
		i++;
	}
	return (1);
}
