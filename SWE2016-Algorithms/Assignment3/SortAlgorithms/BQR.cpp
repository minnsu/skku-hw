#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;
#include <queue>

#define RANGE 10000000

bool Validate(int n, int *d);
// QUICKSORT
void InsertionSort(int *d, int &p, int &r);
int Partition(int *d, int &p , int &r);
void QuickSort(int *d, int p, int r);
// NEW
void BucketSort(int *d, int &n);
void NEWSort(int n, int *d);
// Radix
void RadixSort(int n, int *d);
void MyVeryFastSort(int n, int *d, int key) {
    switch(key){
        case 1:
			NEWSort(n, d);
            break;
		case 2:
            QuickSort(d, 0, n-1);
			break;
		case 3:
			RadixSort(n, d);
			break;
    }
}


int main() {
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-RANGE, RANGE);
	
    int N;
	printf("Enter size : ");
	scanf("%d", &N);
	int ***arr = new int**[3];
	for(int i = 0; i < 3; i++){
		arr[i] = new int*[10];
		for(int j = 0; j < 10; j++){
			arr[i][j] = new int[N];
		}
	}
	for(int k = 0; k < 3; k++){
		for(int j = 0; j < 10; j++){
			for(int i = 0; i < N; i++){
				arr[k][j][i] = dis(gen);
			}
		}
	}
		

    char **sort_name = new char*[3];
	sort_name[0] = "QIB";
	sort_name[1] = "Quick";
	sort_name[2] = "Radix";

	int key; 
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::milliseconds elapsed_time;
    double res_time;
    double aver = 0;
	int how_much_correct;
	for(int k = 0; k < 3; k++){
		key = k+1;
		how_much_correct = 0, aver = 0;
		for(int i = 0; i < 10; i++){
			start = std::chrono::system_clock::now();
			MyVeryFastSort(N, arr[k][i], key);
	        end = std::chrono::system_clock::now();
	
		    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			res_time = elapsed_time.count();
			if(Validate(N, arr[k][i])){how_much_correct++;}
			aver += res_time;
			delete[] arr[k][i];
		}
		printf("Average time of %s algorithm : %lfms\nCorrect : %d / 10\n", sort_name[k], aver / 10, how_much_correct);
	}

	return 0;
}

bool Validate(int n, int *d){
	for(int i=1;i<n;i++)
	{
		if( d[i-1] > d[i] )
		{
			return false;
		}
	}	
	return true;
}

void BucketSort(int &min, int &max, int *d, int *list){
	int i, j, size = max - min, dcount = 0;
	for(i = min; i <= max; i++){
		if(list[i] != 0){
			size = list[i];
			for(j = 0; j < size; j++){
				d[dcount++] = i - 100000000;
			}
		}
	}
	delete[] list;
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
	int i = p - 1, j;
	for(j = p; j < r; j++){
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

void NEWSort(int n, int *d){
	int i;
	int min = 100000001, max = -100000001;
	for(i = 0; i <= 200; i++){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	for(i = n / 2; i <= n / 2 + 200; i++){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	for(i = n-1; i >= n - 200; i--){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	if(32 * n < max - min){
		QuickSort(d, 0, n-1);
		return;
	}

	int *list = new int[200000000];
	min = 200000001, max = -1;
	for(i = 0; i < n; i++){
		list[d[i] + 100000000]++;
		if(d[i] + 100000000 < min) min = d[i] + 100000000;
		if(d[i] + 100000000 > max) max = d[i] + 100000000;
	}
	BucketSort(min, max, d, list);
}

void RadixSort(int n, int *d){
	std::queue<int> nradixq[10]; // -0 ~ -9
	std::queue<int> pradixq[10]; // 0 ~ 9
	int i, j, ten = 1, rad, dcount = 0;
	for(j = 0; j <= 9; j++, ten *= 10){
		for(i = 0; i < n; i++){
			rad = d[i] / ten % 10;
			if(d[i] >= 0){
				pradixq[rad].push(d[i]);
			}
			else{
				rad = - rad;
				nradixq[rad].push(d[i]);
			}
		}
		dcount = 0;
		for(i = 9; i >= 0; i--){
			while(!nradixq[i].empty()){
				d[dcount++] = nradixq[i].front(); nradixq[i].pop();
			}
		}
		for(i = 0; i < 10; i++){
			while(!pradixq[i].empty()){
				d[dcount++] = pradixq[i].front(); pradixq[i].pop();
			}
		}
	}
}