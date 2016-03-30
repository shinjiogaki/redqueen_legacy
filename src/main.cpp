


// Uncomment your favorite One


//#define TUTORIAL01
//#define TUTORIAL02
//#define TUTORIAL03
#define TUTORIAL04
//#define TUTORIAL05
//#define TUTORIAL06
//#define TUTORIAL0
//#define TUTORIAL08
//#define TUTORIAL09
//#define TUTORIAL10


// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// The simplest scene: A single sphere
#ifdef TUTORIAL01
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id,  0.0f ); // Shutter Open
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );
	rqSetCameraTime      ( camera_id,  1.0f ); // Shutter Close
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


// Particles
#ifdef TUTORIAL02
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 800, 800 );
	rqSetCameraTime      ( camera_id,  0.0f ); // Shutter Open
	rqSetCameraFOV       ( camera_id, 25.0f );
	rqSetCameraPosition  ( camera_id, 8, 8, -8 );
	rqSetCameraTime      ( camera_id,  1.0f ); // Shutter Close
	rqSetCameraFOV       ( camera_id, 25.0f );
	rqSetCameraPosition  ( camera_id, 8, 8, -8 );

	// Object
	auto object_id = rqAddObject( );
	rqSetObjectName( object_id, "particles" );
	const auto N = 65536*16;

	float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
	unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));

	for(auto i = 0; i < N; ++i)
	{
		positions[i*3+0] = 4*rand()/(float)RAND_MAX-2.0f;
		positions[i*3+1] = 4*rand()/(float)RAND_MAX-2.0f;
		positions[i*3+2] = 4*rand()/(float)RAND_MAX-2.0f;
		radii[i] = 0.02f;
		ids  [i] = i;
	}

	rqAddVertexData  ( object_id, AtomParticle, "position", N, 3, positions );
	rqAddVertexData  ( object_id, AtomParticle, "radius"  , N, 1, radii     );
	rqAddPrimitives  ( object_id, AtomParticle, N, ids );
	
	std::free(positions);
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
	rqSetRendererSample ( 128 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;

}
#endif


// Flake Shader
#ifdef TUTORIAL03
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id,  0.0f ); // Shutter Open
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );
	rqSetCameraTime      ( camera_id,  1.0f );  // Shutter Close
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );


	// Shader
	auto shader_id = rqAddShader();

	auto layer0_id = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer0_id, SideBoth , ElementAlbedo   , 1,1,1 );
	rqSetLayerColor ( shader_id, layer0_id, SideBoth , ElementRoughness, 0,0,0 );
	rqSetLayerColor ( shader_id, layer0_id, SideInner, ElementIOR      , 2,2,2 );

	auto layer1_id = rqAddLayer( shader_id );
	rqSetLayerColor ( shader_id, layer1_id, SideOuter, ElementAlbedo   , 0.0f, 0.0f, 0.0f );
	rqSetLayerColor ( shader_id, layer1_id, SideBoth , ElementNormal   , 1.0f, 1.0f, 1.0f );
	rqSetLayerFlake ( shader_id, layer1_id, SideBoth , ElementAlbedo   , 0.9f, 0.6f, 0.3f, 0.01, 0.01, 0.1 );
	rqSetLayerFlake ( shader_id, layer1_id, SideBoth , ElementNormal   , 0.9f, 0.9f, 0.9f, 0.01, 0.01, 0.1 );
	rqSetLayerColor ( shader_id, layer1_id, SideBoth , ElementRoughness, 0.1,0.1,0.1 );
	rqSetLayerColor ( shader_id, layer1_id, SideInner, ElementIOR      , 500, 500, 500 );

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





