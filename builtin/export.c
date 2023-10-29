/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:06:10 by ilsahin           #+#    #+#             */
/*   Updated: 2023/10/29 20:16:47 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//kendi verdiğimiz değişkenin adını da kontrol etmemiz lazım (export a=b)

int	env_len(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
		env++;
	return (env - g_ms.env);
}

int	export_len(void)
{
	char	**export;

	export = g_ms.export;
	while (*export)
		export++;
	return (export - g_ms.export);
}

void	add_export(char *str)
{
	int		i;
	char	**export;
	char	**new_export;

	i = 0;
	export = g_ms.export;
	new_export = ft_calloc(sizeof(char **), export_len() + 2);
	while (export[i])
	{
		new_export[i] = ft_strdup(export[i]);
		i++;
	}
	new_export[i] = ft_strdup(str);
	free_array(g_ms.export);
	g_ms.export = new_export;
}

int export_pos(char *str, char *export)
{
	int i = 0;
	int pos;
	char *tmp;
	
	while(export[i] && export[i] != '=')
	{
		i++;
	}
	pos = i;
	tmp = ft_substr(export, 0, pos);
	if(ft_strcmp(tmp, str))
	{
		free(tmp);
		return TRUE;
	}
	free(tmp);
	return FALSE;
}

int	check_export(char *str)
{
	char	**export;

	export = g_ms.export;
	while(*export)
	{
		if(ft_strcmp(*export, str) || export_pos(str, *export))
			return FALSE;
		export++;
	}
	return TRUE;
}

int	check_env(char *str)
{
	char	*head;

	head = ft_strchr(str, '=');
	if (!head)
	{
		if(check_export(str))
			add_export(str);
		return (FALSE);
	}
	if (head == str)
		return (FALSE);
	while (*str)
	{
		if (is_whitespace(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}


void	add_env(char *str)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_ms.env;
	new_env = ft_calloc(sizeof(char **), env_len() + 2);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_array(g_ms.env);
	g_ms.env = new_env;
}

int	is_include(char *str)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	env = g_ms.env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && str[j])
		{
			if (str[j] == '=' && env[i][j] == '=')
				return (i);
			if (str[j] != env[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

void	builtin_export(char **input)
{
	int		pos;
	char	*tmp_env;
	char	*tmp_export;

	input++;
	if (!*input)
		print_export();
	while (*input)
	{
		if (check_env(*input))
		{
			pos = is_include(*input);
			if (pos != -1)
			{
				tmp_env = g_ms.env[pos];
				g_ms.env[pos] = ft_strdup(*input);
				tmp_export = g_ms.export[pos];
				g_ms.export[pos] = ft_strdup(*input);
				free(tmp_env);
				free(tmp_export);
			}
			else
			{
				add_env(*input);
				add_export(*input);
			}
		}
		input++;
	}
	set_paths();
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
