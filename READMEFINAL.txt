Documento informativo para la parte práctica del examen final de enero:

- Práctica XII: Derivación Numérica. Encontramos las siguientes funciones:
    · NormaMaximaVector: Calcula la norma máxima de un vector pasado como argumento.
    · DiferenciasCentrales: Función que calcula la derivada NUMÉRICA por el método de las diferencias centrales.
    · DiferenciaAlante: Función que calcula la derivada NUMÉRICA por el método de diferencia hacia adelante.
    · DiferenciaAtras: Función que calcula la derivada NUMÉRICA por el método de diferencia hacia detrás.
    · DerivadaVelocidad: Función que calcula la derivada Analítica de x(t) = -70 + 7t + 70e^(-t/10) respeco a t que es igual a la velocidad.
    · DerivadaAceleracion: Función que calcula la derivada Analítica de v(t) (función anterior) respeco a t que es igual a la aceleración.
    · main(): Se cuentan las líneas del fichero y se guardan los datos en vectores creados de forma dinámica. Se calcula la derivada numérica
        con las funciones anteriores. Para el primer valor se usa DiferenciaAlante, para el último se usa DiferenciaAtras y para el resto DiferenciasCentrales.
        Se hace lo mismo de forma analítica. Luego se repite todo el proceso para calcular la aceleración (segunda derivada).
        Se guardan los resultado en un fichero.
    
    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - Las funciones DerivadaVelocidad y DerivadaAceleracion para la ecuación analítica que corresponda en nuestro problema.
        - Tener cuidado con el fichero posicion.txt (el formato tendría que ser igual a este para que funcione el programa).
        - La forma de guardar los resultados en los ficheros es peculiar, podría ser necesario cambiar esto para otro problema.
        - Salen por separado los resultados numéricos y analíticos, que luego es lo que se pide comparar. Como está con \t no es mayor problema para representar.
    
- Práctica XIII: Integración numérica. Encontramos las siguientes funciones:
    · Radianes: Función que calcula los radianes en función de los grados pasado como argumento.
    · Funcion: Función que devuelve el valor de la función que usamos en nuestro caso. La función en este caso depende de Theta y Fi.
    · FuncionCG: Función que devuelve la función con cambio de variable que necesitamos para calcular la Cuadratura Gaussiana.
    . 

    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - Tener en cuenta que nuestra función depende de dos parámetros: Theta lo vamos cambiando (enunciado) y Fi varía en función de los intervalos que escojamos.
        - Para FuncionCG, Fi es a lo que llamamos u en la fórmula del cambio. 
    
- Práctica XIV: Ecuaciones diferneciales de primer orden con condiciones iniciales: Método de Euler. Encontramos las siguientes cosas:
    EDOReales: 
        · En Ejercicio1 encontramos la función de la resolución de una ecuación diferencial por el método de Euler para un xmax.
        · En Ejercicio2 encontramos las funciones de la la resolución de una ecuación diferencial por los métodos de Euler RK2 y RK4 para un xmax.
        · Encontramos también un archivo con las funciones para crear ficheros de forma automática para estos métodos.
    En la práctica:
        · Encontramos la función de Euler pero pasando como argumento una tolerancia y haciendo do while en vez de xmax y npasos. Esto sirve cuando no 
            tenemos el valor de xmax.
        · FuncionYPrima que devuelve el valor de nuestra función particular.
        · También está la función de nombrar ficheros de forma automática para el método de Euler.
    
    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - Tener claro si tenemos el valor de xmax o tenemos un límite para escoger entre la función que hace do while y la que tiene un número de pasos preestablecido.
        - La FuncionYPrima para nuestro caso en particular.
        - Luego tendríamos que cambiar los datos del problema: xmin, xmax, h, tolerancia, la condición inicial...

