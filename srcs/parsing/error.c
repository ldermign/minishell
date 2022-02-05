/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:08:31 by elisa             #+#    #+#             */
/*   Updated: 2022/01/25 11:23:59 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_check(char *line, t_parsing *parsing, int i)
{
	if (line[parsing->i_line + i] != ' '
		&& line[parsing->i_line + i] != '\0')
	{
		error_command(line, parsing);
		return (-1);
	}
	parsing->i_line += i;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	return (0);
}

void	error_command(char *line, t_parsing *parsing)
{
	write(1, "error : ", 8);
	while (line[parsing->i_line] && line[parsing->i_line] != ' ')
	{
		ft_putchar(line[parsing->i_line]);
		parsing->i_line++;
	}
	printf(": command not found\n");
	parsing->error = 1;
}




// ^\ envoie le signal de sortie (SIGQUIT), qui indique classiquement à l'application de quitter au plus vite sans rien sauvegarder ; de nombreuses applications ne remplacent pas le comportement par défaut, qui consiste à arrêter l'application immédiatement¹. Ainsi, lorsque vous appuyez sur Ctrl+ 4(ou tout ce qui envoie le caractère ^\) dans catou bc, aucun des deux ne remplace le comportement par défaut, l'application est tuée.

// Le terminal lui-même imprime la ^\partie du message : c'est une représentation visuelle du caractère que vous avez tapé, et le terminal est en mode cuit et avec l'écho activé (les caractères sont affichés par le terminal dès que vous les tapez, par opposition à mode sans écho où les caractères ne sont envoyés qu'à l'application, qui choisit ou non de les afficher). La Quitpartie vient de bash : il remarque que son processus enfant est mort à cause d'un signal d'arrêt, et c'est sa façon de vous le faire savoir.

// Les shells gèrent tous les signaux courants, de sorte que si vous tapez ^\ dans un shell, vous ne tuez pas votre session, vous obtenez simplement une nouvelle invite, identique à ^C.



