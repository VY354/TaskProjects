#include <stdio.h>
#include<stdlib.h>

int main()
{
  system("clear");
  
  /*Обозначение переменных*/
  int t1, t2, t3;
  float d, e, q;
  
  printf("введите число t1:"); scanf("%d",&t1);
  printf("введите число t2:"); scanf("%d",&t2);
  printf("введите число t3:"); scanf("%d",&t3);
  printf("введите число  d:"); scanf("%f",&d);
  printf("введите число  e:"); scanf("%f",&e);
  
  printf("------------------\n");
  
  /*Проверка на наличие решения q1*/
  if (d==0 || t1==0)
	printf("Для q1 решений нет\n");
  else
    {
	q=((t1+t2/t3)/d)*(e/(t3+t2/t1));
	printf("Ответ: q1 = %f\n",q);
    }

  /*Проверка на наличие решения q2*/		
  if (t1==0 || t2==0 || t3==0)
	printf("Для q2 решений нет\n");
  else
    {
	q=(1.0/t1-2/t2+3/t3)*10e-3;
	printf("Ответ: q2 = %f\n",q);
    }
	
  /*Проверка на наличие решения q3*/
  if (t2==0 || t3==0 || e==-0.5)
	printf("Для q3 решений нет\n");
  else
    {
	q=1/3+t1/(t2*t3)+(t1*t3)/t2+d/(e+0.5);
	printf("Ответ: q3 = %f\n",q);
    }
	
  return  0;  
}


