/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:15 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:01:03 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	b_env(t_data *data)
{
	t_input	*current;

	current = data->input;
	if (!data->env || !data->env->name)
	{
		printf("aucune variable d'environnement\n");
		return ;
	}
	while (current->next && current->next->type != T_OP
		&& current->next->type != T_PIPE)
	{
		current = current->next;
		if (ft_strncmp_end(current->token, "env", 4) != 0)
		{
			ft_printf_stderr("env: '%s': No such file or directory\n",
				current->token);
			return ;
		}
	}
	print_lle(data);
}