- Práctica XV: Resolución de ecuaciones diferenciales de orden n con condiciones iniciales. Transformando estas a sistmeas. Encontramos los siguiente:
    EDOMatrices:
        · Ejercicio1: Encontramos la función para resolver sistemas de ecuaciones diferenciales de orden 1 por Euler.
        · Ejercicio2: Encontramos las funciones para resolver sistemas de ecuaciones diferenciales de orden 1 por RK2 y RK4.
        TENER EN CUENTA QUE SON PARA UN XMAX.
    En la práctica:
        · SistemaYPrima: Devuelve el valor del sistema en forma de matriz para el caso concreto del enunciado de la práctica.
        · Encontramos las tres funciones vistas anteriormente EulerSistemas, RK2Sistemas y RK4Sistemas.

    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - Ver si necesitamos xmax y por tanto calcular npasos o cambiamos a un do while hasta cierta tolerancia como en la práctica anterior (Comentado).
        - Los nombres de los ficheros.
        - Los datos h, n(tamaño matrices), tmin, tmax, (o xmin/xmax), a2 si usas RK2 por otro método.
        - Las condiciones iniciales (y0).
        - Añadir tolerancia si se hace por do while.

- Práctica XVI: Resolución de ecuaciones diferenciales de segundo orden con condiciones de contorno: Método del disparo. Encontramos:
    · uReal: Función que devuelve la solución analítica del problema planteado.
    · SistemaYPrima: Devuelve el valor de la matriz sistema de nuestro caso. (Una vez transformado).
    · RK4Sistemas: Método de Ronge-Kutta de cuarto orden para sistemas de ecuaciones diferenciales de primer orden. 
    · main(): Datos iniciales, primera y segunda suposición del método, interpolación hasta que el resultado real menos el nuestro esté por debajo de una tolerancia.

    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - Los valores iniciales para nuestro problema en particular: h, n(número de ecuaciones del sistema), rmin, rmax, tol y condición inicial (tras la primera suposición).
        - La función uReal (tiene que ser específica de cada problema).
        - La función SistemaYPrima (tiene que ser específica de cada problema).
        - Como ya haces el while en el main creo que no es necesario, pero igual tienes que cambiar la función del método de RK4, cambiando el for por un while hasta cierta condición.

- Práctica XVII: Resolución de ecuaciones diferenciales de segundo orden con condiciones de contorno: Método del las diferencias finitas. Encontramos:
    · uReal: Función que devuelve la solución analítica del problema planteado.
    · polP: Función que devuelve el polinomio p(x) para nuestro caso.
    · polQ: Función que devuelve el polinomio q(x) para nuestro caso.
    · polR: Función que devuelve el polinomio r(x) para nuestro caso.
    · ResultadoCorrecto: Función que retorn true o false en función de si la solución X del sistema A*X = B es correcta.
        Para ello calcula A*X - B y tiene que estar muy cercano a cero en función de una tolerancia.
    · Cuadrada: Función para comprobar si la matriz es cuadrada.
    · FilasColumnas: Función que devuelve true o false en función de si el número de columnas de A es igual al número de filas de B.
    · Tridiagonal: Función que retorna true o false en función de si la matriz pasada como argumento es tridiagonal o no.
    · LuTridiagonal: Función que ejecuta el método LU para el caso donde la matriz A pasada como argumento es tridiagonal.
    · EDODiferenciasFinitas: Función que calcula la matriz solución del sistema aplicando DiferneciasFinitas para llegar a un sistema de ecuaciones
        y, posteriormente, calcular su resultado medianete el método LuTridiagonal.
    · main(): Se definen las variables iniciales, se calcula el número de pasos que hay que dar, se guardan los resultados en un fichero, calculando a su vez 
        los errores cometidos. Este proceso se repite 3 veces para 3 valores de h distintos en nuestro caso.
    
    --- COSAS QUE HABRÍA QUE CAMBIAR ---
        - La función uReal (tiene que ser específica de cada problema).
        - Los polinomios p, q y r, se tienen que ajustar a nuestro problema. En nuestro caso q y r eran iguales a 0.
        - Los valores iniciales de nuestro problema: h, rmin, rmax, las condiciones de contorno...
        - Los nombres de los ficheros de salida si fuese necesario.
    
- Práctica XVIII: Caso específico de resolución de ecuaciones diferenciales: El movimiento del péndulo de Foucault.

    La diferencia con el resto de prácticas anteriores es que aquí se pide hallar el valor de h necesario para que la precisión de la solución esté por debajo
    de cierta tolerancia. Para ello hemos creado un bucle do while en el main del programa que compara una solución obtenida con la anterior hasta que la diferencia
    entre estas esté por debajo de la tolerancia. De esta forma sacamos el valor de h, que se va multiplicando por 0.5 en cada iteración.