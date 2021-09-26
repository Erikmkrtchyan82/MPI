#include "mpi_sort.h"



#include <chrono>
#include <iostream>

#include <mpi.h>

#include "sorting.h"
#include "defs.h"

using namespace insertion;
using namespace shell;
using namespace quick;
using namespace selection;
using namespace std;


int main( int argc, char* argv[] ) {
	
	const int master_rank = 0;
	int my_rank, num_procs, miniArrCount, count, *arr;
	int destination = 0;
	MPI_Status status;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &my_rank );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procs );

	if ( my_rank == master_rank ) {
		std::cout << "Input count: ";
		std::cin >> count;

		
		arr = new int[count];

		generate( arr, count );


		destination = master_rank;

		miniArrCount = count / ( num_procs );
		int* miniArr = new int[miniArrCount];

		count -= ( num_procs - 1 ) * miniArrCount;

		

		auto start = chrono::high_resolution_clock::now();


		
		for ( int i = 1; i < num_procs; ++i ) {
			copy_arr( arr + count + ( i - 1 ) * ( miniArrCount ), miniArr, miniArrCount );
			MPI_Send( miniArr, miniArrCount, MPI_INT, i, 0, MPI_COMM_WORLD );
		}

#if 0
#define in
		string s = "insertion";
		insertion_sort( arr, count );	//	[ 2.1 ]
#endif
#if 0
#define sh
		string s = "shell";
	    shell_sort( arr, count );		//	[ 2.2 ]
#endif
#if 0
#define se
		string s = "selection";
		selection_sort( arr, count );	//	[ 2.3 ]
#endif
#if 1
#define qu
		string s = "quick";
		quick_sort( arr,0, count-1 );	//	[ 2.4 ]
#endif


		
		for ( int i = 1; i < num_procs; ++i ) {
			MPI_Recv( miniArr, miniArrCount, MPI_INT, i, 0, MPI_COMM_WORLD, &status );
			count = merge( arr, count, miniArr, miniArrCount );
		}



		auto stop = chrono::high_resolution_clock::now();
		cout << "Time taken by " << s << " function: " << chrono::duration_cast<chrono::microseconds >( stop - start ).count() << " microseconds" << '\n';

		

		delete[]arr;
		delete[]miniArr;


	}
	else {
		MPI_Probe( 0, 0, MPI_COMM_WORLD, &status );
		MPI_Get_count( &status, MPI_INT, &miniArrCount );
		int* buf = new int[miniArrCount];

		MPI_Recv( buf, miniArrCount, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );

#ifdef in
		insertion_sort( buf, miniArrCount );		//	[2.1]
#endif
#ifdef sh
		shell_sort( buf, miniArrCount );			//	[2.2]
#endif
#ifdef se
		selection_sort( buf, miniArrCount );		//	[2.3]
#endif
#ifdef qu
		quick_sort( buf, 0, miniArrCount - 1 );	//	[2.4]
#endif
		
		MPI_Send( buf, miniArrCount, MPI_INT, 0, 0, MPI_COMM_WORLD );

		delete[]buf;
	}

	
	MPI_Finalize();
	return 0;
}

