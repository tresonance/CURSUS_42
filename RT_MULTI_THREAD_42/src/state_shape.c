/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:57:45 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:57:54 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

/*t_obj	*generalize_initialize(void)
{
	t_obj *obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (NULL);
	obj->matte_factor = 0.2;
	obj->glossy_factor = 0.7;

	obj->matte = (t_color){1.0, 0.2 , 0.5};
	//obj->matte = scalcol(1.0 / obj->matte_factor, obj->matte);
	obj->glossy = (t_color){1.0, 0.0, 0.0};
	obj->base.rdir = (t_vector){1.0, 0.0, 0.0};
	obj->base.sdir = (t_vector){0.0, 1.0, 0.0};
	obj->base.tdir = (t_vector){0.0, 0.0, 1.0};
	obj->center =(t_vector){3.0, 4.0, 120.0 };

	obj->refractive_index = (double)REFRACTION_DIAMOND;
	obj->opacity = 0.1; //do not forget to check the range [0 1]
	obj->transparency = 1.0 - obj->opacity;
	obj->enclosed = TRUE;

	obj->next = NULL;
	return(obj);
}*/


/*t_obj	*initialize_cuboid(void)
{
	t_obj *cuboid;

	if (!(cuboid = generalize_initialize()))
		return (NULL);
	cuboid->a = 35.0;
	cuboid->b = 55.0;
	cuboid->c = 35.0;
	cuboid->center =(t_vector){3.0, 4.0, 2.0 };
	strcpy(cuboid->name, "cuboid");
	move_obj(cuboid, 0.0, 0.0, -50.0);
	rotate_x_obj(cuboid, -115.0);
	rotate_y_obj(cuboid, -22.0);
	//rotate_z_obj(cuboid, 15.0);
	return(cuboid);
}*/

/*t_obj   *initialize_cylinder(void)
{
        t_obj *cylin;

        if (!(cylin = generalize_initialize())) 
                return (NULL);
        cylin->zdisk = 25.0;
	cylin->radius = 10.0;
	cylin->center =(t_vector){3.0, 4.0, 2.0 };
        ft_strcpy(cylin->name, "cylinder");
       //move_obj(cylin, 0.0, 0.0, -50.0);
       //rotate_x_obj(cylin, -5.0);
       //rotate_y_obj(cylin, -10.0);
       //rotate_z_obj(cylin, 15.0);
       return(cylin);
}*/


/*t_obj   *initialize_sphere(void)
{
        t_obj *sphere;

        if (!(sphere = generalize_initialize()))
                return (NULL);
	sphere->radius = 15.0;
        sphere->center =(t_vector){ 0.0, 0.0, -60.0 };
        strcpy(sphere->name, "sphere");
       //move_obj(sphere, 0.0, 0.0, 0.0);
       //rotate_x_obj(sphere, -72.0);
       //rotate_y_obj(sphere, -60.0);
       //rotate_z_obj(sphere, -15.0);
       return(sphere);
}*/

/*t_obj   *initialize_cone(void)
{
        t_obj *cone;

        if (!(cone = generalize_initialize()))
                return (NULL);
	cone->radius = 15.0;
	cone->zdisk = 15.0;
        cone->center =(t_vector){ 0.0, 0.0, -20.0 };
        ft_strcpy(cone->name, "cone");
       //move_obj(cone, 0.0, 0.0, 0.0);
       //rotate_x_obj(cone, -72.0);
       //rotate_y_obj(cone, -60.0);
       //rotate_z_obj(cone, -15.0);
       return(cone);
}*/

/*t_obj   *initialize_plane(void)
{
        t_obj *plane;

        if (!(plane = generalize_initialize()))
                return (NULL);
        plane->center =(t_vector){ 0.0, 0.0, 20.0 };
        ft_strcpy(plane->name, "plane");
       //move_obj(plane, 0.0, 0.0, 0.0);
       //rotate_x_obj(plane, -72.0);
       //rotate_y_obj(plane, -60.0);
       //rotate_z_obj(plane, -15.0);
       return(plane);
}*/

