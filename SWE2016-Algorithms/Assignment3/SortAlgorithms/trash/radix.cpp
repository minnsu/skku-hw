#include <cstdio>
#include <random>
#include <cstdlib>
#include <chrono>
#include <queue>

void MyVeryFastSort(int n, int *d){
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
	printf("THIS IS RADIX SORT ALGORITHM\nEnter size : ");
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