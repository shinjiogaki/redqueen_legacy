

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Redqueen Copyright (c) shinji All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#define API __declspec(dllexport) 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Units
// Time     : 0 to 1
// Angle    : degree
// Position : meter
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Primitives
static const int AtomNull     = 0;
static const int AtomParticle = 1;
static const int AtomCylinder = 2;
static const int AtomTriangle = 3;
static const int AtomTetragon = 4;
static const int AtomInstance = 5;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Visibility
static const int InvisibleFromLight  = 1;
static const int InvisibleFromCamera = 2;
static const int Invisible           = 3;

// Sideness
static const int SideOuter = 0;
static const int SideInner = 1;
static const int SideBoth  = 2;


// Elements
static const int ElementAlbedo    = 0;
static const int ElementEmission  = 1;
static const int ElementIOR       = 2;
static const int ElementRoughness = 3;
static const int ElementNormal    = 4;
static const int ElementJitter    = 5;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AOVs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Channels
static const unsigned int ChannelBeauty    = 1 <<  0;
static const unsigned int ChannelLightPath = 1 <<  1; // Reserved
static const unsigned int ChannelUserData  = 1 <<  2;
static const unsigned int ChannelDR        = 1 <<  3; // Diffuse Reflection
static const unsigned int ChannelDRColor   = 1 <<  4; // Diffuse Reflection Texture
static const unsigned int ChannelDT        = 1 <<  5; // Diffuse Transmittance
static const unsigned int ChannelDTColor   = 1 <<  6; // Diffuse Transmittance Texture
static const unsigned int ChannelGR        = 1 <<  7; // Glossy
static const unsigned int ChannelGRColor   = 1 <<  8;
static const unsigned int ChannelGT        = 1 <<  9;
static const unsigned int ChannelGTColor   = 1 << 10;
static const unsigned int ChannelSR        = 1 << 11; // Specular
static const unsigned int ChannelSRColor   = 1 << 12;
static const unsigned int ChannelST        = 1 << 13;
static const unsigned int ChannelSTColor   = 1 << 14;
static const unsigned int ChannelE         = 1 << 15; // Emission
static const unsigned int ChannelNormal    = 1 << 16;
static const unsigned int ChannelTangent   = 1 << 17;
static const unsigned int ChannelPosition  = 1 << 18;
static const unsigned int ChannelDepth     = 1 << 19;

static const unsigned int ChannelDiffuse  = ChannelDR + ChannelDT; // Diffuse
static const unsigned int ChannelGlossy   = ChannelGR + ChannelGT; // Glossy
static const unsigned int ChannelSpecular = ChannelSR + ChannelST; // Specular


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
// Textures
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Addressing
static const int AddressingWrap  = 0;
static const int AddressingClamp = 1;

// Sampler
static const int PixelSamplerNearest    = 0;
static const int PixelSamplerStochastic = 1; // Stochastic Bilinear
static const int PixelSamplerBilinear   = 2;

