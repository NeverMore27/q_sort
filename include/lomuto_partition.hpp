#include <iostream> 
#include <algorithm>
#include <iterator>

template <class Iterator>
void quickSort(Iterator left, Iterator right)
{
	Iterator i = left, j = right;
	Iterator x = left;
	while (i <= j)
	{
		while (*i > *x) i++;
		while (*j < *x) j--;
		if (i <= j)
		{
			std::iter_swap(j, i);
			i++;
			j--;
		}
	}
	if (i<right)
		quickSort(i, right);

	if (left<j)
		quickSort(left, j);
}