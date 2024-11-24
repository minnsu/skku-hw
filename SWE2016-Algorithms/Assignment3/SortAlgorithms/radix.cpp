#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////
#include <queue>

void MyVeryFastSort(int n, int *d){
	std::queue<int> nradixq[10]; // -0 ~ -9
	std::queue<int> pradixq[10]; // 0 ~ 9
	int i, j, ten = 1, rad, dcount = 0;
	for(j = 0; j <= 8; j++, ten *= 10){
		for(i = 0; i < n; i++){
			rad = d[i] / ten % 10;
			if(d[i] >= 0){
				pradixq[rad].push(d[i]);
			}
			else{
				rad = rad != 0 ? rad + 10 : rad;
				nradixq[rad].push(d[i]);
			}
		}
		dcount = 0;
		for(i = 0; i < 10; i++){
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
