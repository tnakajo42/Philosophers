/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_restaurant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:20:44 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/06 18:06:54 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	open_restaurant(t_philo *ph, int i, int j)
{
	ph->fork->nofiu = ph->nop;
	if (ph->nop % 2 == 1)
		ph->fork->nofiu--;
	ph->nofp = 0;
	while (++i < ph->nop)
	{
		ph->status[i].time = ph->tte;
		ph->status[i].init_time = 0;
		ph->status[i].life = ph->ttd;
		pthread_mutex_lock(&ph->status[i].status_mutex);
		pthread_join(ph->status[i].threads, NULL);
		pthread_join(ph->fork[i].fork_threads, NULL);
	}
	while (42)
	{
		while (++j < ph->nop)
			pthread_mutex_unlock(&ph->status[j].status_mutex);
		ph->time = get_time() - ph->init_time;
		j = -1;
		while (++j < ph->nop)
			pthread_mutex_lock(&ph->status[j].status_mutex);
		if (what_philo_do(ph, -1))
			return ;
		j = -1;
	}
}

int	what_philo_do(t_philo *ph, int i)
{
	while (++i < ph->nop)
	{
		if (ph->status[i].status == 'e' && ph->time >= ph->status[i].time)
			ph->status[i].status = 'S';
		else if (ph->status[i].status == 's' && ph->time >= ph->status[i].time)
			ph->status[i].status = 'T';
		else if (ph->status[i].life <= ph->time)
			ph->status[i].status = 'D';
		else if (ph->status[i].status == 't' && ph->nop != 1)
		{
			if (i == 0 && ph->status[ph->nop - 1].status != 'e' \
				&& ph->status[i + 1].status != 'e')
				ph->status[i].status = 'E';
			else if (i + 1 == ph->nop && ph->status[0].status != 'e' \
				&& ph->status[i - 1].status != 'e')
				ph->status[i].status = 'E';
			else if (i + 1 != ph->nop && ph->status[i + 1].status != 'e' \
				&& i != 0 && ph->status[i - 1].status != 'e')
				ph->status[i].status = 'E';
		}
		if (print_status(ph, i, -1))
			return (1);
	}
	return (0);
}

int	print_status(t_philo *ph, int i, int j)
{
	if (ph->status[i].status == 'D')
	{
		while (++j < ph->nop)
		{
			pthread_mutex_unlock(&ph->status[j].status_mutex);
			pthread_mutex_unlock(&ph->fork[j].status_mutex);
		}
		return (printf("%u %i died\n", ph->time, i + 1));
	}
	if (ph->status[i].status == 'S')
	{
		printf("%u %i is sleeping\n", ph->time, i + 1);
		ph->status[i].status = 's';
		ph->status[i].time = ph->tts + ph->time;
		ph->fork->nofiu = ph->fork->nofiu - 2;
	}
	else if (ph->status[i].status == 'T')
	{
		printf("%u %i is thinking\n", ph->time, i + 1);
		ph->status[i].status = 't';
	}
	if (ph->status[i].status == 'E')
		if (serve_food(ph, i, -1))
			return (1);
	return (0);
}

int	serve_food(t_philo *ph, int i, int j)
{
	ph->status[i].status = 'e';
	take_two_forks(ph, i);
	printf("%u %i is eating\n", ph->time, i + 1);
	ph->status[i].time = ph->tte + ph->time;
	ph->status[i].life = ph->ttd + ph->time;
	ph->status[i].eat_times++;
	if (ph->status[i].eat_times == ph->nom)
		ph->nofp++;
	if (ph->nofp == ph->nop)
	{
		while (++j < ph->nop)
		{
			pthread_mutex_unlock(&ph->status[j].status_mutex);
			pthread_mutex_unlock(&ph->fork[j].status_mutex);
		}
		return (1);
	}
	return (0);
}

void	take_two_forks(t_philo *ph, int i)
{
	int	j;

	j = 0;
	while (j < 2)
	{
		if (ph->fork->nofiu < ph->nop)
			printf("%u %i has taken a fork\n", ph->time, i + 1);
		else
			printf("%u %i is looking a fork\n", ph->time, i + 1);
		ph->fork->nofiu++;
		j++;
	}
}
