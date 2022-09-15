/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:57:05 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 23:57:07 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// signals.c
void	signal_handler(int sig, siginfo_t *siginfo, void *context);
void	set_heredoc_signal(int sig, siginfo_t *siginfo, void *context);
void	set_command_signal(int sig, siginfo_t *siginfo, void *context);
void	setup_signals(struct sigaction sa, void (*f)(int, siginfo_t*, void*));

#endif
