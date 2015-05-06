//Theodore Nguyen 704-156-701 cs32 homework 3 winter 2015/


#include <iostream>
#include <string>
using namespace std;


int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	if(n2 == 0 || n1 == 0)
		return 0;
	if(*a1 == *a2)
	{
		int k = (countIncludes(a1+1, n1-1, a2+1, n2-1) + countIncludes(a1+1, n1-1, a2, n2));
		if(n2 != 1)
			return k;
		if(n2 == 1)
			return k+1;
	}
	else
		return countIncludes(a1+1, n1-1, a2, n2);
	return 0;
}

void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

void separate(double a[], int n, double separator, int& firstNotGreater, int& firstLess)
{
	if(n < 0)
		n =0;
	// It will always be the case that just before evaluating the loop
	// 	      // condition:
	// 	      	      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	// 	      	      	      //  Every element earlier than position firstNotGreater is > separator
	// 	      	      	      	      //  Every element from position firstNotGreater to firstUnknown-1 is
	// 	      	      	      	      	      //    == separator
	// 	      	      	      	      	      	      //  Every element from firstUnknown to firstLess-1 is not known yet
	// 	      	      	      	      	      	      	      //  Every element at position firstLess or later is < separator
	
	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while(firstUnknown < firstLess)
	{
		if(a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if(a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

void order(double a[], int n)
{
	if(n <= 1)
		return;
	int fng, fl;
	separate(a, n, a[n/2], fng, fl);
	order(a, fng);
	order(a, n-fl);
}

