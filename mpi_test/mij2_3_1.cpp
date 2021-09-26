#include <iostream>
#include "mpi.h"

using namespace std;

const int n = 200, m = 120;

void print(int* Array, const int count);

void generate(int arr[n][m], const int& rows, const int& columns);

int main(int argc, char* argv[]) {
	int root = 0;
	int size, buf[n][m];
	int rank;
	int* displs, * rcounts, * rbuf;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	const int stride = ( rank + 5 ) * 10;
	int *sendbuf=new int[ stride ];
	
	rbuf = new int[ size * stride ];
	displs = new int[size];
	rcounts = new int[size];

	generate(buf, n, m);

	for(int i=0;i<stride;++i) {
		sendbuf[i] = buf[rank][i];
	}
	
	for(int i=0;i<size;++i) {
		displs[i] = i * stride;
		rcounts[i] = stride;
	}

	MPI_Gatherv(sendbuf, stride, MPI_INT, rbuf, rcounts, 
		displs, MPI_INT, root, MPI_COMM_WORLD);

	if(root==rank) {
		print(rbuf, size * stride);
	}

	MPI_Finalize();
}

void print(int* Array, const int count){
	for(int i=0;i<count;++i) {
		if (i % (n+1) == 0)
			cout << endl;
		cout << Array[i];
	}
}

void generate(int arr[n][m], const int& rows, const int& columns) {
	for(int i=0;i<rows;++i) {
		for(int j=0;j<columns;++j) {
			arr[i][j] = rand() % 10000;
		}
	}
}

