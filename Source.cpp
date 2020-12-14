#include<iostream>
#include<climits>
const int size = 6;

struct Point
{
	size_t minDist;// min distance from initial point
	bool check;// is point visited
	int source;
};
int findMinDist(Point* arr, int size, int _index)
{
	int min = INT_MAX;
	int index = _index;
	for (int i = 0; i < size; i++)
	{
		if (arr[i].minDist < min && arr[i].check == false)
		{
			min = arr[i].minDist;
			index = i;
		}
	}
	return index;
}
void initPoints(Point* array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		array[i].minDist = INT_MAX;
		array[i].check = false;
		array[i].source = -1;
	}
}
void deikstra(int graph[][size], int start, int finish)
{
	Point array[size];
	initPoints(array, size);

	array[start].minDist = 0;
	array[start].check = true;
	// find where to go from starting point
	for (size_t i = 0; i < size; i++)
	{
		int possiblePoint = findMinDist(array, size, start);
		array[possiblePoint].check = true;

		for (size_t j = 0; j < size; j++)
		{
			if (array[j].check == false && graph[possiblePoint][j] > 0 && array[possiblePoint].minDist != INT_MAX
				&& array[possiblePoint].minDist + graph[possiblePoint][j] < array[j].minDist)
			{
				array[j].minDist = array[possiblePoint].minDist + graph[possiblePoint][j];
				array[j].source = possiblePoint;
			}
		}
	}
	// find route
	std::cout << "Route: ";
	int pass = finish;
	while (pass != start)
	{
		std::cout << pass << " ";
		pass = array[pass].source;
	}
	std::cout << "\nPoint: " << finish << "\nDistance: " << array[finish].minDist <<
		"\nSource: " << array[finish].source << std::endl;
}

int main()
{
	int graph[size][size] = { {0, 10, 20, 0, 0, 0},
							  {10, 0, 0, 50, 10, 0},
							  {20, 0, 0, 20, 40, 0},
							  {0, 50, 20, 0, 30, 15},
							  {0, 10, 40, 30, 0, 5},
							  {0, 0,  0,  15, 5, 0} };

	deikstra(graph, 1, 3);

	return 0;
}