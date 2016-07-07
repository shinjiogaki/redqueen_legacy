
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Sphere with Geometry Light
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
	rqSetShaderColor        ( shader_id, SideFace, ElementEmission , 100,100,100 );
	rqSetShaderGeometryLight( shader_id, SideFace, true );

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
	rqSetRendererSample (1024);

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	rqShutdown ( );

	return 0;
}
