# Redqueen

A Simple Production Renderer for Educational Purpose (Made in Japan)

###To give a shot:
  
1. Download and Install Visual C++ Redistributable for Visual Studio 2015
 <https://www.microsoft.com/en-us/download/details.aspx?id=48145>
2. Double click "tutorialxx.exe" in the "bin" folder

###To create your app:
  
1. Download and Install Visual Studio Community <https://www.visualstudio.com/en-us/products/free-developer-offers-vs.aspx>
2. Select "Release" and "x64" in Configuration Manager to build your application


###Features:
* Extremely Simple APIs
* Small Memory Footprint
* Reasonably Fast
![Benchmark](https://github.com/shinjiogaki/redqueen/blob/master/images/rungholt.png)
* Deformation Blur with Consistent Motion
* Integrators:
  * Unidirectional Path Tracing with MIS for Outdoor Scenes
  * Progressive Final Gathering for Interior Scenes
  * Photon Mapping for SDS Paths
* Primitives: Particle / Cylinder (with Runtime Tessellation) / Triangle / Tetragon
![Primitives](https://github.com/shinjiogaki/redqueen/blob/master/images/fur.png)
* Light Sources: Point / Parallel / Geometry / Sky
* Per Light AOVs
![Per Light AOVs](https://github.com/shinjiogaki/redqueen/blob/master/images/per_light_aovs.png)
* Uber Shader (The parameters are automatically interpreted as those of Eugene d'Eon's model when applied to hair strands)
![Materials(Uber Shader)](https://github.com/shinjiogaki/redqueen/blob/master/images/materials.png)
* Brute-force SSS
![Materials(Brute-force SSS)](https://github.com/shinjiogaki/redqueen/blob/master/images/sss_boundaries.png)
* Three-Dimensional Procedural Shaders using Voronoi Cells
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

# Publications
* [An N-ary BVH Child Node Sorting Technique for Occlusion Test](http://jcgt.org/published/0005/02/02/)
* [Ray Tracing of Quadratic Parametric Surface](http://gcoe-mi.jp/english/temp/publish/62e18d4d8cbad1e01f68cebb2e81ac3e.pdf)
* [Direct Ray Tracing of Phong Tessellation](http://www.jp.square-enix.com/info/library/)
* [An Empirical Fur Shader](http://www.jp.square-enix.com/info/library/)
