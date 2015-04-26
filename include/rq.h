

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Redqueen Copyright (c) shinji All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __rq_h__
#define __rq_h__


#define API __declspec(dllexport) 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enumerations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Visibility : char { Invisible = 0, InvisibleFromLight = 1, InvisibleFromCamera = 2, Visible = 3 };

enum Channel : int
{
	Beauty            = 1 <<  0,
	LightPath         = 1 <<  1,
	Lambertian        = 1 <<  2, // CameraAOV + LightAOV
	LambertianColor   = 1 <<  3,
	Transmissive      = 1 <<  4, // CameraAOV + LightAOV
	TransmissiveColor = 1 <<  5,
	Glossy            = 1 <<  6, // CameraAOV + LightAOV
	GlossyColor       = 1 <<  7,
	Specular          = 1 <<  8,
	SpecularColor     = 1 <<  9,
	Emissive          = 1 << 10,
	Normal            = 1 << 11,
	Tangent           = 1 << 12,
	Position          = 1 << 13,
	Depth             = 1 << 14,
	UserData          = 1 << 15
	// More Channels to come
};


enum class Element : char
{
	Lambertian, Transmissive, Glossy, Specular, Emissive,
	Diffusion, // SSS
	ShadowTransparency,
	Normal,
	Weight,
	Anisotropy, Roughness, Angle, // Polishing
	IOR, Fresnel, Thickness, //
	Clip
};

enum class AngleMeasure : char { Horizontal, Vertical, Diagonal }; // For Field of View
enum class Sideness     : char { Face, Back, Both }; // 2 sided-material
enum class Projection   : char { Perspective, Spherical, Orthographic }; // For camera and Gobo
enum class Addressing   : char { Wrap, Clamp };
enum class PixelSampler : char { Nearest, Stochastic, Bilinear };
enum class Filter       : char { None, Gradient, Normal, Gaussian, Variance };
enum class Path         : char { Null, Occlusion, DiffuseReflection, DiffuseTransmittance, GlossyReflection, GlossyRefraction, SpecularReflection, SpecularRefraction };
enum class Material     : char { Conductor, Dielectric, DielectricFilm };
//enum class BRDF         : char { Ward };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

API int  rqAddCamera            ( );
API void rqSetCameraName        ( const int camera_id, const char*        name    );
API void rqSetCameraProjection  ( const int camera_id, const Projection   type    );
API void rqSetCameraAngleMeasure( const int camera_id, const AngleMeasure measure );
API void rqSetCameraFOV         ( const int camera_id, const float        degree  );
API void rqSetCameraBokeh       ( const int camera_id, const float        degree  );
API void rqSetCameraTime        ( const int camera_id, const float        time    ); // time should be either 0.0f or 1.0f for now
API void rqSetCameraSample      ( const int camera_id, const int          samples ); // AA Samples (can be an arbitrary number)

API void rqSetCameraResolution  ( const int camera_id, const int width, const int height );
API void rqSetCameraRegion      ( const int camera_id, const int left, const int top, const int right, const int bottom );

API void rqSetCameraPosition    ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraTarget      ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraUpVector    ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraExposure    ( const int camera_id, const float r, const float g, const float b );

API int  rqAddCameraAOV         ( const int camera_id );
API void rqSetCameraAOVName     ( const int camera_id, const int aov_id, const char*   name    );
API void rqSetCameraAOVChannel  ( const int camera_id, const int aov_id, const Channel channel );
API void rqSetCameraAOVUserData ( const int camera_id, const int aov_id, const char*   name    );

API void rqInitializeCameras ( );
API void rqFinalizeCameras   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Point Light
API int  rqAddPointLight           ( );
API void rqSetPointLightTime       ( const int point_light_id, const float time );
API void rqSetPointLightPosition   ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightDirection  ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightColor      ( const int point_light_id, const float r, const float g, const float b );
API void rqSetPointLightPhoton     ( const int point_light_id, const int   photon     );
API void rqSetPointLightSample     ( const int point_light_id, const int   sample     );
API void rqSetPointLightBlur       ( const int point_light_id, const float blur       );
API void rqSetPointLightOffset     ( const int point_light_id, const float offset     );
API void rqSetPointLightInnerAngle ( const int point_light_id, const float inner_angle_degree );
API void rqSetPointLightOuterAngle ( const int point_light_id, const float outer_angle_degree );
API void rqSetPointLightShaderLink ( const int point_light_id, const int shader_id ); // Light Linking
API int  rqAddPointLightAOV        ( const int point_light_id ); // Add AOV Channel
API void rqSetPointLightAOVName    ( const int point_light_id, const int aov_id, const char*   name );
API void rqSetPointLightAOVChannel ( const int point_light_id, const int aov_id, const Channel channel );


