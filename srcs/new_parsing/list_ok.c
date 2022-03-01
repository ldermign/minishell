/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:28:49 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/01 21:49:14 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_arg	*reverse_list(t_list_arg *list)
{
	t_list_arg	*ret;
	
	ret = init_args();
	while (list->first != NULL)
	{
		insertion(ret, list->first->command);
		delete(list);
	}
	free(list);
	return (ret);
}



// t_list_arg	*new_list(t_list_arg *list)
// {
// 	t_args		*new;
// 	t_list_arg	*ret;

// 	ret = init_args();
// 	while (list->first != NULL)
// 	{
// 		new = list->first;
// 		new->next = ret->first;		//	>> probleme
// 		list->first = list->first->next;
// 		ret->first = new;
// 		// printf("test -> [%s]\n", list->first->command);
// 	}
// 	return (ret);
// }


// t_list_arg	*new_list(t_list_arg *list)
// {
//     t_args* tmp = NULL;
//     t_list_arg* ret = NULL;

//     while (list != NULL)
//     {
//         tmp = list->first;
//         list->first = tmp->next;
//         tmp->next = ret->first;
//         ret->first = tmp;
//     }
//     return (ret);
// }




// /* inverse la liste fournie en parametre et la renvoie */
// t_list_arg	*inverse(t_list_arg *list)
// {
//     /* un élément temporaire */
//     t_list* travail = NULL;
//     /* la liste inversée */
//     t_list* ret = NULL;
//     /* on parce la liste list tant qu'il y a un élément */
//     while (list != NULL)
//     {
//         /* on prend le premier element de la liste */
//         travail = list;
//         /* le début de la liste devient l'élément suivant */
//         list = travail->next;
//         /* on libère l'élélement de la liste  et on le place en début de la
//              liste à renvoyer*/
//         travail->next = ret;
//         /* l'élément qu'on vient de mettre en début de liste devient
//             le début de la liste de à renvoyer */
//         ret = travail;
//     }
//     /* YAPUKA renvoyer la liste inversée */
//     return (ret);
// }




// t_list_arg	*new_list(t_list_arg **list)
// {
//     t_list_arg	*middle = *list;
//     t_list_arg	*front = NULL;
//     t_list_arg	*back = NULL;

// 	front->first = middle->first->next;
//     if (*list != NULL)
// 	{
//         while (1)
// 		{
//             middle->first->next = back->first;
//             if (front == NULL)
// 				break;
//             back = middle;
//             middle = front;
//             front->first = front->first->next;
//         }
//         *list = middle;
//     }
// 	return (*list);
// }
