//Theodore Nguyen 704-156-701 CS32 homework 3 winter 2015
//

#include <iostream>
#include <cmath>
using namespace std;


//REturn true if the somePredicate function returns true for at least ONE of the array elements, false otherwise
//

bool somePredicate(double x)
{
	return x < 0;
}


bool anyTrue(const double a[], int n)
{
	
	if(n == 0)
		{/* cout << "this is the end\n";*/ return false;}	

	if(somePredicate(a[n-1]))
		{/* cout << "FOUND\n";*/ return true;}
	//cout << "failcounter\n";
	if(anyTrue(a, n-1))
		return true;	
	
	return false;

}

int countTrue(const double a[], int n)
{
	if(n == 0)
		return 0;
	return (somePredicate(a[n-1]) + countTrue(a, n-1));
}






int firstTrue(const double a[], int n)
{
	if(n == 0)
		return -1;
	if(somePredicate(*a))
		return 0;
	else
	{	
		if(firstTrue(a+1, n-1) == -1)
			return -1;
		return (1 + firstTrue(a+1, n-1));
	}
}


int indexOfMin(const double a[], int n)
{
	if(n <= 0)
	{
		n = 0;	return -1;
	}
	if(n == 1)
		return 0;
	if(a[0] > a[n-1])
		return (1 + indexOfMin(a+1, n-1)); 
	else
		return 	indexOfMin(a, n-1);
	
}	


bool includes(const double a1[], int n1, const double a2[], int n2)
{
	
	if(n2 == 0)
		return true;
	if(n1 <= 0 || n2 < 0)
	{
		n1 = n2 = 0;
		return false;
	}
	if(*a1 == *a2)
		return includes(a1+1, n1-1, a2+1, n2-1);
	else
		return includes(a1+1, n1-1, a2, n2);
	
}


