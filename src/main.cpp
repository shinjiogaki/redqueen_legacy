


// Uncomment your favorite one

//#define TUTORIAL01 // Sphere with Parallel Light
//#define TUTORIAL02 // Sphere with Sky      Light
//#define TUTORIAL03 // Sphere with Geometry Light
#define TUTORIAL04 // Sphere with Flake & Stone Shader
//#define TUTORIAL05 // Particles with Motion Blur
//#define TUTORIAL06 // Loading .obj File & Texture Mapping
//#define TUTORIAL07 // Hair Shading
//#define TUTORIAL08 // Instancing & Final Gathering
//#define TUTORIAL09 // redqueen.exe
//#define TUTORIAL10 // Turn Table Animation


// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Sphere with Parallel Light
#ifdef TUTORIAL01
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );

	// Object
	auto object_id = rqAddObject( );
	float        position[ ] = { 0, 0,  0 };
	float        radius  [ ] = { 1.0 };
	unsigned int id      [ ] = { 0   };
	rqAddVertexData  ( object_id, AtomParticle, "position", 1, 3, position );
	rqAddVertexData  ( object_id, AtomParticle, "radius"  , 1, 1, radius   );
	rqAddPrimitives  ( object_id, AtomParticle, 1, id );
	
	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,1);
	rqSetParallelLightDirection( light_id, 1,-1,1);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 256 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	rqShutdown ( );

	return 0;

}
#endif


// Sphere with Sky Light
#ifdef TUTORIAL02
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id,  ShutterOpen );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );

	// Object
	auto object_id = rqAddObject( );
	float        position[ ] = { 0, 0,  0 };
	float        radius  [ ] = { 1.0 };
	unsigned int id      [ ] = { 0   };
	rqAddVertexData  ( object_id, AtomParticle, "position", 1, 3, position );
	rqAddVertexData  ( object_id, AtomParticle, "radius"  , 1, 1, radius   );
	rqAddPrimitives  ( object_id, AtomParticle, 1, id );
	
	// Sky Light
	// Visit sIBL (http://www.hdrlabs.com/sibl/archive.html)
	//rqSetSkyLightColor(1,1,1);
	//rqSetSkyLightImage("Barce_Rooftop_C_3k.hdr");
	rqSetSkyLightColor(1000,1000,1000);
	rqSetSkyLightImage("sky.png");
	rqSetSkyLightSample(512);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample (512);

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	rqShutdown ( );

	return 0;

}
#endif


// Sphere with Geometry Light
#ifdef TUTORIAL03
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, 4 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, 4 );

	// Shader
	auto shader_id = rqAddShader();
	auto layer0_id = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementEmission , 100,100,100 );
	rqSetShaderGeometryLight( shader_id, SideOuter, true );

	// Sphere
	{
		auto object_id = rqAddObject( );
		float        position[ ] = { 0, 0,  0 };
		float        radius  [ ] = { 1.0 };
		unsigned int id      [ ] = { 0   };
		rqAddVertexData  ( object_id, AtomParticle, "position", 1, 3, position );
		rqAddVertexData  ( object_id, AtomParticle, "radius"  , 1, 1, radius   );
		rqAddPrimitives  ( object_id, AtomParticle, 1, id );
	}

	// Geometry Light
	{
		auto object_id = rqAddObject( );
		float        position[ ] = { 10, 10,  10 };
		float        radius  [ ] = { 1.0 };
		unsigned int id      [ ] = { 0   };
		rqAddVertexData  ( object_id, AtomParticle, "position", 1, 3, position );
		rqAddVertexData  ( object_id, AtomParticle, "radius"  , 1, 1, radius   );
		rqAddPrimitives  ( object_id, AtomParticle, 1, id );
		rqSetObjectShader( object_id, AtomParticle, shader_id );
	}
	
	// Sky Light
	rqSetSkyLightColor(0,0,0);

	// Geometry Light
	rqSetGeometryLightSample(256);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample (256);

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	rqShutdown ( );

	return 0;
}
#endif


