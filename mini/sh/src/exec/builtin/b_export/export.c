/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/07 20:11:38 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

/// @brief version head -|- built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    b_export(t_data *data)
{
	if (data->input->type == 0)// `export`[ ] et la suite est .. ?
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
		printf("export.c > b_export : \t export tout nu, input = T_CMD\n");
	}
	else if (data->input->type == 1)
	{
		if (is_valid_env_var_syntax(data->input->next->token) == TRUE)
		{
			add_env_var(data, data->input->next->token);// add ou maj NAME=value
		}
		printf("export.c > b_export : \t export avec arg, input = T_CMD_ARG + T_ARG\n");
	}
	else 
		return ;
}
// int main(int ac, char **av, char **envp)
// {
// 	t_data	*data = malloc(sizeof(t_data));
// 	if(!data)
// 		return 0;
// 	(void)ac;
// 	(void)av;
// 	init_env(data, envp);
// 	// b_env(data);
// 	// b_export(data);
// }


// MAYBE ! quand je tape export fjfboewf, ndepqndq st considere comme T_CMD_ARG et nest PAS differencier de sil y a un =