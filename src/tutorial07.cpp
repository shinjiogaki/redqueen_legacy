
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Hair Shading
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
	rqSetShaderColor ( shader_id, SideBoth, ElementGlossy   , 0.6f, 0.6f, 0.6f ); // Transmittance
	rqSetShaderColor ( shader_id, HairRoot, ElementDiffuse  , 0.4f, 0.2f, 0.0f ); // Reflection
	rqSetShaderColor ( shader_id, HairTip , ElementDiffuse  , 0.0f, 0.2f, 0.4f ); // Reflection
	rqSetShaderColor ( shader_id, HairRoot, ElementRoughness, 0.2f, 0.2f, 0.2f ); // for R, TT, TRT
	rqSetShaderColor ( shader_id, HairTip , ElementRoughness, 1.0f, 1.0f, 1.0f ); // for R, TT, TRT
	rqSetShaderIOR ( shader_id, 1.5f ); // IOR

	// Object
	const auto W =  8;
	const auto H =  8;
	const auto S =  8; // Num Segments
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
				radii    [  S*n + s      ] = 0.02 * (s+0.5)/S;
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
	rqSetSkyLightColor (0.5,0.5,0.5);

	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.0f );

	// Renderer
	rqSetRendererSample ( 256 );
	rqSetRendererBounce ( 4   );
	rqSetRendererClamp  ( 1.0f, 1.0f, 1.0f );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );
	rqShutdown   ( );

	return 0;
}