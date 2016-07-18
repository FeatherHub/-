#pragma once

class Vertex;

class ShortestPathProblem
{
public:
	//DAG������ Single source shortest paths
	//Source ����, Desination�� Source�� �̵�
	//�ִ� �Ÿ� = ��� (���� Vertex ������ �ִܰŸ� + ���� Vertex�� ��)�� �� �ּ�
	int TopDown(Vertex* s, Vertex* d);
	
	//int Memo()
	//int BottomUp()
private:
	int min(int a, int b) { return a < b ? a : b; }
};