

// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Sphere with Sky Light
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 23 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
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
	// To get maps, visit sIBL http://www.hdrlabs.com/sibl/archive.html
	//rqSetSkyLightColor(1,1,1);
	//rqSetSkyLightImage("Barce_Rooftop_C_3k.hdr");
	rqSetSkyLightColor(1000,1000,1000);
	rqSetSkyLightImage("sky.png");
	rqSetSkyLightSample(512);

	// Display
	rqCreatePreviewWindow ( );
	rqSetDisplayGamma  ( 1.45f );

	// Renderer
	rqSetRendererSample (512);

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	rqShutdown ( );

	return 0;

}
