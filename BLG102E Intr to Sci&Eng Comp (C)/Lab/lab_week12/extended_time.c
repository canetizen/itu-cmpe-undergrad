#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int hour;
	int minute;
	int second;
} Time;

typedef struct {
	int year;
	int month;
	int day;	
} Date;

typedef struct {
	Time *time;
	Date *date;
} ExtendedTime;


int addTime(Time* op1, Time* op2, Time* op3) {
	int counter = 0;

	op3->hour = op1->hour + op2->hour;
	op3->minute = op1->minute + op2->minute;
	op3->second = op1->second + op2->second;
	
	if (op3->second >= 60) {
		op3->second -= 60;
		op3->minute++;
	}
	
	if (op3->minute >= 60) {
		op3->minute -= 60;
		op3->hour++;
	}
	
	if (op3->hour >= 24) {
		op3->hour -= 24;
		counter++;
	}
	
	return counter;
}

int subtractTime(Time* op1, Time* op2, Time* op3) {
    op3->hour = 0;
    op3->minute = 0;
    op3->second = 0;
	if (op1->second - op2->second < 0){
        op3->second = op1->second - op2->second + 60;
        op3->minute -= 1;
    } else {
        op3->second = op1->second - op2->second;
    }
    if (op1->minute - op2->minute < 0){
        op3->minute = op1->minute - op2->minute + 60;
        op3->hour -= 1;
    } else {
        op3->minute = op1->minute - op2->minute;
    }
    if (op1->hour - op2->hour < 0){
        op3->hour = op1->hour - op2->hour + 24;
        return -1;
    } else {
        op3->hour = op1->hour - op2->hour;
        return 0;
    }
}

void addDate(Date* op1, Date* op2, Date* op3,int carry) {
	op3->year = op1->year + op2->year;
	op3->month = op1->month + op2->month;
	op3->day = op1->day + op2->day;
	
	op3->day += carry;
	
	if (op3->day > 30) {
		op3->day -= 30;
		op3->month++;
	}
	
	if (op3->month > 12) {
		op3->day -= 12;
		op3->year++;
	}
}

void subtractDate(Date* op1, Date* op2, Date* op3, int burrow) {
	op3->day = 0 + burrow;
    op3->month = 0;
    op3->year = 0;
    op3->day = op1->day - op2->day;
    op3->month = op1->month - op2->month;
    op3->year = op1->year - op2->year;
	if (op1->day - op2->day < 0){
        op3->day = op1->day - op2->day + 30;
        op3->month -= 1;
    } 
    if (op1->month - op2->month < 0){
        op3->month = op1->month - op2->month + 12;
        op3->year -= 1;
    } 

}


void addExtendedTime(ExtendedTime* op1, ExtendedTime* op2, ExtendedTime* op3) {
	int carry = addTime(op1->time, op2->time, op3->time);
    addDate(op1->date, op2->date, op3->date, carry); 
}

void subtractExtendedTime(ExtendedTime* op1, ExtendedTime* op2, ExtendedTime* op3) {
	int borrow = subtractTime(op1->time, op2->time, op3->time);
    subtractDate(op1->date, op2->date, op3->date, borrow);
}

void printExtendedTime(ExtendedTime *e3) {
	printf("Extended Time is %02d/%02d/%04d %02d:%02d:%02d\n", e3->date->day, e3->date->month, e3->date->year, e3->time->hour, e3->time->minute, e3->time->second);
}

int main() {
	Time *t1 = malloc(sizeof(Time));
	Time *t2 = malloc(sizeof(Time));
	Time *t3 = malloc(sizeof(Time));
	Date *d1 = malloc(sizeof(Time));
	Date *d2 = malloc(sizeof(Time));
	Date *d3 = malloc(sizeof(Time));
	ExtendedTime *e1 = malloc(sizeof(Time));
	ExtendedTime *e2 = malloc(sizeof(Time));
	ExtendedTime *e3 = malloc(sizeof(Time));
	
	printf("Enter timeA:");
	scanf("%d %d %d", &t1->hour, &t1->minute, &t1->second);
	printf("Enter dateA:");
	scanf("%d %d %d", &d1->year, &d1->month, &d1->day);
	
	printf("Enter timeB:");
	scanf("%d %d %d", &t2->hour, &t2->minute, &t2->second);
	printf("Enter dateB:");
	scanf("%d %d %d", &d2->year, &d2->month, &d2->day);
	
	e1->time = t1;
	e1->date = d1;
	
    e2->time = t2;
	e2->date = d2;
	
	e3->time = t3;
	e3->date = d3;
	
	addExtendedTime(e1,e2,e3);
	printExtendedTime(e3);
	subtractExtendedTime(e1,e2,e3);
	printExtendedTime(e3);
	
    free(t1); 
    free(t2); 
    free(t3); 
    free(d1); 
    free(d2); 
    free(d3); 
    free(e1); 
    free(e2); 
    free(e3);
    t1 = NULL; 
	t2 = NULL; 
	t3 = NULL; 
	d1 = NULL; 
	d2 = NULL; 
	d3 = NULL; 
	e1 = NULL; 
	e2 = NULL; 
	e3 = NULL;
	return EXIT_SUCCESS;
}
