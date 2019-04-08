/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:44:17 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/09 00:52:26 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_newchar(t_line *line, int buf)
{
	int		col;
	int		old_size;
	t_list	*new_newline;
	int		*diff;

	ft_putchar(buf);
	if (line->top + 2 >= line->buf_size)
	{
		old_size = line->buf_size;
		line->buf_size *= 2;
		line->command = ft_realloc(line->command, line->buf_size, old_size);
	}
	line->command[line->index + 1] = buf;
	init_terms();
	col = tgetnum("co");
	if (buf == '\n')
	{
		diff = (int*)malloc(sizeof(int));
		*diff = col - ((line->current_index + 1) % col);
		new_newline = ft_lstnew(diff, 0);
		if (line->new_lines == NULL)
			line->head_newlines = new_newline;
		ft_lstadd_end(&(line->new_lines), new_newline);
		line->new_lines = new_newline;
	}
	update_index(line, 1);
	line->top++;
	if (decision_down_left(line, col))
		go_down_left();
}

t_list	*delete_current_newline(t_line *line)
{
	t_list	*tmp_newlines;

	tmp_newlines = line->new_lines;
	if (line->new_lines->previous)
	{
		line->new_lines->previous->next = line->new_lines->next;
		line->new_lines = line->new_lines->previous;
	}
	else
	{
		line->head_newlines = line->new_lines->next;
		line->new_lines = NULL;
	}
	free(tmp_newlines);
	return (line->new_lines);
}

t_list	*free_next_newlines(t_line *line)

{
	t_list	*tmp;
	t_list	*tmp_next;

	if (line->new_lines && line->new_lines->next)
	{
		tmp = line->new_lines->next;
		while (tmp)
		{
			tmp_next = tmp->next;
			free(tmp->next);
			tmp = tmp_next;
		}
		line->new_lines->next = NULL;
	}
	return (line->new_lines);
}

void	print_char_inline(t_line *line, int buf)
{
	if (line->index >= line->top)
		print_newchar(line, buf);
	else
		move_cursor(buf, line);
}
