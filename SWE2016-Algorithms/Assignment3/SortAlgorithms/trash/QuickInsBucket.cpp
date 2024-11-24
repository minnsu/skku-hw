#include <cstdio>
#include <random>
#include <cstdlib>
#include <chrono>


void BucketSort(int n, int *d){
	int *list = new int[200000000];
	int i, j, size, dcount = 0;
	int min = 200000001, max = -1;
	for(i = 0; i < n; i++){
		list[d[i] + 100000000]++;
		if(d[i] + 100000000 < min) min = d[i] + 100000000;
		if(d[i] + 100000000 > max) max = d[i] + 100000000;
	}
	for(i = min; i <= max; i++){
		if(list[i] != 0){
			size = list[i];
			for(j = 0; j < size; j++){
				d[dcount++] = i - 100000000;
			}
		}
	}
}

void InsertionSort(int *d, int &p, int &r){
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

int Partition(int *d, int &p, int &r){
	int med_of_3 = d[p] > d[r] ? p : r;
	int tmp = (p + r) / 2;
	if(d[med_of_3] > d[tmp]){
		med_of_3 = d[tmp] > d[r] ? tmp : r;
	}

	tmp = d[r];
	d[r] = d[med_of_3];
	d[med_of_3] = tmp;

	int pivot = d[r];
	int i = p - 1;
	for(int j = p; j < r; j++){
		if(d[j] <= pivot){
			i++;
			tmp = d[j];
			d[j] = d[i];
			d[i] = tmp;
		}
	}
	tmp = d[r];
	d[r] = d[i+1];
	d[i+1] = tmp;
	return i + 1;
}

void QuickSort(int *d, int p, int r){
	int q;
	if(r - p < 60){
		InsertionSort(d, p, r);
	}
	else if(p < r){
		q = Partition(d, p, r);
		QuickSort(d, p, q - 1);
		QuickSort(d, q + 1, r);
	}
}

void MyVeryFastSort(int n, int *d){
	if(n > 10000000){
		BucketSort(n, d);
	}
	else{
		QuickSort(d, 0, n-1);
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
	printf("THIS IS QUICK_INS_BUCKET SORT ALGORITHM\nEnter size : ");
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