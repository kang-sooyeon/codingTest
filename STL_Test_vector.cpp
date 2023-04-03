#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 10

using namespace std;

struct Point {
	int r;
	int c;
};

struct Block {
	vector<Point> p;
	int size;
};


vector<int> v;
vector<Block> blocks;


bool isEven(int num)
{
	if (num % 2)
		return false;
	else
		return true;
}


void print()
{
	for (auto& val : v) {
		cout << val << " ";
	}
	cout << endl;
}



void print_block()
{
	for (auto &block : blocks) {
		cout << block.size << " ";
	}
	cout << endl;
}

bool isThree(Block& b)
{
	if (b.size == 3)
		return true;
	else
		return false;
}

bool isLessThan(Block& b1, Block& b2)
{
	if (b1.size < b2.size)
		return true;
	else
		return false;
}

int main()
{
	
	
	// vector 테스트
	for (int i = 10; i >= 1; i--)
	{
		v.push_back(i);
	}
	print();

	// 기본 오름차순 정렬
	//sort(v.begin(), v.end());

	// 내림차순 정렬
	// sort(vec.begin(), vec.end(), greater<int>());

	//remove_if(v.begin(), v.end(), isEven);		// 삭제 후 전체 길이 그대로..
	//v.erase(remove_if(v.begin(), v.end(), isEven), v.end());  // 삭제 후 전체 길이 조정
	//v.erase(remove(v.begin(), v.end(), 5), v.end());  // 삭제 후 전체 길이 조정


	//v.insert(v.begin(), 100);

	//vector<int> v2(2, 200);
	//auto iter2 = v.insert(v.begin(), v2.begin(), v2.end());	// v의 맨앞 원소에 v2 삽입후, 새로 삽입된 앞 위치 가짐.

	//*iter2 = 300;
	//v.erase(v.begin(), v.begin() + 3);	// 0~2 원소 삭제


	// ** unique
	// ***인접한 같은 원소 유일하게만듬(인접하지 않은 중복은 제거 안함), 따라서 모든 원소를 중복제거하기 위해서는 정렬후 사용.
	// 종복원소 제거후, 전체 길이 조정
	//sort(v.begin(), v.end());
	//v.erase(unique(v.begin(), v.end()), v.end());	

	print();
	

	for (int i = 0; i < 2; i++)
	{
		Block b;
		b.size = 3;
		blocks.push_back(b);
	}


	for (int i = 0; i < 2; i++)
	{
		Block b;
		b.size = 4;
		blocks.push_back(b);
	}


	print_block();
	//blocks.erase(remove_if(blocks.begin(), blocks.end(), isThree), blocks.end());
	// 
	//sort(blocks.begin(), blocks.end(), isThree);
	sort(blocks.begin(), blocks.end(), isLessThan);

	print_block();
	
	return 0;
}

// map


// map<int, int> count;

//vector<pair<int, int>> sortByValue(count.begin(), count.end()); // count map을 vector sortByBalue에 복사
//sort(sortByValue.begin(), sortByValue.end(), compare); // Value로 정렬

