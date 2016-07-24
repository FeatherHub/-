#include "Knapsack.h"
#include "Item.h"

int KnapSack::TopDown(Item* itemArr, int itemNum, int maxWeight)
{
	if (itemNum <= 0 || maxWeight <= 0)
		return 0;

	//���� �� ������ - max(���� ���, �� ���� ���) ���
	if (itemArr[itemNum - 1].Weight() <= maxWeight)
	{
		int includeCase = itemArr[itemNum - 1].Price() 
			+ TopDown(itemArr, itemNum - 1, maxWeight - itemArr[itemNum - 1].Weight());

		int notIncludeCase = TopDown(itemArr, itemNum - 1, maxWeight);

		return max(includeCase, notIncludeCase);
	}
	//���� �� ������ - �� ���� ��� ���
	else
	{
		return TopDown(itemArr, itemNum - 1, maxWeight);
	}
}

int KnapSack::Memo(Item* itemArr, int itemNum, int maxWeight)
{
	//row : weight [0,maxWeight] -> maxWeight+1
	//col : item id [0, itemNum) -> itemNum
	//memo[i][j] : accumulated price in selecting item j when maxWeight is i

	int** memo = new int*[maxWeight + 1];
	for (int i = 0; i <= maxWeight; i++)
		memo[i] = new int[itemNum];

	//init memo with NOT_CALCULATED
	for (int i = 0; i <= maxWeight; i++)
	{
		for (int j = 0; j < itemNum; j++)
		{
			memo[i][j] = NOT_CALCULATED;
		}
	}

	int res = _Memo(memo, itemArr, itemNum, maxWeight);

	for (int i = 0; i <= maxWeight; i++)
		delete[] memo[i];
	delete[] memo;

	return res;
}

int KnapSack::_Memo(int** memo, Item* itemArr, int itemNum, int maxWeight)
{
	if (itemNum <= 0 || maxWeight <= 0)
		return 0;

	if (memo[maxWeight][itemNum - 1] != NOT_CALCULATED)
		return memo[maxWeight][itemNum - 1];

	int res;

	if (itemArr[itemNum - 1].Weight() <= maxWeight)
	{
		int includeCase = itemArr[itemNum - 1].Price()
			+ TopDown(itemArr, itemNum - 1, maxWeight - itemArr[itemNum - 1].Weight());

		int notIncludeCase = TopDown(itemArr, itemNum - 1, maxWeight);

		res = max(includeCase, notIncludeCase);
	}
	else
	{
		res = TopDown(itemArr, itemNum - 1, maxWeight);
	}

	memo[maxWeight][itemNum - 1] = res;
	
	return res;
}

int KnapSack::BottomUp(Item* itemArr, int itemNum, int maxWeight)
{
	int** table = new int*[maxWeight + 1];
	for (int i = 0; i <= maxWeight; i++)
		table[i] = new int[itemNum];

	for (int i = 0; i <= maxWeight; i++)
	{
		for (int j = 0; j < itemNum; j++)
		{
			table[i][j] = NOT_CALCULATED;
		}
	}

	//�ʱⰪ ����
	//ù��° �������� �� ����
	table[0][0] = 0;
	//ù��° �������� ���� �� ������ ����
	if(table[itemArr[0].Weight()][0] <= maxWeight)
		itemArr[0].Price();

	//��� ���Կ� ���� ��� -> ���� ���� ���
	//�� ĭ�� �� ĭ�� ���� �����Ͽ� �ڽ��� �ְų� �� �ְų��ؼ� �ڱ� ĭ�� ä���
	for (int itemId = 1; itemId < itemNum; itemId++)
	{
		for (int curWeight = 0; curWeight <= maxWeight; curWeight++)
		{
			if (table[curWeight][itemId-1] != NOT_CALCULATED)
			{
				int availableWeight = maxWeight - curWeight;
				int curItemWeight = itemArr[itemId].Weight();
				int curItemPrice = itemArr[itemId].Price();

				//���� �� ���� �� ���� ���, ���� ���� ��ġ�� ����
				if (curItemWeight <= availableWeight)
				{
					//availableWeight�� index�� ����� �� �ֵ��� ��ȯ
					int availableIdx = maxWeight - availableWeight;
					table[availableIdx + curItemWeight][itemId] =
						table[curWeight][itemId - 1] + curItemPrice;
				}
				//�� �ִ� ���, ū ���̸� ���� ���� ��ġ�� ����
				table[curWeight][itemId] = max(table[curWeight][itemId],
					table[curWeight][itemId - 1]);
			}
		}
	}

	//������ ���� ���� �����ؼ� �ִ밪 ��ȯ
	int maxPrice = 0;
	for (int w = 0; w <= maxWeight; w++)
	{
		maxPrice = max(maxPrice, table[w][itemNum - 1]);
	}

	for (int i = 0; i <= maxWeight; i++)
		delete[] table[i];
	delete[] table;

	return maxPrice;
}