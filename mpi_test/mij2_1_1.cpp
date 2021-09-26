#include <iostream>
#include "mpi.h"

using namespace std;

int main( int argc, char *argv[] ) {

	int rank, size;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	int a, position;
	double b;
	char buf[ 100 ];

	if ( rank == 0 ) {
		cin >> a >> b;

		MPI_Pack( &a, 1, MPI_INT, buf, 100, &position, MPI_COMM_WORLD );
		MPI_Pack( &b, 1, MPI_DOUBLE, buf, 100, &position, MPI_COMM_WORLD );
		MPI_Bcast( buf, 100, MPI_CHAR, 0, MPI_COMM_WORLD );
	}
	else {
		position = 0;
		MPI_Unpack( buf, 100, &position, &a, 1, MPI_INT, MPI_COMM_WORLD );
		MPI_Unpack( buf, 100, &position, &b, 1, MPI_DOUBLE, MPI_COMM_WORLD );
		cout << rank << ": " << a << ", " << b << endl;
	}
	MPI_Finalize();
}
