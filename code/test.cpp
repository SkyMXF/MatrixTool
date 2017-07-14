#include "MatrixTool.h"

int main()
{
	Mat A(3, 3);
	A.data[0] = 1;
	A.data[1] = 3;
	A.data[2] = 5;
	A.data[3] = 3;
	A.data[4] = 61;
	A.data[5] = 4;
	A.data[6] = 4.2;
	A.data[7] = 8;
	A.data[8] = 1;

	Mat invA(3, 3);
	MatrixTool tools;
	
	//time_t startTime = time(0);
	tools.Gauss(invA, A);
	//time_t endTime = time(0);

	tools.coutMat(A);
	cout << endl;
	tools.coutMat(invA);
	//cout << "\n" << endTime - startTime << endl;

	system("pause");
	return 0;
}