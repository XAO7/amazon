//AmazonGame.h�������������ļ�ͨ�õĽṹ��Step��Point
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

typedef struct _Point { //��ṹ
	int x = 4, y = 4;
}Point, SPosition;

typedef struct _Step { //���ṹ
	Point start, end, bar;
	double value = 0;
}Step;



