#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <chrono> // time measure
#include <algorithm> // std sort

template<typename Type>
void Insertion_Sort(Type *_array, int _n);
template<typename Type>
void Insertion_Sort_without_Swap(Type *_array, int _n);
template<typename Type>
bool Is_Sorted(Type *_array, int _n);

template<typename Type>
void Merge(Type *_arrayA, Type *_arrayB, int _nA, int _nB, Type *_arrayOut);
template<typename Type>
void Merge_Sort(Type *_array, int _first, int _last);


int main(int argc, char **argv)
	{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> dist(0, 100000000); // random genarator

	int N = atoi(argv[1]);
	printf("N = %d\n", N);

	int *data = new int [N];
	printf("DATA : ");
	for(int i = 0; i < N; i++)
	{
		data[i] = dist(gen);
	//	printf("%10d\n", data[i]);
	}

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	
	if(strcmp(argv[2], "insertion") == 0)
	{
		Insertion_Sort<int>(data, N);
	}
	else if(strcmp(argv[2], "insertion_without_swap") == 0)
	{
		Insertion_Sort_without_Swap<int>(data, N);
	}
	else if(strcmp(argv[2], "std") == 0)
	{
		std::sort( &(data[0]), &(data[N]) );
	}
	else if(strcmp(argv[2], "merge") == 0)
	{
		Merge_Sort<int>(data, 0, N);
	}

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds timediff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double T = timediff.count();
	
	bool isCorrect = Is_Sorted<int>(data, N);
	if(isCorrect)
	{ printf("Correct!\n"); }
	else 
	{ printf("Wrong!\n"); }
	for(int i = 0; i < N; i++)
	{
		printf("%10d\n", data[i]);
	}
	printf("Runtime = %d ms\n", (int)T);
	return 0;
}


template<typename Type>
void Insertion_Sort(Type *_array, int _n)
{
	for(int i = 1; i < _n; i++)
	{
		for(int j = i; j > 0; j--)
		{
			if(_array[j-1] > _array[j])
			{
				Type tmp = _array[j];
				_array[j] = _array[j-1];
				_array[j-1] = tmp;
			}
		}
	}
}

template<typename Type>
void Insertion_Sort_without_Swap(Type *_array, int _n)
{
	for(int i = 0; i < _n; i++)
	{
		Type tmp = _array[i];
		for(int j = i; j > 0; j--)
		{
			if(_array[j-1] > tmp)
			{
				_array[j] = _array[j-1];
			}
			else
			{
				_array[j] = tmp;
				break;
			}
		}
		if(_array[0] > tmp)
		{
			_array[0] = tmp;
		}
	}
}

template<typename Type>
bool Is_Sorted(Type *_array, int _n)
{
	for(int i = 1; i < _n; i++)
	{
		if(_array[i-1] > _array[i] )
		{
			return false;
		}
	}
	return true;
}

template<typename Type>
void Merge(Type *_array, int start, int end, Type *_arrayOut)
{
	int posA = start;
	int mid = (end - start) / 2;
	int posB  = mid;
	int k = 0;
	while( posA < mid && posB < end )
	{
		if( _array[ posA ] < _array[ posB ] )
		{
			_arrayOut[k] = _array[ posA ];
			posA++;
		}
		else
		{
			_arrayOut[k] = _array[ posB ];
			posB++;
		}	
		k++;
	}
	for( ; posA < mid ; posA++ )
	{
		_arrayOut[k] = _array[posA];
		k++;
	}
	for( ; posB < end ; posB++ )
	{
		_arrayOut[k] = _array[posB];
		k++;
	}
}

template<typename Type>
void Merge_Sort(Type *_array, int _first, int _last)
{
	if(_last-_first <= 6)
	{
		Insertion_Sort_without_Swap<Type>(_array, _last - _first );
	}
	else
	{
		int midpoint = ( _first + _last ) / 2;
		Merge_Sort<Type>( _array , _first , midpoint );
		Merge_Sort<Type>( _array , midpoint , _last );
		Type *tmp = new Type[_last - _first];
		Merge<Type>(_array, _first, _last, tmp);
		for(int i = 0;  i < _last - _first; i++)
		{
			_array[_first + i] = tmp[i];
		}
		delete [] tmp;
	}
}
