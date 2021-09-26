#include <iostream>
#include <mpi.h>

#include "../../../../../../Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h"

void findPrimes( int* arr, const int& count, int* primeArr, int& primesCount );

int main1( int argc, char* argv[] ) {
	const int master_rank = 0;
	const int count_i = 100, count_j = 150;
	int matrix[100][150], *primeArr, primesCount = 0;
	MPI_Status status;
	int my_rank, num_procs, mpi_error;


	if ( mpi_error = MPI_Init( &argc, &argv ) ) {
		std::cerr << "ERROR1" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}
	if ( mpi_error = MPI_Comm_size( MPI_COMM_WORLD, &num_procs ) ) {
		std::cerr << "Error: MPI_Init" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}
	if ( mpi_error = MPI_Comm_rank( MPI_COMM_WORLD, &my_rank ) ) {
		std::cerr << "ERROR2" << std::endl;
		MPI_Abort( MPI_COMM_WORLD, mpi_error );
	}

	if ( my_rank == master_rank ) {
		for ( int i = 0; i < count_i; ++i ) {
			for ( size_t j = 0; j < count_j; j++ ) {
				matrix[i][j] = rand() % RAND_MAX;
			}
		}

		for ( int i = 1; i < count_i; i++ ) {
			int* newArr = new int[count_j];
			for ( int j = 0; j < count_j; j++ ) {
				newArr[j] = matrix[i][j];
			}
			MPI_Send( newArr, count_j, MPI_INT, i, 0, MPI_COMM_WORLD );
		}

		for ( int i = 1; i < count_i; i++ ) {
			int chCount;
			MPI_Probe( MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
			MPI_Get_count( &status, MPI_INT, &chCount );

			int* newArr = new int[chCount];

			MPI_Recv( newArr, chCount, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );

			for ( int i = 0; i < chCount; i++ ) {
				primeArr[primesCount + i] = newArr[i];
			}
			primesCount += chCount;
		}


		for ( size_t j = 0; j < primesCount; j++ ) {
			std::cout << primeArr[j] << "\t";
		}

	}
	else {

		int chCount;
		MPI_Probe( MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
		MPI_Get_count( &status, MPI_INT, &chCount );
		int* newArr = new int[chCount];

		MPI_Recv( newArr, chCount, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );

		int* primes = new int[chCount];
		int count;
		findPrimes( newArr, chCount, primes, count );

		MPI_Send( primes, count, MPI_INT, 0, 0, MPI_COMM_WORLD );
	}


	MPI_Finalize();
	return 0;
}

void findPrimes( int* arr, const int& count, int* primeArr, int& primesCount ) {
	primesCount = 0;
	for ( int i = 0; i < count; i++ ) {
		bool isPrime = true;
		for ( int j = 2; j <= ( ( int )sqrt( arr[i] ) ); j++ ) {
			if ( arr[i] % j == 0 ) {
				isPrime = false;
				break;
			}
		}
		if ( isPrime ) {
			primeArr[primesCount] = arr[i];
			primesCount++;
		}
	}
}