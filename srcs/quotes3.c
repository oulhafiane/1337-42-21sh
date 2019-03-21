/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:50:02 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/21 13:45:05 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_special(char c)
{
	const char	*escapchar = " !@#$%^&*()-_+=,;.\"\n\t\v\f\r\\";

	if (ft_strchr(escapchar, c))
		return (1);
	return (0);
}

int				handle_dollar(char **line, char **new_line, int *i)
{
	char *head;
	char *env;
	char *tmp;

	if (is_special(*((*line) + 1)))
		return (0);
	head = ++(*line);
	while (*head && !is_special(*head))
		head++;
	tmp = ft_strndup(*line, head - *line);
	if ((env = getenv(tmp)) == NULL)
		env = "";
	free(tmp);
	while (*env)
		(*new_line)[(*i)++] = *env++;
	*line = head;
	return (1);
}

int				handle_tilda(char **line, char **new_line, int *i)
{
	char	*head;
	char	*home;
	int		j;

	j = 0;
	if (ft_isalpha(*((*line) + 1)))
		return (0);
	head = ++(*line);
	if (head[0] == '/' || head[0] == '\0')
	{
		if ((home = getenv("HOME")) == NULL)
				home = "";
	}
	else
		return (0);
	while (head[j])
		(*new_line)[(*i)++] = head[j++];
	*line = head;
	return (1);
}

t_command_list	*init_quotes(t_line *line, t_command_list *commands)
{
	init_list(commands);
	handle_quote(line, commands, -1);
	return (commands);
}
