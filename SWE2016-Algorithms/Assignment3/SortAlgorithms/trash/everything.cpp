#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

bool Validate(int n, int *d);
// HEAPSORT
void Heapify(int now, int size, int *d);
void Heapsort(int n, int *d);
// MERGESORT
void Merge(int *d, int leftstart, int mid, int rightend);
void MergeSort(int *d, int p, int r);
// QUICKSORT
void InsertionSort(int *d, int &p, int &r);
int Partition(int *d, int &p , int &r);
void QuickSort(int *d, int p, int r);


void MyVeryFastSort(int n, int *d, int key) {
    switch(key){
        case 1:
            std::sort(d, d + n);
            break;
        case 2:
            QuickSort(d, 0, n-1);
            break;
        case 3:
            MergeSort(d, 0, n-1);
            break;
        case 4:
            Heapsort(n, d);
            break;
    }
}


int main() {
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-100000000, 100000000);
	
    int N;
	printf("Enter size : ");
	scanf("%d", &N);
	int ***arr = new int**[5];
	for(int i = 0; i < 5; i++){
		arr[i] = new int*[10];
		for(int j = 0; j < 10; j++){
			arr[i][j] = new int[N];
		}
	}
	for(int k = 0; k < 5; k++){
		for(int j = 0; j < 10; j++){
			for(int i = 0; i < N; i++){
				arr[k][j][i] = dis(gen);
			}
		}
	}
		

    char **sort_name = new char*[4];
	sort_name[0] = "lib";
	sort_name[1] = "quick";
	sort_name[2] = "merge";
	sort_name[3] = "heap";

	int key; 
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::milliseconds elapsed_time;
    double res_time;
    double aver = 0;
	int how_much_correct;
	for(int k = 0; k < 4; k++){
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
void Heapsort(int n, int *d){
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

void InsertionSort(int *d, int &p, int &r){
    int i, j;
    int key;
    for(i = p; i <= r; i++){
        key = d[i];
        for(j = i-1; j >= 0; j--){
            if(d[j] > key){
                d[j+1] = d[j];
            }
			else{
                break;
            }
        
        }
        d[j+1] = key;
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
	int j;
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
	if(r - p < 100){
		InsertionSort(d, p, r);
	}
	else if(p < r){
		q = Partition(d, p, r);
		QuickSort(d, p, q - 1);
		QuickSort(d, q + 1, r);
	}
}