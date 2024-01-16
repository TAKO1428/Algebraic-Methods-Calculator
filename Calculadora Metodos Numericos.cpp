#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#define MAX 128

// Funciones de calculo
float f(float *, int, float);
void fCreate(float *, int *);
float max(float, float);
void printMatrix(float[MAX][MAX], int, int);
void listArray(int, int, float[]);
float der(float *, int, float);
void sDer(int);
void cDer();

// Lista de metodos
void biseccion(void);
void gaussSeidel(void);
void gnInterpolacion(void);
void nrSolve(void);
void simpson(void);
void trapecio(void);

int main() {
    int sel;
    char continuar;

    system("color b"); // Fondo negro, texto cian
    std::cout << "========================================\n";
    std::cout << " CALCULADORA DE METODOS NUMERICOS\n";
    std::cout << "========================================\n";

    do {
        std::cout << "\n---------------- MENU ----------------\n";
        std::cout << "1 - Metodo de Biseccion\n";
        std::cout << "2 - Eliminacion de Gauss-Seidel\n";
        std::cout << "3 - Interpolacion de Newton\n";
        std::cout << "4 - Metodo de Newton-Raphson\n";
        std::cout << "5 - Regla de Simpson\n";
        std::cout << "6 - Regla del Trapecio\n";
        std::cout << "--------------------------------------\n";

        std::cout << "\nIngrese el numero a la izquierda del metodo para elegir.\n";
        std::cout << "\nEleccion-->:";
        std::cin >> sel;
        system("cls");


        switch (sel)
        {
        case 1:
            biseccion();
            break;
        case 2:
            gaussSeidel();
            break;
        case 3:
            gnInterpolacion();
            break;
        case 4:
            nrSolve();
            break;
        case 5:
            simpson();
            break;
        case 6:
            trapecio();
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }

        printf("\n¿Desea realizar otro calculo? (S/N): ");
        scanf(" %c", &continuar); // Nota el espacio antes de %c para consumir cualquier newline anterior
    } while (continuar == 'S' || continuar == 's');

    std::cout << "\n\nGracias por usar la calculadora de metodos numéricos. ¡Hasta luego!\n";
    std::cout << "============== REALIZADO POR TAPIA MONROY YRKO GAEL ==============\n";
	getchar();
	getchar();
	return 0;
}

double evaluarPolinomio(const std::vector<double> &coeficientes, double x)
{
    double resultado = 0;
    int grado = coeficientes.size() - 1;
    for (int i = grado; i >= 0; --i)
    {
        resultado += coeficientes[i] * std::pow(x, i);
    }
    return resultado;
}

