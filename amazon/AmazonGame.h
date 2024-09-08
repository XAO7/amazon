//AmazonGame.h：定义了所有文件通用的结构体Step和Point
#pragma once
#define BLACK 0
#define WHITE 1
#define EMP 2
#define BAR 3

#define ERROR_TIME_MAX 5

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<ctime>
using namespace std;

typedef struct _Point { //点结构
	int x = 4, y = 4;
}Point, SPosition;

typedef struct _Step { //步结构
	Point start, end, bar;
	double value = 0;
}Step;



