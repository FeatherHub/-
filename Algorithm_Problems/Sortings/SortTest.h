#pragma
#include <vector>

// SortTest ���
// �׽�Ʈ ������	: �پ��� ������ �׽�Ʈ �����͸� �����Ѵ�
// ���� �׽�Ʈ	: ��� ���࿡ �󸶳� �ð��� �ɷȴ��� �����Ѵ�

class SortTest
{
public:
	SortTest();
	~SortTest();
	
	void TestAlgorithm(void sorter(int*, int), const char* algoName);

private:
	void ResetData();
	void PrintArray(const std::vector<int>& v);
	void TestSet(void sorter(int*, int), const std::vector<int>& v);
	bool IsSorted(int* arr, int n);
	
	std::vector<int> m_data_one;
	std::vector<int> m_data_two;
	std::vector<int> m_data_three;
	std::vector<int> m_data_identity;
	std::vector<int> m_data_asc;
	std::vector<int> m_data_desc;
	std::vector<int> m_data_random1;
	std::vector<int> m_data_random2;
};