// Sphere with Flake & Stone Shader
#ifdef TUTORIAL04
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen ); 
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );


	// Shader
	auto shader_id = rqAddShader();

	auto layer_id = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer_id, SideOuter, ElementAlbedo   , 1.0f, 1.0f, 1.0f );
	rqSetLayerColor ( shader_id, layer_id, SideBoth , ElementNormal   , 1.0f, 1.0f, 1.0f );

	// Flake
	rqSetLayerFlake ( shader_id, layer_id, SideBoth , ElementAlbedo   , 0.7f, 0.6f, 0.3f, 0.01, 0.01, 0 );

	// Stone
	rqSetLayerImage ( shader_id, layer_id, SideBoth , ElementAlbedo   , "stone.png");
	rqSetLayerStone ( shader_id, layer_id, SideBoth , ElementAlbedo   , 0.7, 1.0, 0.2, 10 );

	rqSetLayerColor ( shader_id, layer_id, SideBoth , ElementRoughness, 1,1,1 );
	rqSetLayerColor ( shader_id, layer_id, SideInner, ElementIOR      , 500, 500, 500 );

	// Object
	auto object_id = rqAddObject( );
	rqSetObjectShader( object_id, AtomParticle, shader_id );
	float        positions[ ] = { 0, 0,  0 };
	float        radii    [ ] = { 1.0 };
	unsigned int ids      [ ] = { 0   };
	rqAddVertexData  ( object_id, AtomParticle, "position", 1, 3, positions );
	rqAddVertexData  ( object_id, AtomParticle, "radius"  , 1, 1, radii     );
	rqAddPrimitives  ( object_id, AtomParticle, 1, ids );
	
	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,1);
	rqSetParallelLightDirection( light_id, 1,-1,1);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 256 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;

}
#endif


// Particles with Motion Blur
#ifdef TUTORIAL05
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 43 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen );
	rqSetCameraFOV       ( camera_id, 40.0f );
	rqSetCameraPosition  ( camera_id, 8, 8, -8 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 40.0f );
	rqSetCameraPosition  ( camera_id, 8, 8, -8 );

	// Object
	auto object_id = rqAddObject( );
	rqSetObjectName( object_id, "particles" );
	const auto N = 10000;

	float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *motions0  = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *motions1  = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
	unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));

	for(auto i = 0; i < N; ++i)
	{
		positions[i*3+0] =   5*rand()/(float)RAND_MAX-2.5f;
		positions[i*3+1] =   5*rand()/(float)RAND_MAX-2.5f;
		positions[i*3+2] =   5*rand()/(float)RAND_MAX-2.5f;
		motions0 [i*3+0] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions0 [i*3+1] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions0 [i*3+2] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+0] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+1] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+2] = 0.5*rand()/(float)RAND_MAX-0.25f;

		radii[i] = 0.05f;
		ids  [i] = i;
	}

	rqAddVertexData ( object_id, AtomParticle, "position", N, 3, positions );
	rqAddVertexData ( object_id, AtomParticle, "motion"  , N, 3, motions0  );
	rqAddVertexData ( object_id, AtomParticle, "motion"  , N, 3, motions1  );
	rqAddVertexData ( object_id, AtomParticle, "radius"  , N, 1, radii     );
	rqAddPrimitives ( object_id, AtomParticle, N, ids );
	
	std::free(positions);
	std::free(motions0 );
	std::free(motions1 );
	std::free(radii    );
	std::free(ids      );

	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,1);
	rqSetParallelLightDirection( light_id, 1,-1,1);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 1024 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;

}
#endif