void biseccion(void)
{
    int grado;
    std::cout << "Bienvenido al programa para resolver ecuaciones con el metodo de Biseccion.\n";

    // Crear sistema de ecuaciones.
    std::cout << "\n\nCONSTRUIR FUNCION\n-----------------------------------------------\n";
    std::cout << "Introduzca el grado de la funcion: ";
    std::cin >> grado;

    std::vector<double> coeficientes(grado + 1);
    std::cout << "Ingrese los coeficientes de la ecuacion: \n";
    for (int i = 0; i <= grado; i++)
    {
        std::cout << i << ". Coeficiente de termino: ";
        std::cin >> coeficientes[i];
    }

    double a, b;
    double tolerancia = 1e-10; // Tolerancia muy pequeña para una aproximación precisa
    int maxIteraciones;
    std::cout << "Ingrese el intervalo inicial [a, b]\n";
    std::cout << "Valor de a: ";
    std::cin >> a;
    std::cout << "Valor de b: ";
    std::cin >> b;

    // Establece el número de iteraciones
    std::cout << "Ingrese el numero maximo de iteraciones: ";
    std::cin >> maxIteraciones;

    // Iniciar iteraciones
    std::cout << "\nIteracion | " << std::setw(20) << "x"
              << " | " << std::setw(20) << "f(x)"
              << "\n";
    std::cout << std::string(60, '-') << "\n";

    double c;
    for (int i = 0; i < maxIteraciones; i++)
    {
        c = (a + b) / 2;
        double valorFuncion = evaluarPolinomio(coeficientes, c);

        std::cout << std::setw(9) << i + 1 << " | " << std::setw(20) << std::setprecision(12) << c << " | " << std::setw(20) << valorFuncion << "\n";

        if (std::abs(valorFuncion) <= tolerancia)
        {
            std::cout << "\nRaiz encontrada: " << c << "\n";
            return;
        }
        if (evaluarPolinomio(coeficientes, a) * valorFuncion < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }

    std::cout << "\nRaiz aproximada tras " << maxIteraciones << " iteraciones: " << c << "\n";
    getchar();
    getchar();
}

void gaussSeidel(void)
{
    int i, j, p = 1, k, N;
    float A[MAX][MAX], X[MAX], sum;
    printf("Bienvenido al programa para resolver sistemas de ecuaciones lineales mediante el metodo de iteracion de Gauss-Seidel.");
    printf("\nPrimero crea el sistema de ecuaciones necesario.");

    // Crear sistema de ecuaciones.
    printf("\n\nCONSTRUIR FUNCIONES\n-----------------------------------------------\n");
    printf("ADVERTENCIA: En la matriz de coeficientes obtenida del sistema de ecuaciones ingresado, los valores de la diagonal deben ser el valor más alto absoluto de la fila en la que se ubican");
    printf("\nIngrese el grado de la ecuacion: ");
    scanf("%d", &N);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d.Coeficiente de %d variable en la ecuacion: ", i + 1, j + 1);
            scanf("%f", &A[i][j]);
        }
        printf("%d.El numero constante opuesto a la ecuacion en la matriz: ", i + 1);
        scanf("%f", &A[i][N]);
        printf("\n");
    }
    // Imprime la matriz principal resultante
    printMatrix(A, N, N);

    // Establece el número de iteraciones
    printf("\nIngrese el numero de iteraciones: ");
    scanf("%d", &k);

    // Crea e imprime la matriz inicial para los pasos de iteración
    printf("\n\nIngrese los elementos iniciales de la matriz de variables para las iteraciones.");
    for (i = 0; i < N; i++)
    {
        printf("\n%d.Valor inicial para variable: ", i + 1);
        scanf("%f", &X[i]);
    }
    listArray(0, N, X);
    printf("\n");

    // Iniciar iteraciones
    while (p <= k)
    {
        for (i = 0; i < N; i++)
        {
            sum = 0;
            for (j = 0; j < N; j++)
            {
                if (i != j)
                {
                    sum += (A[i][j] * X[j]);
                }
            }
            X[i] = (A[i][N] - sum) / A[i][i];
        }
        listArray(p, N, X);
        printf("\n");
        p++;
    }
    printf("\n\nIteraciones completadas en %d pasos.", k);
    getchar();
    getchar();
}