// Parallel Light aka DIrectional Light
API int  rqAddParallelLight           ( );
API void rqSetParallelLightTime       ( const int parallel_light_id, const float time );
API void rqSetParallelLightDirection  ( const int parallel_light_id, const float x, const float y, const float z );
API void rqSetParallelLightColor      ( const int parallel_light_id, const float r, const float g, const float b );
API void rqSetParallelLightPhoton     ( const int parallel_light_id, const int   photon );
API void rqSetParallelLightSample     ( const int parallel_light_id, const int   sample );
API void rqSetParallelLightBlur       ( const int parallel_light_id, const float blur   );
API void rqSetParallelLightOffset     ( const int parallel_light_id, const float offset );
API void rqSetParallelLightShaderLink ( const int parallel_light_id, const int shader_id ); // Light Linking
API int  rqAddParallelLightAOV        ( const int parallel_light_id ); // Add AOV Channel
API void rqSetParallelLightAOVName    ( const int parallel_light_id, const int aov_id, const char*   name );
API void rqSetParallelLightAOVChannel ( const int parallel_light_id, const int aov_id, const Channel channel );


// Gaffer Initializes all Non-Area Lights (Point Lights and Parallel Lights)
API void rqInitializeGaffer( );
API void rqFinalizeGaffer  ( );


// Sky Light
API void rqSetSkyLightTime       ( const float time   );
API void rqSetSkyLightImage      ( const char* name   );
API void rqSetSkyLightBackdrop   ( const char* name   );
API void rqSetSkyLightPhoton     ( const int   photon );
API void rqSetSkyLightSample     ( const int   sample );
API void rqSetSkyLightColor      ( const float r, const float g, const float b );
API void rqSetSkyLightNorth      ( const float x, const float y, const float z );
API void rqSetSkyLightZenith     ( const float x, const float y, const float z );
API void rqSetSkyLightShaderLink ( const int shader_id );
API int  rqAddSkyLightAOV        ( );
API void rqSetSkyLightAOVName    ( const int aov_id, const char*   name );
API void rqSetSkyLightAOVChannel ( const int aov_id, const Channel channel );

API void rqInitializeSkyLight  ( );
API void rqFinalizeSkyLight    ( );


// Geometry Light
API void rqSetGeometryLightTime          ( const float time );
API void rqSetGeometryLightPhoton        ( const int photon );
API void rqSetGeometryLightSample        ( const int sample );
API void rqSetGeometryLightShaderLink    ( const int shader_id );
API int  rqAddGeometryLightAOV           ( );
API void rqSetGeometryLightAOVName       ( const int aov_id, const char*   name    );
API void rqSetGeometryLightAOVChannel    ( const int aov_id, const Channel channel );
API void rqSetGeometryLightAOVShaderName ( const int aov_id, const char*   shader  );

API void rqInitializeGeometryLight ( );
API void rqFinalizeGeometryLight   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rendering
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetRendererSample     ( const int   sample     );
API void rqSetRendererBounce     ( const int   bounce     );
API void rqSetRendererRadius     ( const float radius     );
API void rqSetRendererResolution ( const float resolution );
API void rqSetRendererDistance   ( const float distance   );
API void rqSetRendererRayDepth   ( const int   depth      );
API void rqSetRendererPhotonDepth( const int   depth      );
API void rqSetRendererClamp      ( const float r, const float g, const float b );

API void rqInitializeRenderer  ( );
API void rqFinalizeRenderer    ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetDisplayGamma  ( const float gamma   ); // Not working yet
API void rqSetPreviewWindow ( const bool  preview );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

API int  rqAddShader                ( );
API void rqSetShaderName            ( const int shader_id, const char*      name );
API void rqSetShaderTime            ( const int shader_id, const float      time );
API void rqSetShaderSmoothAngle     ( const int shader_id, const float      smooth_angle           );
API void rqSetShaderRoundCorner     ( const int shader_id, const float      round_corner           ); // Not working yet
API void rqSetShaderHairUV          ( const int shader_id, const bool       assign_hair_texture_uv );
API void rqSetShaderVisibility      ( const int shader_id, const Visibility visibility             );