// Loading .obj File & Texture Mapping
#ifdef TUTORIAL06
int main( )
{
	
	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen );
	rqSetCameraFOV       ( camera_id, 30.0f );
	rqSetCameraPosition  ( camera_id, 4, 4, 4 );
	rqSetCameraTarget    ( camera_id, -0.66,0.91,-0.31 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 30.0f );
	rqSetCameraPosition  ( camera_id, 4, 4, 4 );
	rqSetCameraTarget    ( camera_id, -0.66,0.91,-0.31 );

	// Texture
	const auto w = 256;
	const auto h = 256;
	const auto tile = 16;
	const auto image_id = rqAddImage();
	rqSetImageName( image_id, "checker.png" );
	rqCreateImage( image_id, w, h );
	for( auto v = 0; v < h; ++v )
	{
		for( auto u = 0; u < w; ++u )
		{
			if( ((u/tile)%2)^((v/tile)%2) )
				rqSetImageColor(image_id, u,v,0,0,0);
			else
				rqSetImageColor(image_id, u,v,1,1,1);
		}
	}

	// Shader
	auto shader_id = rqAddShader();
	rqSetShaderName     ( shader_id, "teapot" );
	rqSetShaderTwoSided ( shader_id, false    );

	// Layer
	auto layer0_id = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementAlbedo   , 0.9,0.9,0.9 );
	rqSetLayerImage ( shader_id, layer0_id, SideOuter, ElementAlbedo   , "checker.png" );
	rqSetLayerColor ( shader_id, layer0_id, SideBoth , ElementRoughness, 1, 1, 1   );
	rqSetLayerColor ( shader_id, layer0_id, SideInner, ElementIOR      , 8, 8, 8   );

	// Object
	auto object_id = rqAddObject( );
	rqLoadObject( object_id, "teapot.obj" );
	
	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,0.5);
	rqSetParallelLightDirection( light_id, 1,-1,1);

	// Sky Light
	rqSetSkyLightColor ( 0.5,0.5,1.0);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 256 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;
}
#endif


// Hair Shading
#ifdef TUTORIAL07
int main( )
{
	
	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample      ( camera_id, 31 ); // AA samples can be an arbitrary number
	rqSetCameraResolution  ( camera_id, 512, 512 );
	rqSetCameraProjection  ( camera_id, ProjectionPerspective );
	rqSetCameraAngleMeasure( camera_id, AngleMeasureVertical  );
	rqSetCameraTime     ( camera_id, ShutterOpen );
	rqSetCameraFOV      ( camera_id, 30.0f );
	rqSetCameraBokeh    ( camera_id,  0.0f );
	rqSetCameraPosition ( camera_id, 2, 1, -2 );
	rqSetCameraTarget   ( camera_id, 0, 0,  0 );
	rqSetCameraUpVector ( camera_id, 0, 1,  0 );
	rqSetCameraTime     ( camera_id,  ShutterClose );
	rqSetCameraFOV      ( camera_id, 30.0f );
	rqSetCameraBokeh    ( camera_id,  0.0f );
	rqSetCameraPosition ( camera_id, 2, 1, -2);
	rqSetCameraTarget   ( camera_id, 0, 0,  0 );
	rqSetCameraUpVector ( camera_id, 0, 1,  0 );

	// AOV
	auto aov_id = rqAddCameraAOV( camera_id );
	rqSetCameraAOVName     ( camera_id, aov_id, "parameter.png" );
	rqSetCameraAOVUserData ( camera_id, aov_id, "parameter" );
	
	// Shader
	auto shader_id = rqAddShader();
	auto layer_id  = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer_id, SideOuter, ElementAlbedo   , 1.0f, 1.0f, 1.0f ); // Reflection
	rqSetLayerColor ( shader_id, layer_id, SideInner, ElementAlbedo   , 0.9f, 0.8f, 0.7f ); // Transmittance
	rqSetLayerColor ( shader_id, layer_id, SideBoth , ElementRoughness, 0.2f, 0.4f, 0.6f ); // for R, TT, TRT
	rqSetLayerColor ( shader_id, layer_id, SideBoth , ElementIOR      , 1.5f, 1.5f, 1.5f ); // IOR

	// Object
	const auto S = 8;  // Num Segments
	const auto W = 64;
	const auto H = 64;
	const auto N = W*H; // Num Strands


	float        *positions = (float       *)std::malloc( N *  S    * 3 * sizeof(float)       );
	float        *radii     = (float       *)std::malloc( N *  S    * 1 * sizeof(float)       );
	unsigned int *ids       = (unsigned int*)std::malloc( N * (S-1) * 1 * sizeof(unsigned int));

	auto object_id = rqAddObject( );
	rqSetObjectShader( object_id, AtomCylinder, shader_id );

	auto n  = 0;
	auto id = 0;
	for(auto v = 0; v < H; ++v )
	{
		for(auto u = 0; u < W; ++u )
		{
			for(auto s = 0; s < S; ++s)
			{
				positions[ (S*n + s)*3+0 ] = (u+rand()/(float)RAND_MAX)/W - 0.5;
				positions[ (S*n + s)*3+1 ] = ((s+0.5)/S - 0.5) * 1.2;
				positions[ (S*n + s)*3+2 ] = (v+rand()/(float)RAND_MAX)/H - 0.5;
				radii    [  S*n + s      ] = 0.004 * (s+0.5)/S;
			}
			for(auto s = 0; s < S-1; ++s)
			{
				ids[ id ] = S*n + s;
				++id;
			}
			++n;
		}
	}

	rqAddVertexData ( object_id, AtomCylinder, "position", N*S, 3, positions );
	rqAddVertexData ( object_id, AtomCylinder, "radius"  , N*S, 1, radii     );
	rqAddPrimitives ( object_id, AtomCylinder, N*(S-1), ids);
	
	std::free(positions);
	std::free(radii    );
	std::free(ids      );


	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,1);
	rqSetParallelLightDirection( light_id, 1,0,1);

	// Sky Light
	rqSetSkyLightColor (0.2,0.2,0.2);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 256 );
	rqSetRendererBounce ( 4   );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;
}
#endif


