/*
* @file :   "Hilos.c"
* @author : Luciano  Flores  Castillo
            Cristian Herrera Leizgold
* @date :   8/11/2020
* @brief :  Código para la parte A de la tarea 1 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int sucesion_Collatz (int n); 

int main(int argc, char * argv[]) {
    pid_t pid;
    const int SIZE = 4096;
    const char *name = "SM";
    int shm_fd;
    void *ptr;
    char buf[40];
    struct timeval time;
    
    if(argc < 2){ // para corroborar si se incluyó un número al correr
        printf("Usage: <executable> val \n");
        printf("with val a integer number \n");
        return 0;
    }

    int a = atoi(argv[1]);
    if (a < 0)
    {
        printf("Error, numero ingresado %d menor a 0.\n",a);
        return 0;
    }
    /*Crea el proceso hijo*/
    pid = fork();
    if(pid == 0) {
        /*Obtiene la fecha y hora del proceso*/
        gettimeofday(&time,NULL);
        strftime(buf,40, "Fecha y Hora %m - %d - %Y/%T",localtime(&time.tv_sec));
        printf("%s PID hijo %d\n",buf,getpid());
        /*Crea memoria compartida*/
        shm_fd = shm_open(name,O_CREAT|O_RDWR,0666);
        ftruncate(shm_fd,SIZE);
        ptr = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
        /*Ciclo de collatz*/
        while(a>1) {
               a = sucesion_Collatz (a);  	
               /*Escribe a memoria compartida*/
               sprintf(ptr,"%d",a);
               ptr += sizeof(a);
               }
    }
    /*Proceso padre*/
    else {
        /*Espera un tiempo para verificar que el proceso hijo pasa al estado zombie*/
        sleep(5);
        /*Espera a que termine el proceso hijo*/
        wait(NULL);
        /*Obtiene la fecha y hora del proceso*/
        gettimeofday(&time,NULL);
        strftime(buf,40, "Fecha y Hora %m - %d - %Y/%T",localtime(&time.tv_sec));
        printf("%s PID padre %d\n",buf,getpid());
        /*Crea memoria compartida*/
        shm_fd = shm_open(name,O_RDONLY,0666);
        ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
        /*Lee desde la memoria compartida*/
        while(*(char *)ptr > 1) {
               /*Escribe a la salida*/
               printf("%s\n",(char *)ptr);	
               ptr += sizeof(a);
        }
        /*Remueve el espacio de memoria compartida*/
        shm_unlink(name);
    }
    return 0;
}


/*Funcion de Collatz*/
int sucesion_Collatz (int n) {
        int aux; 
        if(n%2 == 0){
               aux = n/2;
        }
        else {
               aux = 3*n + 1;
        }
        return aux;
}