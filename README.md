# Redqueen

A Simple Production Renderer for Educational Purpose

1. Install https://software.intel.com/sites/default/files/managed/14/91/w_ccompxe_redist_
msi_2015.0.108.zip
2. Download and double click "redqueen.exe" in the bin folder to give it a shot.

Select "Release" and "x64" in Configuration Manager to build your application.

Features:
* Extremely Simple APIs
* Small Memory Footprint
* Integrators: Unidirectional Path Tracing/Progressive Final Gathering/Photon Mapping
* Primitives: Particle/Cylinder/Triangle/Tetragon
* Light Sources: Point/Parallel/Geometry/Sky
* Per Light AOVs
* Per Vertex User Data
* Multi-Level Instancing
* Uber Shader for Surface/Hair (The parameters of uber shader are automatically interpreted as the parameters of Eugene's model)
* OBVH (with some advanced algorithms)
* Utilising AVX (Redqueen does not use Embree)

Goals:
* Compact - reduce memory consumption 
* Simple - so that people can use without manual
* Fast - make best use of the instruction sets of modern CPUs
* Robust - never crashes
* Free - targeting at individuals and small studios
