# Redqueen

A Simple Production Renderer

### To give a shot:
  
1. Install Visual C++ Redistributable <https://www.microsoft.com/en-us/download/details.aspx?id=48145>
2. Double click "tutorialxx.exe" in the "bin" folder

### To create your app:
  
1. Install Visual Studio Community <https://www.visualstudio.com/en-us/products/free-developer-offers-vs.aspx>
2. Select "Release" and "x64" in Configuration Manager to build your application


### Features:
* Extremely simple APIs
* Small memory footprint
* Reasonably fast
![Benchmark](https://github.com/shinjiogaki/redqueen/blob/master/images/robot.png)
![Benchmark](https://github.com/shinjiogaki/redqueen/blob/master/images/living.png)
* Integrators:
  * Unidirectional path tracing with MIS for outdoor scenes
  * Progressive final gathering for interior scenes
  * Photon mapping for SDS paths
* Primitives: particle / cylinder (with runtime tessellation) / triangle / tetragon / cube (for voxel art)
![Primitives](https://github.com/shinjiogaki/redqueen/blob/master/images/fur.png)
* OBVH with refitting / treelet reordering / child node sorting for fast occlusion test
* Multi-level instancing (40559990463 triangles in the image below)
![Multi-level instancing](https://github.com/shinjiogaki/redqueen/blob/master/images/mli.gif)
![Multi-level instancing](https://github.com/shinjiogaki/redqueen/blob/master/images/forest.png)
* Deformation blur with consistent motion
* Light sources: point / parallel / geometry / sky
* Per light AOVs
![Per light AOVs](https://github.com/shinjiogaki/redqueen/blob/master/images/per_light_aovs.png)
![Per light AOVs](https://github.com/shinjiogaki/redqueen/blob/master/images/aov_pm.png)
* AOVs (Per vertex user data can be easily obtained)
![AOVs](https://github.com/shinjiogaki/redqueen/blob/master/images/aov2.png)
* Uber shader (The parameters are automatically interpreted as those of d'Eon's model when applied to hair strands)
![Materials(Uber shader)](https://github.com/shinjiogaki/redqueen/blob/master/images/materials.png)
* Brute-force SSS
![Materials(Brute-force SSS)](https://github.com/shinjiogaki/redqueen/blob/master/images/volume.png)
* Three-dimensional procedural shaders using Voronoi cells
![Materials(Brute-force SSS)](https://github.com/shinjiogaki/redqueen/blob/master/images/weathering.png)
* Redqueen does not use Embree

### Goals:
* Compact - reduce memory consumption 
* Simple - so that people can use without manual
* Fast - make best use of the instruction sets of modern CPUs
* Robust - never crashes
* Free - targeting at individuals and small studios

# Publications
* [An N-ary BVH Child Node Sorting Technique for Occlusion Tests](http://jcgt.org/published/0005/02/02/)
* [Ray Tracing of Quadratic Parametric Surface](http://gcoe-mi.jp/english/temp/publish/62e18d4d8cbad1e01f68cebb2e81ac3e.pdf)
* [Direct Ray Tracing of Phong Tessellation](http://www.jp.square-enix.com/info/library/)
* [An Empirical Fur Shader](http://www.jp.square-enix.com/info/library/)
* [Production Ray Tracing of Feature Lines](http://www.iliyan.com/publications/FeatureLineDrawing)
* [Shader Development at OLM](https://github.com/shinjiogaki/reports/blob/master/Shader%20Development%20at%20OLM.pdf)
      
# Technical Report
* [Fragmentation-Aware BVH Contraction](https://github.com/shinjiogaki/reports/blob/master/Fragmentation-Aware%20BVH%20Construction.pdf)

# Presentation
* [Procedural Shading & Texturing (CEDEC)](https://speakerdeck.com/shinjiogaki/procedural-shading-and-texturing)

# 日本語記事
* [行列を使ったポリゴン・メッシュの扱いについて](http://qiita.com/shinjiogaki/items/d16abb018a843c09b8c8)
* [BVHのはなし](https://shinjiogaki.github.io/bvh/)
