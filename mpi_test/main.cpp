#include <iostream>
#include <string>
//#include "mpi.h"
#include "../../../../../../Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h"

void generate( int*, const int& );
void initArray( int*, int*, const int& );
void print( int*, const int& );
int findMax( int*, const int& );

int main0( int argc, char* argv[] ) {
	const int maximum_message_length = 80;
	const int master_rank = 0;
	int count, miniArrCount, * array;
	MPI_Status status;
	int my_rank;
	int num_procs;
	int destination;
	int mpi_error;

	if ( mpi_error = MPI_Init( &argc, &argv ) ) {
		std::cerr << "ERROR1" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}

	if ( mpi_error = MPI_Comm_rank( MPI_COMM_WORLD, &my_rank ) ) {
		std::cerr << "ERROR2" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}

	if ( mpi_error = MPI_Comm_size( MPI_COMM_WORLD, &num_procs ) ) {
		std::cerr << "ERROR3" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}


	if ( my_rank == master_rank ) {
		std::cout << "Input count: ";
		std::cin >> count;

		array = new int[count];
		generate( array, count );
		print( array, count );

		destination = master_rank;

		miniArrCount = count / num_procs;
		int* miniArr = new int[miniArrCount];

		for ( int i = 1; i < num_procs; ++i ) {
			initArray( array + ( i - 1 ) * ( miniArrCount ), miniArr, miniArrCount );

			if ( mpi_error = MPI_Send( miniArr, miniArrCount, MPI_INT, i, 0, MPI_COMM_WORLD ) ) {
				std::cout << "ERROR4" << std::endl;
				MPI_Abort( MPI_COMM_WORLD, mpi_error );
			}
		}

		int max = INT_MIN;

		if ( count = count % num_procs ) {
			initArray( array + ( num_procs - 1 ) * miniArrCount, miniArr, count );
			max = findMax( miniArr, count );
		}

		for ( int i = 1, temp; i < num_procs; ++i ) {
			if ( mpi_error = MPI_Recv( &temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status ) ) {
				std::cout << "ERROR7" << std::endl;
				MPI_Abort( MPI_COMM_WORLD, mpi_error );
			}

			if ( temp > max )
				max = temp;
		}

		std::cout << "Max: " << max << std::endl;
	}
	else {
		MPI_Probe( 0, 0, MPI_COMM_WORLD, &status );
		MPI_Get_count( &status, MPI_INT, &miniArrCount );
		int* miniArr = new int[miniArrCount];

		if ( mpi_error = MPI_Recv( miniArr, miniArrCount, MPI_INT, 0, 0, MPI_COMM_WORLD, &status ) ) {
			std::cout << "ERROR5" << std::endl;
			MPI_Abort( MPI_COMM_WORLD, mpi_error );
		}

		std::cout << my_rank << "has received successfully" << std::endl;

		int max = findMax( miniArr, miniArrCount );

		if ( mpi_error = MPI_Send( &max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD ) ) {
			std::cout << "ERROR6" << std::endl;
			MPI_Abort( MPI_COMM_WORLD, mpi_error );
		}
	}

	if ( mpi_error = MPI_Finalize() ) {
		std::cout << "ERROR8" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}
	else {
		std::cout << "Program executed successfully" << std::endl;
	}
}

void generate( int* arr, const int& count ) {
	for ( int i = 0; i < count; ++i ) {
		arr[i] = rand() % RAND_MAX;
	}
}

void initArray( int* oldArr, int* newArr, const int& count ) {
	for ( int i = 0; i < count; ++i ) {
		newArr[i] = oldArr[i];
	}
}

void print( int* arr, const int& count ) {
	std::cout << "/////////////////////////////////////\n\n" << std::endl;
	for ( int i = 0; i < count; ++i ) {
		if ( i % 10 == 0 )
			std::cout << '\n';

		std::cout << arr[i] << '\t';
	}
}

int findMax( int* arr, const int& count ) {
	int max = arr[0];

	for ( int i = 1; i < count; ++i )
		if ( arr[i] > max )
			max = arr[i];

	return max;
}
