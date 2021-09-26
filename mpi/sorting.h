#pragma once
#include <vector>

int merge( int* m_arr, int m_size, int* arr, int arr_size );
void copy_arr( int* oldArr, int* newArr, const int& count );

void print( std::vector< int > &vec );
void print( int * arr, int n );
void generate( std::vector<int>& vec );
void generate( int*arr, int n );
namespace shell {
void shell_sort( std::vector< int > &arr );
void shell_sort( int *arr, int n );
}
namespace quick {
void quick_sort( int * arr, int low, int high );
void quick_sort( std::vector< int > &arr, int low, int high );
}
namespace insertion {
void insertion_sort( int*arr, int n );
void insertion_sort( std::vector< int > &arr );
}
namespace selection {
void selection_sort( int*arr, int n );
void selection_sort( std::vector< int > &arr );
}
