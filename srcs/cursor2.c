/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:52:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/04/09 16:47:57 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		get_current_row(int height)
{
	char	buf;
	int		row;
	char	begin;

	begin = 0;
	row = 0;
	tputs("\E[6n", 1, ft_putchar);
	while (read(0, &buf, 1) > 0)
	{
		if (begin == 3 && buf == 'R')
			break;
		if (begin == 2 && buf == ';')
			begin = 3;
		else if (begin == 1 && buf == 91)
			begin = 2;
		else if (begin == 0 && buf == 27)
			begin = 1;
		else if (begin == 2)
			row = (row * 10) + (buf - '0');
	}
	if (row >= 0 && row <= height)
		return (row);
	else 
		return (get_current_row(height));
}

void	go_down_left(void)
{
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
}

void	go_home(t_line *line, int col)
{
	size_t	step;

	step = line->index + 2;
	while (--step >= 1)
		go_left(line, col);
}

void	go_end(t_line *line, int col)
{
	size_t	step;

	step = (line->top - line->index) + 1;
	while (--step > 0)
		go_right(line, col);
}
