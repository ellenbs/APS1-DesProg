# APS 1 - Geometria Computacional
> Insper - Instituto de Ensino e Pesquisa \
> 5º Semestre - Engenharia da Computaçāo \
> Antonio Fonseca, Ellen Shen e Enrico Damiani

Este arquivo consiste em resumir o funcionamento das funções utilizadas no projeto. Temos um problema de um [Ponto em Polígono](https://en.wikipedia.org/wiki/Point_in_polygon), um clássico da Geometria Computacional, que foi resolvido por meio do algoritmo de Ray Casting.

## Funções

1. Verify Double: 
- Ela verifica se dois números do tipo <b>double</b> são iguais, utilizando o módulo da diferença entre os dois.
- Entradas:
```sh
int verify_double(double number1, double number2);
```
2. Categorize Points:
- Categoriza qual ponto possui maior valor no <b>eixo Y</b>.
- Entradas:

```sh
void categorize_points(point *p_low, point *p_high, point a, point b);
```

3. Line Equation:
- Calcula a reta entre dois pontos e seus coeficientes.
- Entradas:

```sh
void line_equation(double *angular_coeficient, double *linear_coeficient, double *constant_x, point p_low, point p_high);
```
4. Calculate Projected for P_Y:
- Calcula o valor projetado de X para o Y do ponto dado, usando a equação linear.
- Entradas:

```sh
double calculate_projected_for_p_y(double constant_x, double a, double b, point p);
```
5. Compare Projected with P_X:
- Compara o valor projetado de X com o X do ponto dado, verificando se o ponto se encontra a esquerda, em cima ou a direita da reta.
- Entradas:

```sh
int compare_projected_with_p_x(double projected, point p, point p_high, point p_low);
```

6. Type of Projected:
- Calcula como o ponto projetado se comporta, caso caia em uma situaçāo em que "corta um canto", "raspa um canto", ou que uma parede está sobre uma parede. Utilizamos a estratégia chamada de <b>perturbaçāo</b>.
- Entradas:

```sh
iint type_of_projected(int projected, point p, point p_low, point p_high);
```
7. Verify:
- Verifica se o ponto está, exatamente sobre a aresta, se um raio disparado dele para a direita cruza a aresta ou o caso contrário.
- Entradas:

```sh
int verify(point p, point a, point b);
```

8. Inside:
- Verifica se o ponto está dentro do polígono.
- Entradas:

```sh
int inside(point p, point poly[], int n);
```
