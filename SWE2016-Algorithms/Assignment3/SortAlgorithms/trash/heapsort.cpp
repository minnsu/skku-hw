#include <cstdio>
#include <random>
#include <cstdlib>
#include <chrono>

void Heapify(int now, int size, int *d){
	int l = 2*now + 1;
	int r = 2*now + 2;
	int largest = now;

	if(l <= size && d[l] > d[now]){
		largest = l;
	}
	else{
		largest = now;
	}
	if(r <= size && d[r] > d[largest]){
		largest = r;
	}
	if(largest != now){
		int tmp = d[now];
		d[now] = d[largest];
		d[largest] = tmp;
		Heapify(largest, size, d);
	}
}

void MyVeryFastSort(int n, int *d)
{// heap sort
	// make max heap
	for(int i = n / 2 - 1; i >= 0; i--){
		Heapify(i, n, d);
	}
	int tmp;
	for(int i = n; i >= 0; i--){
		tmp = d[0];
		d[0] = d[i];
		d[i] = tmp;
		n--;
		Heapify(0, n, d);
	}
}

bool Validate(int n, int *d)
{
	for(int i=1;i<n;i++)
	{
		if( d[i-1] > d[i] )
		{
			return false;
		}
	}	
	return true;
}

int main() {
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-100000000, 100000000);
	
    int N;
	printf("THIS IS HEAP SORT ALGORITHM\nEnter size : ");
	scanf("%d", &N);
	int *arr = new int[N];
	for(int i = 0; i < N; i++){
		arr[i] = dis(gen);
	}
    printf(" === Sort Operation : Start ===\n");
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	MyVeryFastSort(N, arr);
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    printf(" === Sort Operation : End   ===\n");

    std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	bool res_validate = Validate(N, arr);

	if( res_validate ) { printf("Correct!\n"); }
	else { printf("Wrong!\n"); }
	printf( "%d\n" , (int)res_time);

    delete [] arr;
	return 0;
}