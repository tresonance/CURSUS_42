/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 02:53:20 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:13:29 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	translate1(t_env *e, t_matrix *m, t_vector *n, t_vector *r)
{
	*m = identity_matrix();
	*n = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&(*n));
	*r = crossvect(n, &e->up);
	normalize(&(*r));
}

void	translate(int key, t_env *e)
{
	t_matrix	m;
	t_vector	n;
	t_vector	r;
	t_vector	up;

	translate1(e, &m, &n, &r);
	if (key == LEFT)
		m = translate_matrix((t_vector){r.x * 10.0, r.y * 10.0, r.z * 10.0});
	if (key == RIGHT)
		m = translate_matrix((t_vector){-r.x * 10.0, -r.y * 10.0, -r.z * 10.0});
	if (key == UP)
		m = translate_matrix((t_vector){e->up.x * 10.0, e->up.y * 10.0, e->up.z
			* 10.0});
	if (key == DOWN)
		m = translate_matrix((t_vector){-e->up.x * 10.0, -e->up.y * 10.0,
			-e->up.z * 10.0
		});
	if (key == PLUS)
		m = translate_matrix((t_vector){n.x * 10.0, n.y * 10.0, n.z * 10.0});
	if (key == MINUS)
		m = translate_matrix((t_vector){-n.x * 10.0, -n.y * 10.0, -n.z * 10.0});
	e->cam.dir = matrix_mul_vect(m, e->cam.dir);
	e->cam.pos = matrix_mul_vect(m, e->cam.pos);
}

void	rotate1(t_env *e, t_matrix *m, t_vector *n, t_vector *r)
{
	*m = translate_matrix(opposite(&e->cam.pos));
	e->cam.dir = matrix_mul_vect(*m, e->cam.dir);
	*m = identity_matrix();
	*n = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&(*n));
	*r = crossvect(n, &e->up);
	normalize(&(*r));
}

void	rotate_n_axis(int key, t_env *e)
{
	t_vector	n;
	t_vector	r;
	t_matrix	m;

	m = identity_matrix();
	n = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&(n));
	r = crossvect(&n, &e->up);
	normalize(&(r));
	if (key == Q)
		m = rotate_matrix(n, 10 * M_PI / 180.0);
	if (key == E)
		m = rotate_matrix(n, -10 * M_PI / 180.0);
	e->up = matrix_mul_vect(m, e->up);
}

void	rotate(int key, t_env *e)
{
	t_matrix	m;
	t_vector	n;
	t_vector	r;
	t_vector	up;

	rotate1(e, &m, &n, &r);
	up = crossvect(&r, &n);
	if (key == A)
		m = rotate_matrix(e->up, -10 * M_PI / 180.0);
	if (key == D)
		m = rotate_matrix(e->up, 10 * M_PI / 180.0);
	if (key == W)
		m = rotate_matrix(r, 10 * M_PI / 180.0);
	if (key == S)
		m = rotate_matrix(r, -10 * M_PI / 180.0);
	e->cam.dir = matrix_mul_vect(m, e->cam.dir);
	m = translate_matrix(e->cam.pos);
	e->cam.dir = matrix_mul_vect(m, e->cam.dir);
}