// Particles
#ifdef TUTORIAL04
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 31 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 960, 540 );
	rqSetCameraTime      ( camera_id,  0.0f ); // Shutter Open
	rqSetCameraFOV       ( camera_id, 70.0f );
	rqSetCameraPosition  ( camera_id, 20, 20, -20 );
	rqSetCameraTime      ( camera_id,  1.0f ); // Shutter Close
	rqSetCameraFOV       ( camera_id, 70.0f );
	rqSetCameraPosition  ( camera_id, 20, 20, -20 );

		const auto U = 128;
		const auto V = 128;
		const auto N = U * V / 2;

	// Object
	{
		auto object_id = rqAddObject( );
		rqSetObjectName( object_id, "group1" );


		float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
		float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
		unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));


		auto shader_id = rqAddShader();
		auto layer0_id = rqAddLayer( shader_id );
		rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementEmission , 1,1,1 );
		rqSetShaderGeometryLight( shader_id, SideOuter, true );

		auto i = 0;
		for(auto v = 0; v < V; ++v)
		{
			for(auto u = 0; u < U; ++u)
			{
				if(((0==u%2)^(0==v%2)))
				{
				positions[i*3+0] = u*2+1-U;
				positions[i*3+1] = 0;
				positions[i*3+2] = v*2+1-V;
				radii[i] = 0.75f;
				ids  [i] = i;
				++i;
				}
			}
		}
		rqAddVertexData  ( object_id, AtomParticle, "position", N, 3, positions );
		rqAddVertexData  ( object_id, AtomParticle, "radius"  , N, 1, radii     );
		rqAddPrimitives  ( object_id, AtomParticle, N, ids );
		rqSetObjectShader( object_id, AtomParticle, shader_id );
		
		std::free(positions);
		std::free(radii    );
		std::free(ids      );
	}

	// Object
	{
		auto object_id = rqAddObject( );
		rqSetObjectName( object_id, "group2" );

		float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
		float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
		unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));

		auto shader_id = rqAddShader();
		auto layer0_id = rqAddLayer( shader_id );
		rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementAlbedo   , 0.9,0.9,0.9 );
		rqSetLayerColor ( shader_id, layer0_id, SideInner, ElementIOR      , 100,100,100 );
		rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementRoughness, 1.0,1.0,1.0 );

		auto i = 0;
		for(auto v = 0; v < V; ++v)
		{
			for(auto u = 0; u < U; ++u)
			{
				if(!((0==u%2)^(0==v%2)))
				{
				positions[i*3+0] = u*2+1-U;
				positions[i*3+1] = 0;
				positions[i*3+2] = v*2+1-V;
				radii[i] = 0.75f;
				ids  [i] = i;
				++i;
				}
			}
		}

		rqAddVertexData  ( object_id, AtomParticle, "position", N, 3, positions );
		rqAddVertexData  ( object_id, AtomParticle, "radius"  , N, 1, radii     );
		rqAddPrimitives  ( object_id, AtomParticle, N, ids );
		rqSetObjectShader( object_id, AtomParticle, shader_id );
		
		std::free(positions);
		std::free(radii    );
		std::free(ids      );
	}


	// Floor
	{
		auto object_id = rqAddObject( );
		rqSetObjectName( object_id, "floor" );

		auto shader_id = rqAddShader();
		auto layer0_id = rqAddLayer( shader_id );
		rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementAlbedo   , 0.9,0.9,0.9 );
		rqSetLayerColor ( shader_id, layer0_id, SideInner, ElementIOR      , 100,100,100 );
		rqSetLayerColor ( shader_id, layer0_id, SideOuter, ElementRoughness, 1.0,1.0,1.0 );

		float positions[ ] = { -U, -0.75, V, U, -0.75, V, U, -0.75, -V, -U, -0.75, -V };

		unsigned int vertex_ids[ ] = { 0,1,2,3 };

		rqAddVertexData  ( object_id, AtomTetragon, "position", 4, 3, positions );
		rqSetObjectShader( object_id, AtomTetragon, shader_id );
		rqAddPrimitives  ( object_id, AtomTetragon, 1, vertex_ids );
	}

	// Lights
	rqSetSkyLightColor      ( 0,0,0);
	rqSetGeometryLightSample( 256 );

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








