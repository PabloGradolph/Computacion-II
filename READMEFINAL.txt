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