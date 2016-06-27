
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Instancing and Final Gathering
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
		rqSetShaderColor ( shader_id0, SideFace, ElementDiffuse, 0.7f, 0.7f, 0.7f );
		rqSetShaderTwoSided( shader_id0, false );
	}

	// Shader 1
	{
		rqSetShaderColor ( shader_id1, SideBoth, ElementSpecular, 1,1,1 );
		rqSetShaderIOR   ( shader_id1, 1.5 );
		rqSetShaderTwoSided( shader_id1, true );
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
		rqSetPointLightColor     ( point_light_id, 1.0, 0.5, 0.0 );
		rqSetPointLightDirection ( point_light_id, 0.5, -1.0, 0.0 );
		//rqSetPointLightOuterAngle( point_light_id, 180 );
		//rqSetPointLightInnerAngle( point_light_id, 25 );
		rqSetPointLightBlur      ( point_light_id, 0 );
		rqSetPointLightSample    ( point_light_id, 256 );
		rqSetPointLightPhoton    ( point_light_id, 1000000 );
	}
	
	{
		auto point_light_id = rqAddPointLight( );
		rqSetPointLightPosition  ( point_light_id,  0.0,  1.5, 0.0 );
		rqSetPointLightColor     ( point_light_id,  0.0,  0.5, 1.0 );
		rqSetPointLightDirection ( point_light_id, -0.5, -1.0, 0.0 );
		//rqSetPointLightOuterAngle( point_light_id,  180 );
		//rqSetPointLightInnerAngle( point_light_id,  25 );
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
		rqSetSkyLightPhoton ( 0 );
		
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
	rqSetRendererResolution( 0.001 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	// Shutdown redqueen
	rqShutdown( );

	return 0;

}