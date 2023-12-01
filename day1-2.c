#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int parse_word_digit(char* str, int* index) {
	int i = *index;

	switch (str[i]) {
	case 'o':
		if (str[i+1] == 'n' && str[i+2] == 'e') {
			*index += 2;
			return 1;
		}
		break;
	case 't':
		switch (str[i+1]) {
		case 'h':
			if (str[i+2] == 'r' && str[i+3] == 'e' && str[i+4] == 'e') {
				*index += 4;
				return 3;
			}
			break;
		case 'w':
			if (str[i+2] == 'o') {
				*index += 2;
				return 2;
			}
			break;
		}
		break;
	case 'f':
		switch (str[i+1]) {
		case 'i':
			if (str[i+2] == 'v' && str[i+3] == 'e') {
				*index += 3;
				return 5;
			}
			break;
		case 'o':
			if (str[i+2] == 'u' && str[i+3] == 'r') {
				*index += 4;
				return 4;
			}
			break;
		}
		break;
	case 's':
		switch (str[i+1]) {
		case 'e':
			if (str[i+2] == 'v' && str[i+3] == 'e' && str[i+4] == 'n') {
				*index += 4;
				return 7;
			}
			break;
		case 'i':
			if (str[i+2] == 'x') {
				*index += 3;
				return 6;
			}
			break;
		}
		break;
	case 'e':
		if (str[i+1] == 'i' && str[i+2] == 'g' && str[i+3] == 'h' && str[i+4] == 't') {
			*index += 4;
			return 8;
		}
		break;
	case 'n':
		if (str[i+1] == 'i' && str[i+2] == 'n' && str[i+3] == 'e') {
			*index += 3;
			return 9;
		}
		break;
	}

	*index += 1;
	return 0;
}

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

		int digit = parse_word_digit(str, &i);
		if (digit) {
			if (first_digit < 0) {
				first_digit = digit;
			}

			last_digit = digit;
		}
	}

	if (first_digit == -1) {
		return 0;
	}

	return first_digit * 10 + last_digit;
}

void test() {
	assert(trebuchet_decode("two1nine") == 29);
	assert(trebuchet_decode("eightwothree") == 83);
	assert(trebuchet_decode("abcone2threexyz") == 13);
	assert(trebuchet_decode("xtwone3four") == 24);
	assert(trebuchet_decode("4nineeightseven2") == 42);
	assert(trebuchet_decode("zoneight234") == 14);
	assert(trebuchet_decode("7pqrstsixteen") == 76);
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
