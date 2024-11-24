#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////

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

void MyVeryFastSort(int n, int *d){
	int i;
	int min = 100000001, max = -100000001;
	for(i = 0; i <= 200; i++){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	for(i = n/2; i <= (n/2) + 200; i++){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	for(i = n-1; i >= (n-200); i--){
		if(d[i] < min) min = d[i];
		if(d[i] > max) max = d[i];
	}
	if(32 * n < max - min){ // 할당 시간 상수 찾기
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

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////


// Utilized to check the correctness
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

int main(int argc, char **argv)
{
	if( argc != 3 )
	{
		fprintf( stderr , "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int n, *d;
	FILE *input = fopen( argv[1] , "rb" );
	int e = fread( &n , sizeof(int) , 1 , input );
	d = new int [ n ];
	e = fread( d , sizeof(int) , n , input );
	fclose(input);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your sorting algorithm
	MyVeryFastSort( n , d );

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	bool res_validate = Validate( n , d );

	// Write the results (corretness and time)
	FILE *output = fopen( argv[2] , "w" );
	if( res_validate ) { fprintf( output , "OKAY\n" ); printf("OKAY\n"); }
	else { fprintf( output , "WRONG\n" ); printf("WRONG\n");  }
	fprintf( output , "%d\n" , (int)res_time );
	printf( "%d\n" , (int)res_time );
	fclose(output);

	delete [] d;

	return 1;
}
