/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:19:48 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/04 08:41:13 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_path(char *path, char *cmd)
{
	size_t	i;
	int		j;
	char	*dst;

	if (path == NULL || cmd == NULL)
		return (NULL);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(cmd) + 2);
	if (dst == NULL)
		return (NULL);
	while (i < ft_strlen(path))
	{
		dst[i] = path[i];
		i++;
	}
	dst[i++] = '/';
	while (i < ft_strlen(path) + ft_strlen(cmd) + 1)
	{
		dst[i] = cmd[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

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
		perror("Fork"); // voir le cas d'erreur
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, args, env) == -1)
			perror(args[0]); // voir le cas d'erreur
		exit(EXIT_FAILURE);
	}
}

int	built_in_env(t_env_ms *stack)
{
	while (stack)
	{
		printf("%s\n", stack->var);
		stack = stack->next;
	}
	return (EXIT_SUCCESS);
}

int	size_variable(char *prompt)
{
	int	i;
	int	ret;
	int	len;

	i = 0;
	ret = 0;
	len = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	while (prompt[i] != '=')
	{
		len++;
		i++;
	}
	i++;
	len++;
	if (prompt[i] == '"')
	{
		i++;
		ret = 1;
	}
	while ((ret == 1 && prompt[i] != '"') || (ret == 0 && prompt[i] != ' '))
	{
		i++;
		len++;
	}
	return (len);
}

char	*get_good_variable(char *prompt)
{
	int		i;
	int		j;
	int		ret;
	char	*str;

	i = 0;
	j = 0;
	ret = 0;
	str = malloc(sizeof(char) * (size_variable(prompt) + 1));
	if (str == NULL)
	{
		printf("Bad malloc.\n");
		return (NULL);
	}
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	while (j < size_variable(prompt))
	{
		str[j] = prompt[i];
		if (ret == 0 && prompt[i] == '=' && prompt[i + 1] == '"')
		{
			i++;
			ret = 1;
		}
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	light_parse_export(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	i += 6;
	while (prompt[i] == ' ')
		i++;
	if (prompt[i] != '=')
		return (EXIT_FAILURE);
	i++;
	if (prompt[i] == '&' || prompt[i] == '(' || prompt[i] == ')' || prompt[i] == ';' || prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|') // pas vraiment, checker commant il fonctionnne
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	built_in_export(t_env *env, char *prompt)
{
	int		i;
	int		ret;
	char	*str;

	i = 6;
	if (light_parse_export(prompt) == -1)
	{
		printf("Error command export\n");
		return (EXIT_FAILURE);
	}
	while (prompt[i] == ' ')
		i++;
	str = get_good_variable(prompt);
	ret = check_if_variable_already_exist(&(env->env_ms), &prompt[i]);
	if (ret == -1)
		add_var_env_minishell(&(env->env_ms), str);
	else
		change_var_env_minishell(&(env->env_ms), str, ret);
	// print_env_ms(&(env->env_ms));
	return (EXIT_SUCCESS);
}

int	built_in_unset(t_env *env, char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = check_if_variable_already_exist(&(env->env_ms), args[1]);
	if (ret != -1)
		supp_var_env_ms(&(env->env_ms), ret);
	return (EXIT_SUCCESS);
}

int	light_parse_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	i += 4;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			return (i);
		}
	}
	return (-1);
}

int	built_in_echo(char *prompt)
{
	int	i;
	int	len;
	int	line_break;

	i = 0;
	line_break = light_parse_echo(prompt);
	if (line_break != -1)
		i = line_break;
	else
	{
		while (prompt[i] == ' ')
			i++;
		i += 4;
		while (prompt[i] == ' ')
			i++;
	}
	len = ft_strlen(&prompt[i]);
	write(1, &prompt[i], len);  // verifier pour les redirections... a ecrire dans un fichier
	if (line_break == -1)
		write(1, "\n", 1); // verifier pour les redirections... a ecrire dans un fichier
	return (EXIT_SUCCESS);
}

void	built_in_exit(t_env *env, char **cmd_args, char *prompt)
{
	free_lst(env->env_ms);
	ft_free_tab(cmd_args);
	ft_free_tab(env->path);
	// ft_free_tab(env->env_bash); // il me dit qu'il faut pas free parce que j'ai pas alloue mais si ouesh...
	// free(env->rel); faut l'allouer d'abord en fait....
	free(prompt);
	exit (0);
}

int	built_in_to_create(t_env *env, char **cmd_args, char *prompt)
{
	// print_tab_char(cmd_args);
	if (ft_pos_strstr(cmd_args[0], "cd") != -1)
		return (built_in_cd(env, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "pwd") != -1)
		return (built_in_pwd());
	else if (ft_pos_strstr(cmd_args[0], "env") != -1)
		return (built_in_env(env->env_ms));
	else if (ft_pos_strstr(cmd_args[0], "export") != -1)
		return (built_in_export(env, prompt));
	else if (ft_pos_strstr(cmd_args[0], "unset") != -1)
		return (built_in_unset(env, cmd_args));
	else if (ft_pos_strstr(cmd_args[0], "echo") != -1)
		return (built_in_echo(prompt));
	else if (ft_pos_strstr(cmd_args[0], "exit") != -1)
		built_in_exit(env, cmd_args, prompt);
	return (-1);
}

void start_built_in(char *prompt, t_env *env)
{
	int		i;
	char	*good_path;
	char	**args;

	i = 0;
	while (prompt[i] == ' ')
		i++;
	args = get_cmd_and_args_split(&prompt[i]);
	if (built_in_to_create(env, args, prompt) != -1)
	{
		ft_free_tab(args);
		// print_env_ms(&(env->env_ms));
		return ;
	}
	good_path = working_path(env->path, args[0]);
	execute_cmd(good_path, args, env->env_bash);
	// err = execve(good_path, args, env->env);
	// if (err == -1)
	// printf("err = %d\n", err);
	ft_free_tab(args);
	// print_env_ms(&(env->env_ms));
}
