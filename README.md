# Redqueen

A Simple Production Renderer for Educational Purpose

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
* Free - targeting at individuals and small stusios
