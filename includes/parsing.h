/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 14:57:06 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <mlxe.h>
#include <mlxe_structs.h>

typedef struct s_map
{
	char* NO;//chemin par raport au programme
	char* SO;
	char* WE;
	char* EA;
	t_color F;//mlxe_color(r,g,b)
	t_color C;//mlxe_color(r,g,b)
	unsigned char **grid;
}	t_map;

t_map*	parsing(char* path);
void	free_map(t_map* map);

#endif
