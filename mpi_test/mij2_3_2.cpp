#include <iostream>
#include "mpi.h"

using namespace std;

struct complex_t {
	int re;
	int im;
} Complex_num;


void complexDevide( complex_t *invec, complex_t *inoutvec, int *n, MPI_Datatype *type ) {
	complex_t c;
	for(int i=0;i<*n;++i ) {
		c.re = ( inoutvec[ i ].re * invec[ i ].re + inoutvec[ i ].im * invec[ i ].im ) /
			(pow(inoutvec[i].re,2)+ pow( inoutvec[ i ].im, 2 ) );
		c.im= ( inoutvec[ i ].re * invec[ i ].im - inoutvec[ i ].im * invec[ i ].re ) /
			( pow( inoutvec[ i ].re, 2 ) + pow( inoutvec[ i ].im, 2 ) );
		inoutvec[ i ] = c;
	}
}

//
//void complexMultiply( complex_t *invec, complex_t *inoutvec, int *n, MPI_Datatype *type ) {
//
//	complex_t c;
//	for (int i = 0; i < *n; ++i ) {
//		c.re = ( inoutvec[ i ].re * invec[ i ].re ) - ( inoutvec[ i ].im * invec[ i ].im );
//		c.im = ( inoutvec[ i ].re * invec[ i ].im ) + ( inoutvec[ i ].im * invec[ i ].re );
//		inoutvec[i] = c;
//	}
//}

void generate( complex_t arr[ 5 ], int rank ) {
	for ( int i = 0; i < 5; ++i ) {
		arr[ 0 ].im = rank * ( rand() % 1000 ) + ( rand() % 1000 );
		arr[ 0 ].re = rank * ( rand() % 1000 ) + ( rand() % 1000 );
	}
}

void print( complex_t arr[ 5 ] ) {
	for ( int i = 0; i < 5; ++i ) {
		std::cout << arr[ i ].re << " + " << arr[ i ].im << std::endl;
	}
	std::cout << "\n\n";
}

int main( int argc, char *argv[] ) {
	MPI_Op MPI_Complex_Devide;

	int rank;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	MPI_Datatype MPI_Complex,
		types[ 2 ] = { MPI_INT, MPI_INT };

	MPI_Aint displs[ 2 ];
	int blockLen[ 2 ] = { 1, 1 };

	MPI_Address( &Complex_num.re, &displs[ 1 ] );
	MPI_Address( &Complex_num.im, &displs[ 2 ] );

	displs[ 1 ] -= displs[ 0 ];
	displs[ 0 ] = 0;
	
	MPI_Type_struct( 2, blockLen, displs, types, &MPI_Complex );
	MPI_Type_commit( &MPI_Complex );

	complex_t sendBuf[ 5 ], rcvBuf[ 5 ];
	generate( sendBuf, rank );

	MPI_Op_create( (MPI_User_function *)complexDevide, 0, &MPI_Complex_Devide );
	MPI_Reduce( sendBuf, rcvBuf, 5, MPI_Complex, MPI_Complex_Devide, 0, MPI_COMM_WORLD );

	print( sendBuf );
	print( rcvBuf );

	MPI_Finalize();

	return 0;
}
