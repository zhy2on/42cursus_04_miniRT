int	main(int ac, char **av)
{
	t_minirt	rt;
	t_figures	*figures;
	t_cam		*cam;

	if (ac < 2 || ac > 3)
	{
		printf("Usage: %s <scene.rt>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	init_minirt(&rt);
	parse_file(&rt, av);
	cam = rt.scene.cam;
	while (cam)
	{
		printf("cam: %f %f %f , %f %f %f , %d\n", cam->o.x, cam->o.y, cam->o.z,
			cam->nv.x, cam->nv.y, cam->nv.z, cam->fov);
		printf("llc: %f %f %f\n", cam->llc.x, cam->llc.y, cam->llc.z);
		cam = cam->next;
	}
	figures = rt.scene.figures;
	while (figures)
	{
		if (figures->flag == SP)
			printf("sp: %f %f %f %f %d\n",
				figures->fig.sp.c.x, figures->fig.sp.c.y, figures->fig.sp.c.z,
				figures->fig.sp.r, figures->fig.sp.inside);
		else if (figures->flag == PL)
			printf("pl: %f %f %f\n",
				figures->fig.pl.p.x, figures->fig.pl.p.y, figures->fig.pl.p.z);
		figures = figures->next;
	}
	init_mlx(&rt);
	mlx_loop(rt.mlx);
	return (0);
}
