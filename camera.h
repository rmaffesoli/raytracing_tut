#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

class camera {
    public:
        camera(
            point3 cam_pos,
            point3 cam_aim,
            vec3 cam_up,
            double vfov,
            double aspect_ratio,
            double aperture,
            double focus_dist
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_h  = 2.0 * h;
            auto viewport_w = aspect_ratio * viewport_h;

            w = unit_vector(cam_pos - cam_aim);
            u = unit_vector(cross(cam_up, w));
            v = cross(w, u);

            origin = cam_pos;
            hor = focus_dist * viewport_w * u;
            ver = focus_dist * viewport_h * v;
            lower_left = origin - hor/2 -ver/2 - focus_dist*w;

            lens_radius = aperture /2;
        }

        ray get_ray(double s, double t) const {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v *rd.y();

            return ray(
                origin + offset,
                lower_left + s*hor + t*ver - origin - offset);
        }

    private:
        point3 origin;
        point3 lower_left;
        vec3 hor;
        vec3 ver;
        vec3 u,v,w;
        double lens_radius;
};

#endif