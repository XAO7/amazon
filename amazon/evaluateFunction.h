//evaluateFunction.h�����ݵ�ǰ���̼�������ֵ
//

#include"AlphaBeta.h"
#include"DataStruct.h"
#include<math.h>

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

//���ֱ���---����ȫ�ֱ���
extern double t1, t2;    //��������ֵ,t1----queenmove  t2----kingmove
extern double c1, c2;   //λ������ֵ,c1---queenmove   c2---kingmove
extern double w, s;

//KingMove��QueenMove��ģ������----����ȫ�ֱ���
extern int KingmoveBlack[12][12];
extern int KingmoveWhite[12][12];
extern int QueenmoveBlack[12][12];
extern int QueenmoveWhite[12][12];
extern int Mobility[12][12];//���ȵ�����
extern int aWhite[4];
extern int aBlack[4];

/////////��������//////////
void SearchKingMove();
void SearchQueenMove();
void t1account();
void t2account();
void c1account();
void c2account();
void MobilitySearch();
void aaccount();
void saccount();
double evaluateAll();
