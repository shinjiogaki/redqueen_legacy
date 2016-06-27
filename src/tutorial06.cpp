
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Loading .obj File & Texture Mapping
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
	rqSetShaderColor    ( shader_id, SideFace, ElementDiffuse, 0.9,0.9,0.9 );
	rqSetShaderImage    ( shader_id, SideFace, ElementDiffuse, "checker.png" );
	rqSetShaderIOR      ( shader_id, 8 );

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