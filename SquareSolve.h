/*!
\file
\brief Заголовочный файл для функций обработки и их комментирования
*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define SS_INF_NROOTS (-1)
#define TIME_LEN 26
#define TESTING_FILE "test.txt"
#define TESTING_DEBUG_FILE "debug.txt"
#define TESTING_KEY "alsrjhfvhliufrmhjiuwmrhpw9re98mvrmupwiveumry39"
#define FAILED_TESTING 2
#define NO_RIGHTS 3
#define FNF 1
#define EPS 10e-8

/*!
Решает линейные уравнения (частный случай квадратных уравнений) вида ax + b = 0
\param[in] a, b Параметры уравнения
\param[out] x Корень уравнения
\return Количество корней
*/
int solveLinear(double a, double b, double* c);

/*!
Сравнивает строку1 и строку2
\param[in] str1, str2 строка1 и строка2
\return 1 если строка1 > строка2, -1 если строка1 < строка2, 0 если строка1 = строка2
*/
int compare_str(char *str1, char *str2);

/*!
Решает квадратные уравнения вида ax^2 + bx + c = 0
\param[in] a, b, c Параметры уравнения
\param[out] x1, x2 Корни уравнения
\return Количество корней
*/
int solveSquare(double a, double b, double c, double* x1, double* x2);

/*!
Проверяет решение квадратного уравнения вида ax^2 + bx + c = 0 методом подстановки
\param[in] a, b, c Параметры уравнения
\param[in] x Проверяемый корень уравнения
\return 1 если корень правильный, 0 в противном случае
*/
int checkSquareRoot(double a, double b, double c, double x);

/*!
Проверяет правильность работы функции solveSquare 
\note Для работы требует файл с тестами и ключом
\note Активируется в исходном коде программы
\note Требуются права записи в месте расположения
\return Результат проверки рабты функции solveSquare
*/
int testSquare(void);
