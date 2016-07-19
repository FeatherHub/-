#pragma once

class Vertex;

class ShortestPathDAG
{
public:
	//DAG������ Single source shortest paths
	//Source ����, Desination�� Source�� �̵�
	//�ִ� �Ÿ� = ��� (���� Vertex ������ �ִܰŸ� + ���� Vertex�� ��)�� �� �ּ�
	int TopDown(Vertex* s, Vertex* d);
	
	//�� Vertex�� s�κ��� �ڽſ��Ա����� �ִܰ�θ� �����ϴ� ����� ������
	//�� ����� Memo�� Ȱ���Ѵ�
	int Memo(Vertex* s, Vertex* d);

	//Breadth First Search�� ����ϴ�
	//source ���� �̿��� �ְ� ����ϰ� �����ϰ� �ϸ鼭 destination���� �����Ѵ�
	//Ȥ�� queue�� ��� ������
	int BottomUp(Vertex* s, Vertex* d);

private:
	int min(int a, int b) { return a < b ? a : b; }
};