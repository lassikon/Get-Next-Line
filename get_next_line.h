/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:08:21 by lkonttin          #+#    #+#             */
/*   Updated: 2023/12/13 14:48:58 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*buf;
	struct s_list	*next;
}	t_list;

char	*ft_calloc(size_t size);
t_list	*ft_lstlast(t_list *list);
int		len_to_newline(t_list *list);
void	copy_str(t_list *list, char *str);
int		found_newline(t_list *list);
void	clean_and_free(t_list **list, t_list *clean_node, char *buf);
int		trim_list(t_list **list);
int		add_to_list(t_list **list, char *buf);
int		create_list(t_list **list, int fd);
char	*get_next_line(int fd);

#endif