// Instancing and Final Gathering
#ifdef TUTORIAL08
int main( )
{

	////////////////////////
	// Startup
	////////////////////////
	rqStartup( );


	////////////////////////
	// Camera
	////////////////////////
	auto camera_id = rqAddCamera( );
	{
		rqSetCameraSample      ( camera_id, 23 ); // AA samples can be an arbitrary number
		//rqSetCameraRegion      ( camera_id, 16, 16, 496, 496 ); // Render Region
		rqSetCameraResolution  ( camera_id, 512, 512 );
		rqSetCameraProjection  ( camera_id, ProjectionPerspective );
		rqSetCameraAngleMeasure( camera_id, AngleMeasureVertical  );

		rqSetCameraTime     ( camera_id, ShutterOpen );
		rqSetCameraFOV      ( camera_id, 35.0f );
		rqSetCameraBokeh    ( camera_id,  0.4f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		rqSetCameraTime     ( camera_id, ShutterClose );
		rqSetCameraFOV      ( camera_id, 35.0f );
		rqSetCameraBokeh    ( camera_id,  0.4f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		// AOVs
		auto aov_id0 = rqAddCameraAOV( camera_id ); rqSetCameraAOVName ( camera_id, aov_id0,     "normal.png" );
		auto aov_id1 = rqAddCameraAOV( camera_id );	rqSetCameraAOVName ( camera_id, aov_id1, "lambertian.png" );
		auto aov_id2 = rqAddCameraAOV( camera_id );	rqSetCameraAOVName ( camera_id, aov_id2,    "my_data.png" );
		auto aov_id3 = rqAddCameraAOV( camera_id );	rqSetCameraAOVName ( camera_id, aov_id3,    "tangent.png" );

		rqSetCameraAOVChannel  ( camera_id, aov_id0, ChannelNormal   );
		rqSetCameraAOVChannel  ( camera_id, aov_id1, ChannelDR       );
		rqSetCameraAOVChannel  ( camera_id, aov_id2, ChannelUserData );
		rqSetCameraAOVChannel  ( camera_id, aov_id3, ChannelTangent  );
		rqSetCameraAOVUserData ( camera_id, aov_id2, "my_data"       );
	}


	////////////////////////
	// Shader
	////////////////////////
	auto shader_id0 = rqAddShader( ); rqSetShaderName ( shader_id0, "wall" );
	auto shader_id1 = rqAddShader( ); rqSetShaderName ( shader_id1, "ball" );
	
	// Matrix for Color and UV
	float color_matrix[4][4] = { 1,0,0,0,   0,1,0,0,   0,0,1,0,   0,0,0,1 };	
	float    uv_matrix[3][3] = { 2,0,0,  0,2,0,   0,0,1 };
	
	// Shader 0 
	{
		auto layer_id0 = rqAddLayer( shader_id0 );
		rqSetLayerColor ( shader_id0, layer_id0, SideOuter, ElementAlbedo   , 0.7f, 0.7f, 0.7f );
		rqSetLayerColor ( shader_id0, layer_id0, SideInner, ElementAlbedo   , 0.2f, 0.2f, 0.2f );
		rqSetLayerColor ( shader_id0, layer_id0, SideBoth , ElementRoughness, 1.0f, 1.0f, 1.0f );
		rqSetLayerColor ( shader_id0, layer_id0, SideInner, ElementIOR      , 100, 100, 100 );
		rqSetShaderTwoSided( shader_id0, true );
	}

	// Shader 1
	{
		auto layer_id = rqAddLayer( shader_id1 );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementAlbedo   , 1,1,1 );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementRoughness, 0,0,0 );
		rqSetLayerColor ( shader_id1, layer_id, SideInner, ElementIOR      , 1.33,1.33,1.33 );
	}


	// Smoothing ( to create vertex normals and tangents )
	{
		rqSetShaderSmoothAngle( shader_id0, -1 );
		rqSetShaderSmoothAngle( shader_id1, -1 );
	}


	////////////////////////
	// Geometry
	////////////////////////
	auto instanced_object_id = rqAddObject( );
	{
		rqSetObjectName( instanced_object_id, "particles" );
		{
			float        positions[ ] = { 0, 0,  0 };
			float        radii    [ ] = { 0.2 };
			unsigned int ids      [ ] = { 0   };
			rqSetObjectShader( instanced_object_id, AtomParticle, shader_id1  );
			rqAddVertexData  ( instanced_object_id, AtomParticle, "position", 1, 3, positions );
			rqAddVertexData  ( instanced_object_id, AtomParticle, "radius"  , 1, 1, radii     );
			rqAddPrimitives  ( instanced_object_id, AtomParticle, 1, ids );
		}
	}
	
	// Add Object
	auto object_id = rqAddObject( );
	{
		rqSetObjectName( object_id, "scene" );

		// Instance
		{
			float matrix0[16] = { 0.8660254,-0.5,0,-0.6,  0.5,0.8660254,0,0.3,  0,0,1,0,   0,0,0,1 };
			float matrix1[16] = { 1,0,0, 0.0,  0,1,0,0.3,  0,0,1,0,   0,0,0,1 };
			float matrix2[16] = { 1,0,0,+0.6,  0,1,0,0.3,  0,0,1,0,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( object_id );
			auto instance_id1 = rqAddInstance( object_id );
			auto instance_id2 = rqAddInstance( object_id );
			rqSetInstance( object_id, instance_id0, instanced_object_id, matrix0 );
			rqSetInstance( object_id, instance_id1, instanced_object_id, matrix1 );
			rqSetInstance( object_id, instance_id2, instanced_object_id, matrix2 );
		}
		
		// Mesh
		{
	
			// xyzxyz...
			float positions[ ] =
			{
				-1, 0,  1, -1, 0, -1,  1, 0, -1,  1, 0, 1,
				-1, 2,  1, -1, 2, -1,  1, 2, -1,  1, 2, 1,
				-1, 2,  1, -1, 0,  1,  1, 0,  1,  1, 2, 1,
				-1, 2, 1,  -1, 0,  1, -1, 0, -1, -1, 2, -1, 
				 1, 2, -1,  1, 0, -1,  1, 0,  1,  1, 2, 1
			};

			// uvuvuvuv...
			float uvs[ ] =
			{
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1
			};

			// rgbrgb...
			float my_data[ ] =
			{
				1,0,0, 1,0,0, 1,0,0, 1,0,0,
				0,1,0, 0,1,0, 0,1,0, 0,1,0,
				0,0,1, 0,0,1, 0,0,1, 0,0,1,
				0,1,1, 0,1,1, 0,1,1, 0,1,1,
				1,0,1, 1,0,1, 1,0,1, 1,0,1
			};

			unsigned int vertex_ids[ ] = { 0,1,2,3 , 4, 5, 6, 7,   8, 9, 10, 11,   12, 13, 14, 15,   16, 17, 18, 19  };

			rqAddVertexData  ( object_id, AtomTetragon, "position", 20, 3, positions );
			rqAddVertexData  ( object_id, AtomTetragon, "uv"      , 20, 2, uvs       );
			rqAddVertexData  ( object_id, AtomTetragon, "my_data" , 20, 3, my_data   );
			rqSetObjectShader( object_id, AtomTetragon, shader_id0 );
			rqAddPrimitives  ( object_id, AtomTetragon, 5, vertex_ids );
		}
		
	}


	////////////////////////
	// Light
	////////////////////////			
	{
		auto point_light_id = rqAddPointLight( );
		rqSetPointLightPosition  ( point_light_id, 0.0,  1.5, 0.0 );
		rqSetPointLightColor     ( point_light_id, 1.0, 0.5, 0.5 );
		rqSetPointLightDirection ( point_light_id, 0.5, -1.0, 0.0 );
		rqSetPointLightOuterAngle( point_light_id, 180 );
		rqSetPointLightInnerAngle( point_light_id, 25 );
		rqSetPointLightBlur      ( point_light_id, 0 );
		rqSetPointLightSample    ( point_light_id, 256 );
		rqSetPointLightPhoton    ( point_light_id, 1000000 );
	}
	
	{
		auto point_light_id = rqAddPointLight( );
		rqSetPointLightPosition  ( point_light_id,  0.0,  1.5, 0.0 );
		rqSetPointLightColor     ( point_light_id,  0.5,  1.0, 0.50 );
		rqSetPointLightDirection ( point_light_id, -0.5, -1.0, 0.0 );
		rqSetPointLightOuterAngle( point_light_id,  180 );
		rqSetPointLightInnerAngle( point_light_id,  25 );
		rqSetPointLightBlur      ( point_light_id,  0 );
		rqSetPointLightSample    ( point_light_id,  256 );
		rqSetPointLightPhoton    ( point_light_id, 1000000 );
	}


	
	////////////////////////
	// Skylight
	////////////////////////
	{
		rqSetSkyLightColor  ( 0, 0, 0 );
		rqSetSkyLightZenith ( 0, 1,  0 );
		rqSetSkyLightNorth  ( 0, 0, -1 );
		rqSetSkyLightSample ( 0 );
		rqSetSkyLightPhoton ( 1000000 );
		
		// Light AOVs
		auto aov_id = rqAddSkyLightAOV ( );
		rqSetSkyLightAOVName    ( aov_id, "sky_lambertian.png");
		rqSetSkyLightAOVChannel ( aov_id, ChannelDR );
	}


	////////////////////////
	// Display
	////////////////////////
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );


	////////////////////////
	// Rendering
	////////////////////////
	rqSetRendererClamp     ( 1000, 1000, 1000);
	rqSetRendererSample    ( 256 );
	rqSetRendererBounce    ( 1 );
	rqSetRendererResolution( 0.05 );
	rqSetRendererRadius    ( 0.05 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	// Shutdown redqueen
	rqShutdown( );

	return 0;

}
#endif



#ifdef TUTORIAL09 // redqueen.exe
int main( int argc, char *argv[ ] )
{
	if( 2 <= argc )
	{
		for( auto i = 2; i < argc; ++i )
		{
			if( 0 == strcmp( argv[ i ], "-preview" ) ) { rqSetPreviewWindow( true ); }
		}
		rqGo( argv[ 1 ] );
	}
	return 0;
}
#endif


#ifdef TUTORIAL10 // Turn Table
int main( int argc, char *argv[ ] )
{

for(auto i = 0; i < 300; ++i )
{
	rqStartup    ( );
	rqLoadScene( argv[ 1 ] );
	auto cos_ = cosf((i/300.0f)*3.14159265*2);
	auto sin_ = sinf((i/300.0f)*3.14159265*2);
	auto cos__ = cosf((i/300.0f)*3.14159265*4);
	auto sin__ = sinf((i/300.0f)*3.14159265*4);

	rqSetParallelLightDirection(0, cos__, -1, sin__ );

	rqSetCameraTime(0,0);
	rqSetCameraPosition(0, 12*cos_,4 ,12*sin_ );
	rqSetCameraTime(0,1);
	rqSetCameraPosition(0, 12*cos_,4 ,12*sin_);
	rqInitialize ( ); // Initialize everything in an appropriate Order
	rqRender();
	rqFinalize   ( ); // Finalize   everything in an appropriate Order
	rqShutdown   ( );
}
	return 0;
}
#endif
