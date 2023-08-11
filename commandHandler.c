/*
	Command handler
	Also written in nano ;)

*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *USAGE_STRING = "Usage %s -k [key_type]\n";

void handle_command(int argc, char *argv[], char **key_type) {

	int opt;

	while ((opt = getopt(argc, argv, "k:")) != -1) {
		switch (opt) {
			case 'k':
				*key_type = optarg;
				break;

		}
	}

	if(*key_type == NULL) {

		fprintf(stderr, USAGE_STRING, argv[0]);
		exit(EXIT_FAILURE);
	}
}
