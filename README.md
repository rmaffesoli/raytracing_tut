# C++ Raytracer




This repo is a c++ raytracing implementation. 

As I work in the 3D animation field I wanted to explore creating a raytrace rendering program for my capstone project.
This Repo implements a standard raytracing solution that allows form the camera to be repositioned, as well as many objects of three different material types. The material types are Lambert, Metallic, and Dielectric. 
This repo also exhibits many of the featuers used in Production level ray tracers such as: 
bounced lighting values, 
  colored reflecitons
  colored refractions
  glossy reflecitons
  index of refraction for dielectric materials
  glossy refractions
  depth of field
  camera lensing

This repo pushes the dielectric material further allowing for glossy refractions as well as a the ability to change the refration color. Currently this raytracer is implemented in a scanline manner and is single threaded at this time. 


Based upon Peter Shirley's work found [here](https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview). 

## Usage
This raytracer must be compiled using the -std=c++11 argument. When running the subsequent ./a.out file, an image out put will be placed in `../output/rgb_out.ppm` relative to the source file.
```bash
> g++ -std=c++11 main.cpp && ./a.out

```
![sample output](https://github.com/rmaffesoli/raytracing_tut/blob/master/output/rgb_out_final.png?raw=true)

#Structure
  All classes are defined in their own header files while the main.cpp is used to pull everthing together when rendereding the final image.
  

# Rubric items addressed:
 1. The project demonstrates an understanding of C++ functions and control structures.
 2. The project reads data from a file and process the data, or the program writes data to a file.
 3. The project uses Object Oriented Programming techniques.
 4. Classes use appropriate access specifiers for class members.
 5. Class constructors utilize member initialization lists.
 6. Classes follow an appropriate inheritance hierarchy.
 7. Overloaded functions allow the same function to operate on different parameters.
 8. Derived class functions override virtual base class functions.
 9. The project makes use of references in function declarations.
 10. The project uses smart pointers instead of raw pointers.
