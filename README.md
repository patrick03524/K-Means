# Practica De Clustering
Universidad Católica San Pablo
Estructuras de Datos Avanzadas
CComp6-1
Patrick Xavier Márquez Choque
## Tabla de Contenidos
* [Introducción](#introducción)
* [Líbrerías Necesarias](#librerías-necesarias)
* [Resultados](#resultados)

## Introducción
El código se desarolló en C++.
Se implementó el método de Clustering K-Means
K-Means es un algoritmo de Clustering que tiene como objetivo particiones de grupos de datos en base a una determinada cantidad de centroides que utilizarán los valores más cercanos para formar parte de su cluster o grupo. En este algoritmo se implemento la distancia euclidiana para calcular la distancia de cada punto x y de su determinado centroide.
También se obtuvieron 2 métodos para resolver esto:
* Un método utilizando 100 000 filas del dataset enviado por el correo, que corresponden a las dimensiones del Dataset de Amazon Start_Lon y Start_Lan como x e y respectivamente; se realiza en primer lugar un filtrado de todas las filas para solo obtener el dataset deseado en el archivo sample.csv.
* Un método utilizando cantidades ingresadas por el usuarios de números aleatorios. Una cantidad determinada de numeros aleatorios como las dimensiones x e y y una cantidad determinada de centroides como el algoritmo lo desarrolla.

##  Librerías Necesarias
OPENGL & FreeGLUT para la parte gráfica
OpenGL+FreeGLUT-2.8.1+glew-1.10.0

##  Resultados
El resultado al compilar es el siguiente: 

![Alt text](https://github.com/patrick03524/K-Means/blob/main/img/1.PNG)

Resultados al escojer el segundo método con 1000 números aleatorios y 3 centroides.

![Alt text](https://github.com/patrick03524/K-Means/blob/main/img/5.PNG)

Resultados al escojer el segundo método con 1 000 000 números aleatorios y 10 centroides.

![Alt text](https://github.com/patrick03524/K-Means/blob/main/img/4.PNG)

Resultados al escojer el segundo método con 14 000 000 números aleatorios y 10 centroides.

![Alt text](https://github.com/patrick03524/K-Means/blob/main/img/3.PNG)