// Surface Shader
API int  rqAddSurfaceShader         ( const int shader_id );
API void rqSetSurfaceSideness       ( const int shader_id, const int layer_id, const Sideness   sideness      );
API void rqSetSurfaceMaterial       ( const int shader_id, const int layer_id, const Material   material      );
API void rqSetSurfaceVirtualLight   ( const int shader_id, const int layer_id, const bool       virtual_light );
API void rqSetSurfaceColor          ( const int shader_id, const int layer_id, const Element    element, const float r, const float g, const float b ); // Set Color or Values
API void rqSetSurfaceImage          ( const int shader_id, const int layer_id, const Element    element, const char* name, const float gamma, const float color_matrix[ 4 ][ 4 ], const float uv_matrix[ 3 ][ 3 ] );

// Displacement Map (Needs Tangents and Normals to Work. They can be created by setting a proper smoothing angle )
API int  rqAddDisplacementShader    ( const int shader_id );
API void rqSetDisplacementLevel     ( const int shader_id, const int displacement_id, const int level ); // Subdivision Level
API void rqSetDisplacementVector    ( const int shader_id, const int displacement_id, const float x, const float y, const float z );
API void rqSetDisplacementImage     ( const int shader_id, const int displacement_id, const char* name, const float gamma, const float color_matrix[ 4 ][ 4 ], const float uv_matrix[ 3 ][ 3 ] );

// Volume Shader
//API int  rqAddVolumeShader        ( const int shader_id );
//API void rqSetVolumeTransmittance ( const int shader_id, const float r, const float g, const float b ); // Transmittance Per Meter
//API void rqSetVolumeAlbedo        ( const int shader_id, const float r, const float g, const float b ); // Decay Per Particle Collision
//API void rqSetVolumeAverageCosine ( const int shader_id, const float cosine );                          // Phase Function

// Shader Library
API void rqInitializeShaders ( );
API void rqFinalizeShaders   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddObject     ( );
API int  rqAddObject     ( const char* name );
API void rqSetObjectName ( const int object_id, const char* name );
API void rqSetObjectTime ( const int object_id, const float time );

// Part ( Limitation: particles and cylinders and mesh(triangles and tetragons) should be in different groups )
API int  rqAddPart ( const int object_id );

// Set Temporal Shader ID
API void rqSetShaderID ( const int object_id, const int part_id, const int shader_id );

// Vertex Data
API void rqAddRadii    ( const int object_id, const int part_id, const int n, const float* data );
API void rqAddUVs      ( const int object_id, const int part_id, const int n, const float* data );
API void rqAddPositions( const int object_id, const int part_id, const int n, const float* data );
API void rqAddNormals  ( const int object_id, const int part_id, const int n, const float* data );
API void rqAddTangents ( const int object_id, const int part_id, const int n, const float* data );

// Primitive
API void rqAddParticles ( const int object_id, const int part_id, const int n, const int* vertex_ids );
API void rqAddCylinders ( const int object_id, const int part_id, const int n, const int* vertex_ids );
API void rqAddTriangles ( const int object_id, const int part_id, const int n, const int* vertex_ids );
API void rqAddTetragons ( const int object_id, const int part_id, const int n, const int* vertex_ids );

// Multi-Level Instance
API int  rqAddInstance ( const int object_id );
API void rqSetInstance ( const int object_id, const int instance_id, const int instanced_object_id, const float matrix[4][4] = 0, int shader_id = 0 );


// Per Vertex/Primitive data "position", "uv", and "radius" are reserved.
API void rqAddVertexData    ( const int object_id, const int part_id, const char* name, const int n, const int dim, const float* data ); // The length of data is n x 1 s s .....
//API void rqAddPrimitiveData ( const int object_id, const int part_id, const char* name, const int n, const int dim, const float* data ); // The length of data is n x 1 s s .....

// Mesh Processing to Come..


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Accelerator
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqInitializeAccelerator( );
API void rqFinalizeAccelerator  ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqStartup      ( );
API void rqInitialize   ( ); // Initialize everything in an appropriate Order
API void rqFinalize     ( ); // Finalize   everything in an appropriate Order
API void rqShutdown     ( );
//API void rqSerialize    ( const char* folder_name ); // Serialize   Scene
//API void rqDeserialize  ( const char* folder_name ); // Deserialize Scene
API void rqGo           ( const char* folder_name ); // This function does everything for you
API void rqRender       ( );
API void rqRenderPixels ( const int num_of_pixels, float* rgb_s, const int subpixel_id );


#endif