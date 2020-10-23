/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:49:33 by gdelabro          #+#    #+#             */
/*   Updated: 2017/07/10 16:24:13 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		find_word(char *str, char *s, int i)
{
	int i2;

	i2 = 0;
	while (str[i] && s[i2])
	{
		if (str[i] != s[i2])
			return (0);
		i++;
		i2++;
	}
	if (s[i2])
		return (0);
	return (1);
}

void	fill_buf(t_pf *e, char *str, char *color)
{
	int i;

	i = -1;
	while (str[e->i] && str[e->i++] != '}')
		;
	while (color[++i])
		e->buf[e->i2++] = color[i];
}

int		test_colors(t_pf *e, char *str)
{
	if (find_word(str, "{cyan}", e->i))
		fill_buf(e, str, cCYAN);
	else if (find_word(str, "{none}", e->i))
		fill_buf(e, str, cNONE);
	else if (find_word(str, "{orange}", e->i))
		fill_buf(e, str, cORANGE);
	else if (find_word(str, "{black}", e->i))
		fill_buf(e, str, cBLACK);
	else if (find_word(str, "{red}", e->i))
		fill_buf(e, str, cRED);
	else if (find_word(str, "{green}", e->i))
		fill_buf(e, str, cGREEN);
	else if (find_word(str, "{brown}", e->i))
		fill_buf(e, str, cBROWN);
	else if (find_word(str, "{yellow}", e->i))
		fill_buf(e, str, cYELLOW);
	else if (find_word(str, "{blue}", e->i))
		fill_buf(e, str, cBLUE);
	else if (find_word(str, "{magenta}", e->i))
		fill_buf(e, str, cMAGENTA);
	else if (find_word(str, "{gray}", e->i))
		fill_buf(e, str, cGRAY);
	else
		return (0);
	return (1);
}
