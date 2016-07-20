#pragma once

class Matrix;

/* MCMP(Matrix Chain Multiplication Problem) */
class MCMP
{
public:
	//startIdx, endIdx�� ������ �����ϱ� ���� ������
	int TopDown(Matrix** matArr, int beginIdx, int endIdx);
	int Memo(Matrix** matArr, int matNum);
	int BottomUp(Matrix** matArr, int matNum);

private:
	int _Memo(Matrix** matArr, int** memo, int sIdx, int eIdx);
	int min(int a, int b) { return a < b ? a : b; }
private:
	enum { NOT_CALCED = -1 };
};