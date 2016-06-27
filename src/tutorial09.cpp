
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Multi-Level Instancing & Procedural Shader
int main( )
{

	// Startup
	rqStartup( );


	// Camera
	auto camera_id = rqAddCamera( );
	{
		rqSetCameraSample      ( camera_id, 23 ); // AA samples can be an arbitrary number
		rqSetCameraResolution  ( camera_id, 512, 512 );
		rqSetCameraProjection  ( camera_id, ProjectionPerspective );
		rqSetCameraAngleMeasure( camera_id, AngleMeasureVertical  );

		rqSetCameraTime     ( camera_id, ShutterOpen );
		rqSetCameraFOV      ( camera_id, 30.0f );
		rqSetCameraPosition ( camera_id, 3,3,3 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		rqSetCameraTime     ( camera_id, ShutterClose );
		rqSetCameraFOV      ( camera_id, 30.0f );
		rqSetCameraPosition ( camera_id, 3,3,3 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );
	}


	// Shader
	auto shader_id = rqAddShader( ); rqSetShaderName ( shader_id, "ball" );
	rqSetShaderColor ( shader_id, SideFace, ElementDiffuse, 1,1,1 );
	rqSetShaderImage ( shader_id, SideFace, ElementDiffuse, "stone.png");
	rqSetShaderStone ( shader_id, SideFace, ElementDiffuse, 0.6, 0.1, 0.7, 8 );
	rqSetShaderIOR   ( shader_id, 100 );


	// Sphere
	auto instanced_object_id = rqAddObject( );
	{
		rqSetObjectName( instanced_object_id, "sphere" );
		{
			float        positions[ ] = { 0, 0,  0 };
			float        radii    [ ] = { 0.3 };
			unsigned int ids      [ ] = { 0   };
			rqSetObjectShader( instanced_object_id, AtomParticle, shader_id  );
			rqAddVertexData  ( instanced_object_id, AtomParticle, "position", 1, 3, positions );
			rqAddVertexData  ( instanced_object_id, AtomParticle, "radius"  , 1, 1, radii     );
			rqAddPrimitives  ( instanced_object_id, AtomParticle, 1, ids );
		}
	}
	
	// X
	auto xgroup_object_id = rqAddObject( );
	{
		rqSetObjectName( xgroup_object_id, "xgroup" );

		// Instance
		{
			float matrix0[16] = { 1,0,0,-0.6,  0,1,0,0.0,  0,0,1,0,   0,0,0,1 };
			float matrix1[16] = { 1,0,0, 0.0,  0,1,0,0.0,  0,0,1,0,   0,0,0,1 };
			float matrix2[16] = { 1,0,0,+0.6,  0,1,0,0.0,  0,0,1,0,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( xgroup_object_id );
			auto instance_id1 = rqAddInstance( xgroup_object_id );
			auto instance_id2 = rqAddInstance( xgroup_object_id );
			rqSetInstance( xgroup_object_id, instance_id0, instanced_object_id, matrix0 );
			rqSetInstance( xgroup_object_id, instance_id1, instanced_object_id, matrix1 );
			rqSetInstance( xgroup_object_id, instance_id2, instanced_object_id, matrix2 );
		}
		
	}

	// Y
	auto ygroup_object_id = rqAddObject( );
	{
		rqSetObjectName( ygroup_object_id, "ygroup" );

		// Instance
		{
			float matrix0[16] = { 1,0,0, 0.0,  0,1,0, 0.6,  0,0,1,0,   0,0,0,1 };
			float matrix1[16] = { 1,0,0, 0.0,  0,1,0, 0.0,  0,0,1,0,   0,0,0,1 };
			float matrix2[16] = { 1,0,0, 0.0,  0,1,0,-0.6,  0,0,1,0,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( ygroup_object_id );
			auto instance_id1 = rqAddInstance( ygroup_object_id );
			auto instance_id2 = rqAddInstance( ygroup_object_id );
			rqSetInstance( ygroup_object_id, instance_id0, xgroup_object_id, matrix0 );
			rqSetInstance( ygroup_object_id, instance_id1, xgroup_object_id, matrix1 );
			rqSetInstance( ygroup_object_id, instance_id2, xgroup_object_id, matrix2 );
		}		
	}
	
	// Z
	auto zgroup_object_id = rqAddObject( );
	{
		rqSetObjectName( zgroup_object_id, "zgroup" );

		// Instance
		{
			float matrix0[16] = { 1,0,0, 0.0,  0,1,0,0.0,  0,0,1,-0.6,   0,0,0,1 };
			float matrix1[16] = { 1,0,0, 0.0,  0,1,0,0.0,  0,0,1, 0.0,   0,0,0,1 };
			float matrix2[16] = { 1,0,0, 0.0,  0,1,0,0.0,  0,0,1,+0.6,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( zgroup_object_id );
			auto instance_id1 = rqAddInstance( zgroup_object_id );
			auto instance_id2 = rqAddInstance( zgroup_object_id );
			rqSetInstance( zgroup_object_id, instance_id0, ygroup_object_id, matrix0 );
			rqSetInstance( zgroup_object_id, instance_id1, ygroup_object_id, matrix1 );
			rqSetInstance( zgroup_object_id, instance_id2, ygroup_object_id, matrix2 );
		}		
	}

	// Skylight
	rqSetSkyLightColor  ( 1,1,1 );
		
	// Display
	rqSetPreviewWindow ( true );
	rqSetDisplayGamma  ( 1.45f );


	// Rendering
	rqSetRendererClamp     ( 1000, 1000, 1000);
	rqSetRendererSample    ( 256 );
	rqSetRendererBounce    ( 1 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	// Shutdown redqueen
	rqShutdown( );

	return 0;

}