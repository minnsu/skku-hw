#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char** argv){
	int n, m, start;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d %d", &n, &m, &start); // store input at inputstring	
	
	int to, from, time;
	int NumOfInfected = 0, max_time = 0;
	bool *infected = new bool[n + 1];
	unsigned int *min_time_each = new unsigned int[n + 1];
	for(int i = 0; i < n + 1; i++){
		infected[i] = false;
		min_time_each[i] = 1001;
	}
	infected[start] = true;
	min_time_each[start] = 0;
	
    for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &to, &from, &time);
		if(from == start || infected[from]){
			infected[to] = true;
		}
		if(infected[to]){
			min_time_each[to] = min_time_each[to] > min_time_each[from] + time ? min_time_each[from] + time : min_time_each[to];
		}
	}
	fclose(fr); // file close
	
	for(int i = 0; i < n + 1; i++){
		if(infected[i]){
			NumOfInfected++;
			max_time = max_time > min_time_each[i] ? max_time : min_time_each[i];
		}
	}
	

	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	fprintf(fw, "%d %d", NumOfInfected, max_time);	
    
	fclose(fw); // file close	
	return 0;
}
