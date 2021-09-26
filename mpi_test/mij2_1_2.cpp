#include <iostream>
#include "mpi.h"

struct A {
	long id;
	float velocity;
	int type;
	char description[ 50 ];
};


void generate( A ob[ 100 ] );

int main( int argc, char *argv[] ) {

	int rank, size;

	MPI_Init( &argc, &argv );

	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	A obj[ 100 ];

	if ( rank == 0 ) {
		generate( obj );
	}

	MPI_Datatype A_type;
	int blocklen[ 4 ]={1,1,1,50};
	MPI_Datatype types[ 4 ] = {MPI_LONG,MPI_FLOAT,MPI_INT,MPI_CHAR};
	MPI_Aint disp[ 4 ];

	MPI_Address( &obj[ 0 ].id, &disp[ 0 ] );
	MPI_Address( &obj[ 0 ].velocity, &disp[ 1 ] );
	MPI_Address( &obj[ 0 ].type, &disp[ 2 ] );
	MPI_Address( &obj[ 0 ].description, &disp[ 3 ] );

	disp[ 3 ] -= disp[ 0 ];
	disp[ 2 ] -= disp[ 0 ];
	disp[ 1 ] -= disp[ 0 ];
	disp[ 0 ] = 0;

	MPI_Type_struct( 4, blocklen, disp, types, &A_type );
	MPI_Type_commit( &A_type );

	// TO -> 0
	//MPI_Gather( obj, 100, A_type,obj,100,A_type, 0, MPI_COMM_WORLD );

	// TO -> all
	MPI_Bcast( obj, 100, A_type, 0, MPI_COMM_WORLD );

	MPI_Type_free( &A_type );
	
	MPI_Finalize();
	
}
