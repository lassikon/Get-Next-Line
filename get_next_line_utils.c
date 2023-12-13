/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:53:07 by lkonttin          #+#    #+#             */
/*   Updated: 2023/12/13 14:48:57 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

t_list	*ft_lstlast(t_list *list)
{
	while (list != NULL)
	{
		if (list->next == NULL)
			return (list);
		list = list->next;
	}
	return (list);
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buf[i] != '\0')
		{
			if (list->buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

int	trim_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = ft_calloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (0);
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL)
		return (free(buf), 0);
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		++i;
	while (last_node->buf[i] && last_node->buf[++i])
		buf[k++] = last_node->buf[i];
	clean_node->buf = buf;
	clean_node->next = NULL;
	clean_and_free(list, clean_node, buf);
	return (1);
}

void	clean_and_free(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node == 0 || buf == 0)
	{
		if (buf)
			free(buf);
		return ;
	}
	if (clean_node->buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
