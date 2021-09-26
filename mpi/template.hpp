#pragma once
#include <vector>


template < typename T >
void insertion_sort( T*arr, int n ) {
	T key;

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

template < typename T >
void shell_sort( T*arr, int n ) {

	for ( int gap = n / 2; gap > 0; gap /= 2 ) {
		for ( int i = gap; i < n; ++i ) {
			T temp = arr[i];

			int j;
			for ( j = i; j >= gap && arr[j - gap] > temp; j -= gap )
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}

template < typename T >
void selection_sort( T*arr, int n ) {
	int min_idx;

	for ( int i = 0; i < n - 1; i++ ) {
		min_idx = i;
		for ( int j = i + 1; j < n; j++ )
			if ( arr[j] < arr[min_idx] )
				min_idx = j;

		std::swap( arr[min_idx], arr[i] );
	}
}

template <typename T>
void quick_sort( T*arr, int low, int high ) {

	if ( low < high ) {
		T pivot = arr[high];
		int i = ( low - 1 );

		for ( int j = low; j <= high - 1; ++j ) {
			if ( arr[j] < pivot ) {
				++i;
				std::swap( arr[i], arr[j] );
			}
		}
		++i;
		std::swap( arr[i], arr[high] );

		quick_sort( arr, low, i - 1 );
		quick_sort( arr, i + 1, high );
	}
}


namespace vec {

template < typename T >
void insertion_sort( std::vector< T > &arr ) {
	T key;

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


template < typename T >
void shell_sort( std::vector< T > &arr ) {
	int n = arr.size();

	for ( int gap = n / 2; gap > 0; gap /= 2 ) {
		for ( int i = gap; i < n; ++i ) {
			T temp = arr[i];

			int j;
			for ( j = i; j >= gap && arr[j - gap] > temp; j -= gap )
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}


template < typename T >
void selection_sort( std::vector< T > &arr ) {
	int min_idx;

	for ( int i = 0; i < arr.size() - 1; i++ ) {
		min_idx = i;
		for ( int j = i + 1; j < arr.size(); j++ )
			if ( arr[j] < arr[min_idx] )
				min_idx = j;

		swap( arr[min_idx], arr[i] );
	}
}


template <typename T>
void quick_sort( std::vector< T > &arr, int low, int high ) {

	if ( low < high ) {
		T pivot = arr[high];
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
