
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Sphere with Flake & Stone Shader
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraFOV       ( camera_id, 35.0f );
	rqSetCameraPosition  ( camera_id, 0, 0, -4 );


	// Shader
	auto shader_id = rqAddShader();
	rqSetShaderColor ( shader_id, SideFace, ElementDiffuse , 1.0f, 1.0f, 1.0f );
	rqSetShaderImage ( shader_id, SideFace, ElementDiffuse , "stone.png");
	rqSetShaderStone ( shader_id, SideFace, ElementDiffuse , 0.7, 1.0, 0.2, 16 );

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
	rqCreatePreviewWindow ( );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample ( 256 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;

}