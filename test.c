#include <stdio.h>
#include <math.h>
#include "incs/vec3.h"

int main()
{
    t_p3    o;
    t_vec3  dir;
    t_vec3  ret;

    o = create_vec3(0,0,0);
    dir = create_vec3(1,1,1);
    ret = vadd(o, vscale(dir, INFINITY));
    printf("%f %f %f\n", ret.x, ret.y, ret.z);
    printf("%f\n", distance(ret, o));
}