#include "main.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <fstream>

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if  (depth <= 0)
        return color(0,0,0);

    if (world.hit(r,0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5, 0.7, 1.0);
}


hittable_list random_scene() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0.0,-1000,.0), 1000, material_ground));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8) {
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    auto albedo = color::random(0.5,1);
                    auto glossy = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, glossy);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    auto albedo = color::random(0.5,1);
                    auto glossy = random_double(0, 0.5);
                    auto ior = random_double(1.2, 2.5);
                    sphere_material = make_shared<dielectric>(albedo, ior, glossy);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto mat_1 = make_shared<dielectric>(color(1.0,1.0,1.0),1.5 ,0.0);
    world.add(make_shared<sphere>(point3(0,1,0), 1.0, mat_1));

    auto mat_2 = make_shared<lambertian>(color(0.4,0.2,0.1));
    world.add(make_shared<sphere>(point3(-4,1,0), 1.0, mat_2));

    auto mat_3 = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
    world.add(make_shared<sphere>(point3(4,1,0), 1.0, mat_3));

    return world;
}

int main() {
    const auto aspect_ratio = 16.0/9.0;
    const int img_w = 400;
    const int img_h  = static_cast<int>(img_w/aspect_ratio);
    const int samples_pp = 500;
    const int max_depth = 50;
    
    auto world = random_scene();


    const point3 cam_pos(13,2,3);
    const point3 cam_aim(0,0,0);
    const vec3 cam_up(0,1,0);
    const int vfov = 35;
    auto aperture = 0.1;
    auto focus_dist = 10;

    camera cam(cam_pos, cam_aim, cam_up, vfov, aspect_ratio, aperture, focus_dist);
    
    std::ofstream rgb_out("../output/rgb_out.ppm");
    rgb_out << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j = img_h-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < img_w; ++i) {
            color pixel_color(0,0,0);
            for (int s=0; s < samples_pp; ++s) {
                auto u = (i + random_double())/(img_w-1);
                auto v = (j + random_double())/(img_h-1);
                ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(rgb_out, pixel_color, samples_pp);
        }
    }
    std::cerr << "\nDone.\n";
}