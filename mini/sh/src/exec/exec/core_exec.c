/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:02:20 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 21:35:25 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	handle_echo_exit(t_data *data, t_input *input, int in_pipe)
{
	char	*input_str;

	input_str = input->token;
	if (ft_strncmp_end(input_str, "echo", 5) == 0)
	{
		b_echo(data, input);
		return (0);
	}
	if (ft_strncmp_end(input_str, "exit", 5) == 0)
	{
		b_exit(data, input, in_pipe);
		return (0);
	}
	return (1);
}

static int	handle_cd_pwd_env(t_data *data, t_input *input)
{
	char	*input_str;

	input_str = input->token;
	if (ft_strncmp_end(input_str, "cd", 3) == 0)
	{
		b_cd(data);
		return (0);
	}
	if (ft_strncmp_end(input_str, "pwd", 4) == 0)
	{
		b_pwd(data);
		return (0);
	}
	if (ft_strncmp_end(input_str, "env", 4) == 0)
	{
		b_env(data);
		return (0);
	}
	return (1);
}

static int	handle_unset_export(t_data *data, t_input *input)
{
	char	*input_str;

	input_str = input->token;
	if (ft_strncmp_end(input_str, "unset", 6) == 0)
	{
		b_unset(data);
		return (0);
	}
	if (ft_strncmp_end(input_str, "export", 7) == 0)
	{
		b_export(data);
		return (0);
	}
	return (1);
}

int	kind_of_token(t_data *data, t_input *input, int in_pipe)
{
	if (handle_echo_exit(data, input, in_pipe) == 0)
		return (0);
	if (handle_cd_pwd_env(data, input) == 0)
		return (0);
	if (handle_unset_export(data, input) == 0)
		return (0);
	return (1);
}

void	exec_cmd(t_data *data, t_input *head)
{
	t_input	*curr;

	curr = head;
	if (!curr)
		return ;
	exec_pipe(data, curr);
}
