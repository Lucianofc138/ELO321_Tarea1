README

AUTORES:
-Cristian Herrera Leizgold  201621049-0  cristian.herreral@sansano.usm.cl
-Luciano  Flores  Castillo  201621023-7  luciano.flores@sansano.usm.cl

PROGRAMAS:
-Procesos.c: 
	Este programa crea un proceso padre e hijo los cuales impimen sus fechas y horas respectivas de ejecucion, 
    luego generan un espacio de memoria compartida, por el cual, se comunican en modo productor consumidor, 
    posteriormente el proceso hijo escribe el resultado del algoritmo collatz en la memoria compartida y finalmente 
    el proceso padre lee desde la memoria compartida mostrando 	luego el resultado por pantalla.

	Compilacion: gcc Procesos.c -o exe_proce -lrt
	Ejecucion: ./exe_proce val      (val: numero entero para entrada del programa)
    
-Hilos.c: programa correspondiente a la parte B de la tarea

    Compilacion: gcc Hilos.c -o exe_hilos -pthread
	Ejecucion: ./exe_hilos G  (para la versión con variables globales, Parte B.0, 1 y 2)
               ./exe_hilos L  (para la versión con variables locales,  Parte B.3)