#include <stdio.h>

#define MAXLEN 50

void lstrip(const char *src, char *dst) {
    int first = 0;  // index of first non-space character
    while (src[first] == ' ') {
        first++;
    }
    int i = 0;
    while (src[i + first] != '\0') {
        dst[i] = src[i + first];
        i++;  // increment, decrement, ...
    }
    dst[i + first] = '\0';
}

void rstrip(const char *src, char *dst) {
	int length = 0;
	while (src[length] != '\0') {
		length++;
	}
	length--;
	while (src[length] == ' ') {
		length--;
	}
	int i;
	for (i = 0; i <=length; i++) {
		dst[i] = src[i];
	}
	dst[i] = '\0';
}

void strip(const char *src, char *dst) {
	char temp[MAXLEN];
	lstrip(src, temp);
	rstrip(temp, dst);
}

int main() {
    printf("enter the string: ");
    char line[MAXLEN];
    scanf("%[^\n]%*c", line);
	
	printf("enter the trim type (l, r, b): ");
    char type;
    scanf("%c", &type);
    if(type == 'l'){
        char lstripped[MAXLEN];
        lstrip(line, lstripped);
        printf("|%s|\n", lstripped);
    }
    else if(type == 'r'){
        char rstripped[MAXLEN];
        rstrip(line, rstripped);
        printf("|%s|\n", rstripped);
    }
    else if(type == 'b'){
        char stripped[MAXLEN];
        strip(line, stripped);
        printf("|%s|\n", stripped);
    }
    else{
        printf("unexpected command.");
    }
    
    return 0;
}
