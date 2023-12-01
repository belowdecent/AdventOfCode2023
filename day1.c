#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int trebuchet_decode(char* str) {
	int first_digit = -1;
	int last_digit = -1;

	int i = 0;
	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			if (first_digit < 0) {
				first_digit = str[i] - 48;
			}

			last_digit = str[i] - 48;
		} 

		i++;
	}

	if (first_digit == -1) {
		return 0;
	}

	return first_digit * 10 + last_digit;
}

void test() {
	char* test1 = "1abc2";
	char* test2 = "pqr3stu8vwx";
	char* test3 = "a1b2c3d4e5f";
	char* test4 = "treb7uchet";

	assert(trebuchet_decode(test1) == 12);
	assert(trebuchet_decode(test2) == 38);
	assert(trebuchet_decode(test3) == 15);
	assert(trebuchet_decode(test4) == 77);
}

int main() {
	test();

	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("day1input.txt", "r");
	if (fp == NULL) {
		printf("Couldn't find the input file!\n");
		return EXIT_FAILURE;
	}

	int trebuchet_total = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		trebuchet_total += trebuchet_decode(line);
	}
	
	printf("Total: %i\n", trebuchet_total);
	
	fclose(fp);
	return EXIT_SUCCESS;
}
