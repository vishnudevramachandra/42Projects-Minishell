/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:09:56 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 20:12:27 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_list	*new_lst_using_content(
	void *content, void *(*f)(void *), void (*del)(void *))
{
	struct s_list	*lst;
	void			*mapped_content;

	mapped_content = f(content);
	lst = ft_lstnew(mapped_content);
	if (!lst)
		del(mapped_content);
	return (lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	struct s_list	*mapped_lst;
	struct s_list	*last_node;

	if (!lst)
		return (NULL);
	mapped_lst = new_lst_using_content(lst->content, f, del);
	if (!mapped_lst)
		return (NULL);
	last_node = mapped_lst;
	lst = lst->next;
	while (lst)
	{
		last_node->next = new_lst_using_content(lst->content, f, del);
		last_node = last_node->next;
		if (!last_node)
		{
			ft_lstclear(&mapped_lst, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (mapped_lst);
}

// #include <stdio.h>

// void	*add_one(void *n)
// {
// 	int	*ptr = malloc(sizeof(int));
// 	*(int *)ptr = *(int *)n + 1;
// 	return (ptr);
// }

// int	main(void)
// {
// 	int		tab[] = {0, 1, 2, 3};
// 	t_list	*l = ft_lstnew(tab);
// 	int		i;

// 	printf("src: %d", *(int *)(l->content));
// 	i = 1;
// 	while (i < 4)
// 	{
// 		ft_lstadd_back(&l, ft_lstnew((void *)(tab + i)));
// 		printf(", %d", *(int *)(ft_lstlast(l)->content));
// 		i++;
// 	}
// 	printf("\n");
// 	t_list *m = ft_lstmap(l, add_one, free);
// 	printf("map: %d", *(int *)(m->content));
// 	m = m->next;
// 	while (m)
// 	{
// 		printf(", %d", *(int *)(m->content));
// 		m = m->next;
// 	}
// 	printf("\n");
// 	ft_lstclear(&m, free);
// }
