#include "ShortestPathDAG.h"
#include "Vertex.h"
#include <queue>

int ShortestPathDAG::TopDown(Vertex* s, Vertex* d)
{
	if (d == s)
		return 0;

	int shortest = INT_MAX;

	//�ڽ��� ����Ű�� edge�κ��� �Ž��� �ö� vertex�� ���Ѵ�
	auto& edgeToMeList = d->EdgeToMeList();
	for (auto& edgeToMe = edgeToMeList.begin(); edgeToMe != edgeToMeList.end(); ++edgeToMe)
	{
		int res = TopDown(s, (*edgeToMe)->StartV()) + (*edgeToMe)->Val();

		shortest = min(res, shortest);
	}

	return shortest;
}

int ShortestPathDAG::Memo(Vertex* s, Vertex* d)
{
	if (s == d)
		return 0;

	if (d->ShortestPathWeight() != Vertex::NOT_CALCULATED)
		return d->ShortestPathWeight();

	int shortestPath = INT_MAX;

	auto& edgeToMeList = d->EdgeToMeList();
	for (auto& edgeToMe = edgeToMeList.begin(); edgeToMe != edgeToMeList.end(); ++edgeToMe)
	{
		int res = Memo(s, (*edgeToMe)->StartV()) + (*edgeToMe)->Val();
		
		shortestPath = min(res, shortestPath);
	}

	d->ShortestPathWeight(shortestPath);

	return shortestPath;
}

int ShortestPathDAG::BottomUp(Vertex* s, Vertex* d)
{
	//�ҽ��� ť�� �ִ´�
	//ť�� ���鼭 �̿����� �ִ´�
	//�� V�� �ִܰŸ��� �����Ѵ�, ������ �ִ� ���� ���ؼ� ���� ������ �����Ѵ�

	s->ShortestPathWeight(0);

	std::queue<Vertex*> verticesToVisit;
	verticesToVisit.push(s);
	while (verticesToVisit.empty() == false)
	{
		auto& curV = verticesToVisit.back();
		verticesToVisit.pop();

		auto& adjEdgeList = curV->EdgeToOtherList();
		for (auto& e = adjEdgeList.begin(); e != adjEdgeList.end(); ++e)
		{
			auto neighborV = (*e)->TargetV();
			int neightborSP = neighborV->ShortestPathWeight();
			neightborSP = min(neightborSP, curV->ShortestPathWeight() + (*e)->Val());
			neighborV->ShortestPathWeight(neightborSP);

			verticesToVisit.push(neighborV);
		}
	}

	return d->ShortestPathWeight();
}
