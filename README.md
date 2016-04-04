# Redqueen

A Simple Production Renderer for Educational Purpose (Made in Japan)

###To give a shot:
  
1. Download and Install Intel Compiler Redistributable Libraries <https://software.intel.com/en-us/articles/redistributables-for-intel-parallel-studio-xe-2016-composer-edition-for-windows>
2. Double click "tutorialxx.exe" in the "bin" folder

###To create your app:
  
1. Download and Install Visual Studio Community <https://www.visualstudio.com/en-us/products/free-developer-offers-vs.aspx>
2. Select "Release" and "x64" in Configuration Manager to build your application


###Features:
* Extremely Simple APIs
* Small Memory Footprint
* Motion Blur with Consistent Motion
* Integrators:
  * Unidirectional Path Tracing with MIS for Outdoor Scenes
  * Progressive Final Gathering for Interior Scenes
  * Photon Mapping for SDS Paths
* Primitives: Particle / Cylinder (with Runtime Tessellation) / Triangle / Tetragon
![Primitives](https://github.com/shinjiogaki/redqueen/blob/master/images/fur.png)
* Light Sources: Point / Parallel / Geometry / Sky
* Per Light AOVs
* Uber Shader (The parameters are automatically interpreted as those of Eugene's model when applied to hair strands)
![Materials(Uber Shader)](https://github.com/shinjiogaki/redqueen/blob/master/images/materials.png)
* Three-Dimensional Procedural Shaders using Voronoi Cells
![Procedural Shaders](https://github.com/shinjiogaki/redqueen/blob/master/images/stone.png)
![Procedural Shaders](https://github.com/shinjiogaki/redqueen/blob/master/images/beauty-20160305-222532.png)
* Multi-Level Instancing (40559990463 triangles in the image below)
![Multi-Level Instancing](https://github.com/shinjiogaki/redqueen/blob/master/images/mli.gif)
![Multi-Level Instancing](https://github.com/shinjiogaki/redqueen/blob/master/images/forest.png)
* AOVs with Per Vertex User Data
![AOVs](https://github.com/shinjiogaki/redqueen/blob/master/images/aov2.png)
* OBVH with Refitting / Treelet Reordering / Child Node Sorting for Fast Occlusion Test
* Redqueen does not use Embree

###Goals:
* Compact - reduce memory consumption 
* Simple - so that people can use without manual
* Fast - make best use of the instruction sets of modern CPUs
* Robust - never crashes
* Free - targeting at individuals and small studios
