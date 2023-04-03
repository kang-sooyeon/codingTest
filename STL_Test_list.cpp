
/////////////////// 
// list는 내장 unique, remove, removeif 함수 가짐.
// 실제 원소삭제되어 크기도 조정됨, std::unique,와 std::remove와 다름
//
/*
// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near {
	bool operator() (double first, double second)
	{
		return (fabs(first - second) < 5.0);
	}
};

int main()
{
	double mydoubles[] = { 12.15,  2.72, 73.0,  12.77,  3.14,
						 12.77, 73.35, 72.25, 15.3,  72.25 };
	std::list<double> mylist(mydoubles, mydoubles + 10);

	mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
	// 15.3,  72.25, 72.25, 73.0,  73.35

	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
	// 15.3,  72.25, 73.0,  73.35

	mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15             // <-- 인접 원소 두개 비교.. 참이면 뒤에꺼 삭제..
	// 15.3,  72.25, 73.0

	mylist.unique(is_near());           //  2.72, 12.15, 72.25			  // <-- 인접 원소 두개 비교.. 참이면 뒤에꺼 삭제

	std::cout << "mylist contains:";
	for (std::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}


int main ()
{
  int myints[]= {17,89,7,14};
  std::list<int> mylist (myints,myints+4);

  mylist.remove(89);

  std::cout << "mylist contains:";
  for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

*/


/*
// list::remove_if
#include <iostream>
#include <list>

// a predicate implemented as a function:
bool single_digit(const int& value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator() (const int& value) { return (value % 2) == 1; }
};

int main()
{
	int myints[] = { 15,36,7,17,20,39,4,1 };
	std::list<int> mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1

	mylist.remove_if(single_digit);           // 15 36 17 20 39

	mylist.remove_if(is_odd());               // 36 20

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
*/