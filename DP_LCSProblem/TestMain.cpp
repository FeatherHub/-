#include "LCSProblem.h"

#include <iostream>
using namespace std;

int main()
{
	char str1[]{ "abcbdab" };
	char str2[]{ "bdcaba" };

	//null-���� ���� ũ�� : s 
	//null-������ ���� ũ�� : s-1 <- strlen(...), size(...) ���� ���
	//null-������ ������ ���� �ε��� : s-2

	int tdRes = LCSProblem::TopDown(str1, strlen(str1) - 1,
									str2, strlen(str2) - 1);

	cout << tdRes << endl;

	int mmRes = LCSProblem::Memo(str1, strlen(str1) - 1,
									str2, strlen(str2) - 1);

	cout << mmRes << endl;

	int buRes = LCSProblem::BottomUp(str1, strlen(str1) - 1,
										str2, strlen(str2) - 1);

	cout << buRes << endl;

	return 0;
}