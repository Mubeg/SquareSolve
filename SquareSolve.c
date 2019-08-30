/*!
\file
\brief Главный файл программы

Данный файл содержит функции обработки, тестирования и управления программой
*/

#include "SquareSolve.h"

#define SWITCH_TESTING_ON

int compare_str(char *str1, char *str2){

	const int len1 = strlen(str1);
	const int len2 = strlen(str2);
	int min_len = (len1 > len2)? len2: len1;

	for(int i = 0; i < min_len; i++){
		if(str1[i] > str2[i]){
			return  1;
		}
		else if(str1[i] < str2[i]){
			return -1;		
		}
	}
	
	if(len1 == len2){
		return 0;	
	}
	return (len1 > len2)? 1 : -1;
}

int is_equal(double first, double second){
	return fabs(first - second) < EPS;
}

int solveLinear(double a, double b, double* x){
	assert(x != NULL);
	if(a == 0)
		return  (b == 0)? SS_INF_NROOTS : 0;
	*x = -b/a;
	return 1;
}

int solveSquare(double a, double b, double c, double* x1, double* x2){
	
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));

	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	double d = b*b - 4*a*c;
	if(is_equal(a, 0))
		return solveLinear(b, c, x1);
	if(is_equal(d, 0)){
		*x1 = -b/(2*a);
		return 1;
	}
	else if(d < 0)
		return 0;

	*x1 = (-b - sqrt(d))/(2*a);
	*x2 = (-b + sqrt(d))/(2*a);
	return 2;
}

int checkSquareRoot(double a, double b, double c, double x){
	return fabs(a*x*x + b*x + c) < 0 + EPS;
}

int testSquare(void){
	int failedTesting = 0;
	FILE *file;
	FILE *errors;
	if((errors = fopen(TESTING_DEBUG_FILE, "a")) == NULL){
		return NO_RIGHTS;
	}
	if((file = fopen(TESTING_FILE, "r")) == NULL){
		return FNF;
	}

	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	char key[46];
	int nTests = 0;
	fscanf(file, "%46s %d", key, &nTests);
	assert(compare_str(key, TESTING_KEY) == 0);
	for(int i = 1; i <= nTests; i++){
		x1 = 0;
		x2 = 0;
		int checkNumeration = 0;
		fscanf(file, "%d) %lg %lg %lg", &checkNumeration, &a, &b, &c);
		assert(checkNumeration == i);
		int nRoots = solveSquare(a, b, c, &x1, &x2);
		time_t curTime = time(NULL);
		switch(nRoots){
			case 0:
				if((b*b - 4*a*c < 0 || (a == 0 && b == 0)))
					continue;
				fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = %d\n\n", ctime(&curTime), checkNumeration, a, b, c, nRoots);
				failedTesting = 1;
				break;
			case 1: 
				if(checkSquareRoot(a, b, c, x1))
					continue;
				fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = %d; x = %lg\n\n", ctime(&curTime), checkNumeration, a, b, c, nRoots, x1);
				failedTesting = 1;
				break;
			case 2: 
				if(checkSquareRoot(a, b, c, x1))
					continue;
				else{
					fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = %d; x1 = %lg\n\n", ctime(&curTime), checkNumeration, a, b, c, nRoots, x1);
					failedTesting = 1;
					break;
				}
				if(checkSquareRoot(a, b, c, x2))
					continue;
				else{
					fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = %d; x2 = %lg\n\n", ctime(&curTime), checkNumeration, a, b, c, nRoots, x2);
					failedTesting = 1;
					break;
				}

			case SS_INF_NROOTS:
				if(fabs(a) < EPS && fabs(b) < EPS && fabs(c) < EPS)
					continue;
				fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = SS_INF_ROOTS\n\n", ctime(&curTime), checkNumeration, a, b, c);
				failedTesting = 1;
				break;
			default:
				fprintf(errors, "%sError: test №%d a: %lg b: %lg c: %lg -- Output = %d\n\n", ctime(&curTime), checkNumeration, a, b, c, nRoots);
				failedTesting = 1;
				return 1;
		} 
	}
	fclose(errors);
	fclose(file);
	if(failedTesting){
		return FAILED_TESTING;
	}
	return 0;
}

int main(){
	#ifdef SWITCH_TESTING_ON 
		int answer = testSquare();
		switch(answer){
			case 0: printf("Тестирование пройдено успешно\n");
				break;
			case FNF: printf("Файл с тестами не найден\n");
				return 2;
			case FAILED_TESTING: printf("Тестирование не пройдено\nОтправьте файл %s на почту %%s\n", TESTING_DEBUG_FILE);
				return 2;
			case NO_RIGHTS: printf("Пожалуйста, запустите программу от имени более привелигерованного пользователя\n");
				return 2;
			default: printf("main(): ERROR: Unexpexted output from testSquare()\n");
				return 2;
		}
		return 0;
	#endif
	double  a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	scanf("%lg %lg %lg", &a, &b, &c);
	//printf("%lg %lg %lg\n", a, b, c);
	int nRoots = solveSquare(a, b, c, &x1, &x2);

	switch(nRoots){
		case 0: printf("No roots\n");
			break;
		case 1: printf("x = %lg\n", x1);
			break;
		case 2: printf("x1 = %lg\nx2 = %lg\n", x1, x2);
			break;
		case SS_INF_NROOTS: printf("Any number\n");
			break;
		default: printf("main(): ERROR: invalid nroots = %d\n", nRoots);
			return 1;
	} 
	return 0;
}
