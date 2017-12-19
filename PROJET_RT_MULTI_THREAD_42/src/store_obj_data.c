/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_obj_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:58:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:58:32 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

static int	get_obj1(t_obj **new, char ***tab, int *i)
{
	
	int flag;

	if (tab && *tab)
		(*new)->name = ft_strdup((*tab)[*i]);
	else
		return (0);
	flag = (ft_strcmp((*new)->name, "\tlight") == 0);
	*i += 1;
	if (0 != ft_strcmp("\t{", (*tab)[*i]))
		return (0);
	*i += 1;
	if (0 == is_light_object(*new, *tab, i))
		return (0);
	if (0 == csg_operator(*new, *tab, i))
		return (0);
	if (0 == get_degrade(*new, *tab, i))
		return (0);
	if (0 == get_matte_color(*new, *tab, i))
		return (0);
	if (0 == get_matte_colorv1(*new, *tab, i))
		return (0);
	if (0 == get_matte_colorv2(*new, *tab, i))
		return (0);
	if (0 == get_position(*new, *tab, i))
		return (0);
	if(flag == TRUE)
		return (1);
	if (0 == get_glossy_color(*new, *tab, i))
		return (0);
	//if (0 == get_opacity(*new, *tab, i))
	//	return (0);
	if (0 == get_indice(*new, *tab, i))
		return (0);
	if (0 == get_matte_factor(*new, *tab, i))
		return (0);
	if (0 == get_glossy_factor(*new, *tab, i))
		return (0);
	if (0 == get_specular_factor(*new, *tab, i))
		return (0);
	if (0 == get_tag(*new, *tab, i))
		return (0);;
	if (0 == get_type(*new, *tab, i))
		return (0);
	if (0 == get_hide_value(*new, *tab, i))
		return (0);	
	return (1);
}

int			get_obj(t_obj **obj, char **tab, int *i)
{
	t_obj	*new;
	int flag;
	
	if (NULL == (new = (t_obj *)malloc(sizeof(t_obj))))
		return (0);
	if (0 == get_obj1(&new, &tab, i))
		return (0);
	flag = (ft_strcmp(new->name, "\tlight") == 0);
	if (flag == FALSE)
	{
		if (!ft_strcmp("\tplane", new->name) || /* !ft_strcmp("\tthinring", new->name) || */!ft_strcmp("\tcylinder", new->name) || !ft_strcmp("\tcone", new->name) || !ft_strcmp("\ttorus", new->name) || !ft_strcmp("\tmobius", new->name))
		{
			if( 0 == get_axe(new, tab, i))
				return (0);
		}
		if (!ft_strcmp("\tsphere", new->name) ||  !ft_strcmp("\tcuboid", new->name) || !ft_strcmp("\tcylinder", new->name) || !ft_strcmp("\tcone", new->name) || !ft_strcmp("\tblock", new->name) ||  !ft_strcmp("\tbrick", new->name) || !ft_strcmp("\tchessboard", new->name) || !ft_strcmp("\tthinring", new->name) || !ft_strcmp("\ttorus", new->name) || !ft_strcmp("\tmobius", new->name) || !ft_strcmp("\tbox", new->name))
		{
			if(0 == get_size(new, tab, i))
				return (0);
		}
	}
	if( 0 == get_cut_info(new, tab, i))
			return (err_exit2("Error: cut_info"));
	if (0 != ft_strcmp("\t}", tab[(*i)++]))
		return (0);
	new->next = NULL;
	add_obj_to_scene(obj, new);
	return (1);
}

int			parser_obj(t_obj **obj, char **tab, int i)
{
	if (NULL == tab[i])
		return (0);
	while (0 == ft_strcmp("", tab[i]))
		i += 1;
	if (NULL == tab[i])
		return (0);
	if (0 != ft_strcmp("content", tab[i++]))
		return (0);
	if (0 != ft_strcmp("{", tab[i++]))
		return (0);
	while (tab[i] != NULL && tab[i][0] != '\0')
	{
		if (0 == ft_strcmp("\tlight", tab[i]) ||
			0 == ft_strcmp("\tplane", tab[i]) ||
			0 == ft_strcmp("\tcylinder", tab[i]) ||
			0 == ft_strcmp("\tcone", tab[i]) ||
			0 == ft_strcmp("\tsphere", tab[i]) ||
			0 == ft_strcmp("\tcuboid", tab[i]) ||
			0 == ft_strcmp("\tblock", tab[i]) ||
			0 == ft_strcmp("\tbrick", tab[i]) ||
			0 == ft_strcmp("\tchessboard", tab[i]) ||
			0 == ft_strcmp("\tthinring", tab[i]) ||
			0 == ft_strcmp("\ttorus", tab[i]) ||
			0 == ft_strcmp("\ttriangle", tab[i]) ||
			0 == ft_strcmp("\tbox", tab[i]) ||
			0 == ft_strcmp("\tmobius", tab[i]))
		{

			if (0 == get_obj(obj, tab, &i))
				return (0);
		}
		else
			i += 1;
	}
	return (1);
}
