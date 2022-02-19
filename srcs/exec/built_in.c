/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/19 19:07:11 by ldermign         ###   ########.fr       */
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

void	execute_cmd(char *path, char **args, char **env)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		sig_error = 127;
		perror("fork"); // voir le cas d'erreur
		return ;
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, args, env) == -1)
		{
			printf("bash: %s: command not found\n", args[0]);
			sig_error = 127;
		}
		return ;
	}
	sig_error = 0;
}

char	**copy_env_in_tab_char(t_env_ms **ms)
{
	t_it		it;
	t_env_ms	*first;
	char		**copy;

	it.i = 0;
	it.j = 0;
	it.k = 0;
	it.ret = 0;
	first = *ms;
	copy = malloc(sizeof(char *) * size_env(ms) + 1);
	if (copy == NULL)
		return (NULL);
	while (*ms)
	{
		it.j = 0;
		it.k = 0;
		copy[it.i] = malloc(sizeof(char) * ft_strlen((*ms)->var) + 3);
		while ((*ms)->var[it.j])
		{
			if ((*ms)->var[it.j - 1] == '=' && it.ret == 0)
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
		copy[it.i][it.k] = '\0';
		it.i++;
		*ms = (*ms)->next;
	}
	copy[it.i] = NULL;
	*ms = first;
	return (copy);
}

void	print_in_alphabetical_order(t_env_ms **ms)
{
	int			i;
	int			len;
	char		*swap;
	char		**copy;

	i = 0;
	len = size_env(ms);
	swap = NULL;
	copy = copy_env_in_tab_char(ms);
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
		write(1, "export ", 8); ///pas forcement ici, dans fichier aussi
		ft_putstr(copy[i]); ///pas forcement ici, dans fichier aussi
		write(1, "\n", 1); ///pas forcement ici, dans fichier aussi
		i++;
	}
	ft_free_tab(copy);
}

int	built_in_export(t_env *env, char *prompt, char **cmd_args)
{
	int		i;
	int		size;
	int		pos;
	int		add;
	char	*str;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	if (cmd_args[1] == NULL)
	{
		print_in_alphabetical_order(&(env->env_ms));
		return (EXIT_SUCCESS);
	}
	add = light_parse_export(&prompt[i]);
	if (add == -1)
		return (EXIT_FAILURE);
	while (prompt[i] == ' ')
		i++;
	pos = check_if_variable_already_exist(&(env->env_ms), &prompt[i]);
	size = size_variable(&prompt[i], add, pos);
	str = get_good_variable(&prompt[i], size, add, pos);
	if (pos == -1)
		add_var_env_minishell(&(env->env_ms), str);
	else
		change_var_env_minishell(&(env->env_ms), str, pos);
	return (EXIT_SUCCESS);
}

int	built_in_to_create(t_struct *ms, char **cmd_args, char *prompt)
{
	// print_tab_char(cmd_args);
	if (ft_pos_strstr(cmd_args[0], "cd") != -1)
		return (built_in_cd(&(ms->env), cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "pwd") != -1)
		return (built_in_pwd());
	else if (ft_pos_strstr(cmd_args[0], "env") != -1)
		return (built_in_env(ms->env.env_ms));
	else if (ft_pos_strstr(cmd_args[0], "export") != -1)
		return (built_in_export(&(ms->env), prompt, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "unset") != -1)
		return (built_in_unset(&(ms->env), cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "echo") != -1)
		return (built_in_echo(ms, cmd_args, prompt));
	else if (ft_pos_strstr(cmd_args[0], "exit") != -1)
		built_in_exit(&(ms->env), cmd_args, prompt);
	return (-1);
}

void command(char *prompt, t_struct *ms)
{
	int		i;
	int		last;
	char	*good_path;
	char	**args;

	i = 0;
	// add_history(prompt);
	// print_env_ms(&(ms->env));
	while (prompt[i] == ' ')
		i++;
	args = get_cmd_and_args_split(&prompt[i]);
	if (args == NULL)
		return ;
	last = last_redir(args);
	if (last != -1)
	{
		get_redirections(ms, args, last);
		ft_free_tab(args);
		// print_env_ms(&(ms->env));
		return ;
	}
	if (built_in_to_create(ms, args, prompt) != -1)
	{
		ft_free_tab(args);
		// print_env_ms(&(ms->env));
		return ;
	}
	// if (redirection(env, args, prompt) != -1)
	// {
	// 	ft_free_tab(args);
	// 	return ;
	// }
	good_path = working_path(ms->env.path, args[0]);
	execute_cmd(good_path, args, ms->env.env_bash);
	ft_free_tab(args);
	// print_env_ms(&(env->env_ms));
}