// Code to Build Your Own Software
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

		// Camera Pose - Shutter Open
		rqSetCameraTime     ( camera_id,  0.0f );
		rqSetCameraFOV      ( camera_id, 35.0f );
		rqSetCameraBokeh    ( camera_id,  0.4f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		// Camera Pose - Shutter Close
		rqSetCameraTime     ( camera_id,  1.0f );
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
	auto shader_id2 = rqAddShader( ); rqSetShaderName ( shader_id2, "wire" );
	
	// Matrix for Color and UV
	float color_matrix[4][4] = { 1,0,0,0,   0,1,0,0,   0,0,1,0,   0,0,0,1 };	
	float    uv_matrix[3][3] = { 2,0,0,  0,2,0,   0,0,1 };
	
	// Shader 0 
	{
		auto layer_id0 = rqAddLayer( shader_id0 );
		rqSetLayerColor ( shader_id0, layer_id0, SideInner, ElementAlbedo   , 0.4f, 0.4f, 0.9f );
		rqSetLayerColor ( shader_id0, layer_id0, SideOuter, ElementAlbedo   , 0.9f, 0.9f, 0.9f );
		rqSetLayerColor ( shader_id0, layer_id0, SideBoth , ElementRoughness, 1.0f, 1.0f, 1.0f );
		rqSetLayerColor ( shader_id0, layer_id0, SideOuter, ElementIOR      , 1,1,1 );
		rqSetLayerColor ( shader_id0, layer_id0, SideInner, ElementIOR      , 500, 500, 500 );
		//rqSetShaderTwoSided( shader_id0, true );
	}

	// Shader 1
	{
		auto layer_id = rqAddLayer( shader_id1 );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementAlbedo   , 1,1,1 );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementRoughness, 0,0,0 );
		rqSetLayerColor ( shader_id1, layer_id, SideInner, ElementIOR      , 2,2,2 );
	}
	{
		auto layer_id = rqAddLayer( shader_id1 );
		rqSetLayerColor ( shader_id1, layer_id, SideOuter, ElementAlbedo   , 0.0f, 0.0f, 0.0f );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementNormal   , 1.0f, 1.0f, 1.0f );
		rqSetLayerFlake ( shader_id1, layer_id, SideBoth , ElementAlbedo   , 0.9f, 0.6f, 0.3f, 0.005, 0.004, 0.1 );
		rqSetLayerFlake ( shader_id1, layer_id, SideBoth , ElementNormal   , 0.9f, 0.9f, 0.9f, 0.005, 0.004, 0.1 );
		rqSetLayerColor ( shader_id1, layer_id, SideBoth , ElementRoughness, 0.1,0.1,0.1 );
		rqSetLayerColor ( shader_id1, layer_id, SideInner, ElementIOR      , 500, 500, 500 );
	}


	// Shader 2
	{
		auto layer_id = rqAddLayer( shader_id2 );
		rqSetLayerColor ( shader_id2, layer_id, SideBoth, ElementAlbedo   , 1.0f, 1.0f, 1.0f );
		rqSetLayerColor ( shader_id2, layer_id, SideBoth, ElementRoughness, 1.0f, 1.0f, 1.0f );
		rqSetLayerColor ( shader_id2, layer_id, SideBoth, ElementIOR      , 1.5f, 1.5f, 1.5f );
	}

	// Smoothing ( to create vertex normals and tangents )
	{
		rqSetShaderSmoothAngle( shader_id0, -1 );
		rqSetShaderSmoothAngle( shader_id1, -1 );
		rqSetShaderSmoothAngle( shader_id2, -1 );
	}


	////////////////////////
	// Geometry
	////////////////////////
	auto instanced_object_id = rqAddObject( );
	{
		rqSetObjectName( instanced_object_id, "particles" );
		{
			float        positions[ ] = { 0, 0,  0 };
			float        radii    [ ] = { 0.3 };
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

		
		// Cylinder (Ribbon) Example
		{
			// xyzxyz...
			float        reference[ ] = { -0.8,  1.0, 0.0,    -0.4,  1.0, 0.0,   0,  1.0, 0.0,   0.4,  1.0,  0.0,    0.8,   1.0, 0.0 };
			float        offset0  [ ] = {  0.0, +0.1, 0.0,     0.0, -0.1, 0.0,   0, +0.1, 0.0,   0.0, -0.1,  0.0,    0.0,  +0.1, 0.0 };
			float        offset1  [ ] = {  0.0, -0.1, 0.0,     0.0, +0.1, 0.0,   0, -0.1, 0.0,   0.0, +0.1,  0.0,    0.0,  -0.1, 0.0 };
			float        radii    [ ] = { 0.01, 0.01, 0.01, 0.01, 0.01 };
			unsigned int ids      [ ] = { 0, 1, 2, 3  };
			rqSetObjectShader( object_id, AtomCylinder, shader_id2 );
			rqAddVertexData  ( object_id, AtomCylinder, "position", 5, 3, reference );
			rqAddVertexData  ( object_id, AtomCylinder, "motion"  , 5, 3, offset0   );
			rqAddVertexData  ( object_id, AtomCylinder, "motion"  , 5, 3, offset1   );
			rqAddVertexData  ( object_id, AtomCylinder, "radius"  , 5, 1, radii     );
			rqAddPrimitives  ( object_id, AtomCylinder, 4, ids);
		}
		
	}


	////////////////////////
	// Light
	////////////////////////			
	{
		auto point_light_id = rqAddPointLight( );
		rqSetPointLightPosition  ( point_light_id, 0.0,  1.5, 0.0 );
		rqSetPointLightColor     ( point_light_id, 1.0,  1.0, 1.0 );
		rqSetPointLightDirection ( point_light_id, 0.5, -1.0, 0.0 );
		rqSetPointLightOuterAngle( point_light_id, 90 );
		rqSetPointLightInnerAngle( point_light_id, 60 );
		rqSetPointLightBlur      ( point_light_id, 0.1 );
		rqSetPointLightSample    ( point_light_id, 256 );
		rqSetPointLightPhoton    ( point_light_id, 1000000 );
	}
	
	{
		auto point_light_id = rqAddPointLight( );
		rqSetPointLightPosition  ( point_light_id,  0.0,  1.5, 0.0 );
		rqSetPointLightColor     ( point_light_id,  1.0,  1.0, 1.0 );
		rqSetPointLightDirection ( point_light_id, -0.5, -1.0, 0.0 );
		rqSetPointLightOuterAngle( point_light_id,  90 );
		rqSetPointLightInnerAngle( point_light_id,  60 );
		rqSetPointLightBlur      ( point_light_id,  0.1 );
		rqSetPointLightSample    ( point_light_id,  256 );
		rqSetPointLightPhoton    ( point_light_id, 1000000 );
	}


	
	////////////////////////
	// Skylight
	////////////////////////
	{
		rqSetSkyLightColor  ( 1, 1,  1 );
		rqSetSkyLightZenith ( 0, 1,  0 );
		rqSetSkyLightNorth  ( 0, 0, -1 );
		rqSetSkyLightSample ( 0 );
		rqSetSkyLightPhoton ( 1000000 );
		// From sIBL Library
		//rqSetSkyLightImage ( "d:\\Redqueen\\Model\\Materials\\light\\image.hdr" );
		//rqSetSkyLightImage ( "BasketballCourt_3k.hdr" );
		
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
	rqSetRendererBounce    ( 2 );
	rqSetRendererResolution( 0 ); // Turn Off FG
	rqSetRendererRadius    ( 0 ); // Turn off Caustics Photon

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


#ifdef TUTORIAL10 // Turntable
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
