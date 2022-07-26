int	main(int ac, char **av)
{
	t_minirt	minirt;
	t_figures	*lst;
	t_light		*light;
	t_cam		*cam;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&minirt);
	parse_file(&minirt, av);
	lst = minirt.figures;
	cam = minirt.cam;
	while (cam)
	{
		printf("cam: %f %f %f , %f %f %f , %d\n", cam->o.x, cam->o.y, cam->o.z,
			cam->nv.x, cam->nv.y, cam->nv.z, cam->fov);
		printf("llc: %f %f %f\n", cam->llc.x, cam->llc.y, cam->llc.z);
		cam = cam->next;
	}
	while (lst)
	{
		if (lst->flag == SP)
			printf("sp: %f %f %f %f %d\n", lst->fig.sp.c.x, lst->fig.sp.c.y, lst->fig.sp.c.z, lst->fig.sp.r, lst->fig.sp.inside);
		else if (lst->flag == PL)
			printf("pl: %f %f %f\n", lst->fig.pl.p.x, lst->fig.pl.p.y, lst->fig.pl.p.z);
		lst = lst->next;
	}
	printf("A: %f %d\n", minirt.scene.ambient_light, minirt.scene.al_color);
	light = minirt.scene.l;
	while (light)
	{
		printf("L: %f %f %f %f %d\n", light->o.x, light->o.y, light->o.z, light->br, light->color);
		light = light->next;
	}
	return (0);
}
