#include "quick_sort.hpp"
int main(void)
{
	
	std::vector <int> k = { 1, 23, 45, 8, 9, 0 };
	std::vector <int> j = { 1, 23, 45, 8, 9, 0 };
	srand(time(0));
	unsigned int start_time = clock();
	parallel_quick_sort(k.data(), k.data()+k.size());
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	std::cout << search_time<<std::endl;
	 start_time = clock();
	quick_sort(j.data(), j.data() + j.size());
	end_time = clock();
	search_time = end_time - start_time;
	std::cout << search_time << std::endl;
	return 0;
}
