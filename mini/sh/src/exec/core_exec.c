/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:02:20 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/06 15:36:51 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	kind_of_token(t_data *data, t_input *input)
{
	char	*input_str;
	input_str = input->token;

	if (ft_strncmp_end(input_str, "echo", 4) == 0)
	{
		b_echo(data);
		return (0);
	}
	// if (ft_strncmp_end(input_str, "exit", 4) == 0)
	// {
	// 	b_exit(data);
	// 	return (0);
	// }
	// else if (ft_strncmp_end(input_str, "cd", 2) == 0)
	// {
	// 	b_cd(data);
	// 	return (0);
	// }
	else if (ft_strncmp_end(input_str, "pwd", 3) == 0)
	{
		b_pwd(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "env", 3) == 0)
	{
		b_env(data);
		return (0);
	}
	// else if (ft_strncmp_end(input_str, "unset", 5) == 0)
	// {
	// 	b_unset(data);
	// 	return (0);
	// }
	// else if (ft_strncmp_end(input_str, "export", 6) == 0)
	// {
	// 	b_export(data);
	// 	return (0);
	// }
	return (1);
}
