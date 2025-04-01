/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:59:39 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 16:31:37 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in `echo` `echo -n`
/// @param input
void	b_echo(t_input *input)
{
	while(input->next->type == T_ARG)
	{
		ft_putstr_fd(input->next->token, 1);
		if (!input->next->next)
			write(1, "\n", 1);
		input->next = input->next->next;
	}
}

// [ ] gestion plusieurs n
// [ ] adapter avec token CMD_ARG et CMD
