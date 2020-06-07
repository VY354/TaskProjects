//Подключаем стандаотную библтотеку ввода и вывода
#include <stdio.h>
//Подключаем математическую библиотеку
#include <math.h>
//Прототип функции для ввода области поиска корня
float* InputBorder(int,float,float);
//Прототип функции нахождения корня. Один из аргументов - указатель га массив с границами поиска
float FindRoot(float*,float,float,int,int);
//Прототип функции для проверки знаков функции на граниче отрезка
int CheckSign(float,float,float,float,int);
//Прототип функции для рассчета значения функции
float CulcExpr(float,float,float,int);
//главная функция
int main(){
	
	//очистка экрана перед началом работы
	system("clear");
	//переменные для хранения точности и номера функции
	int accr,choose;
	//коэффициенты в функциях
	float a,b;
	//выводи список доступных функций
	printf("Choose equasion:\n");
	printf("1: Y = log2(ax)-b\n");
	printf("2: Y = x^4+ax^3-bx\n");
	printf("3: Y = x^5+ax^2-b\n");
	printf("4: Y = ax+b\n");
	printf("5: Y = a*x^3+b\n");
	printf("6: Y = a/(1+e^(-x+b))-1\n");
	//просим ввести номер функции
	printf("Enter number of equasion: "); scanf("%d",&choose);
	//цикл для проверки существования функции с введенным номером
	while(choose<1 || choose>6){
		//просим повторно ввести номер функции
		printf("There is no equasion with this number. Please, enter correct number: "); scanf("%d",&choose);
	}
	//просимм ввести знач
	printf("Enter value of parameter a: "); scanf("%f",&a);	
	//доп. условие для логарифма
	if(choose==1){
		//проверка на правильность введенного значения
		while(a<=0){
			//повторно просим ввести параметр
			printf("Incorrect data. Please, enter other value of a ( a>0 ): "); scanf("%f",&a);
		}
	}
	//просим ввести значение параметра b
	printf("Enter value of parameter b        : "); scanf("%f",&b);
	//Просим ввести точность ( количество знаков после зяпятой )
	printf("Enter accuracy (signs after comma): "); scanf("%d",&accr);
	//вывод значения х, при котором у=0
	printf("Y ~ 0 when x = %f\n",FindRoot(InputBorder(choose,a,b),a,b,accr,choose));
	//так как функция main типа int, то она должна что-то возвращать
	return 0;
}
//реализация функции для ввода границ поиска. Она возвращаем указатель на массивБ в котором хранятся границы
float* InputBorder(int choose,float a,float b)
{
	//задаем переменные для хранения границ и указатель на массив
	float left,right,*pBorder;
	//создаем статической массив для границ ( static, чтобы при выходе из функции он не удалялся )
	float static Border[2];
	//заносим в указатель массив, т.е. ссылку на его 1-ый элемент
	pBorder=Border;
	//просим ввести левую нраницу поиска
	printf("Choose Left  border of searching:"); scanf("%f",&left);
	//заносим значение в 1 элемент массива
	Border[0]=left;
	//снова доп. условие для логарифма
	if(choose==1)
	{
		//проверка корректности введенных значений
		while(left<=0)
		{
			//говорим пользователю в каких пределах должно быть значение
			printf("Left  border of searching must be >= 0.\n");
			//просим ввести границу
			printf("Incorrect data. Please, enter other value ( Left>=0 ): "); scanf("%f",&left);
			//заносим значение в 1 элемент массива
			Border[0]=left;
		}
	}
	//просим ввести значение правой границы поиска
	printf("Choose Right border of searching: "); scanf("%f",&right);
	//заносим значение во 2 элемент массива
	Border[1]=right;
	//проверка на то, чтобы значения функции от крайних значений не имели одинаковый знак 
	//В условии финкция CheckSign вернет либо 0, либо 1
	while(CheckSign(left,right,a,b,choose))
	{
		//просим ввести левую границу
		printf("Choose Left  border of searching: "); scanf("%f",&left);
		//заносим ее в массив
		Border[0]=left;
		//снова доп. условие для логарифма
		if(choose==1)
		{
			//проверяем корректность значения
			while(left<=0)
			{
				//нопоминание пользователю
				printf("Left  border of searching must be >= 0.\n");
				//просим ввести левую границу
				printf("Incorrect data. Please, enter another value ( Left>=0 ): "); scanf("%f",&left);
				//зносим значение в массив
				Border[0]=left;
			}
		}
		//просим ввести правую границу
		printf("Choose Right border of searching: "); scanf("%f",&right);
		//заносим в массив
		Border[1]=right;
	}
	//возвращаем указатель на массив Border
	return pBorder;
}
//реализация функции для проверка знака, использует как условие в функции InputBorder
int CheckSign(float left,float right,float a,float b,int choose)
{
	//задаем переменные для хранения значений функции на границах
	float LeftExpr,RightExpr;
	//считаем значения исходя их номера функции, которую выбрал пользователь
	switch(choose){
		//если 1 номер
		case(1):{
			//считаем значение на левой ганице
			LeftExpr=log2(a*left)-b;
			//считаем значение на правой границе
			RightExpr=log2(a*right)-b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 2 номер
		case(2):{
			//считаем значение на левой ганице
			LeftExpr=powf(left,4)-a*powf(left,3)-b*left;
			//считаем значение на правой границе
			RightExpr=powf(right,4)-a*powf(right,3)-b*right;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 3 номер
		case(3):{
			//считаем значение на левой ганице
			LeftExpr=powf(left,5)+a*powf(left,2)-b;
			//считаем значение на правой границе
			RightExpr=powf(right,5)+a*powf(right,2)-b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 4 номер
		case(4):{
			//считаем значение на левой ганице
			LeftExpr=a*left+b;
			//считаем значение на правой границе
			RightExpr=a*right+b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 5 номер
		case(5):{
			//считаем значение на левой ганице
			LeftExpr=a*powf(left,3)+b;
			//считаем значение на правой границе
			RightExpr=a*powf(right,3)+b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 6 номер
		case(6):{
			//считаем значение на левой ганице
			LeftExpr=a/(1+exp(-left+b))-1;
			//считаем значение на правой границе
			RightExpr=a/(1+exp(-right+b))-1;
			//здесь break не нужет, т.к. дальше нет вариантов
		}
	}
	//проверка совпадения знаков функции на границах поиска
	if((LeftExpr>=0&&RightExpr>=0)||(LeftExpr<=0&&RightExpr<=0)){
		//увежомляем пользователя о неправильно введенных данных и возвращаем 1, чтобы в функции InputBorder заного ввести значения границы
		printf("Incorrect data. Y(Left) and Y(Right) have same sign. Please, enter another value.\n");
		return 1;
	}
	else
		//все норм, значения введены корректно
		return 0;
}
//реализация функции для вычисления значения функции в центре выбранного отрезка поиска
float CulcExpr(float center,float a,float b,int choose){
	//вводим переменную для вычисления значения функции
	float expr;
	//считаем значения исходя их номера функции, которую выбрал пользователь
	switch(choose){
		//если 1 номер
		case(1):{
			//считаем значение в центре
			expr=log2(a*center)-b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 2 номер
		case(2):{
			//считаем значение в центре
			expr=powf(center,4)+a*powf(center,3)-b*center;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 3 номер
		case(3):{
			//считаем значение в центре
			expr=powf(center,5)+a*powf(center,2)-b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 4 номер
		case(4):{
			//считаем значение в центре
			expr=a*center+b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 5 номер
		case(5):{
			//считаем значение в центре
			expr=a*powf(center,3)+b;
			//выходим из switch, чтобы не проверять остальные условия
			break;
		}
		//если 6 номер
		case(6):{
			//считаем значение в центре
			expr=a/(1+exp(-center+b))-1;
		}
	}
	//возвращаем значение функции в центре
	return expr;
}
//реализация функции для нахождения нуля функции
float FindRoot(float* pBorder,float a,float b,int accr,int choose)
{   /*вводим переменную для контроля зацикливания программы ввиду того,
	  что при реальном вычислении (left+right)/2, при малых значения точности, значение округляется ближайшего left или right
	*/
	int i=0;
	//вводим пременные для: хранения выражения, левой границы, правой границы и центра
	float expr,left,right,center;
	//присваиваем левой границе значение первого элемента массива Border
	left=*pBorder;
	//присваиваем правой границе значение второго элемента массива Border
	right=*(pBorder+1);
	//вычисляем центр отрезка
	center=(left+right)/2;
	//вычисляем значение функции в этой точке
	expr=CulcExpr(center,a,b,choose);
	//цикл для поиска нуля функции
	while(1){
		/*взял условие i>100, т.к. в большинстве случаев необходимо сделать ~30 вычислений центра и значения функции в нем.
		  если программа зациклится, то значения центра будет постоянно находиться в указанном интервале точности, ввиду округления до ближайшего
		  левого или правого края, а при больших значения номера итерации они будут близки к значению в центре.
		*/
		if(i>100){
			//говорим пользователю, что невозможно определить точное значение центра
			printf("ERROR: couldn't define center.\n");
			//выводм последнее значение центра, то есть значения, где функция почти была равна 0
			printf("Last center is: %-10f\n",center);
			//преррываем работу цикла while
			break;
		}
		//проверка точности вычисления. значение функции в центре отрезк находится в пределах точности
		if(expr<=pow(10,-accr) && expr>=-pow(10,-accr))
			//прерываем работу цикла while
			break;
		//если значние функции в центре больше нуля, то мы должны рассматривать левую часть отрезка, т.е. [ left ; center ]
		if(expr>0) right=center;
		//иначе правую часть
		else left=center;
		//считаем значение центра для нового отрезка
		center=(left+right)/2;
		//считаем значение функции в этой точке
		expr=CulcExpr(center,a,b,choose);
		//увеличиваем счетчик на 1
		i++;		
	}
	//возвращаем значение точки, где функция ~0
	return center;
}
