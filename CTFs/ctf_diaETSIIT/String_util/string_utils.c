#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/mman.h>

void error(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void upper(char* msg) {
	for (int i = 0; i < strlen(msg); i++) {
		msg[i] = toupper(msg[i]);
	}
}

void lower(char* msg) {
	for (int i = 0; i < strlen(msg); i++) {
		msg[i] = tolower(msg[i]);
	}
}

void print(char* msg) {
	printf("%s", msg);
}

#define N_OPERATIONS 3
#define MSG_SIZE 0x1000
#define USERNAME_SIZE 200

typedef void (*op_fn)(char* msg);

struct operation {
	op_fn fn;
	const char* name;
};

struct operation operations[N_OPERATIONS] = {
	{ .fn = print, .name = "print"},
	{ .fn = upper, .name = "upper"},
	{ .fn = lower, .name = "lower"},
};
char username[USERNAME_SIZE] = "unknown";


int main() {
	// Ignore me
	setbuf(stdout, NULL);

	printf("Usuario: ");
	fgets(username, USERNAME_SIZE, stdin);
	printf("Bienvenido, %s\n", username);

	void* msg = mmap((void*)0x1234000, MSG_SIZE, PROT_READ|PROT_WRITE|PROT_EXEC,
	                 MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0);
	if (msg == MAP_FAILED)
		error("mmap");

	printf("Introduce el mensaje: ");
	fgets(msg, MSG_SIZE, stdin);

	while (true) {
		printf("Elige una operación:\n");
		for (int i = 0; i < N_OPERATIONS; i++) {
			printf(" - %d: %s\n", i, operations[i].name);
		}
		printf("> ");

		int i = 0;
		scanf("%d", &i);

		if (i < 0 || i > N_OPERATIONS) {
			printf("Operación inválida.\n\n");
			continue;
		}

		operations[i].fn(msg);
		printf("\n");
	}
}