// Filter
static const int FilterNone     = 0;
static const int FilterGradient = 1;
static const int FilterNormal   = 2;
static const int FilterGaussian = 3;
static const int FilterVariance = 4;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddCamera            ( );
API void rqSetCameraName        ( const int camera_id, const char* name       );
API void rqSetCameraTime        ( const int camera_id, const float time       ); // should be either 0.0f or 1.0f for now
API void rqSetCameraProjection  ( const int camera_id, const int   projection );
API void rqSetCameraAngleMeasure( const int camera_id, const int   measure    );
API void rqSetCameraFOV         ( const int camera_id, const float degree     );
API void rqSetCameraBokeh       ( const int camera_id, const float degree     );
API void rqSetCameraSample      ( const int camera_id, const int   samples    ); // AA Samples (can be an arbitrary number! 1,2,3,4,5,6,7,...)
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
//API void rqSetPointLightTime       ( const int point_light_id, const float time ); 
API void rqSetPointLightPosition   ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightDirection  ( const int point_light_id, const float x, const float y, const float z );
API void rqSetPointLightColor      ( const int point_light_id, const float r, const float g, const float b );
API void rqSetPointLightPhoton     ( const int point_light_id, const int   photon ); // # of Light Paths
API void rqSetPointLightSample     ( const int point_light_id, const int   sample );
API void rqSetPointLightBlur       ( const int point_light_id, const float blur   );
API void rqSetPointLightOffset     ( const int point_light_id, const float offset );
API void rqSetPointLightInnerAngle ( const int point_light_id, const float angle  ); // [degree]
API void rqSetPointLightOuterAngle ( const int point_light_id, const float angle  ); // [degree]
API void rqSetPointLightLink       ( const int point_light_id, const int shader_id ); // Light Linking
API int  rqAddPointLightAOV        ( const int point_light_id ); // Add AOV Channel
API void rqSetPointLightAOVName    ( const int point_light_id, const int aov_id, const char* name    );
API void rqSetPointLightAOVChannel ( const int point_light_id, const int aov_id, const int   channel ); // Select from Channels defined above


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddParallelLight           ( );
//API void rqSetParallelLightTime       ( const int parallel_light_id, const float time   ); 
API void rqSetParallelLightDirection  ( const int parallel_light_id, const float x, const float y, const float z );
API void rqSetParallelLightColor      ( const int parallel_light_id, const float r, const float g, const float b );
API void rqSetParallelLightPhoton     ( const int parallel_light_id, const int   photon ); // # of Light Paths
API void rqSetParallelLightSample     ( const int parallel_light_id, const int   sample );
API void rqSetParallelLightBlur       ( const int parallel_light_id, const float blur   ); // Angle[degree]
API void rqSetParallelLightOffset     ( const int parallel_light_id, const float offset );
API void rqSetParallelLightLink       ( const int parallel_light_id, const int shader_id ); // Light Linking
API int  rqAddParallelLightAOV        ( const int parallel_light_id ); // Add AOV channel
API void rqSetParallelLightAOVName    ( const int parallel_light_id, const int aov_id, const char* name    );
API void rqSetParallelLightAOVChannel ( const int parallel_light_id, const int aov_id, const int   channel ); // Select from Channels defined above

API void rqInitializeGaffer ( ); // Takes care of all non-area lights
API void rqFinalizeGaffer   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sky Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetSkyLightImage      ( const char* name   );
//API void rqSetSkyLightTime       ( const float time   );
API void rqSetSkyLightBackdrop   ( const char* name   );
API void rqSetSkyLightPhoton     ( const int   photon ); // # of Light Paths
API void rqSetSkyLightSample     ( const int   sample );
API void rqSetSkyLightColor      ( const float r, const float g, const float b );
API void rqSetSkyLightNorth      ( const float x, const float y, const float z );
API void rqSetSkyLightZenith     ( const float x, const float y, const float z );
API void rqSetSkyLightShader     ( const int shader_id ); // Window
API void rqSetSkyLightLink       ( const int shader_id ); // Light Link
API int  rqAddSkyLightAOV        ( );
API void rqSetSkyLightAOVName    ( const int aov_id, const char* name    );
API void rqSetSkyLightAOVChannel ( const int aov_id, const int   channel );

API void rqInitializeSkyLight ( );
API void rqFinalizeSkyLight   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry Light
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//API void rqSetGeometryLightTime       ( const float time   );
API void rqSetGeometryLightPhoton        ( const int photon    ); // # of Light Paths
API void rqSetGeometryLightSample        ( const int sample    );
API void rqSetGeometryLightShader        ( const int shader_id ); // Mesh Light
API void rqSetGeometryLightLink          ( const int shader_id ); // Light Link
API int  rqAddGeometryLightAOV           ( );
API void rqSetGeometryLightAOVName       ( const int aov_id, const char* name    );
API void rqSetGeometryLightAOVChannel    ( const int aov_id, const int   channel );
API void rqSetGeometryLightAOVShaderName ( const int aov_id, const char* shader  );

