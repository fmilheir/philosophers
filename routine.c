/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:21:15 by fmilheir         #+#    #+#             */
/*   Updated: 2022/11/02 00:21:15 by fmilheir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

void	mini_print(t_philo *philo, char *str, long time)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%04ld ms : Philo %d %s", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->utils->mutex_msg);
}

void	routine2(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		deal_pair(philo);
	else
		deal_odd(philo);
	pthread_mutex_lock(&philo->utils->time);
	philo->n_eaten++;
	pthread_mutex_lock(&philo->utils->looper);
	if (philo->n_eaten == philo->utils->meals && philo->utils->meals != -1)
		philo->utils->loop++;
	pthread_mutex_unlock(&philo->utils->looper);
	pthread_mutex_unlock(&philo->utils->time);
	mini_print(philo, "is sleeping\n", get_time(philo->start));
	sleeper(philo->utils->time_to_sleep);
	mini_print(philo, "is thinking\n", get_time(philo->start));
}

int	prompt_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%04lld ms : philo %d died\n", \
		get_time(philo->start), philo->philo_id);
	return (EXIT);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		routine2(philo);
	}
}
