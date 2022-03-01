/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelqasm <abelqasm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:49:37 by abelqasm          #+#    #+#             */
/*   Updated: 2022/01/04 15:37:42 by abelqasm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_separate(char **str)
{
	char	*line;
	char	*fre;

	fre = *str;
	if (ft_srch_n(*str) == -1)
	{
		if (*str != NULL && **str != '\0')
			line = ft_strdup(*str);
		else
			line = NULL;
		free(fre);
		*str = NULL;
	}
	else
	{
		line = ft_substr(*str, 0, ft_srch_n(*str) + 1);
		*str = ft_substr(*str, ft_srch_n(*str) + 1,
				ft_strlen(*str) - ft_srch_n(*str));
		free(fre);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str[10240];
	int			i;
	char		*line;

	if (fd <= -1 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_strdup("");
	while (ft_srch_n(str[fd]) == -1)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		line[i] = 0;
		str[fd] = ft_strjoin(str[fd], line);
	}
	free(line);
	return (ft_separate(&str[fd]));
}
