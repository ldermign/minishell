/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:55:27 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/11 18:03:35 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parsing(t_parsing *parsing)
{	
	parsing->error = 0;
	parsing->result = NULL;
	parsing->file_redirection = NULL;
	parsing->i_line = 0;
	parsing->option = 0;
	parsing->red1 = 0;
	parsing->red2 = 0;
}
