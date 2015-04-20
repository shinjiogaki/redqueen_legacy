
// Select your favorite One

//#define CLASSIC
#define MY_APP


// Include API header
#include "rq.h"

#include <iostream>



// Code to Build redqueen.exe
#ifdef CLASSIC
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



// Code to Build Your Own Software
#ifdef MY_APP
int main( )
{

	////////////////////////
	// Startup redqueen
	////////////////////////
	rqStartup( );


	////////////////////////
	// Camera
	////////////////////////
	auto camera_id = rqAddCamera( );
	{
		rqSetCameraSample      ( camera_id, 31 ); // AA samples can be an arbitrary number
		//rqSetCameraRegion      ( camera_id, 16, 16, 496, 496 ); // Render Region
		rqSetCameraResolution  ( camera_id, 512, 512 );
		rqSetCameraProjection  ( camera_id, Projection  ::Perspective );
		rqSetCameraAngleMeasure( camera_id, AngleMeasure::Vertical    );

		// Camera Pose - Shutter Open
		rqSetCameraTime     ( camera_id,  0.0f );
		rqSetCameraFOV      ( camera_id, 40.0f );
		rqSetCameraBokeh    ( camera_id,  0.5f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		// Camera Pose - Shutter Close
		rqSetCameraTime     ( camera_id,  1.0f );
		rqSetCameraFOV      ( camera_id, 40.0f );
		rqSetCameraBokeh    ( camera_id,  0.5f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0.2, 1,  0 ); // Camera Blur :)

		// AOVs
		auto aov_id0 = rqAddCameraAOV( camera_id );
		auto aov_id1 = rqAddCameraAOV( camera_id );
		auto aov_id2 = rqAddCameraAOV( camera_id );
		rqSetCameraAOVName     ( camera_id, aov_id0,     "normal.png" );
		rqSetCameraAOVName     ( camera_id, aov_id1, "lambertian.png" );
		rqSetCameraAOVName     ( camera_id, aov_id2,    "my_data.png" );	
		rqSetCameraAOVChannel  ( camera_id, aov_id0, Channel::Normal     );
		rqSetCameraAOVChannel  ( camera_id, aov_id1, Channel::Lambertian );
		rqSetCameraAOVChannel  ( camera_id, aov_id2, Channel::UserData   );
		rqSetCameraAOVUserData ( camera_id, aov_id2, "my_data" );
	}


	////////////////////////
	// Shader
	////////////////////////
	auto shader_id0 = rqAddShader( );
	auto shader_id1 = rqAddShader( );
	{
		float color_matrix[4][4] =
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	
		float uv_matrix[3][3] =
		{
			2,0,0,
			0,2,0,
			0,0,1
		};
	
		auto surface_shader_id0 = rqAddSurfaceShader( shader_id0 );
		rqSetShaderName   ( shader_id0, "white" );
		//rqSetShaderVisibility ( shader_id0, Visibility::InvisibleFromLight );
		rqSetSurfaceColor ( shader_id0, surface_shader_id0, Element::Lambertian, 0.8f, 0.8f, 0.8f );
		//rqSetSurfaceImage ( shader_id0, surface_shader_id0, Element::Emissive, "C:\\Shinji\\redqueen\\light.hdr", 1.0f, 0, 0 ); // null : identity matrix
	
		auto surface_shader_id1 = rqAddSurfaceShader( shader_id1 );
		rqSetShaderName   ( shader_id1, "glossy");
		//rqSetShaderVisibility ( shader_id1, Visibility::InvisibleFromCamera );
		rqSetSurfaceColor ( shader_id1, surface_shader_id1, Element::Lambertian, 0.9f, 0.9f, 0.9f );
		rqSetSurfaceColor ( shader_id1, surface_shader_id1, Element::Glossy    , 1.0f, 1.0f, 1.0f );
		rqSetSurfaceColor ( shader_id1, surface_shader_id1, Element::Roughness , 0.2f, 0.2f, 0.2f );
		rqSetSurfaceColor ( shader_id1, surface_shader_id1, Element::IOR       , 5.0f, 5.0f, 5.0f ); // For Fresnel
		//rqSetSurfaceImage ( shader_id1, surface_shader_id1, Element::Glossy,  "C:\\Shinji\\redqueen\\light.hdr", 1.0f, 0, 0 ); // null : identity matrix
		
		/*
		// Displacement Map Example
		{
			rqSetShaderSmoothAngle( shader_id0, 180 );
		
			rqAddDisplacementShader ( shader_id0 );
			rqSetDisplacementVector ( shader_id0, 0, 0, 0, -0.1 );
			//rqSetDisplacementImage  ( shader_id0, 0, "C:\\Shinji\\redqueen\\stone.jpg", 0.2f, 0, 0 );
			rqSetDisplacementLevel  ( shader_id0, 0, 16 );
								    
			rqAddDisplacementShader ( shader_id0 );
			rqSetDisplacementVector ( shader_id0, 1, 0, 0, 0.01 );
			//rqSetDisplacementImage  ( shader_id0, 1, "C:\\Shinji\\redqueen\\stone.jpg", 0.2f, 0, 0 );
			rqSetDisplacementLevel  ( shader_id0, 1, 4 );
		}
		*/

	}	

	////////////////////////
	// Geometry
	////////////////////////

	auto instanced_object_id = rqAddObject( );
	{

		// Particles
		rqSetObjectName( instanced_object_id, "particles" );
		{
			// Add Group
			auto part_id = rqAddPart ( instanced_object_id );

			// xyzxyz...
			float positions[ ] = { 0.3, 0.2, 0, -0.3, 0.2, 0 };
			float radii    [ ] = { 0.2, 0.2 };
			int   ids      [ ] = { 0, 1   };
			rqSetShaderID ( instanced_object_id, part_id, shader_id1  );
			rqAddPositions( instanced_object_id, part_id, 2, positions );
			rqAddRadii    ( instanced_object_id, part_id, 2, radii );
			rqAddParticles( instanced_object_id, part_id, 2, ids );
		}
	}


	// Add Object
	auto object_id = rqAddObject( );
	{

		
		// Instance
		{
			float matrix0[4][4] = { 1,0,0,0,   0,1,0,0,     0,0,1,0,   0,0,0,1 };
			float matrix1[4][4] = { 1,0,0,0,   0,1,0,0.5,   0,0,1,0,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( object_id );
			auto instance_id1 = rqAddInstance( object_id );
			rqSetInstance( object_id, instance_id0, instanced_object_id, matrix0 );
			rqSetInstance( object_id, instance_id1, instanced_object_id, matrix1 );
		}

		// Add Group
		auto part_id = rqAddPart ( object_id );

		// Trianlges
		{
			// xyzxyz...
			float positions[ ] =
			{
				-1, 0,  1, -1, 0, -1,  1, 0, -1,  1, 0, 1,
				-1, 2,  1, -1, 2, -1,  1, 2, -1,  1, 2, 1,
				-1, 2,  1, -1, 0,  1,  1, 0,  1,  1, 2, 1,
				-1, 2, -1, -1, 0, -1, -1, 0,  1, -1, 2, 1,
				 1, 2, -1,  1, 0, -1,  1, 0,  1,  1, 2, 1
			};

			// uvuvuvuv...
			float uvs[ ] =
			{
				0, 1, 0, 0, 1, 0, 1, 1,
				0, 1, 0, 0, 1, 0, 1, 1,
				0, 1, 0, 0, 1, 0, 1, 1,
				0, 1, 0, 0, 1, 0, 1, 1,
				0, 1, 0, 0, 1, 0, 1, 1
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

			rqAddPositions ( object_id, part_id, 20, positions );
			rqAddUVs       ( object_id, part_id, 20, uvs       );
			rqAddVertexData( object_id, part_id, "my_data", 20, 3, my_data );

			{
				int vertex_ids[ ] = { 0, 1, 2, 0, 2, 3 };
				rqSetShaderID  ( object_id, part_id,    shader_id0 );
				rqAddTriangles ( object_id, part_id, 2, vertex_ids );
			}
			
			{
				int vertex_ids[ ] = { 4, 5, 6, 7,   8, 9, 10, 11,   12, 13, 14, 15,   16, 17, 18, 19  };
				rqSetShaderID  ( object_id, part_id,    shader_id0 );
				rqAddTetragons ( object_id, part_id, 4, vertex_ids );
			}

		}

		
		// Cylinder (Ribbon) Example
		/*
		{
			// Add Group
			auto part_id = rqAddPart ( object_id );

			// xyzxyz...
			float positions[ ] = { -1, -1, 0, 0, 0,  0, 1, 1,  0 };
			float radii    [ ] = { 0.05, 0.025, 0.0 };
			int   ids      [ ] = { 0, 1  };
			rqSetShaderID ( object_id, part_id, shader_id1 );
			rqAddPositions( object_id, part_id, 3, positions );
			rqAddRadii    ( object_id, part_id, 3, radii );
			rqAddCylinders( object_id, part_id, 2, ids);
		}
		*/

	}



	////////////////////////
	// Light
	////////////////////////
	
	{
		/*
		auto point_light_id = rqAddPointLight( );
		{
			rqSetPointLightPosition  ( point_light_id, 2.5, 3.0, 2.5 );
			rqSetPointLightColor     ( point_light_id,  20,  2,  2 );
			rqSetPointLightDirection ( point_light_id,  -1,  -1,  -1 );
			rqSetPointLightInnerAngle( point_light_id,  0 );
			rqSetPointLightOuterAngle( point_light_id,  5 );
		}
		*/
	
		auto parallel_light_id = rqAddParallelLight( );
		{
			rqSetParallelLightDirection( parallel_light_id, 1, -1, 1 );
			rqSetParallelLightColor    ( parallel_light_id, 0.5, 0.5, 0.5 );
			rqSetParallelLightPhoton   ( parallel_light_id, 1000000 );

			// Light AOVs
			auto aov_id = rqAddParallelLightAOV ( parallel_light_id );
			rqSetParallelLightAOVName    ( parallel_light_id, aov_id, "parallel_light_lambertian.hdr");
			rqSetParallelLightAOVChannel ( parallel_light_id, aov_id, Channel::Lambertian );
		}
	}



	////////////////////////
	// Skylight
	////////////////////////
	{
		rqSetSkyLightColor  ( 0.5, 0.5, 1 );
		rqSetSkyLightZenith ( 0, 1, 0 );
		rqSetSkyLightNorth  ( 0, 0, -1 );
		rqSetSkyLightSample ( 64 );
		rqSetSkyLightPhoton (1000000);
		//rqSetSkyLightImage ( "C:\\Shinji\\redqueen\\image.hdr" );
		
		// Light AOVs
		auto aov_id = rqAddSkyLightAOV ( );
		rqSetSkyLightAOVName    ( aov_id, "sky_lambertian.hdr");
		rqSetSkyLightAOVChannel ( aov_id, Channel::Lambertian );
	}


	////////////////////////
	// Display
	////////////////////////
	rqSetPreviewWindow ( true );


	////////////////////////
	// Rendering
	////////////////////////
	rqSetRendererClamp ( 1, 1, 1 );
	rqSetRendererSample( 256 );
	rqSetRendererBounce( 3 );
	rqSetRendererResolution( 0.1 );
	//rqSetRendererDistance ( 0 );

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	// Shutdown redqueen
	rqShutdown( );

	return 0;

}
#endif
