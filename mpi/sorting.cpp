#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>

#include "defs.h"

using namespace std;

void print( vector< int > &vec ) {
	for_each( vec.begin(), vec.end(), []( int &x ) { cout << x << " "; } );
	cout << endl;
}

void print( int * arr, int n ) {
	for_each( arr, arr + n, []( int &x ) { cout << x << " "; } );
	cout << endl;
}

void generate( vector<int>& vec ) {

	srand( time( nullptr ) );
	for ( int& x : vec ) {
		x = rand() % vec.size();
	}
}

void generate( int*arr, int n ) {
	srand( time( nullptr ) );
	for_each( arr, arr + n, [&]( int &x ) { x = rand() % n; } );
}

namespace shell {

void shell_sort( vector< int > &arr ) {
	int n = arr.size();

	for ( int gap = n / 2; gap > 0; gap /= 2 ) {
		for ( int i = gap; i < n; ++i ) {
			int temp = arr[i];

			int j;
			for ( j = i; j >= gap && arr[j - gap] > temp; j -= gap )
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}

void shell_sort( int *arr, int n ) {

	for ( int gap = n / 2; gap > 0; gap /= 2 ) {
		for ( int i = gap; i < n; ++i ) {
			int temp = arr[i];

			int j;
			for ( j = i; j >= gap && arr[j - gap] > temp; j -= gap )
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}

}

namespace quick {
void quick_sort( int * arr, int low, int high ) {

	if ( low < high ) {
		int pivot = arr[high];
		int i = ( low - 1 );

		for ( int j = low; j <= high - 1; ++j ) {
			if ( arr[j] < pivot ) {
				++i;
				swap( arr[i], arr[j] );
			}
		}
		++i;
		swap( arr[i], arr[high] );

		quick_sort( arr, low, i - 1 );
		quick_sort( arr, i + 1, high );
	}
}
void quick_sort( vector< int > &arr, int low, int high ) {

	if ( low < high ) {
		int pivot = arr[high];
		int i = ( low - 1 );

		for ( int j = low; j <= high - 1; ++j ) {
			if ( arr[j] < pivot ) {
				++i;
				swap( arr[i], arr[j] );
			}
		}
		++i;
		swap( arr[i], arr[high] );

		quick_sort( arr, low, i - 1 );
		quick_sort( arr, i + 1, high );
	}
}



}

namespace insertion {
void insertion_sort( int*arr, int n ) {
	int key;

	for ( int i = 1; i < n; ++i ) {
		key = arr[i];
		int j = i - 1;
		while ( j >= 0 && key < arr[j] ) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}
void insertion_sort( vector< int > &arr ) {
	int key;

	for ( int i = 1; i < arr.size(); ++i ) {
		key = arr[i];
		int j = i - 1;
		while ( j >= 0 && key < arr[j] ) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}


}

namespace selection {
void selection_sort( int*arr, int n ) {
	int min_idx;

	for ( int i = 0; i < n - 1; i++ ) {
		min_idx = i;
		for ( int j = i + 1; j < n; j++ )
			if ( arr[j] < arr[min_idx] )
				min_idx = j;


		swap( arr[min_idx], arr[i] );
	}
}
void selection_sort( vector< int > &arr ) {
	int min_idx;

	for ( int i = 0; i < arr.size() - 1; i++ ) {
		min_idx = i;
		for ( int j = i + 1; j < arr.size(); j++ )
			if ( arr[j] < arr[min_idx] )
				min_idx = j;


		swap( arr[min_idx], arr[i] );
	}
}


}

int merge( int* m_arr, int m_size, int* arr, int arr_size ) {
	int m_copy_pos = 0, m_pos = 0, arr_pos = 0;

	int* m_copy = new int[m_size];
	std::copy( m_arr, m_arr + m_size, m_copy );

	while ( m_copy_pos != m_size && arr_pos != arr_size ) {
		if ( m_copy[m_copy_pos] < arr[arr_pos] ) {
			m_arr[m_pos++] = m_copy[m_copy_pos++];
		}
		else {
			m_arr[m_pos++] = arr[arr_pos++];
		}
	}

	if ( m_copy_pos == m_size ) {
		while ( arr_pos != arr_size )
			m_arr[m_pos++] = arr[arr_pos++];
	}
	else {
		while ( m_copy_pos != m_size )
			m_arr[m_pos++] = m_copy[m_copy_pos++];
	}

	delete[]m_copy;

	return m_pos;
}

void copy_arr( int* oldArr, int* newArr, const int& count ) {
	for ( int i = 0; i < count; ++i ) {
		newArr[i] = oldArr[i];
	}
}
