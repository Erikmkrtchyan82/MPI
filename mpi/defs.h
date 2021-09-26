#if 0
#pragma once

#include <chrono>
#include <string>
#include <fstream>
using namespace std::chrono;

static struct file {

	steady_clock::time_point start;
	steady_clock::time_point stop;
	std::ofstream f{"a.txt"};

	
	void START() {
		start = high_resolution_clock::now();
	}

	void STOP() {
		stop = high_resolution_clock::now();
	}

	void PRINT( std::string x ) {
		auto duration = duration_cast< microseconds >( stop - start );
		f << "Time taken by " << x << " function: " << duration.count() << " microseconds" << '\n';
	}

	void print(std::string s) {
		f << s<<'\n';
	}

	~file() {
		f.close();
	}
	
} file;


#endif