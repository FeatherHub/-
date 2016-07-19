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

//source�κ��� �� vertex������ �ִܰŸ��� ���̺��� �̿��ؼ� ����Ѵ�
int ShortestPathDCG::BottomUp(Vertex* s, Vertex* d, int vertexNum)
{
	//vertexNum * vertexNum 2���� ���̺� ����
	Vertex*** table = new Vertex**[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		table[i] = new Vertex*[vertexNum];
	}

	//���̺��� ��� ���Ҹ� nullptr�� �ʱ�ȭ
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			table[i][j] = nullptr;
		}
	}

	//Initialization
	s->ShortestPathWeight(0);
	table[s->Id()][0] = s;

	for (int step = 0; step < vertexNum-1; step++)
	{
		for (int vertexId = 0; vertexId < vertexNum; vertexId++)
		{
			if (table[vertexId][step] != nullptr)
			{
				auto& curV = table[vertexId][step];

				auto& edgeList = curV->EdgeToOtherList();
				for (auto& e = edgeList.begin(); e != edgeList.end(); ++e)
				{
					auto neighborV = (*e)->TargetV();

					int shortesPath = INT_MAX;
					int oldRes = INT_MAX;

					//�̹� ���� ���� ������
					if (table[neighborV->Id()][step + 1] != nullptr)
					{
						//���ϱ� ���� �����´�
						oldRes = table[neighborV->Id()][step + 1]->ShortestPathWeight();
					}

					int newRes = curV->ShortestPathWeight() + (*e)->Val();

					shortesPath = min(oldRes, newRes);

					//�ִܰŸ��� ���� ���ŵ� ���̸� vertex�� �� ����
					if (shortesPath == newRes)
					{
						neighborV->ShortestPathWeight(shortesPath);
					}

					table[neighborV->Id()][step + 1] = neighborV;
				}
			}
		}
	}

	int shortest = INT_MAX;
	for (int step = 0; step < vertexNum; step++)
	{
		if (table[d->Id()][step] != nullptr)
		{
			int tmp = (table[d->Id()][step])->ShortestPathWeight();
			shortest = min(tmp, shortest);
		}
	}

	return shortest;
}
