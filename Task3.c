//подключаем стандартную библтотеку ввода вывода и потока ошибок
#include <stdio.h>
//подключаем стандартную математическую библтотеку
#include <math.h>
//подключаем стандартную библитотеку с функциями для выделения памяти
#include <stdlib.h>
//подключаем стандартную библитотеку для использования функкий работы со временем
#include <time.h>
//подкллючаем бибилтотеку для работы со строками
#include <string.h>
//прототип функции для запонения массива операндов
void Fill_Number_Arr(int**,char*,int);
//прототип функции для заполения массива приопритетов операций
void Fill_Priority(int**,char*);
//прототип функции для построения последовательности операций
void Build_Operation_Sequence(char**,char*,int,int);
//прототип функции для рассчета арифметического выраджения
float Culc_Expr(int*,char*,int*);
//прототип функции для выполнения текущй операции
void Do_Operation(int*,int*,int,int*);
//прототип функции для добаления операции
void Add_Operation(char*,int*);
//прототип функции для удаления операции
void Delete_Operation(char*,int*);
//прототип функции для проверки наличия операции в списке
int Check_Operation(char*,int,char);
//простотип функции в которой будет происходить игра
int Play(float,int*,char*);
//главная функция
int main()
{
	//очищаем экран консоли
	system("clear");
	//задаем переменные для длины выражения, длины чисел, и изнасальный 
	//размер массива лоступных операций
	int LengthExpr, LengthNumber,SizeOperationArr=2;
	//переменная для действия
	int key;
	//указатель на массив приоритетов операций
	int *Priority=NULL;
	//указатель на массив чисел
	int *NumberArr=NULL;
	//указатели на миссив доступных операций и массив текущей последовательности операций
	char *OperationArr=NULL,*CurrentOperationArr=NULL;
	//выделяем память для начального заполнения массива достпных действий
	OperationArr=(char*)realloc(OperationArr,SizeOperationArr*sizeof(char));
	OperationArr[0]='+';
	OperationArr[1]='-';
	//выделяем память для массивов
	CurrentOperationArr=(char*)malloc(sizeof(char));
	NumberArr=(int*)malloc(sizeof(int));
	Priority=(int*)malloc(sizeof(int));
	//просим пользователья ввести длину выражения и чисел
	printf("Enter length of expression (number of operations) ----> "); scanf("%d",&LengthExpr);
	printf("Enter length of numbers    (number of digits)     ----> "); scanf("%d",&LengthNumber);
	system("clear");
	//цикл для игры
	while(1)
	{
		//выводим перечень доступных действий и некоторую дополнительную информацию
		printf("------------------------------------------------------|\n");
		printf("1 - Play                                              |\n");
		printf("2 - Add operation                                     | Available operations | "); puts(OperationArr);
		printf("3 - Delete operation                                  |\n");
		printf("4 - Change length of expression (number of operations)| Length of expression | %d\n",LengthExpr);
		printf("5 - Change length of numbers    (number of digits)    | Length of numbers    | %d\n",LengthNumber);
		printf("------------------------------------------------------|\n");
		printf("0 - exit                                              |\n");
		printf("------------------------------------------------------|\n");
		printf("----> ");
		scanf("%d",&key);
		if(key==0) break;
		//выполняем уод в зависимости от выбранного дейтсивия
		switch(key)
		{
			//если выбрали "играть"
			case(1):
			{
				//выводим на эеран правила игры
				system("clear");
				printf("-------------------------------------------\n");
				printf("You have 1 minute to answer\n");
				printf("If you give wrong answer you lose 10 points\n");
				printf("If time out you also lose 10 points\n");
				printf("When your points < 0 game end\n");
				printf("-------------------------------------------\n");
				printf("Enter 1 to continue "); scanf("%d",&key);
				//цикл для запуска последовательности функций до тех пор, пока не введем 0
				while(key==1)
				{
					//создаем выражение
					Build_Operation_Sequence(&CurrentOperationArr,OperationArr,LengthExpr,SizeOperationArr);
					//запоняем чесловой массив
					Fill_Number_Arr(&NumberArr,CurrentOperationArr,LengthNumber);
					//заполняем массив приоритетов операций
					Fill_Priority(&Priority,CurrentOperationArr);
					//запускаем функцию "играть", и, если значение=, которое она вернет меньше 0, то game over
					if(Play(Culc_Expr(NumberArr,CurrentOperationArr,Priority),NumberArr,CurrentOperationArr)<0)
					{
						system("clear");
						printf("                 >>> GAME OVER <<<\n");
						break;
					}
					printf("-------------------------------------------\n");
					//спрашиваем у пользователя хочет ли от продолжить
					printf("Want continue? ( 1 / 0 ) ----> "); scanf("%d",&key);
					system("clear");
				}
				break;
			}
			//если выбрали добаление еще одной операции
			case(2):
			{
				system("clear");
				Add_Operation(OperationArr,&SizeOperationArr);
				system("clear");
				break;
			}
			//если выбрали удаление операции
			case(3):
			{
				//проверяем не является ли массив доступных дейтсвий пустым
				if(OperationArr==NULL)
				{
					system("clear");
					printf("         >>> OperationArr is empty <<<\n");
					break;
				}
				system("clear");
				Delete_Operation(OperationArr,&SizeOperationArr);
				system("clear");
				break;
			}
			//если выбрали изменение длины выражения
			case(4):
			{
				system("clear");
				printf("Enter new length of expression ----> "); scanf("%d",&LengthExpr);
				system("clear");
				break;
			}
			//если выбрали  изменение длины числа
			case(5):
			{
				system("clear");
				printf("Enter new length of numbers ----> "); scanf("%d",&LengthNumber);
				system("clear");
				break;
			}
			//если ввели не существующее действие
			default:
			{
				system("clear");
				printf("         >>> There is no such action <<<\n");
			}
		}
	}
	return 0;
}
//реализация функции, где происходит игра
int Play(float Result, int *NumberArr, char *CurrentOperationArr)
{
	//переменные для вывода выражения, ответа игрока, и дейтвия
	int i=0,j=0,answ,key;
	//переменная для хранения счета игрока
	static int Score=0;
	//переменные для хранения текущего времени
	time_t currT,newT;
	//переменная для хранения разницы начального и текущего времени
    int diff;
	//если счет менбше 0, то game over
	if(Score<0) Score=0;
	system("clear");
	//цикл для вывода выражения на экран
	while(j<strlen(CurrentOperationArr)+1)
		{
			if(CurrentOperationArr[j]!='(' && CurrentOperationArr[j]!=')')
			{
				printf("%d%c",NumberArr[i],CurrentOperationArr[j]);
				i++;
			}
			if(CurrentOperationArr[j]=='(')
			{
				printf("%c",CurrentOperationArr[j]);
			}
			if(CurrentOperationArr[j]==')')
			{
				printf("%d%c%c",NumberArr[i],CurrentOperationArr[j],CurrentOperationArr[j+1]);
				i++;
				j++;
			}
			j++;
		}
	printf("\n-------------------------------------------\n");
	//заносим в переменную время в секундах
	time(&currT); 
	//просим пользователя ввести ответ
	printf("SCORE | %d\n",Score);
	printf("------------------------\n");
	printf("Enter answer ----> "); scanf("%d",&answ);
	//сохраняем текущее время в секундах
	time(&newT);
	//высчитываем разницу времен
	diff = difftime(newT,currT);
	//если она больше минуты, то говорим. что превышем лимит времени
	if(diff>=60)
	{
		system("clear");
		Score-=10;
		printf("    >>> TIME OUT <<<");
		printf("------------------------\n");
		printf("SCORE | -10\n");
		printf("------------------------\n");
		printf("Rigth answer is | %d\n",(int)Result);
	}
	//если ответ совпал
	else if(answ==(int)Result)
	{
		system("clear");
		Score+=10;
		printf(" >>> You are RIGHT <<<\n");
		printf("------------------------\n");
		printf("SCORE | +10\n");
	}
	//если ответ не совпал
	else if(answ!=(int)Result)
	{
		system("clear");
		Score-=10;
		printf("     >>> WRONG <<<\n");
		printf("------------------------\n");
		printf("SCORE | -10\n");
	}	
    //возвращаем в main счет игрока
	return Score;
}
//реализация функции для заполнения массива чисел для выражения
void Fill_Number_Arr(int **NumberArr,char *CurrentOperationArr, int LengthNumber)
{
	//генерим "случайную" последовательность
	srand(time(NULL));
	int i=0,j=0;
	//проходимся по всей длине массива текущих операций
	while(j<strlen(CurrentOperationArr)+1)
	{
		//если встретили операцию, то нужно добаить число
		if(CurrentOperationArr[j]!='(' && CurrentOperationArr[j]!=')')
		{
			(*NumberArr)=(int*)realloc((*NumberArr),++i*sizeof(int));
			(*NumberArr)[i-1]=1+rand()%(int)(pow(10,LengthNumber));
		}
		// если встретили ")" то нужно добавить число и прейти в массиве операций на 2 вперед
		if(CurrentOperationArr[j]==')')
		{
			(*NumberArr)=(int*)realloc((*NumberArr),++i*sizeof(int));
			(*NumberArr)[i-1]=1+rand()%(int)(pow(10,LengthNumber));
			j++;
		}
		//переходим на следующий знак массива действий
		j++;
		
	}
}
//реализация функции для проверки наличия операции в списке доспутных
int Check_Operation(char *OperationArr, int SizeOperationArr,char act)
{
	int i;
	//если выбранная оперция уже существует, то возвращаем истину иначе ложь
	for(i=0;i<SizeOperationArr;i++) if(act==OperationArr[i]) return 1;
	return 0;
}
//реализация функции для добавления операции в список доступных
void Add_Operation(char *OperationArr,int *SizeOperationArr)
{
	//переменне для хранения выбранного знака и действия
	char act;
	int i,key;
	//цикл для добавления действий
	while(1)
	{
		//визуальное оформление
		printf("------------------------------------------------------\n");
		printf("Available operations | "); puts(OperationArr);
		printf("------------------------------------------------------\n");
		printf("Choose operation\n");
		printf("------------------------------------------------------\n");
		printf("1 : +\n");
		printf("2 : -\n");
		printf("3 : *\n");
		printf("4 : /\n");
		printf("5 : ^\n");
		printf("------------------------------------------------------\n");
		printf("0 - exit\n");
		printf("------------------------------------------------------\n");
		printf("----> ");
		scanf("%d",&key);
		if(key==0) break;
		//инициализируем переменную act в зависимости от выбранного действия
		switch(key){
			case(1):{act='+';break;}
			case(2):{act='-';break;}
			case(3):{act='*';break;}
			case(4):{act='/';break;}
			case(5):{act='^';break;}
			default:{
				system("clear");
				printf("          >>> There is no such operation <<<\n");
				continue;
			}
		}
		//проверяем отсутсвияе такой операции в списке доступных
		if(Check_Operation(OperationArr,*SizeOperationArr,act)){
			system("clear");
			printf("          >>> This operation is already here <<<\n");
		}
		//иначе добавляем в список
		else{
			system("clear");
			OperationArr=(char*)realloc(OperationArr,++(*SizeOperationArr)*sizeof(char));
			OperationArr[*(SizeOperationArr)-1]=act;
		}
	}
}
//реализация функцуии для удаления действия из списка доступных
//функция аналогична предыдущей.
void Delete_Operation(char *OperationArr,int *SizeOperationArr)
{
	char act;
	int i,key;
	while(1)
	{		
		printf("------------------------------------------------------\n");
		printf("Available operations | "); puts(OperationArr);
		printf("------------------------------------------------------\n");
		printf("Choose operation\n");
		printf("------------------------------------------------------\n");
		printf("1 : +\n");
		printf("2 : -\n");
		printf("3 : *\n");
		printf("4 : /\n");
		printf("5 : ^\n");
		printf("------------------------------------------------------\n");
		printf("0 - exit\n");
		printf("------------------------------------------------------\n");
		printf("----> ");
		scanf("%d",&key);
		if(key==0) break;
		switch(key)
		{
			case(1):{act='+';break;}
			case(2):{act='-';break;}
			case(3):{act='*';break;}
			case(4):{act='/';break;}
			case(5):{act='^';break;}
			default:
			{
				system("clear");
				printf("          >>> There is no such operation <<<\n");
				continue;
			}
		}
		if(Check_Operation(OperationArr,*SizeOperationArr,act)==0){
			system("clear");
			printf("          >>> There is no such operation <<<\n");
		}
		else{
			system("clear");
			i=0;
			//чтобы удалить действияе, нужно дойти до него и сдвинуть все жлементы после него на 1 слево
			while(OperationArr[i]!=act) i++;
			for(i;i<*SizeOperationArr;i++) OperationArr[i]=OperationArr[i+1];
			OperationArr=(char*)realloc(OperationArr,--(*SizeOperationArr)*sizeof(char));
			if(*SizeOperationArr==0) OperationArr=NULL;
		}
	}
}
//реализвация функции для построения последовательности операций, включая скобки
void Build_Operation_Sequence(char **CurrentOperationArr,char *OperationArr,int LengthExpr, int SizeOperationArr)
{	
	srand(time(NULL));
	//act - хранение текущего действия из массива доступных операций
	//CurrSize хранение текущего размера текущего массива операций
	int i=0,j=0,act,CurrSize=0;
	//UseOpenBracket - триггер для установки (
	//UseCloseBracket -  триггер для установки )
	//CountOpen - счет кодичества открывающихся скобок
	//CountClose - счет числа закрывающихся скобок
	int UseOpenBracket=0,CountOpen=0;
	int UseCloseBracket=0,CountClose=0;
	(*CurrentOperationArr)=(char*)malloc(sizeof(char));
	/*Дальше идет алгоритм для корректной расстаноки скобок
	Если честно, я очень много вренени уже потратил на это задание, 
	в особенности на на этот алгоритм и алгоритм счета выражения
	И этот алгорим я писал по меньшей мере неделю назад, и не хочу внова вникать в то, как он работает
	могу лишь сказать то, что расстановка скобок, как "(" ,так и ")" зависит от того, 
	на какой позиции мы находимся
	и от того, сколько уже есть "(" или ")" */
	while(i<=LengthExpr)
	{
		act=OperationArr[rand()%(int)SizeOperationArr];
		UseOpenBracket=rand()%100;
		if(UseOpenBracket>=0 && UseOpenBracket<30 && (*CurrentOperationArr)[CurrSize-1]!=')')
		{
			/*Условие маскимальной позиции для '(' */
			if(i<LengthExpr-CountOpen-1)
			{
				(*CurrentOperationArr)=(char*)realloc((*CurrentOperationArr),(CurrSize+=1)*sizeof(char));
				j=CurrSize;
				(*CurrentOperationArr)[j-1]='(';
				CountOpen++;
			}
		}
		/*иначе просто добаляем символ*/
		if(i<LengthExpr)
		{
			(*CurrentOperationArr)=(char*)realloc((*CurrentOperationArr),(CurrSize+=1)*sizeof(char));
			j=CurrSize;
			(*CurrentOperationArr)[j-1]=act;
		}
		UseCloseBracket=rand()%100;
		if(UseCloseBracket>=0 &&UseCloseBracket<30)
		{
			/*Условие максимальной позиции ')' */
			if(i<LengthExpr-CountOpen && CountOpen>CountClose )
			{
				(*CurrentOperationArr)=(char*)realloc((*CurrentOperationArr),(CurrSize+=1)*sizeof(char));
				j=CurrSize;
				(*CurrentOperationArr)[j-1]=')';
				CountClose++;
			}
		}
		/*Если дошли до знака с номером большим, чем LengthExpr-CountOpen-1 и количество '(' больше чем ')', то
		  Закрываем скобки*/
		else if(i>=LengthExpr-CountOpen-1 && CountOpen>CountClose)
		{
			(*CurrentOperationArr)=(char*)realloc((*CurrentOperationArr),(CurrSize+=1)*sizeof(char));
			j=CurrSize;
			(*CurrentOperationArr)[j-1]=')';
			CountClose++;
		}
		i++;
	}
	//добавляем символ конца строки
	(*CurrentOperationArr)[CurrSize]='\0';
}
//реализвация функции для заполения массива приоритетов в соответсвии с  CurrentOperationArr
void Fill_Priority(int **Priority, char *CurrentOperationArr)
{
	int i;
	char Op;
	(*Priority)=(int*)realloc((*Priority),strlen(CurrentOperationArr)*sizeof(int));
	//просто проходимя то массиу текущих операций и запоняем массив приоритетов в соответсвии с операцией
	for(i=0;i<strlen(CurrentOperationArr);i++)
	{
		Op=CurrentOperationArr[i];
		if(Op=='+'){(*Priority)[i]=1;continue;}
		if(Op=='-'){(*Priority)[i]=2;continue;}
		if(Op=='*'){(*Priority)[i]=4;continue;}
		if(Op=='/'){(*Priority)[i]=5;continue;}
		if(Op=='^'){(*Priority)[i]=7;continue;}
		if(Op=='('){(*Priority)[i]=-1;continue;}
		if(Op==')'){(*Priority)[i]=-2;continue;}
	}	
}
//реализация функции для выполения дейтвия в текущем массиве операций
void Do_Operation(int *NumArr,int *CurrPriority, int Op, int *m)
{
	int A,B;
	//берем два последних элемента массива с текущими цислами
	B=NumArr[*m-1];
	A=NumArr[*m-2];
	//записываем в предпоследний элемент значение вычисления
	if(Op==1) NumArr[*m-2]=A+B;
	else if(Op==2) NumArr[*m-2]=A-B;
	else if(Op==4) NumArr[*m-2]=A*B;
	else if(Op==5) NumArr[*m-2]=A/B;
	else if(Op==7) NumArr[*m-2]=powf(A,B);
	//цменьшаем массив на 1
	--(*m);
	NumArr=(int*)realloc(NumArr,(*m)*sizeof(int));
}
//реализвация функции для вычисления выражения
float Culc_Expr(int *NumberArr, char *CurrentOperationArr, int *Priority)
{
	//переменные для проходов по массивам
	int i=0,j=0,m=0,n=0;
	//NumArr - массив текущих чисел
	//CurrPriority - массив текущих действий
	int *NumArr=NULL;
	int *CurrPriority=NULL;
	CurrPriority=(int*)malloc(sizeof(int));
	//добаляем в массив текущих действий перове число
	m++;
	NumArr=(int*)realloc(NumArr,m*sizeof(int));
	NumArr[m-1]=NumberArr[n];
	//цикл для вычисленияЯ, проходимся по всем символам массива выражения
	while(CurrentOperationArr[i]!='\0') 
	{
		//если встретили открывающуюся скобку
		if(Priority[i]==-1)
		{
			//добавлем ее в массив текущих дейсвтвий
			j++;
			CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
			CurrPriority[j-1]=Priority[i];
		}
		//если встретили закрывающюся скобку
		else if(Priority[i]==-2)
		{
			//Идем влево пока не дойдем до "("
			while(CurrPriority[j-1]!=-1)
			{
				//выполняем действие
				Do_Operation(NumArr,CurrPriority,CurrPriority[j-1],&m);
				--j;
				CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
			}
			//Удаляем "(" из массива
			--j;
			CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
		}
		//в противном случаи
		else
		{
			//смотрим имеет ли последняя операция массива приоритет больше или такой же, как текущая
			//если да то выполняем ее пока приоритет не будет меньше
			while(CurrPriority[j-1]>=Priority[i]-1 && j>0)
			{
				Do_Operation(NumArr,CurrPriority,CurrPriority[j-1],&m);
				--j;
				CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
				continue;	
			}
			//добалячем число
			m++;
			n++;
			NumArr=(int*)realloc(NumArr,m*sizeof(int));
			NumArr[m-1]=NumberArr[n];
			//добавляем знак
			++j;
			CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
			CurrPriority[j-1]=Priority[i];
		}
		//переходим на след. знак массива CurrentOperationArr
		i++;		
	}
	//идем влево пока не закончитсчя массив CurrPriority
	while(j>0)
	{
		Do_Operation(NumArr,CurrPriority,CurrPriority[j-1],&m);
		--j;
		CurrPriority=(int*)realloc(CurrPriority,j*sizeof(int));
	}
	//возвращаем нудевой элемент массива. В нем по итогу будет ответ
	return NumArr[0];
	//Этот же алгоритм, записанный словестно
	//-------------------------------------
	//Если текущий знак "("
			//добавляем скобку
	//Иначе если текущий знак ")"
		//Идем влево пока не дойдем до "("
			//выполняем действие
			//Уменьшаем стек действий на 1
		//Когда дошли до "(" еще раз уменьшаем стек на 1
	//Иначе
		//Пока приоритет предыдущего больше или равен текущему
				//выпоняем предыдущий
		//добавляем число
		//добавляем знак
}









