#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
	
} Vector;

void printVector(Vector *vec) {
	printf("%di + %dj\n", vec->x, vec->y);
}

Vector* add(Vector *v1, Vector *v2) {
	Vector res;
	Vector *result = &res;
	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	return result;
}

Vector* substract(Vector *v1, Vector *v2) {
	Vector res;
	Vector *result = &res;
	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	return result;
}

double magnitudeOfVector(Vector* vec) {
	double magnitude = sqrt(pow(vec->x, 2) + pow(vec->y, 2));
	return magnitude;
}

double angleOfVector(Vector* vec) {
	double angle = atan((double) (vec->y) / (double) (vec->x));
	return angle;
}

int dot_product(Vector *v1, Vector *v2) {
	int dot = (v1->x*v2->x) + (v1->y * v2->y);
	return dot;
}

double angleBetweenVectors(Vector* vec1,Vector* vec2) {
	double angle = acos(dot_product(vec1, vec2) / (magnitudeOfVector(vec1) * magnitudeOfVector(vec2)));
	return angle;
}

int main() {
	Vector *vec1 = (Vector*) malloc(sizeof(Vector));
	Vector *vec2 = (Vector*) malloc(sizeof(Vector));
	printf("Enter vec1 :");
	scanf("%d %d", &(vec1->x), &(vec1->y));
	printf("Enter vec2 :");
	scanf("%d %d", &(vec2->x), &(vec2->y));
	
	printVector(vec1);
	printVector(vec2);

	Vector *res = substract(vec1, vec2);
	printf("vec1 - vec2 = %di + %dj\n", res->x, res->y);
	
	res = add(vec1, vec2);
	printf("vec1 + vec2 = %di + %dj\n", res->x, res->y);
	printf("Angle of vec1: %f\n", angleOfVector(vec1));
	printf("Angle of vec2: %f\n", angleOfVector(vec2));

	printf("Angle between vec1 and vec2: %f\n", angleBetweenVectors(vec1,vec2));
	
	printf("Magnetude of vec1 : %f\n", magnitudeOfVector(vec1));
	printf("Magnetude of vec2 : %f\n", magnitudeOfVector(vec2));
	
	printf("vec1 * vec2 = %d\n", dot_product(vec1, vec2));
	free(vec1);
	free(vec2);
	vec1 = NULL;
	vec2 = NULL;
	return 0;
}


