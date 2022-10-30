En esta carpeta .zip, llamada PracticaXI, se encuentran los siguientes archivos:

	1. EnunciadoPractica.pdf: Contiene el enunciado con lo que se pide en la práctica.
	2. Jacobi_AutovaloresyAutovectores.pdf: Contiene la información necesaria para realizar el método 
	de Jacobi con el que obtenemos los autovalores y autovectores de una matriz cuadrada y simétrica.
	3. CalculoMatrizA.cpp: Contiene el código necesario para calcular la matriz A, que será la que 
	utilizaremos en el método de Jacobi para diagonalizar. Esta matriz A es la que se nombra en el 
	enunciado de la práctica como matriz Kr y es obtenida a partir de los datos de los archivos 
	matrizK.txt y matrizM.txt con los datos del enunciado.
	4. CodigoPracticaXI.cpp: Contiene el código principal de la práctica. En él podemos encontrar las 
	siguientes funciones:
		- NormaMaximaMatriz: Utilizada para calcular la norma máxima de una matriz pasada como 
			argumento. La utilizamos para hacer las comprobaciones de que los resultados son 
			son correctos dentro de cierta tolerancia.
		- MaxEncimaDiagonal: Calcula el valor máximo de una matriz por encima de la diagonal de la 
			misma. Es necesario su cálculo para realizar el método de Jacobi.
		- CuadradaSimetrica: Función que devuelve true o false en función de si la matriz pasada
			como argumento es a la vez cuadrada y simétrica. Se requiere que las matrices sean de 
			esta forma para realizar el método de Jacobi.
		- TrazaMatriz: Función que devuelve la traza (suma de la diagonal) de la matriz pasada como 
			argumento. La utilizamos para comprobar que la traza es invariante entre iteraciones.
		- JacobiDiagonal: Función que realiza el método de Jacobi explicado en el archivo 
			Jacobi_AutovaloresyAutovectores.pdf para obtener los autovalores y autovectores de la 
			matriz A.
		- Comprobaciones: Devuelve true o false en fucnión de si los resultados obtenidos son correctos.
		- main: Función principal donde se leen los datos de la matriz A y se va llamando a las funciones
			en su orden correspondiente.
	5. matrizM.txt, matrizK.txt: Archivos donde se encuentran las matrices M y K obtenidas a partir del 
	enunciado y las cuales utilizaremos para sacar la matriz Kr = A con la que trabajaremos a partir del
	código encontrado en el archivo CalculoMatrizA.cpp.
	6. matrizA.txt: Archivo generado a partir del código encontrado en CalculoMatrizA.cpp. Este archivo será
	el que leeremos para sacar los datos de la matriz con la que vamos a trabajar en el código encontrado en
	CodigoPracticaXI.cpp.
