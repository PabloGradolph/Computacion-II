En esta carpeta .zip, llamada PracticaX, se encuentran los siguientes archivos:

	1. EnunciadoPractica.pdf: Contiene el enunciado con lo que se pide en la práctica.
	2. MetodoNewtonRaphson.pdf: Contiene la información necesaria para realizar el método de Newton-Raphson
	en el que buscamos las soluciones de un sistema de ecuaciones no lineales.
	3. CodigoPracticaX.cpp: Contiene el ´codigo principal de la práctica. En él podemos encontrar las
	siguientes funciones:
		- NormaMaximaMatriz: Función que calcula la norma máxima de una matriz. Es necesario su cálculo
			para la realización del método.
		- MatrizFunciones: Función que devuelve una matriz f con las distintas ecuaciones/funciones
			del sistema de ecuaciones que queremos resolver en este caso (Mirar EnunciadoPractica.pdf).
		- Jacobiana: Función que retorna la matriz Jacobiana de nuestro caso.
		- NewtonRaphson: Función del método Newton-Raphson, retorna la solución del sistema de ecuaciones
			tras un cierto número de iteraciones, en función de una cierta tolerancia.
		- main: Función principal donde se llama al resto de funciones en su orden correspondiente.
			También realizamos la comprobación de que los resultados obtenidos son correctos mediante
			MatrizFunciones(Solución) = 0. Y se calcula el error cometido para cada variable.