/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:46:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:46:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include <stdbool.h>

# define VERBOSE false

# define COLOR_DEBUG "\033[34m"
# define COLOR_INFO "\033[32m"
# define COLOR_WARNING "\033[33m"
# define COLOR_ERROR "\033[31m"
# define COLOR_FATAL "\033[41m"
# define RESET "\033[0m"

typedef enum e_log_level
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
}		t_log_level;

void	log_message(t_log_level log_level, const char *format, ...);

#endif // LOGGER_H