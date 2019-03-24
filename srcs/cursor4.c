/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:39:00 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/03/25 00:01:30 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_index(t_line *line, char step)
{
	int		top;
	int		index;

	line->index += step;
	line->current_index += step;
	if (step == 1 && line->command[line->index] == '\n')
		line->current_index = -1;
	else if (step == -1 && line->command[line->index + 1] == '\n')
	{
		index = line->index;
		while (index >= 0 && line->command[index] != '\n')
			index--;
		top = -1;
		while (line->command[++index] != '\0' && line->command[index] != '\n')
			top++;
		line->current_index = top;
	}
}

int		decision_up_right(t_line *line, int col)
{
	int		marge;

	marge = 0;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((line->current_index + marge) % col == col - 1)
		return (1);
	else
		return (0);
}

int		decision_down_left(t_line *line, int col)
{
	int		marge;

	marge = 0;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((line->current_index + marge) % col == col - 1)
		return (1);
	else
		return (0);
}

int		get_current_rows(t_line *line, int col)
{
	int	i;
	int	j;
	int	count_rows;

	count_rows = 0;
	i = -1;
	j = ft_strlen(GET_MSG(line->print_msg)) + 1;
	while (line->command[++i] != '\0')
	{
		if (line->command[i] == '\n')
		{
			count_rows++;
			j = -1;
		}
		else if (j % col == col - 1)
			count_rows++;
		j++;
	}
	return (count_rows);
}

int		decision_top_down_left(t_line *line, int col)
{
	int		marge;
	int		top;
	int		index;

	marge = 0;
	index = line->index;
	while (index >= 0 && line->command[index] != '\n')
		index--;
	top = -1;
	while (line->command[++index] != '\0' && line->command[index] != '\n')
		top++;
	if (line->index == line->current_index)
		marge = ft_strlen(GET_MSG(line->print_msg));
	if ((top + marge) % col == col - 1)
		return (1);
	else
		return (0);
}

void	set_new_current_index(t_line *line)
{
	int		index;

	index = line->index - 1;
	while (index >= 0 && line->command[index] != '\n')
		index--;
	if (index > 0)
		line->current_index = line->index - index;
	else
		line->current_index = line->index;
}

void	update_newlines(t_line *line, char step)
{
	t_list	*targeted_newline;

	targeted_newline = NULL;
	if (line->new_lines != NULL && line->new_lines->next != NULL)
		targeted_newline = line->new_lines->next;
	else if (line->new_lines == NULL && line->head_newlines != NULL)
		targeted_newline = line->head_newlines;
	if (targeted_newline == NULL)
		return ;
	*((int*)targeted_newline->content) += step;
	if (*((int*)targeted_newline->content) <= 0)
	{
		init_terms();
		*((int*)targeted_newline->content) = tgetnum("col");	
	}
}
