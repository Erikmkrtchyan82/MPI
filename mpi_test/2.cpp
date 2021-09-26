#include <iostream>
#include "mpi.h"
#define MSMPI_NO_DEPRECATE_20
#pragma warning(suppress : 4996)

struct Complex
{
	int re, im;

	Complex(int x = 0, int y = 0) : re(x), im(y) {}

	Complex& operator*=(const Complex& other)
	{
		re = re * other.re - im * other.im;
		im = re * other.im - im * other.re;

		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Complex& num)
{
	os << num.re << (num.im > 0 ? " + " : " ") << num.im <<"i ";
	
	return os;
}

struct Complex Complex_num;

void generate(Complex arr[100], int rank);
void complexMultiply(Complex* invec, Complex* inoutvec, int* len, MPI_Datatype* dtype);
void print(Complex arr[5]);

int main(int argc, char** argv)
{
	MPI_Op MPI_Complex_Multiply;

	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Datatype MPI_Complex, 
		types[2] = { MPI_INT, MPI_INT };
	
	MPI_Aint displacements[2];
	int blockLen[2] = { 1, 1 };

	MPI_Address(&Complex_num.re, &displacements[1]);
	MPI_Address(&Complex_num.im, &displacements[2]);

	MPI_Type_create_struct(2, blockLen, displacements, types, &MPI_Complex);
	MPI_Type_commit(&MPI_Complex);

	Complex sendBuf[5], rcvBuf[5];
	generate(sendBuf, rank);
	
	MPI_Op_create((MPI_User_function*)complexMultiply, 0, &MPI_Complex_Multiply);
	MPI_Reduce(sendBuf, rcvBuf, 5, MPI_Complex, MPI_Complex_Multiply,0, MPI_COMM_WORLD);

	print(sendBuf);
	print(rcvBuf);

	MPI_Finalize();

	return 0;
}

void complexMultiply(Complex* invec, Complex* inoutvec, int* len, MPI_Datatype* dtype)
{
	for (int i = 0; i < *len; ++i)
		inoutvec[i] *= invec[i];
}

void generate(Complex arr[5], int rank)
{
	for (int i = 0; i < 5; ++i)
	{
		arr[0].im = rank * 1000 + i;
		arr[0].re = rank * 1000 + i;
	}
}

void print(Complex arr[5])
{
	for (int i = 0; i < 5; ++i)
		std::cout << arr[i] << ' ';

	std::cout << "\n\n";
}
