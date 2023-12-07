/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:15:29 by lkonttin          #+#    #+#             */
/*   Updated: 2023/12/07 17:24:52 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	trim_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = ft_calloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		++i;
	while (last_node->buf[i])
	{
		i++;
		buf[k] = last_node->buf[i];
		k++;
	}
	clean_node->buf = buf;
	clean_node->next = NULL;
	clean_and_free(list, clean_node, buf);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buf[i] != '\0')
		{
			if (list->buf[i] == '\n')
			{
				str[k] = '\n';
				str[k + 1] = '\0';
				return ;
			}
			str[k] = list->buf[i];
			k++;
			i++;
		}
		list = list->next;
	}
	str[k] = '\0';
}

void	add_to_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		bytes_read;
	char	*buf;

	bytes_read = 0;
	while (!found_newline(*list))
	{
		buf = ft_calloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		/* if (bytes_read < 0)
		{
			free(buf);
			free((*list)->buf);
			free(*list);
			return ;
		} */
		if (bytes_read == 0)
		{
			free(buf);
			return ;
		}
		add_to_list(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				str_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_line = malloc(str_len + 1);
	if (next_line == NULL)
		return (NULL);
	copy_str(list, next_line);
	trim_list(&list);
	return (next_line);
}

/* The read function returns the number of bytes read,
and it can return 0 if the end of the file is reached.
If an error occurs, it returns -1. */