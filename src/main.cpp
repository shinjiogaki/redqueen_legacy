
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
		rqSetCameraSample      ( camera_id, 23 ); // AA samples can be an arbitrary number
		//rqSetCameraRegion      ( camera_id, 16, 16, 496, 496 ); // Render Region
		rqSetCameraResolution  ( camera_id, 512, 512 );
		rqSetCameraProjection  ( camera_id, Projection  ::Perspective );
		rqSetCameraAngleMeasure( camera_id, AngleMeasure::Vertical    );

		// Camera Pose - Shutter Open
		rqSetCameraTime     ( camera_id,  0.0f );
		rqSetCameraFOV      ( camera_id, 40.0f );
		rqSetCameraBokeh    ( camera_id,  1.0f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );

		// Camera Pose - Shutter Close
		rqSetCameraTime     ( camera_id,  1.0f );
		rqSetCameraFOV      ( camera_id, 40.0f );
		rqSetCameraBokeh    ( camera_id,  1.0f );
		rqSetCameraPosition ( camera_id, 0, 1, -4 );
		rqSetCameraTarget   ( camera_id, 0, 1,  0 );
		rqSetCameraUpVector ( camera_id, 0, 1,  0 );
		//rqSetCameraUpVector ( camera_id, 0.1, 1, 0.1 ); // Camera Blur :)

		// AOVs
		auto aov_id0 = rqAddCameraAOV( camera_id );
		auto aov_id1 = rqAddCameraAOV( camera_id );
		auto aov_id2 = rqAddCameraAOV( camera_id );
		auto aov_id3 = rqAddCameraAOV( camera_id );
		rqSetCameraAOVName     ( camera_id, aov_id0,     "normal.png" );
		rqSetCameraAOVName     ( camera_id, aov_id1, "lambertian.png" );
		rqSetCameraAOVName     ( camera_id, aov_id2,    "my_data.png" );	
		rqSetCameraAOVName     ( camera_id, aov_id3,    "tangent.png" );
		rqSetCameraAOVChannel  ( camera_id, aov_id0, Channel::Normal     );
		rqSetCameraAOVChannel  ( camera_id, aov_id1, Channel::Lambertian );
		rqSetCameraAOVChannel  ( camera_id, aov_id2, Channel::UserData   );
		rqSetCameraAOVChannel  ( camera_id, aov_id3, Channel::Tangent    );
		rqSetCameraAOVUserData ( camera_id, aov_id2, "my_data" );
	}


	////////////////////////
	// Shader
	////////////////////////
	auto shader_id0 = rqAddShader( );
	auto shader_id1 = rqAddShader( );
	auto shader_id2 = rqAddShader( );
	{
		// Matrix for Color and UV
		float color_matrix[4][4] = { 1,0,0,0,   0,1,0,0,   0,0,1,0,   0,0,0,1 };	
		float    uv_matrix[3][3] = { 2,0,0,  0,2,0,   0,0,1 };
	
		// Shader 0 
		{
			auto surface_shader_id = rqAddSurfaceShader( shader_id0 );
			rqSetShaderName   ( shader_id0, "white" );
			rqSetSurfaceColor ( shader_id0, surface_shader_id, Element::Lambertian, 0.9f, 0.9f, 0.9f );
		}
	
		// Shader 1
		{
			auto surface_shader_id = rqAddSurfaceShader( shader_id1 );
			rqSetShaderName   ( shader_id1, "glossy");
			rqSetSurfaceColor ( shader_id1, surface_shader_id, Element::Lambertian, 1.0f, 0.5f, 0.0f );
			rqSetSurfaceColor ( shader_id1, surface_shader_id, Element::Glossy    , 1.0f, 1.0f, 1.0f );
			rqSetSurfaceColor ( shader_id1, surface_shader_id, Element::Roughness , 0.1f, 0.1f, 0.1f );
			rqSetSurfaceColor ( shader_id1, surface_shader_id, Element::IOR       , 3.0f, 3.0f, 3.0f ); // For Fresnel
		}
		
		// Shader 2
		{
			auto surface_shader_id = rqAddSurfaceShader( shader_id2 );
			rqSetShaderName   ( shader_id2, "green" );
			rqSetSurfaceColor ( shader_id2, surface_shader_id, Element::Lambertian, 0.5f, 1.0f, 0.8f );
			//rqSetSurfaceColor ( shader_id2, surface_shader_id, Element::Specular  , 1.0f, 1.0f, 1.0f );
			//rqSetSurfaceColor ( shader_id2, surface_shader_id, Element::IOR       , 5.0f, 5.0f, 5.0f ); // For Fresnel
		}

		// Smoothing ( to create vertex normals and tangents )
		{
			rqSetShaderSmoothAngle( shader_id0, 0 );
			rqSetShaderSmoothAngle( shader_id1, 0 );
			rqSetShaderSmoothAngle( shader_id2, 0 );
		}

		// Layered Displacement Map Example
		if( false )
		{
			rqAddDisplacementShader ( shader_id0 );
			rqSetDisplacementVector ( shader_id0, 0, 0, 0, -0.1 );
			//rqSetDisplacementImage  ( shader_id0, 0, "low_freq.jpg", 0.2f, 0, 0 );
			rqSetDisplacementLevel  ( shader_id0, 0, 16 );
								    
			rqAddDisplacementShader ( shader_id0 );
			rqSetDisplacementVector ( shader_id0, 1, 0, 0, 0.01 );
			//rqSetDisplacementImage  ( shader_id0, 1, "high_freq.jpg", 0.2f, 0, 0 );
			rqSetDisplacementLevel  ( shader_id0, 1, 4 );
		}

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
			rqSetShaderID ( instanced_object_id, part_id,    shader_id1  );
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
			float matrix1[4][4] = { 1,0,0,0,   0,1,0,1,     0,0,1,0,   0,0,0,1 };
			auto instance_id0 = rqAddInstance( object_id );
			auto instance_id1 = rqAddInstance( object_id );
			rqSetInstance( object_id, instance_id0, instanced_object_id, matrix0, shader_id1 );
			rqSetInstance( object_id, instance_id1, instanced_object_id, matrix1, shader_id2 );
		}

		// Mesh
		{
			// Add Group
			auto part_id = rqAddPart ( object_id );
	
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
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1,
				0, 1, 0, 0, 1, 0, 0, 1
			};

			// xyzxyz...
			float motion[ ] =
			{
				 0.0, 0, 0,    0.0, -0.3, 0,    0, -0.3, 0,    0, 0, 0, 
				 0.0, 0, 0,    0.0,  0.3, 0,    0,  0.3, 0,    0, 0, 0,  
				 0.0, 0, 0,    0.0,  0.0, 0,    0,  0.0, 0,    0, 0, 0, 
				-0.3, 0, 0,   -0.3,  0.0, 0,    0,  0.0, 0,    0, 0, 0, 
				 0.3, 0, 0,    0.3,  0.0, 0,    0,  0.0, 0,    0, 0, 0, 
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

			int vertex_ids[ ] = { 0,1,2,3 , 4, 5, 6, 7,   8, 9, 10, 11,   12, 13, 14, 15,   16, 17, 18, 19  };

			rqAddPositions ( object_id, part_id, 20, positions );
			rqAddUVs       ( object_id, part_id, 20, uvs       );
			rqAddVertexData( object_id, part_id, "motion" , 20, 3, motion  );
			rqAddVertexData( object_id, part_id, "my_data", 20, 3, my_data );

			rqSetShaderID  ( object_id, part_id,    shader_id0 );
			rqAddTetragons ( object_id, part_id, 5, vertex_ids );
		}

		
		// Cylinder (Ribbon) Example needs AVX2
		/*
		{
			// Add Group
			auto part_id = rqAddPart ( object_id );

			// xyzxyz...
			float positions[ ] = { -1, 0.75, 0,    -0.3, 1, 0.2,   0.3, 0.75, 0.2,   1,  1,  0 };
			float radii    [ ] = { 0.012, 0.008, 0.004, 0.0 };
			int   ids      [ ] = { 0, 1, 2  };
			rqSetShaderID ( object_id, part_id, shader_id1 );
			rqAddPositions( object_id, part_id, 4, positions );
			rqAddRadii    ( object_id, part_id, 4, radii );
			rqAddCylinders( object_id, part_id, 3, ids);
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
			rqSetPointLightPosition  ( point_light_id, 3, 3, -3 );
			rqSetPointLightColor     ( point_light_id,  50,  50,  50 );
			rqSetPointLightDirection ( point_light_id,  -1,  -1,  1 );
			rqSetPointLightInnerAngle( point_light_id,  0 );
			rqSetPointLightOuterAngle( point_light_id,  10 );
			rqSetPointLightPhoton    ( point_light_id, 1000000 );
		}
		*/
		
		/*
		auto parallel_light_id = rqAddParallelLight( );
		{
			rqSetParallelLightDirection( parallel_light_id, 1, -1, 2 );
			rqSetParallelLightColor    ( parallel_light_id, 0.5,0.5,0.5 );
			rqSetParallelLightPhoton   ( parallel_light_id, 1000000 );

			// Light AOVs
			auto aov_id = rqAddParallelLightAOV ( parallel_light_id );
			rqSetParallelLightAOVName    ( parallel_light_id, aov_id, "parallel_light_lambertian.png");
			rqSetParallelLightAOVChannel ( parallel_light_id, aov_id, Channel::Lambertian );
		}
		*/
	}



	////////////////////////
	// Skylight
	////////////////////////
	{
		rqSetSkyLightColor  ( 1, 1, 1 );
		rqSetSkyLightZenith ( 0, 1, 0 );
		rqSetSkyLightNorth  ( 0, 0, -1 );
		rqSetSkyLightSample ( 256 );
		rqSetSkyLightPhoton ( 0 );
		//rqSetSkyLightImage ( "C:\\Shinji\\redqueen\\Model\\OutdoorMIS\\light\\light.png" );
		//rqSetSkyLightImage ( "C:\\Shinji\\hdri\\Factory_Catwalk_2k.pfm" );
		//rqSetSkyLightImage ( "C:\\Shinji\\hdri\\BasketballCourt_3k.hdr" );
		
		// Light AOVs
		auto aov_id = rqAddSkyLightAOV ( );
		rqSetSkyLightAOVName    ( aov_id, "sky_lambertian.png");
		rqSetSkyLightAOVChannel ( aov_id, Channel::Lambertian );
	}


	////////////////////////
	// Display
	////////////////////////
	rqSetPreviewWindow ( true );


	////////////////////////
	// Rendering
	////////////////////////
	rqSetRendererClamp     ( 1000000, 1000000, 1000000 );
	rqSetRendererSample    ( 256 );
	rqSetRendererBounce    ( 2 );
	rqSetRendererResolution( 0 ); // Density Estimation
	rqSetRendererDistance  ( 0 ); // Secondary Final Gathering
	rqSetRendererRadius    ( 0 ); // Turn off Caustics Photon

	rqInitialize ( );
	rqRender     ( );
	rqFinalize   ( );

	// Shutdown redqueen
	rqShutdown( );

	return 0;

}
#endif
