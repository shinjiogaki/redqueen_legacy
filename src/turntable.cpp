
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


// Multi-Level Instancing & Procedural Shader
int main( int argc, char *argv[ ] )
{

	for(auto i = 0; i < 300; ++i )
	{
		rqStartup  ( );
		rqLoadScene( argv[ 1 ] );
		auto cos_ = cosf((i/300.0f)*3.14159265*2);
		auto sin_ = sinf((i/300.0f)*3.14159265*2);
		auto cos__ = cosf((i/300.0f)*3.14159265*4);
		auto sin__ = sinf((i/300.0f)*3.14159265*4);
	
		rqSetParallelLightDirection(0, cos__, -1, sin__ );
	
		rqSetCameraTime(0,0);
		rqSetCameraPosition(0, 12*cos_,4 ,12*sin_ );
		rqSetCameraTime(0,1);
		rqSetCameraPosition(0, 12*cos_,4 ,12*sin_);
		rqInitialize ( );
		rqRender     ( );
		rqFinalize   ( );
		rqShutdown   ( );
	}
	return 0;
}