#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include "sorting.h"
#include "mpi_sort.h"
#include "template.hpp"
#include "defs.h"

using namespace std;
using namespace std::chrono;

const int iter = 10;

void g( void( *f )( int*, int ), string s, string s1 ) {
	int N[3] = { 1'000,10'000,100'000 };

	unsigned *T = new unsigned[iter];

	int count;

	for ( int n : N ) {
		count = iter;
		while ( count-- ) {
			int * arr = new int[n];

			generate( arr, n );

			auto start = high_resolution_clock::now();
			f( arr, n );
			auto stop = high_resolution_clock::now();
			T[count] = duration_cast< microseconds >( stop - start ).count();
		}
		unsigned long long x = accumulate( T, T + iter, 0 );
		cout << s << " " << n << endl;
		cout << "Time taken by " << s1 << " function: " << x / iter << " microseconds" << '\n';
		cout << endl;
	}
	delete[] T;
}

void gg() {
	string s = "quick", s1 = "normal";
	int N[3] = { 1'000,10'000,100'000 };

	unsigned *T = new unsigned[iter];

	int count;

	for ( int n : N ) {
		count = iter;
		while ( count-- ) {
			int * arr = new int[n];

			generate( arr, n );

			auto start = high_resolution_clock::now();
			quick::quick_sort( arr, 0, n - 1 );
			auto stop = high_resolution_clock::now();
			T[count] = duration_cast< microseconds >( stop - start ).count();
		}
		unsigned long long x = accumulate( T, T + iter, 0 );
		cout << s << " " << n << endl;
		cout << "Time taken by " << s1 << " function: " << x / iter << " microseconds" << '\n';
		cout << endl;
	}
	delete[] T;
}

void ggg() {
	int n = 100000;
	int * arr = new int[n];

	generate( arr, n );

	auto start = high_resolution_clock::now();
	quick_sort( arr,0, n-1 );
	auto stop = high_resolution_clock::now();
	cout << "Time taken by " << "quick" << " function: " << duration_cast< microseconds >( stop - start ).count() << " microseconds" << '\n';

}

int main2() {

	//fstream os( "insertion.txt" );

	//g( insertion::insertion_sort, "insertion","normal" );

	//g( insertion_sort, "insertion","template" );

	//g( quick::quick_sort, "quick", "normal" );
	//g( shell_sort, "shell", "template" );

	ggg();



	/*generate( arr, n );

	{
		START;

		insertion_sort<int>( arr, n );

		STOP;

		PRINT( "template" );
	}*/

	//file.START();
	//sort( argc, argv );
	//file.STOP();
	//file.PRINT( "mpi" );

	return 0;




}
