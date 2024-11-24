#include <cstdio>
#include <random>
#include <cstdlib>
#include <chrono>

void Merge(int *d, int leftstart, int mid, int rightend){
    int n1 = mid - leftstart + 1;
    int n2 = rightend - mid;
    int *LEFT = new int[n1 + 1];
    int *RIGHT = new int[n2 + 1];
    for(int i = 0; i < n1; i++){
        LEFT[i] = d[leftstart + i];
    }
    for(int i = 0; i < n2; i++){
        RIGHT[i] = d[mid + i + 1];
    }
    LEFT[n1] = 100000001; // 1억1
    RIGHT[n2] = 100000001;
    int left_iter = 0;
    int right_iter = 0;
    for(int i = leftstart; i <= rightend; i++){
        if(LEFT[left_iter] <= RIGHT[right_iter]){
            d[i] = LEFT[left_iter++];
        }
        else{
            d[i] = RIGHT[right_iter++];
        }
    }
}

void MergeSort(int *d, int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(d, p, q);
        MergeSort(d, q+1, r);
        Merge(d, p, q, r);
    }
}

void MyVeryFastSort(int n, int *d) {
    // merge sort
    MergeSort(d, 0, n-1);
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
	printf("THIS IS MERGE SORT ALGORITHM\nEnter size : ");
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