void gnInterpolacion(void)
{
    int i, j, N;
    float h, k, sum, x, p, A[MAX], M[MAX][MAX];
    printf("Bienvenido al programa de interpolacion de Newton");

    // Determina el valor de diferencia inicial y común para el conjunto de datos
    printf("\n\nPor favor ingrese el valor inicial: ");
    scanf("%3f", &A[0]);
    printf("\n\nIngrese el numero de datos [x y f(x)]: ");
    scanf("%d", &N);
    printf("\nIngrese la cantidad de incremento entre datos: ");
    scanf("%3f", &h);

    // Enumera el conjunto de datos ingresados
    printf("\nDatos(x):\n--------------");
    for (i = 0; i < N; i++)
    {
        A[i] = A[0] + (h * i);
        printf("\nx%d: %3f", i, A[i]);
    }
    printf("\n-----------------------------------\n");

    // Determina la función que crea imágenes de los datos ingresados
    for (i = 0; i < N; i++)
    {
        printf("x%d Introduzca el valor para f(x%d): ", i, i);
        scanf("%3f", &M[i][0]);
    }

    // Cambiar conjuntos para el conjunto de datos creado
    for (j = 0; j < N - 1; j++)
    {
        for (i = 0; i < N - (j + 1); i++)
        {
            M[i][j + 1] = M[i + 1][j] - M[i][j];
        }
    }

    // Enumera el conjunto de datos y los conjuntos de variaciones
    printf("\n\n");
    printf("f(x)\t\t");
    for (i = 1; i < N; i++)
    {
        printf("D%dfo\t\t", i);
    }
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N - i; j++)
        {
            printf("%3f\t", M[i][j]);
        }
        printf("\n");
    }

    // Crea el polinomio requerido para la interpolación y calcula el valor deseado a través de esta función
    printf("\nIngrese el valor que desea calcular en la función del conjunto de datos creado: ");
    scanf("%f", &x);
    k = (x - A[0]) / h;
    sum = M[0][0];
    for (i = 1; i < N; i++)
    {
        p = M[0][i];
        for (j = 0; j < i; j++)
        {
            p *= (k - j);
            p /= j + 1;
        }
        sum += p;
    }
    // Imprime el resultado en la pantalla
    printf("\n\nResultado de la interpolacion:%f", sum);
    getchar();
    getchar();
}

void nrSolve(void)
{
    float p, a, b, k, mul[MAX];
    int i = 2, N;
    printf("Bienvenido al programa de calculo de raíz con el metodo Newton-Raphson.");
    printf("\n\nPrimero crea la funcion principal.");

    // Constructor de funciones (mul -> Coeficientes, N->Número de términos en la función (tamaño de la matriz de coeficientes))
    fCreate(mul, &N);

    // Establece el rango para los valores iniciales que se utilizarán
    do
    {
        printf("\nIngrese el limite inferior del rango para iteraciones: ");
        scanf("%f", &a);
        printf("\nIngrese el limite superior del rango para iteraciones: ");
        scanf("%f", &b);
        if (f(mul, N, a) * f(mul, N, b) > 0)
        {
            printf("\nNo se encontraron raices en el rango que ingreso. Por favor ingrese los valores nuevamente\n");
        }
        else
        {
            printf("\n¡Se encontro al menos 1 raiz en el intervalo!");
        }
        if (b <= a)
        {
            printf("\nEl valor limite superior del rango no puede ser mayor que el valor limite inferior. Vuelva a ingresar los valores para cumplir con las condiciones.");
        }
        printf("\n");
    } while (f(mul, N, a) * f(mul, N, b) > 0 || b <= a); // Continúe tomando hasta que haya una raíz en el rango [a,b] y b>a

    // Compruebe si uno o ambos valores de f(a) y f(b) son iguales a 0 y, de ser así, imprima la raíz directamente
    if (f(mul, N, a) == 0 && f(mul, N, b) != 0)
    {
        printf("\nSe encontro la raiz en el punto a! (%f,0)", a);
    }
    else if (f(mul, N, a) != 0 && f(mul, N, b) == 0)
    {
        printf("\nSe encontro la raiz en el punto b! (%f,0)", b);
    }
    else if (f(mul, N, a) == 0 && f(mul, N, b) == 0)
    {
        printf("\n¡Raiz encontrada en los valores a y b!\nX1[a]:(%f,0)\nX2[b]:(%f,0)", a, b);
    }

    // Si no se encuentra ninguna raíz en los valores límite, iniciamos las iteraciones
    else
    {
        // Condición de parada para iteraciones
        printf("\nIntroduzca el margen minimo de error para las iteraciones: ");
        scanf("%f", &k);

        // Iniciar iteraciones
        printf("\nIteracion %d:\tx%d:%f\tf(x%d):%f\tError:-\t\tMin h.p:%f", i - 2, i - 2, a, i - 2, f(mul, N, a), k);
        p = a - (f(mul, N, a) / der(mul, N, a)); // a = xo, p = x1
        printf("\nIteracion %d:\tx%d:%f\tf(x%d):%f\tError:%f\tMin h.p:%f", i - 1, i - 1, p, i - 1, f(mul, N, p), (p - a), k);
        while (f(mul, N, p) != 0 && (p - a) >= k)
        {
            a = p;
            p = a - (f(mul, N, a) / der(mul, N, a));
            printf("\nIteracion %d:\tx%d:%f\tf(x%d):%f\tError:%f\tMin h.p:%f", i, i, p, i, f(mul, N, p), (p - a), k);
            i++;
        }

        // Estados de finalización
        if ((p - a) < k)
        {
            printf("\n\nIteraciones completadas en %d pasos.", i - 1);
            printf("\nValor raiz aproximado:%f", p);
        }
        else
        {
            printf("\n\nIteraciones completadas en %d pasos.", i - 1);
            printf("\n[X = %f] La raiz fue encontrada!(x%d:%f,f[x%d]:%f)", p, i - 1, p, i - 1, f(mul, N, p));
        }
    }
    getchar();
    getchar();
}

