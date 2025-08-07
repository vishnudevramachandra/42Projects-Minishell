/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:55:21 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 15:43:59 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	struct s_list	*last_node;

	last_node = ft_lstlast(*lst);
	if (last_node)
		last_node->next = new;
	else
		*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	struct s_list	*node = ft_lstnew("one");
// 	struct s_list	*node2 = ft_lstnew("two");
// 	struct s_list	*lst = NULL;

// 	ft_lstadd_back(&lst, node);
// 	ft_lstadd_back(&lst, node2);
// 	while (lst)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }