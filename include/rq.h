

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Redqueen Copyright (c) shinji All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#define API __declspec(dllexport) 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Units: meter & degree
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Class Type
static const int ClassInstance  = 0;
static const int ClassObject    = 1;
static const int ClassPrimitive = 2;

// Atomic Objects (Primitives)
static const int AtomNull     = 0;
static const int AtomCube     = 1; // Axis Aligned Cube
static const int AtomParticle = 2;
static const int AtomCylinder = 3;
static const int AtomTriangle = 4;
static const int AtomTetragon = 5;
static const int AtomInstance = 6;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Visibility
static const int InvisibleFromLight  = 1;
static const int InvisibleFromCamera = 2;
static const int Invisible           = 3;

// Sideness
static const int SideFace = 1; // Front side
static const int SideBack = 2; // Back  side
static const int SideBoth = 3; // Both  sides
static const int HairRoot = 1; // Hair  root
static const int HairTip  = 2; // Hair  tip
static const int HairBoth = 3; // Hair  root & tip

// Elements
static const int ElementEmission     = 0;
static const int ElementDiffuse      = 1;
static const int ElementSpecular     = 2;
static const int ElementGlossy       = 3;
static const int ElementRoughness    = 4;
static const int ElementNormal       = 5;
static const int ElementSSS          = 6;
static const int ElementShadow       = 7;
static const int ElementClearCoat    = 8; // Clear top coat (Specular)
static const int ElementClearCoatIOR = 9;
static const int ElementDiffusion    = 10; // Fake SSS
static const int NumElements         = 11;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AOVs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Channels
static const unsigned int ChannelBeauty    = 1 <<  0;
static const unsigned int ChannelLightPath = 1 <<  1; // Reserved
static const unsigned int ChannelUserData  = 1 <<  2;
static const unsigned int ChannelDR        = 1 <<  3; // Diffuse reflection
static const unsigned int ChannelDRColor   = 1 <<  4; // Diffuse reflection texture
static const unsigned int ChannelDT        = 1 <<  5; // Diffuse transmittance
static const unsigned int ChannelDTColor   = 1 <<  6; // Diffuse transmittance texture
static const unsigned int ChannelGR        = 1 <<  7; // Glossy
static const unsigned int ChannelGRColor   = 1 <<  8;
static const unsigned int ChannelGT        = 1 <<  9;
static const unsigned int ChannelGTColor   = 1 << 10;
static const unsigned int ChannelSR        = 1 << 11; // Specular
static const unsigned int ChannelSRColor   = 1 << 12;
static const unsigned int ChannelST        = 1 << 13;
static const unsigned int ChannelSTColor   = 1 << 14;
static const unsigned int ChannelPM        = 1 << 15; // Participating Media
static const unsigned int ChannelE         = 1 << 16; // Emission
static const unsigned int ChannelNormal    = 1 << 17;
static const unsigned int ChannelTangent   = 1 << 18;
static const unsigned int ChannelPosition  = 1 << 19;
static const unsigned int ChannelDepth     = 1 << 20;

static const unsigned int ChannelDiffuse  = ChannelDR + ChannelDT; // Diffuse
static const unsigned int ChannelGlossy   = ChannelGR + ChannelGT; // Glossy
static const unsigned int ChannelSpecular = ChannelSR + ChannelST; // Specular
static const unsigned int ChannelEmission = ChannelE; // Emission


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Field of View
static const int AngleMeasureHorizontal = 0;
static const int AngleMeasureVertical   = 1;
static const int AngleMeasureDiagonal   = 2;

// Projection for Camera and Light
static const int ProjectionPerspective  = 0;
static const int ProjectionSpherical    = 1;
static const int ProjectionOrthographic = 2;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Texture
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Addressing
static const int AddressingWrap  = 0;
static const int AddressingClamp = 1;

// Sampler
static const int PixelSamplerStochastic = 0; // Stochastic bilinear
static const int PixelSamplerNearest    = 1;
static const int PixelSamplerBilinear   = 2;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddCamera            ( );
API void rqSelectCamera         ( const int camera_id ); // Select camera used for rendering
API void rqSetCameraName        ( const int camera_id, const char* name       );
API void rqSetCameraProjection  ( const int camera_id, const int   projection );
API void rqSetCameraAngleMeasure( const int camera_id, const int   measure    );
API void rqSetCameraFOV         ( const int camera_id, const float degree     );
API void rqSetCameraBokeh       ( const int camera_id, const float degree     );
API void rqSetCameraSample      ( const int camera_id, const int   samples    ); // AA samples (can be an arbitrary number! 1,2,3,4,5,6,7,...)
API void rqSetCameraResolution  ( const int camera_id, const int width, const int height );
API void rqSetCameraRegion      ( const int camera_id, const int left, const int top, const int right, const int bottom );
API void rqSetCameraPosition    ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraTarget      ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraUpVector    ( const int camera_id, const float x, const float y, const float z );
API void rqSetCameraExposure    ( const int camera_id, const float r, const float g, const float b );
API int  rqAddCameraAOV         ( const int camera_id );
API void rqSetCameraAOVName     ( const int camera_id, const int aov_id, const char* name    );
API void rqSetCameraAOVChannel  ( const int camera_id, const int aov_id, const int   channel );
API void rqSetCameraAOVUserData ( const int camera_id, const int aov_id, const char* name    );
API void rqInitializeCameras    ( );
API void rqFinalizeCameras      ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Point Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddPointLight           ( );
API void rqSetPointLightPosition   ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightDirection  ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightTangent    ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightColor      ( const int point_light_id, const float r, const float g, const float b );
API void rqSetPointLightPhoton     ( const int point_light_id, const int   photon ); // # of light paths
API void rqSetPointLightSample     ( const int point_light_id, const int   sample );
API void rqSetPointLightBlur       ( const int point_light_id, const float blur   );
API void rqSetPointLightOffset     ( const int point_light_id, const float offset );
API void rqSetPointLightInnerAngle ( const int point_light_id, const float angle  ); // [degree]
API void rqSetPointLightOuterAngle ( const int point_light_id, const float angle  ); // [degree]
API void rqSetPointLightLink       ( const int point_light_id, const int shader_id ); 
API int  rqAddPointLightAOV        ( const int point_light_id ); // Add AOV channel
API void rqSetPointLightAOVName    ( const int point_light_id, const int aov_id, const char* name    );
API void rqSetPointLightAOVChannel ( const int point_light_id, const int aov_id, const int   channel ); // Select from Channels defined above
API void rqSetPointLightImage      ( const int point_light_id,
	const char*  name,
	const float  gamma            = 1.0f, // Degamma
	const float* color_matrix_4x4 = 0,    // Color correction (Identity matrix if 0)
	const float* uv_matrix_3x3    = 0,    // Tiling           (Identity matrix if 0)
	const int    pixel_sampler    = 0,
	const int    addressing_u     = 0,
	const int    addressing_v     = 0
	); // Light filter


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddParallelLight           ( );
API void rqSetParallelLightDirection  ( const int parallel_light_id, const float x, const float y, const float z );
API void rqSetParallelLightTangent    ( const int parallel_light_id, const float x, const float y, const float z );
API void rqSetParallelLightColor      ( const int parallel_light_id, const float r, const float g, const float b );
API void rqSetParallelLightPhoton     ( const int parallel_light_id, const int   photon ); // # of light paths
API void rqSetParallelLightSample     ( const int parallel_light_id, const int   sample );
API void rqSetParallelLightBlur       ( const int parallel_light_id, const float blur   ); // Angle[degree]
API void rqSetParallelLightOffset     ( const int parallel_light_id, const float offset );
API void rqSetParallelLightLink       ( const int parallel_light_id, const int shader_id ); 
API int  rqAddParallelLightAOV        ( const int parallel_light_id ); // Add AOV channel
API void rqSetParallelLightAOVName    ( const int parallel_light_id, const int aov_id, const char* name    );
API void rqSetParallelLightAOVChannel ( const int parallel_light_id, const int aov_id, const int   channel ); // Select from Channels defined above
API void rqSetParallelLightImage      ( const int parallel_light_id,
	const char*  name,
	const float  gamma            = 1.0f, // Degamma
	const float* color_matrix_4x4 = 0,    // Color correction (Identity matrix if 0)
	const float* uv_matrix_3x3    = 0,    // Tiling           (Identity matrix if 0)
	const int    pixel_sampler    = 0,
	const int    addressing_u     = 0,
	const int    addressing_v     = 0
	); // Light filter


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Non-Area Light - Takes care of all non-area lights (point & parallel lights)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqInitializeGaffer ( );
API void rqFinalizeGaffer   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sky Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetSkyLightBackdrop   ( const char* name   );
API void rqSetSkyLightPhoton     ( const int   photon ); // # of light paths
API void rqSetSkyLightSample     ( const int   sample );
API void rqSetSkyLightColor      ( const float r, const float g, const float b );
API void rqSetSkyLightNorth      ( const float x, const float y, const float z );
API void rqSetSkyLightZenith     ( const float x, const float y, const float z );
API void rqSetSkyLightShader     ( const int shader_id ); // Window
API void rqSetSkyLightLink       ( const int shader_id ); 
API int  rqAddSkyLightAOV        ( );
API void rqSetSkyLightAOVName    ( const int aov_id, const char* name    );
API void rqSetSkyLightAOVChannel ( const int aov_id, const int   channel );
API void rqSetSkyLightImage      (
	const char*  name,
	const float  gamma            = 1.0f, // Degamma
	const float* color_matrix_4x4 = 0,    // Color correction (Identity matrix if 0)
	const float* uv_matrix_3x3    = 0,    // Tiling           (Identity matrix if 0)
	const int    pixel_sampler    = 0,
	const int    addressing_u     = 0,
	const int    addressing_v     = 0
);

API void rqInitializeSkyLight ( );
API void rqFinalizeSkyLight   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetGeometryLightPhoton        ( const int photon    ); // # of light paths
API void rqSetGeometryLightSample        ( const int sample    );
API void rqSetGeometryLightShader        ( const int shader_id ); // Mesh light
API void rqSetGeometryLightLink          ( const int shader_id ); 
API int  rqAddGeometryLightAOV           ( );
API void rqSetGeometryLightAOVName       ( const int aov_id, const char* name    );
API void rqSetGeometryLightAOVChannel    ( const int aov_id, const int   channel );
API void rqSetGeometryLightAOVShaderName ( const int aov_id, const char* shader  );

API void rqInitializeGeometryLight ( );
API void rqFinalizeGeometryLight   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Image
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddImage     ( );
API bool rqSaveImage    ( const int image_id );
API bool rqLoadImage    ( const int image_id );
API void rqSetImageName ( const int image_id, const char* name );
API void rqCreateImage  ( const int image_id, const int width, const int height ); // RGB 32bit float
API void rqSetImageColor( const int image_id, const int u, const int v, const float  r, const float  g, const float  b );
API void rqGetImageColor( const int image_id, const int u, const int v,       float &r,       float &g,       float &b );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader
//
// Surface Properties
// Set non-zero albedo for both sides to compute transmittance.
//
// Color : Color or parameters
// Flake : Volumetric flake shader - This behaves as 2d flake shader when depth=0
// Stone : 3D procedural stone shader - Image is used as an Exemplar
// Shift : Random color shifter using hash function
// Image : Used as a texture map or exemplar 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddShader             ( );
API void rqSetShaderName         ( const int shader_id, const char* name );
API void rqSetShaderTwoSided     ( const int shader_id, const bool two_sided );
API void rqSetShaderPriority     ( const int shader_id, const int  priority ); // Priority in intersection test
API void rqSetShaderGeometryLight( const int shader_id, const int  side, const bool flag );

// Surface Properties
API void rqSetShaderColor( const int shader_id, const int side, const int element, const float r, const float g, const float b );
API void rqSetShaderFlake( const int shader_id, const int side, const int element, const float r, const float g, const float b, const float scale, const float density, const float depth );
API void rqSetShaderStone( const int shader_id, const int side, const int element, const float weathering, const float scale, const float density, const int level );
API void rqSetShaderShift( const int shader_id, const int side, const int element, const int class_type, const float hue, const float saturation, const float value );
API void rqSetShaderImage( const int shader_id, const int side, const int element,
	const char*  name,
	const float  gamma            = 1.0f, // Degamma
	const float* color_matrix_4x4 = 0,    // Color correction (Identity matrix if 0)
	const float* uv_matrix_3x3    = 0,    // Tiling           (Identity matrix if 0)
	const int    pixel_sampler    = 0,
	const int    addressing_u     = 0,
	const int    addressing_v     = 0
	); // Texture

// Volumetric Properties
API void rqSetShaderIOR          ( const int shader_id, const float ior     ); // Index of refraction
API void rqSetShaderDensity      ( const int shader_id, const float density ); // The probability of a ray hitting a particle within a unit distance
API void rqSetShaderAverageCosine( const int shader_id, const float cosine  ); // The "k" parameter of Schlick phase function
API void rqSetShaderParticleColor( const int shader_id, const float r, const float g, const float b );
API void rqSetShaderTransmittance( const int shader_id, const float r, const float g, const float b );

// Geometric Properties
API void rqSetShaderVisibility  ( const int shader_id, const int   visibility   );
API void rqSetShaderSmoothAngle ( const int shader_id, const float smooth_angle );
API void rqSetShaderRoundCorner ( const int shader_id, const float round_corner );

API void rqInitializeShaders ( );
API void rqFinalizeShaders   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry ( Multi-Level Instancing is supported.)
//
// Reserved vertex data
// "position"   : Used as Pref when an object has motion data
// "radius"	    : hair(AtomCylinder)/sphere(AtomParticle)/half width of cube(AtomCube)
// "normal"	    : 
// "tangent"    : 
// "uv"		    : texture coord, you can add multiple times
// "parameter"  : hair root:0 hair tip:1)
//
// Call rqSetObjectDynamic() to render motion blur
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

API int  rqAddObject       ( ); // Returns object_id
API void rqLoadObject      ( const int object_id, const char* name );
API void rqSetObjectName   ( const int object_id, const char* name );
API void rqSetObjectMatrix ( const int object_id, const float* matrix_4x4 = 0 );
API void rqSetObjectDynamic( const int object_id, const int atom );
API void rqSetObjectShader ( const int object_id, const int atom, const int shader_id );
API void rqAddPrimitives   ( const int object_id, const int atom, const int num, const unsigned int* vertex_ids );
API int  rqAddVertexData   ( const int object_id, const int atom, const char* name, const int num, const int dimension, const float* data );
API int  rqAddInstance     ( const int object_id );
API void rqSetInstance     ( const int object_id, const int instance_id, const int   instanced_object_id, const float* matrix_4x4 = 0 );
API void rqOverrideShader  ( const int object_id, const int instance_id, const char* old_name, const char* new_name   );

API void rqInitializeAccelerator( );
API void rqFinalizeAccelerator  ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rendering
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetRendererSample      ( const int   sample     );
API void rqSetRendererBounce      ( const int   bounce     );
API void rqSetRendererRadius      ( const float radius     );
API void rqSetRendererResolution  ( const float resolution );
API void rqSetRendererRayDepth    ( const int   depth      );
API void rqSetRendererPhotonDepth ( const int   depth      );
API void rqSetRendererClamp       ( const float r, const float g, const float b );
API void rqSetRendererError       ( const float r, const float g, const float b ); // The Color used for Nan etc.
API void rqInitializeRenderer     ( );
API void rqFinalizeRenderer       ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetDisplayGamma ( const float gamma );

API void rqCreatePreviewWindow ( );
API void rqUpdatePreviewWindow ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqStartup     ( );
API void rqShutdown    ( );
API void rqInitialize  ( ); // Initialize everything in an appropriate Order
API void rqFinalize    ( ); // Finalize   everything in an appropriate Order
API void rqUpdate      ( ); // Call this after modifying geo (cameras, lights & objects)
API void rqRender      ( ); // For static scene
API void rqRenderPixels( ); // For dynamic scene
API void rqRenderPixels( const int num_of_pixels, float* rgb_s, const int subpixel_id );
API void rqGo          ( const char* folder_name ); // This function does everything for you
API void rqLoadScene   ( const char* folder_name ); // Load scene files from folder
API void rqLoadFile    ( const char*   file_name ); // Load scene from file
API void rqSaveBeauty  ( const char*   file_name ); // Save beauty