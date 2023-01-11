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

- Práctica XV: Resolución de ecuaciones diferenciales de orden n con condiciones iniciales. Transformando a sistmeas. Encontramos los siguiente:

