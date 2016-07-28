
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Particles with Motion Blur
int main( )
{

	rqStartup( );

	// Camera
	const auto AA  = 43;
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, AA ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 800, 800 );
	rqSetCameraFOV       ( camera_id, 40.0f );
	rqSetCameraPosition  ( camera_id, 32, 32, -32 );


	// Texture
	const auto w = 256;
	const auto h = 256;
	const auto tile = 16;
	const auto image_id = rqAddImage();
	rqSetImageName( image_id, "noise.png" );
	rqCreateImage( image_id, w, h );
	for( auto v = 0; v < h; ++v )
	{
		for( auto u = 0; u < w; ++u )
		{
			rqSetImageColor(image_id, u,v, rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
		}
	}


	// Shader
	auto shader_id = rqAddShader();
	rqSetShaderName     ( shader_id, "noise" );
	rqSetShaderTwoSided ( shader_id, false    );
	rqSetShaderColor    ( shader_id, SideFace, ElementDiffuse, 0.9,0.9,0.9 );
	rqSetShaderImage    ( shader_id, SideFace, ElementDiffuse, "noise.png", 1, 0, 0, PixelSamplerNearest, 0, 0 );
	rqSetShaderIOR      ( shader_id, 8 );



	// Object
	auto object_id = rqAddObject( );
	rqSetObjectName( object_id, "particles" );
	const auto N = 300;

	float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *uvs       = (float*)       std::malloc( N * 2 * sizeof(float)       );
	float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
	unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));

	for(auto i = 0; i < N; ++i)
	{
		positions[i*3+0] = rand()%25-12;
		positions[i*3+1] = rand()%25-12;
		positions[i*3+2] = rand()%25-12;
		uvs      [i*2+0] = rand()/(float)RAND_MAX;
		uvs      [i*2+1] = rand()/(float)RAND_MAX;

		radii[i] = 0.5f;
		ids  [i] = i;
	}
	

	// Cubes Initial positions are used to build bvh, hair uv, etc.
	rqSetObjectDynamic( object_id, AtomCube );            // Dynamic object
	rqSetObjectShader ( object_id, AtomCube, shader_id ); // Shader

	rqAddPrimitives   ( object_id, AtomCube,             N,    ids       );
	rqAddVertexData   ( object_id, AtomCube, "position", N, 3, positions );
	rqAddVertexData   ( object_id, AtomCube, "uv"      , N, 2, uvs       );
	rqAddVertexData   ( object_id, AtomCube, "radius"  , N, 1, radii     );

	std::free(positions);
	std::free(radii    );
	std::free(uvs      );
	std::free(ids      );


	// Parallel Light
	auto light_id = rqAddParallelLight();
	rqSetParallelLightColor    ( light_id, 1,1,1);
	rqSetParallelLightDirection( light_id, 1,-1,1);

	// Display
	rqCreatePreviewWindow ( );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 1024 );

	rqInitialize ( );

	// Motion Blur
	for(auto aa = 0; aa < AA; ++aa )
	{

		// Deformation
		//for(auto i = 0; i < N; ++i)
		//{
		//	positions[i*3+0] = ;
		//	positions[i*3+1] = ;
		//	positions[i*3+2] = ;
		//}
		//rqAddVertexData ( object_id, AtomCube, "position", N, 3, positions );

		// Linear Transformation
		float t = (aa+0.5f)/(float)AA * 3.1415 * 0.125;
		float matrix[] = {cos(t),0,-sin(t),0,   0,1.0,0,0,  sin(t),0,cos(t),0,   0,0,0,1 };
		rqSetObjectMatrix ( object_id, matrix );

		// Update
		rqUpdate             ( );
		rqRenderPixels       ( );
		rqUpdatePreviewWindow( );
	}

	rqFinalize ( );

	rqShutdown ( );

	return 0;

}