API void rqInitializeGeometryLight ( );
API void rqFinalizeGeometryLight   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader
//
// Surface Shader
// The order of adding layers matters! You have to add layers from top to bottom.
// In order to pass energy to the next layer, you have to add non-zero Transmittance value.
// 0 = Roughness     : Specular
// 0 < Roughness < 1 : Glossy
//     Roughness = 1 : Diffuse
//
// Volumetric Flake Shader
// This behaves as 2d flake shader when depth=0
//
// two_sided option allows rays to traverse from bottom to top when they hit back side.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API int  rqAddShader     ( );
API void rqSetShaderName ( const int shader_id, const char* name );
//API void rqSetShaderTime ( const int shader_id, const float time );

// Geometry Shader
API void rqSetShaderTwoSided    ( const int shader_id, const bool  two_sided    );
API void rqSetShaderVisibility  ( const int shader_id, const int   visibility   );
API void rqSetShaderSmoothAngle ( const int shader_id, const float smooth_angle );
API void rqSetShaderRoundCorner ( const int shader_id, const float round_corner );

// Surface Shader (The order matters! You have to add layers from top to bottom )
API int  rqAddLayer      ( const int shader_id );
API void rqSetLayerColor ( const int shader_id, const int layer_id, const int side, const int element, const float r, const float g, const float b ); // Set Color or Values
API void rqSetLayerFlake ( const int shader_id, const int layer_id, const int side, const int element, const float r, const float g, const float b , const float scale, const float density, const float depth);
API void rqSetLayerImage ( const int shader_id, const int layer_id, const int side, const int element, const char* name, const float gamma, const float* color_matrix_4x4, const float* uv_matrix_3x3 );

// Volume Shader
//API void rqSetTransmittance();

API void rqInitializeShaders ( );
API void rqFinalizeShaders   ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Geometry
// Multi-Level Instancing is supported.
//
// Vertex Data
// "position" : reserved (Used as Pref when an object has motion data)
// "motion"   : reserved (Offset from position)
// "radius"	  : reserved (hair/particle)
// "normal"	  : reserved
// "tangent"  : reserved
// "uv"		  : reserved (texture coord, you can add multiple times)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

API int  rqAddObject      ( ); // Returns object_id
API void rqSetObjectName  ( const int object_id, const char* name );
//API void rqSetObjectTime  ( const int object_id, const float time );
API void rqSetObjectMatrix( const int object_id, const float* matrix_4x4 = 0 );
API void rqSetObjectShader( const int object_id, const int atom, const int shader_id );
API void rqAddPrimitives  ( const int object_id, const int atom, const int num, const unsigned int* vertex_ids );
API int  rqAddVertexData  ( const int object_id, const int atom, const char* name, const int num, const int dimension, const float* data );
API int  rqSetVertexData  ( const int object_id, const int atom, const char* name, const int num, const int dimension, const float* data );
API int  rqAddInstance    ( const int object_id );
API void rqSetInstance    ( const int object_id, const int instance_id, const int   instanced_object_id, const float* matrix_4x4 = 0 );
API void rqOverrideShader ( const int object_id, const int instance_id, const char* old_name, const char* new_name   );

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
API void rqRender                 ( );
API void rqRenderPixels           ( const int num_of_pixels, float* rgb_s, const int subpixel_id );
API void rqInitializeRenderer     ( );
API void rqFinalizeRenderer       ( );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqSetDisplayGamma  ( const float gamma   );
API void rqSetPreviewWindow ( const bool  preview );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
API void rqStartup    ( );
API void rqSetTime    ( const float time );
API void rqInitialize ( ); // Initialize everything in an appropriate Order
API void rqFinalize   ( ); // Finalize   everything in an appropriate Order
API void rqShutdown   ( );
API void rqGo         ( const char* folder_name ); // This function does everything for you
API void rqLoadScene  ( const char* folder_name ); // Load geo from files
API void rqLoadFile   ( const char* file_name ); // Load geo from file
API void rqSaveBeauty ( const char* file_name ); // Save Beauty