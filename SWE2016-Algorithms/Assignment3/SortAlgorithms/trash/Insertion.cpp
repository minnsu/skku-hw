#include <cstdio>
#include <random>
#include <cstdlib>
#include <chrono>

void InsertionSort(int *d, int p, int r){
    int i, j;
    int tmp;
    for(i = p + 1; i <= r; i++){
        tmp = d[i];
        for(j = i; j > p; j--){
            if(d[j-1] > tmp){
                d[j] = d[j-1];
            }
			else {
				d[j] = tmp;
                break;
            }
        
        }
		if(d[p] > tmp){
			d[p] = tmp;
		}
    }
}

void MyVeryFastSort(int n, int *d){
	InsertionSort(d, 0, n-1);
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
	printf("THIS IS QUICK_5 SORT ALGORITHM\nEnter size : ");
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
