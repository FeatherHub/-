#include "ShortestPathProblem.h"
#include "Vertex.h"

int ShortestPathProblem::TopDown(Vertex* s, Vertex* d)
{
	if (d == s)
		return 0;

	int shortest = INT_MAX;

	//�ڽ��� ����Ű�� edge�κ��� vertex�� ���Ѵ�
	auto& edgeToMeList = d->EdgeToMeList();
	for (auto& edgeToMe = edgeToMeList.begin(); edgeToMe != edgeToMeList.end(); ++edgeToMe)
	{
		int res = TopDown(s, (*edgeToMe)->StartV()) + (*edgeToMe)->Val();

		shortest = min(res, shortest);
	}

	return shortest;
}
