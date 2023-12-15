/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:04:41 by lkonttin          #+#    #+#             */
/*   Updated: 2023/12/15 12:39:02 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	char			*buf;
	struct s_list	*next;
}	t_list;

char	*ft_calloc(size_t size);
t_list	*ft_lstlast(t_list *list);
int		len_to_newline(t_list *list);
char	*clean_and_free(t_list **list, t_list *clean_node, char *buf);
int		trim_list(t_list **list);
char	*get_next_line(int fd);

#endif