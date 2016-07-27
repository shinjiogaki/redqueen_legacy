
// Include API header
#include "rq.h"

#include <iostream>
#include <cstdlib>


int main( int argc, char *argv[ ] )
{
	if( 2 <= argc )
	{
		for( auto i = 2; i < argc; ++i )
		{
			if( 0 == strcmp( argv[ i ], "-preview" ) ) { rqCreatePreviewWindow( ); }
		}
		rqGo( argv[ 1 ] );
	}
	return 0;
}
