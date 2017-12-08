#include <iostream> 
#include <algorithm>
#include <iterator>


template<class Iterator>
It partition(Iterator first, Iterator last) 
{

	auto pivot = *(last - 1);
	auto i = first - 1;
	for (Iterator j = first; j < last - 1; ++j) 
	{
		if (*j <= pivot) 
		{
			++i;
			std::iter_swap(i, j);
		}
	}
	std::iter_swap(i + 1, last - 1);

	return i + 1;
}
