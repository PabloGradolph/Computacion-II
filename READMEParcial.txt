Documento de ayuda para el primer parcial:

    - Práctica VI: Búsqueda de ceros de una función. Usamos bisección, secante y Newton.

        Encontramos:

            · Funcion: Es para definir la función f(x). Esta hay que cambiarla en función del problema.

            · FuncionDerivada: Es para definir la función derivada de f(x), es decir, f'(x). Esta hay que cambiarla en función de la función f(x)
                definida en la función anterior para cada problema.
            
            · Biseccion1: Función para obtener el resultado por el método de la Bisección imprimiendo por pantalla el resultado.
            · Biseccion2: Función para obtener el resultado por el método de la Bisección sin imprimir por pantalla el resultado.

            · Secante1: Función para obtener el resultado por el método de la Secante imprimiendo por pantalla el resultado.
            · Secante2: Función para obtener el resultado por el método de la Secante sin imprimir por pantalla el resultado.

            · Newton1: Función para obtener el resultado por el método de Newton imprimiendo por pantalla el resultado.
            · Newton2: Función para obtener el resultado por el método de Newton sin imprimir por pantalla el resultado.

            · main(): Es importante, además de cambiar la función y su derivada, cambiar los puntos con los que iniciamos las iteraciones de
                cada método: PuntoX1 y PuntoX2 para la bisección. PuntoS1 y PuntoS2 para la secante. PuntoX1 también para Newton (definir uno
                nuevo para Newton si es necesario, en este caso coincidían). Para definir los valores iniciales hay que ver cual es el cero real
                de la función y elegir puntos próximos a éste. También podemos cambiar el valor de la tolerancia ya que cambiará
                el resultado y el número de iteraciones de cada método. Al final también guardamos los resultados en un fichero "iteraciones.txt"
                en el que se va dividiendo el valor de la tolerancia y vemos como necesitamos cada vez más iteraciones (será necesario cambiar
                la tolerancia o la división de la misma si así lo pide el enunciado del ejercicio y también el bucle de impresión en el fichero
                que va de 3 a 12 e igual hay que cambiarlo).
                El número de iteraciones debe ser mayor para la bisección, seguido de la secante y por último de Newton. Si esto no ocurre, 
                sospecha que está mal, aunque no es seguro que esté bien por mucho que esto si que ocurra.

    - Práctica VII: Sistemas de ecuaciones lineales. Método de factorización LU.

        Encontramos:

            · NormaMaximaMatriz: Devuelve el valor máximo de una matriz en valor absoluto (norma máxima). Lo usaremos para comprobar que nuestro resultado
                es correcto.

            · MetodoLu: Función para el cálculo de la solución de un sistema de ecuaciones lineal por el método de factorización LU.
                A esta función hay que pasarle las matrices A (coeficientes del sistema lineal) y B (solución) --> A*X = B (Buscamos X).

            · main(): En el main leemos lo primero los archivos donde están las matrices A y B (identificados los tamaños lo primero).
                Como no podemos leer los datos elevados a menos algo del archivo se ha modificado el código en el main. Hay que comentar
                o eliminar esta parte para una matriz en la que se puedan leer los datos correctamente. También se calcula el error cometido
                en la solución para el ejercicio 2 en particular. Esta parte del código también habría que modificarla para otros problemas.
    
    - Práctica VIII: Sistemas de ecuaciones lineales. Métodos iterativos.

        Encontramos: 

            · DominanteDiagonal: Función que retorna True o False en función de si la matriz pasada como parámetro es Diagonal Dominante o no.
                Es decir, si el elemento de la diagonal es mayor que la suma del resto de elementos de la misma fila (todo en valor absoluto).
                Lo usaremos para que el programa nos avise si la matriz usada no es dominante diagonal y así poder hacer alguna reordenación 
                (si es posible) para mejorar la convergencia.
            
            · NormaMaximaVector: Devuelve el valor máximo de un vector en valor absoluto (norma máxima). Lo usaremos para comprobar que nuestro resultado
                es correcto.
            
            · NormaMaximaMatriz: Devuelve el valor máximo de una matriz en valor absoluto (norma máxima). Lo usaremos para comprobar que nuestro resultado
                es correcto o está dentro de una tolerancia. Cuando esto ocurra terminarán las iteraciones.
            
            · MetodoJacobi: Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Jacobi.
                Hay que cambiar los valores de la solución exacta del sistema para que el proceso pare en algún momento, así como el de 
                la tolerancia.
            
            · MetodoGauss: Función que calcula la solución de un sistema de ecuaciones lineales mediante el método iterativo de Gauss.
                Hay que cambiar los valores de la solución exacta del sistema para que el proceso pare en algún momento.
                También hay que cambiar el valor de if(i<4) en el bucle while en función del tamaño de las matrices. Probablemente nos darán 
                otro tamaño, por ejemplo 3, y habría que poner if(i<3). También puede ser necesario cambiar el valor de la tolerancia.
            
            · main(): En el main se leen las matrices A y B de los ficheros correspondientes, se comprueba que la matriz A sea diagonal dominante,
                se calculan e imprimen los resultados por ambos métodos y te avisa si hay algún error, fuera de la tolerancia (aunque es imposible
                ya que en las propias funciones las iteraciones paran para una cierta tolerancia).
    
    - Práctica IX: Método de factorización LU en sistemas tridiagonales.

        Encontramos:

            · CreacionMatrices.cpp: Genera las matrices tridiagonal y solución específicas de este ejercicio. Probablemente no sea necesario usar 
                este programa en otros ejercicios. Actualmente está para n = 10 aunque para la práctica pedida debería ser n = 1000.
            
            · ResultadoCorrecto: Comprueba que la solución X es correcta comprobando si A*X - B = 0 para cierta tolerancia.

            · Tridiagonal: Función que retorna true o false en función de si la matriz pasada como argumento es tridiagonal o no.

            · Cuadrada: Función que retorna true o false en función de si la matriz pasada como argumento es cuadrada o no.

            · FilasColumnas: Función que compara las columnas de la matriz de coeficientes (A) con las filas de la matriz de términos independientes
                (B) para ver si podemos continuar con la resolución por medio del método.
            
            · LUTridiagonal: Retorna la matriz solución X del sistema de ecuaciones. Para ello tenemos que pasar como argumento la matriz de 
                coeficientes (A) y la de términos independientes (B, aunque en este caso la llamamos F). Las comprobaciones se han hehco antes
                para poder continuar con el método.
            
            · main(): En el main se leen los ficheros donde se encuentran los datos de las matrices. Cambiarlos si es necesario.
                Tenemos que cambiar el tamaño de las matrices n. Ahora está en 10 pero para otros ejercicios habrá que cambiarlo.
                Luego se hacen las comprobaciones: matriz cuadrada, tridiagonal y número de columnas de A coincide con el número
                de filas de B. Se calcula el resultado y se comprueba que es correcto para cierta tolerancia. Los datos de la matriz
                X de soluciones, se guarda en el fichero llamado ResultadoLuTridiagonal.txt.
    
    - Práctica X: Métodos iterativos para sistemas de ecuaciones no lineales. Método de Newton-Raphson.

        Es la práctica en la que más cambios de datos y tamaños de matrices necesitas hacer en función del problema planteado.
        Muy conveniente ayudarte del resumen en estos problemas.

        Encontramos:

            · NormaMaximaMatriz: Devuelve el valor máximo de una matriz en valor absoluto (norma máxima). Lo usaremos para parar el bucle de 
                iteraciones cuando la resta entre la iteración anterior y la nueva sea menor que una tolerancia.
            
            · MatrizFunciones: Función que calcula la matriz f(x) con las 3 funciones del sistema. Esta función es variable y hay que cambiarla
                para cada problema que queramos resolver.
            
            · Jacobiana: Función que calcula la matriz Jacobiana f'(x). Esta función es variable y hay que cambiarla para cada problema en función
                de como sea la matriz f(x) de la función anterior.

            · NewtonRaphson: Función que calcula la solución a un sistema de ecuaciones no lineal por el método iterativo de Newton-Raphson.
                El proceso es iterativo y sigue hasta que la norma máxima de (x(n+1) - x(n)) sea menor que una toleracncia que pasamos como
                argumento. Además, al principio se comprueba que la matriz Jacobiana no es singular para poder calcular la inversa. Mirar la 
                teoría para saber como proceder en caso de que la matriz si que sea singular.
                Tienes que cambiar el tamaño de new_xx para un problema distinto.
            
            · main(): Definimos la matriz xx (x, y, z) (modificar tamaño si es necesario) con los valores iniciales (hay que modificarlos en 
                función del problema). Calculamos la matriz Jacobiana (cambiar tamaño si es necesario). Calculamos la matriz Sol (modificar
                tamaño si es necesario) por medio del método. Comprobamos la solución mediante MatrizFunciones(Sol) = 0 (también hay que 
                modificar el tamaño de la matriz f si es necesario). Calculamos el error cometido para cada variable (también hay que modificar
                el tamaño de la matriz error si es necesario).
    
    - Práctica XI: Diagonalización de una matriz simétrica por el método de Jacobi.

        Encontramos:

            · CalculoMatrizA.cpp: Programa que hace el cálculo de la matriz A a partir de las matrices M y K. Es particular del enunciado de
                este ejercicio. Para otros ejercicios simplemente cambia los valores de la matriz A en el fichero.
            
            · NormaMaximaMatriz: Función para calcular la NormaMáxima que utilizaremos para las comprobaciones.

            · MaxEncimaDiagonal: Función que calcula el máximo valor de los elementos por encima de la diagonal de una matriz. Es necesario
                para desarrollar el método.
            
            · CuadradaSimetrica: Función que devuelve true o false en función de si la función es cuadrada y simétrica o no. Es necesario que
                la matriz sea cuadrada y simétrica para el desarrollo del método.
            
            · TrazaMatriz: Función que calcula la traza de una matriz pasada como argumento (la traza es la suma de los elementos de la diagonal).
                Es interesante para ver como la traza de la matriz no cambia para cada iteración.
            
            · JacobiDiagonal: Función del método de Jacobi para diagonalizar matrices. El proceso es iterativo hasta que el máximo por encima de la 
                diagonal (matriz simétrica, luego máximo también por abajo) esté muy cerca de cero, máximo menor que una tolerancia. 
                En cada iteración se comprueba que la matriz sea cuadrada y simétrica para poder continuar, así como que la traza es invariante.
                Luego se hacen los cáclulos de R y U durante las iteraciones. 
            
            · comprobaciones: Función que comprueba que los resultados obtenidos en las matrices U y Diagonalizada son correctos. Para ello, 
                recorremos la matriz U por columnas. Y hacemos la operacion A*v - lambda*v = 0. Siendo lambda el elemento de la diagonal de la 
                matriz diagonalizada correspondiente a la fila de la matriz U de autovectores (esa fila es v). 
            
            · main(): Se lee la matriz que queremos diagonalizar A a partir del fichero "matrizA.txt" (cambiar los valores para diferentes problemas).
                Se llama a las funciones para realizar el método. Lo único que necesitas cambiar son las tolerancias y los datos de la matriz A.