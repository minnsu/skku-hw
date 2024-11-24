#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sfp.h"

int main(int argc, char *argv[])
{
	FILE *fp_input;
	FILE *fp_output;
	FILE *fp_answer;
	int case_num1, case_num2;
	int idx, x, y;
	int i, i_ans;
	float f, f_ans;
	sfp *sf1;
	sfp *sf2;
	char **sfpbits1;
	char **sfpbits2;
	char sfpbits_ans[17];

	fp_input = fopen("input.txt", "r");
	fp_output = fopen("output.txt", "w");
	fp_answer = fopen("answer.txt", "r");

	printf("Test 1: casting from int to sfp\n");
	fscanf(fp_input, "%d", &case_num1);
	sf1 = (sfp*)malloc(sizeof(sfp)*case_num1);
	sfpbits1 = (char**)malloc(sizeof(char*)*case_num1);
	for(idx = 0; idx < case_num1; idx++) {
		fscanf(fp_input, "%d", &i);
		fscanf(fp_answer, "%s", sfpbits_ans);
		sf1[idx] = int2sfp(i);
		sfpbits1[idx] = sfp2bits(sf1[idx]);
		fprintf(fp_output, "%s\n", sfpbits1[idx]);
		printf("int(%d) => sfp(%s), ", i, sfpbits1[idx]);
		if(!strcmp(sfpbits1[idx], sfpbits_ans))
			printf("CORRECT\n");
		else
			printf("WRONG\n");
	}
	fprintf(fp_output, "\n");
	printf("\n");

	printf("Test 2: casting from sfp to int\n");
	for(idx = 0; idx < case_num1; idx++) {
		fscanf(fp_answer, "%d", &i_ans);
		i = sfp2int(sf1[idx]);
		fprintf(fp_output, "%d\n", i);
		printf("sfp(%s) => int(%d), ", sfpbits1[idx], i);
		if(i == i_ans)
			printf("CORRECT\n");
		else
			printf("WRONG\n");
	}
	fprintf(fp_output, "\n");
	printf("\n");

	printf("Test 3: casting from float to sfp\n");
	fscanf(fp_input, "%d", &case_num2);
	sf2 = (sfp*)malloc(sizeof(sfp)*case_num2);
	sfpbits2 = (char**)malloc(sizeof(char*)*case_num2);
	for(idx = 0; idx < case_num2; idx++) {
		fscanf(fp_input, "%f", &f);
		fscanf(fp_answer, "%s", sfpbits_ans);
		sf2[idx] = float2sfp(f);
		sfpbits2[idx] = sfp2bits(sf2[idx]);
		fprintf(fp_output, "%s\n", sfpbits2[idx]);
		printf("float(%f) => sfp(%s), ", f, sfpbits2[idx]);
		if(!strcmp(sfpbits2[idx], sfpbits_ans))
			printf("CORRECT\n");
		else
			printf("WRONG\n");
	}
	fprintf(fp_output, "\n");
	printf("\n");

	printf("Test 4: casting from sfp to float\n");
	for(idx = 0; idx < case_num2; idx++) {
		fscanf(fp_answer, "%f", &f_ans);
		f = sfp2float(sf2[idx]);
		fprintf(fp_output, "%f\n", f);
		printf("sfp(%s) => float(%f), ", sfpbits2[idx], f);
		if(f == f_ans)
			printf("CORRECT\n");
		else
			printf("WRONG\n");
	}
	fprintf(fp_output, "\n");
	printf("\n");

	printf("Test 5: Addition\n");
	for(x = 0; x < case_num1; x++) {
		for(y = x; y < case_num1; y++) {
			sfp result = sfp_add(sf1[x], sf1[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s + %s = %s, ", sfpbits1[x], sfpbits1[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	for(x = 0; x < case_num2; x++) {
		for(y = x; y < case_num2; y++) {
			sfp result = sfp_add(sf2[x], sf2[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s + %s = %s, ", sfpbits2[x], sfpbits2[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	for(x = 0; x < case_num1; x++) {
		for(y = 0; y < case_num2; y++) {
			sfp result = sfp_add(sf1[x], sf2[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s + %s = %s, ", sfpbits1[x], sfpbits2[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	fprintf(fp_output, "\n");
	printf("\n");
	
	printf("Test 6: Multiplication\n");
	for(x = 0; x < case_num1; x++) {
		for(y = x; y < case_num1; y++) {
			sfp result = sfp_mul(sf1[x], sf1[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s * %s = %s, ", sfpbits1[x], sfpbits1[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	for(x = 0; x < case_num2; x++) {
		for(y = x; y < case_num2; y++) {
			sfp result = sfp_mul(sf2[x], sf2[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s * %s = %s, ", sfpbits2[x], sfpbits2[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	for(x = 0; x < case_num1; x++) {
		for(y = 0; y < case_num2; y++) {
			sfp result = sfp_mul(sf1[x], sf2[y]);
			char *resultbits;
			resultbits = sfp2bits(result);
			fscanf(fp_answer, "%s", sfpbits_ans);
			fprintf(fp_output, "%s\n", resultbits);
			printf("%s * %s = %s, ", sfpbits1[x], sfpbits2[y], resultbits);
			if(!strcmp(resultbits, sfpbits_ans))
				printf("CORRECT\n");
			else
				printf("WRONG\n");
			free(resultbits);
		}
	}
	fprintf(fp_output, "\n");
	printf("\n");

	for(idx = 0; idx < case_num1; idx++) free(sfpbits1[idx]);
	for(idx = 0; idx < case_num2; idx++) free(sfpbits2[idx]);
	free(sfpbits1);
	free(sfpbits2);
	free(sf1);
	free(sf2);

	fclose(fp_input);
	fclose(fp_output);
	fclose(fp_answer);

	return 0;
}