void simpson(void)
{
    int i, j, N, k;
    float a, b, dx, sum, mul[MAX];
    printf("Bienvenido al programa para calcular integrales definidas usando la regla de Simpson.");
    printf("\n\nPrimero crea la funcion principal.");

    // Constructor de funciones (mul -> Coeficientes, N->Número de términos en la función (tamaño de la matriz de coeficientes))
    fCreate(mul, &N);

    // Obtener los valores límite requeridos para una integración específica
    do
    {
        printf("\nIntroduzca el limite inferior de la integral: ");
        scanf("%f", &a);
        printf("\nIngrese el limite superior de la integral (debe ser mayor que el limite inferior): ");
        scanf("%f", &b);
        if (b < a)
        {
            printf("\nEl valor limite superior debe ser mayor que el valor limite inferior.Vuelva a ingresar los valores para adaptarse a las condiciones.");
        }
    } while (b < a); // Siga obteniendo valores hasta que el límite superior sea mayor que el límite inferior

    // Determinar el número máximo de partes en las que se dividirá la función
    printf("\n\nIngrese el numero maximo de iteraciones: ");
    scanf("%d", &k);

    // Iniciar iteraciones
    printf("\n\nITERACIONES:\n----------------------------------------------------\n");
    for (i = 1; i <= k; i++)
    {
        dx = (b - a) / (2 * i);
        sum = f(mul, N, a) + f(mul, N, b);
        for (j = 1; j < (2 * i); j++)
        {
            if (j % 2 == 1)
            {
                sum += 4 * (f(mul, N, (a + (j * dx))));
            }
            else
            {
                sum += 2 * (f(mul, N, (a + (j * dx))));
            }
        }
        printf("\n\n[Iteracion %d]Valor calculado: %f", i, (sum * (b - a)) / (6 * i));
        sum = 0;
    }
    getchar();
    getchar();
}

