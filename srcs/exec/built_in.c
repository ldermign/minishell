/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/10 11:40:36 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*working_path(char **paths, char *name_fct)
{
	int		i;
	int		fd;
	char	*good_path;

	i = 0;
	while (paths[i])
	{
		good_path = create_path(paths[i], name_fct);
		fd = access(good_path, F_OK & X_OK);
		if (fd == -1)
			i++;
		else
			return (good_path);
		free(good_path);
	}
	return (NULL);
}

// 50 lignes

char	**copy_env_in_tab_char(t_env_ms **ms)
{
	t_it		it;
	t_env_ms	*first;
	char		**copy;

	init_struct_it(&it);
	first = *ms;
	copy = malloc(sizeof(char *) * size_env(ms) + 1);
	if (copy == NULL)
		return (NULL);
	while (*ms)
	{
		it.j = 0;
		it.k = 0;
		it.ret = 0;
		if (ft_pos_strstr((*ms)->var, "=") == -1)
		{
			copy[it.i] = malloc(sizeof(char) * ft_strlen((*ms)->var) + 1);
			while ((*ms)->var[it.j])
			{
				copy[it.i][it.k] = (*ms)->var[it.j];
				it.j++;
				it.k++;
			}
		}
		else
		{
			copy[it.i] = malloc(sizeof(char) * ft_strlen((*ms)->var) + 3);
			while ((*ms)->var[it.j])
			{
				if (it.ret == 0
					&& (*ms)->var[it.j - 1] && (*ms)->var[it.j - 1] == '=')
				{
					copy[it.i][it.k] = '"';
					it.k++;
					it.ret = 1;
				}
				copy[it.i][it.k] = (*ms)->var[it.j];
				it.j++;
				it.k++;
			}
			copy[it.i][it.k] = '"';
			it.k++;
		}
		copy[it.i][it.k] = '\0';
		it.i++;
		*ms = (*ms)->next;
	}
	copy[it.i] = NULL;
	*ms = first;
	return (copy);
}

// 30 lignes

void	print_in_alphabetical_order(t_struct *ms, t_env_ms **env)
{
	int			i;
	int			len;
	char		*swap;
	char		**copy;

	i = 0;
	len = size_env(env);
	swap = NULL;
	copy = copy_env_in_tab_char(env);
	while (i < len - 1)
	{
		if ((ft_strcmp(copy[i], copy[i + 1])) > 0)
		{
			swap = copy[i];
			copy[i] = copy[i + 1];
			copy[i + 1] = swap;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < len)
	{
		write(ms->std.fd_to_write, "export ", 8); ///pas forcement ici, dans fichier aussi
		ft_putstr_fd(copy[i], ms->std.fd_to_write); ///pas forcement ici, dans fichier aussi
		write(ms->std.fd_to_write, "\n", 1); ///pas forcement ici, dans fichier aussi
		i++;
	}
	ft_free_tab(copy);
}

// 29 lignes

int	built_in_export(t_struct *ms, t_env *env, char *prompt, char *alpha)
{
	t_it	it;
	char	*str;

	it.i = 0;
	while (prompt[it.i] == ' ')
		it.i++;
	it.i += 6;
	if (alpha == NULL)
	{
		print_in_alphabetical_order(ms, &(env->env_ms));
		return (EXIT_SUCCESS);
	}
	it.add = light_parse_export(&prompt[it.i]);
	if (it.add == -1)
		return (EXIT_FAILURE);
	while (prompt[it.i] == ' ')
		it.i++;
	it.pos = check_if_variable_already_exist(&(env->env_ms), &prompt[it.i]);
	it.len = size_variable(&prompt[it.i], it.add, it.pos);
	if (it.add == 1 && it.pos != -1)
		str = ft_strjoin(get_variable_with_pos(&(env->env_ms), it.pos),
				get_good_variable(&prompt[it.i], it.len, it.add, it.pos));
	else
		str = get_good_variable(&prompt[it.i], it.len, it.add, it.pos);
	if (it.pos == -1)
		add_var_env_minishell(&(env->env_ms), str);
	else
		change_var_env_minishell(&(env->env_ms), str, it.pos);
	return (EXIT_SUCCESS);
}

int	built_in_to_create(t_struct *ms, t_args *cmd, char *prompt)
{
	if (ft_memcmp(cmd->arg_to_pass[0], "cd", 3) == 0)
		return (built_in_cd(&(ms->env), cmd->arg_to_pass[1]));
	else if (ft_memcmp(cmd->arg_to_pass[0], "pwd", 4) == 0)
		return (built_in_pwd());
	else if (ft_memcmp(cmd->arg_to_pass[0], "env", 4) == 0)
		return (built_in_env(ms->env.env_ms));
	else if (ft_memcmp(cmd->arg_to_pass[0], "export", 7) == 0)
		return (built_in_export(ms, &(ms->env), prompt, cmd->arg_to_pass[1]));
	else if (ft_memcmp(cmd->arg_to_pass[0], "unset", 6) == 0)
		return (built_in_unset(&(ms->env), cmd->arg_to_pass[1]));
	else if (ft_memcmp(cmd->arg_to_pass[0], "echo", 5) == 0)
	{
		ms->parsing.result = recup_echo(cmd->arg_to_pass, ms);
		return (built_in_echo(ms, prompt));
	}
	else if (ft_memcmp(cmd->arg_to_pass[0], "exit", 5) == 0)
		built_in_exit(&(ms->env), cmd->arg_to_pass, prompt);
	return (-1);
}

// 38 lignes

void	command(char *prompt, t_struct *ms)
{
	int		i;
	int		last;
	t_args	*all_cmds;
	char	*good_path;
	char	**args;

	i = 0;
	all_cmds = ms->args->first;
	ms->prompt = prompt;
	while (prompt[i] == ' ')
		i++;
	args = get_cmd_and_args_split(&prompt[i]);
	if (args == NULL)
		return ;
	last = last_redir(args);
	init_struct_std(args, &(*ms).std, last);
	while (all_cmds)
	{
		if (ms->parsing.nb_pipe > 0)
		{
			there_is_pipe(ms);
			ft_free_tab(args);
			return ;
		}
		if (last == -1 && built_in_to_create(ms, ms->args->first, prompt) != -1)
		{
			ft_free_tab(args);
			return ;
		}
		else if (last != -1)
		{
			get_redirections(ms, args, last);
			ft_free_tab(args);
			return ;
		}
		good_path = working_path(ms->env.path, args[0]);
		execute_cmd(ms, good_path, args, args, ms->env.env_bash);
		ft_free_tab(args);
		all_cmds = all_cmds->next;
	}
	free_all_cmds_pompt(all_cmds);
}
