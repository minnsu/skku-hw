#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////

int Partition(int *d, int p , int r){
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
	if(p < r){
		q = Partition(d, p, r);
		QuickSort(d, p, q - 1);
		QuickSort(d, q + 1, r);
	}
}

void MyVeryFastSort(int n, int *d){
	QuickSort(d, 0, n-1);
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
