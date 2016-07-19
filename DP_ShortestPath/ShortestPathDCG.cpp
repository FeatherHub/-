#include "ShortestPathDCG.h"
#include "Vertex.h"

int ShortestPathDCG::TopDownMemod(Vertex* s, Vertex* d, int vertexNum)
{
	//vertexNum * vertexNum 2���� ���̺� ����
	int** memo = new int*[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		memo[i] = new int[vertexNum];
	}
	
	//���̺��� ��� ���Ҹ� NOT_CALCULATED�� �ʱ�ȭ
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			memo[i][j] = Vertex::NOT_CALCULATED;
		}
	}

	int res = _TopDownMemod(s, d, memo, vertexNum);

	//���̺� ����
	for (int i = 0; i < vertexNum; i++)
	{
		//�� ����
		delete[] memo[i];
	}
	//�� ����
	delete[] memo;

	return res;
}

//d�κ��� s�� �Ž�������
//s�� ������ �Ǹ� �����Ѵ�

//min( �ִܰŸ�(before d) + d�� ����Ű�� edge�� �� )

int ShortestPathDCG::_TopDownMemod(Vertex* s, Vertex* d, int** memo, int stepLen)
{
	if (s == d || stepLen == 0)
		return 0;

	int shortestPath = INT_MAX;
	int neightborId = -1;

	//�ڱ⸦ ����Ű�� �̿��鿡 �����Ѵ�
	auto& edgeToMeList = d->EdgeToMeList();
	for (auto& e = edgeToMeList.begin(); e != edgeToMeList.end(); ++e)
	{
		auto neighborV = (*e)->StartV();
		int res;
		
		if (memo[neighborV->Id()][stepLen - 1] != Vertex::NOT_CALCULATED)
		{
			res = memo[neighborV->Id()][stepLen - 1] + (*e)->Val();
		}
		else
		{
			res = _TopDownMemod(s, neighborV, memo, stepLen - 1) + (*e)->Val();
		}

		shortestPath = min(res, shortestPath);
		neightborId = neighborV->Id();
	}

	memo[neightborId][stepLen - 1] = shortestPath;

	return shortestPath;
}

int ShortestPathDCG::BottomUp(Vertex* s, Vertex* d, int vertexNum)
{
	return 0;
}
