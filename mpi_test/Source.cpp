#include <iostream>
//#include <mpi.h>

#include "../../../../../../Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h"
#define N 65

int rank, size;
double start_time;
double end_time;

int y, x, i, port1, port2, port3;
int check = 0;       
int signal = 0;      

MPI_Status status;
MPI_Request request;

int main2( int argc, char *argv[] ) {
    MPI_Init( &argc, &argv ); 
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 

    if ( rank == 0 ) {                 
        start_time = MPI_Wtime();
        printf( "2\n" );                
        port1 = ( N / ( size - 1 ) );   

        for ( i = 1; i < size - 1; i++ ) {          
            port2 = port1 * i;                      
            port3 = ( ( i + 1 ) * port1 ) - 1;      
            MPI_Isend( &port2, 1, MPI_INT, i, 100, MPI_COMM_WORLD, &request );
            MPI_Isend( &port3, 1, MPI_INT, i, 101, MPI_COMM_WORLD, &request );
        }

        port2 = ( size - 1 ) * port1; port3 = N;     
        MPI_Isend( &port2, 1, MPI_INT, ( size - 1 ), 100, MPI_COMM_WORLD, &request );
        MPI_Isend( &port3, 1, MPI_INT, ( size - 1 ), 101, MPI_COMM_WORLD, &request );

        for ( x = 3; x < port1; x = x + 2 ) {
            check = 0;
            for ( y = 3; y <= x / 2; y = y + 2 ) {
                if ( x % y == 0 ) { check = 1; break; }
            }
            if ( check == 0 ) printf( "%d\n", x );
        }
    }

    if ( rank > 0 ) {

        MPI_Recv( &port2, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status );
        MPI_Recv( &port3, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status );
        if ( port2 % 2 == 0 ) port2++;
        for ( x = port2; x <= port3; x = x + 2 ) {
            check = 0;
            for ( y = 3; y <= x / 2; y = y + 2 ) {
                if ( x % y == 0 ) { check = 1; break; }
            }
            if ( check == 0 ) printf( "%d\n", x );
        }
        signal = rank;
        MPI_Isend( &signal, 1, MPI_INT, 0, 103, MPI_COMM_WORLD, &request );

    }

    if ( rank == 0 ) {
        for ( i == 1; i < size; i++ ) {
            MPI_Recv( &signal, 1, MPI_INT, i, 103, MPI_COMM_WORLD, &status );
        }
        end_time = MPI_Wtime();
        printf( "\nRunning Time = %f \n\n", end_time - start_time );
    }
    MPI_Finalize();
    return 0;
}