/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:46:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/02 14:46:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdint.h>

typedef struct s_shell	t_shell;

# define MALLOC_FAIL 1

void					reset_shell(t_shell *shell);
void					error_fatal(t_shell *shell, const char *msg,
							uint8_t error_code);

#endif // ERROR_H