void trapecio(void)
{
    int i, j, N, k;
    float a, b, dx, sum, mul[MAX];
    printf("Bienvenido al programa de calculo con la regla del trapecio.");
    printf("\n\nPrimero crea la funcion principal.");

    // Constructor de funciones (mul -> Coeficientes, N->Número de términos en la función (tamaño de la matriz de coeficientes))
    fCreate(mul, &N);

    // Obtener los valores límite requeridos para una integración específica
    do
    {
        printf("\nIngrese el limite inferior de la integral: ");
        scanf("%f", &a);
        printf("\nIngrese el limite superior de la integral (debe ser mayor que el limite inferior): ");
        scanf("%f", &b);
        if (b < a)
        {
            printf("\nEl valor limite superior debe ser mayor que el valor limite inferior.Vuelva a ingresar los valores para adaptarse a las condiciones.");
        }
    } while (b < a); // Siga obteniendo valores hasta que el límite superior sea mayor que el límite inferior

    // Determinar el número máximo de partes en las que se dividirá la función
    printf("\n\nIngrese el numero maximo de iteraciones: ");
    scanf("%d", &k);

    // Iniciar iteraciones
    printf("\n\nITERACIONES:\n----------------------------------------------------\n");
    printf("[Iteracion 1] Valor calculado: %f", (b - a) * ((f(mul, N, a) + f(mul, N, b)) / 2));
    for (i = 1; i < k; i++)
    {
        dx = (b - a) / (i + 1);
        sum = f(mul, N, a) + f(mul, N, b);
        for (j = 0; j < i; j++)
        {
            sum += 2 * f(mul, N, (a + ((j + 1) * dx)));
        }
        printf("\n[Interacion %d] Valor calculado: %f", i + 1, (dx / 2) * sum);
    }
    getchar();
    getchar();
}

// Crea Funcion Principal
void fCreate(float *mul, int *size)
{
    int i, N;
    printf("\n\nCREADOR DE FUNCIONES:\n-----------------------------------\n");
    printf("Introduzca el grado de la funcion:");
    scanf("%d", &N);
    *size = N;

    for (i = 0; i <= N; i++)
    {
        printf("%d.Coeficiente del termino:", i);
        scanf("%f", &mul[i]);
    }

    printf("\nFUNCION CREADA:");

    for (i = N; i >= 1; i--)
        printf("(%f)x^%d+", mul[i], i);

    printf("%f", mul[0]);
    printf("\n----------------------------------\n");
}

// Devuelve el valor de la funcion en el punto ingresado
float f(float *a, int size, float x)
{
    int i, j;
    float r, y = a[0];

    for (i = 1; i <= size; i++)
    {
        r = 1;

        for (j = 1; j <= i; j++)
            r = r * x;

        y += r * (a[i]);
    }
    return y;
}

// Funcion para tomar el error maximo
float max(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Imprimir Matriz
void printMatrix(float M[MAX][MAX], int sizeM, int sizeN)
{
    int i, j;
    for (i = 0; i < sizeM; i++)
    {
        for (j = 0; j < sizeN; j++)
        {
            printf("%f\t", M[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

// Listar el resultado de cada iteracion
void listArray(int k, int N, float array[])
{
    int i;
    printf("%d.Valores de la matriz de resultados: \t[", k);
    for (i = 0; i < N; i++)
    {
        if (i != N - 1)
        {
            printf("%f\t", array[i]);
        }
        else
        {
            printf("%f", array[i]);
        }
    }
    printf("]");
}

// Derivadas
// Calcula derivadas para las funciones
float der(float *a, int size, float x)
{
    int i, j;
    float y = a[1], r;
    for (i = 1; i < size; i++)
    {
        r = 1;
        for (j = 1; j <= i; j++)
        {
            r = r * x;
        }
        y = y + (a[i + 1] * (i + 1) * r);
    }
    return y;
}

void sDer(int op)
{
    int N;
    float x, h, mul[MAX], der;
    fCreate(mul, &N);
    printf("\nIngrese valor para derivar: ");
    scanf("%f", &x);
    printf("\nIngrese el valor de la diferencia: ");
    scanf("%f", &h);
    h *= op;
    der = (f(mul, N, x + h) - f(mul, N, x)) / h;
    printf("\nValor derivado en el punto ingresado: %f", der);
}

void cDer()
{
    int N;
    float x, h, mul[MAX], der;
    fCreate(mul, &N);
    printf("\nIngrese valor para derivar: ");
    scanf("%f", &x);
    printf("\nIngrese el valor de la diferencia: ");
    scanf("%f", &h);
    der = (f(mul, N, x + h) - f(mul, N, x - h)) / (h * 2);
    printf("\nValor derivado en el punto ingresado: %f", der);
}
