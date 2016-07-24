
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Particles with Motion Blur
int main( )
{

	rqStartup( );

	// Camera
	auto camera_id = rqAddCamera( );
	rqSetCameraSample    ( camera_id, 43 ); // AA samples can be an arbitrary number
	rqSetCameraResolution( camera_id, 512, 512 );
	rqSetCameraTime      ( camera_id, ShutterOpen );
	rqSetCameraFOV       ( camera_id, 40.0f );
	rqSetCameraPosition  ( camera_id, 32, 32, -32 );
	rqSetCameraTime      ( camera_id, ShutterClose );
	rqSetCameraFOV       ( camera_id, 40.0f );
	rqSetCameraPosition  ( camera_id, 32, 32, -32 );

	// Object
	auto object_id = rqAddObject( );
	rqSetObjectName( object_id, "particles" );
	const auto N = 1024;

	float        *positions = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *motions0  = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *motions1  = (float*)       std::malloc( N * 3 * sizeof(float)       );
	float        *radii     = (float*)       std::malloc( N * 1 * sizeof(float)       );
	unsigned int *ids       = (unsigned int*)std::malloc( N * 1 * sizeof(unsigned int));

	for(auto i = 0; i < N; ++i)
	{
		positions[i*3+0] =   rand()%25-12;
		positions[i*3+1] =   rand()%25-12;
		positions[i*3+2] =   rand()%25-12;
		motions0 [i*3+0] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions0 [i*3+1] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions0 [i*3+2] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+0] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+1] = 0.5*rand()/(float)RAND_MAX-0.25f;
		motions1 [i*3+2] = 0.5*rand()/(float)RAND_MAX-0.25f;

		radii[i] = 0.5f;
		ids  [i] = i;
	}

	// Spheres
	//rqAddVertexData ( object_id, AtomParticle, "position", N, 3, positions );
	////rqAddVertexData ( object_id, AtomParticle, "motion"  , N, 3, motions0  );
	////rqAddVertexData ( object_id, AtomParticle, "motion"  , N, 3, motions1  );
	//rqAddVertexData ( object_id, AtomParticle, "radius"  , N, 1, radii     );
	//rqAddPrimitives ( object_id, AtomParticle, N, ids );
	
	// Cubes
	rqAddVertexData ( object_id, AtomCube, "position", N, 3, positions );
	//rqAddVertexData ( object_id, AtomCube, "motion"  , N, 3, motions0  );
	//rqAddVertexData ( object_id, AtomCube, "motion"  , N, 3, motions1  );
	rqAddVertexData ( object_id, AtomCube, "half_width"  , N, 1, radii     );
	rqAddPrimitives ( object_id, AtomCube, N, ids );

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