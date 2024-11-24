#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////


// You are NOT ALLOWED to add any header file
#include <set>
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

void QuickSort(int *data, int p, int r){
	int q;
	if(r - p < 60){
		InsertionSort(data, p, r);
	}
	else if(p < r){
		q = Partition(data, p, r);
		QuickSort(data, p, q - 1);
		QuickSort(data, q + 1, r);
	}
}

void countSort(int N, int *data){
	int *countList = new int[100000001];
	int i, j;
	int min = 100000001, max = -1;
	for(i = 0; i < N; i++){
		countList[data[i]]++;
		max = max < data[i] ? data[i] : max;
		min = min > data[i] ? data[i] : min;
	}
	int dataIndex = 0;
	for(i = min; i <= max; i++){
		if(countList[i] == 0){
			continue;
		}
		else{
			while(countList[i] > 0){
				data[dataIndex++] = i;
				countList[i]--;
			}
		}
	}
	delete[] countList;
}
bool setCheck(int *unsort, int *sort, int N){
	std::multiset<int> s1, s2;
	for(int i = 0; i < N; i++){
		s1.insert(unsort[i]);
		s2.insert(sort[i]);
	}
	for(std::multiset<int>::iterator it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end() && it2 != s2.end(); it1++, it2++){
		if(*it1 != *it2){
			return false;
		}
	}
	return true;
}
bool nondecreaseCheck(int *sort, int N){
	for(int i = 1; i < N; i++){
		if(sort[i-1] > sort[i]){
			return false;
		}
	}
	return true;
}
void Find_K_Smallest(int N, int *data, int K, int *result)
{
	// You should fill 'result' array with K smallest values of 'data'
	int *unsort = new int[N];
	for(int j = 0; j < N; j++){
		unsort[j] = data[j];
	}

	int i;
	int min = 100000001, max = -100000001;
	for(i = 0; i <= 100; i++){
		if(data[i] < min) min = data[i];
		if(data[i] > max) max = data[i];
	}
	for(i = N/2; i <= (N/2) + 200; i++){
		if(data[i] < min) min = data[i];
		if(data[i] > max) max = data[i];
	}
	for(i = N-1; i >= (N-200); i--){
		if(data[i] < min) min = data[i];
		if(data[i] > max) max = data[i];
	}
	if(N < (max - min) * 0.03125){
		QuickSort(data, 0, N-1);
	}
	else{
		countSort(N, data);
	}
	
	if(setCheck(unsort, data, N) && nondecreaseCheck(data, N)){
		printf("Success!\n");
	}
	else{
		printf("Failed...\n");
	}

	for(int i = 0; i < K; i++){
		result[i] = data[i];
	}
}



/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////


int main(int argc, char **argv)
{
	if( argc != 3 )
	{
		fprintf( stderr , "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int N, K, *data, *result;
	FILE *input = fopen( argv[1] , "rb" );
	int e = fread( &N , sizeof(int) , 1 , input );
	e = fread( &K , sizeof(int) , 1 , input );
	data = new int [ N ];
	e = fread( data , sizeof(int) , N , input );
	fclose(input);

	result = new int [ K ];	

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your function
	Find_K_Smallest( N , data , K , result );

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	// Write the results
	FILE *output = fopen( argv[2] , "w" );
	fprintf( output , "%d\n" , K );
	for(int i=0;i<K;i++)
	{
		fprintf( output , "%d " , result[i] );
	}
	fprintf( output , "\n%d\n" , (int)res_time );
	fclose(output);

	delete [] data;
	delete [] result;

	return 1;
}
