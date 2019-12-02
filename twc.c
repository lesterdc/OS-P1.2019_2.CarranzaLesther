
/*Comando twc proyecto de SO del segundo parcial del 2019
De Lesther David Carranza, Escuela Supeior Politecnica del Litoral*/
#include <pthread.h>
//Esta libreria es la que me permite saber el #de procesadores
#include <omp.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h> //strcmp
#include <stdlib.h> //exit()
typedef unsigned long count_t;
typedef enum {false=0, true=1} bool;
void *thread_function(void *);
void *excess_thread_function(void *);

//Varibles para el conteo total
count_t total_ccount;
count_t total_wcount;
count_t total_lcount;
count_t total_error;

//variables para la suma
count_t sum_total_ccount;
count_t sum_total_wcount;
count_t sum_total_lcount;
count_t sum_total_error;

//Estructura para los procesos
struct thread_data_structure{
   int  thread_id;
   count_t ccount;
   count_t wcount;
   count_t lcount;
   count_t error;
   char buffer[30];
};

int main(int argc, char **argv)
{
	//Obtengo el numero de procesadores del computador
	int NUM_THREADS= omp_get_max_threads();
	//Los imprimo para que el usuario sepa la informacion
	printf("Numero de procesadores que tiene:%d\n",NUM_THREADS);
	//Cada procesador tendra su estructura 
	struct thread_data_structure thread_data[NUM_THREADS];
	FILE *f;
	int m=1;
	//banderas para controlar los atributos de mi comando twc
    bool banL=false;
    bool banW=false;
    bool banMix=false;
    bool banNa=false;
	pthread_t thread[NUM_THREADS],excess_thread;
    if((strcmp(argv[1],"-wl")==0)||(strcmp(argv[1],"-lw")==0)){
		//Control de banderas para las entradas -wl y -lw (son las mismas)
        banMix=true;
        m=m+1;
    }
    if(strcmp(argv[1],"-l")==0){
		//Solamente si se ingresa -l
        banL=true;
        m=m+1;
    }
    if(strcmp(argv[1],"-w")==0){
		//Solamente si se ingresa -w
        banW=true;
        m=m+1;
    }
    if(((strcmp(argv[1],"-l")==0)&&(strcmp(argv[2],"-w")==0))||((strcmp(argv[1],"-w")==0)&&(strcmp(argv[2],"-l")==0))){
		//si se ingresan por separado -l -w o -l -w
        banMix=true;
        m=m+2;
    }
    if(banMix==false && banW==false && banL==false){
		//aqui es si no se pone nada, se mostraran todas las opciones
        banNa=true;
    }
	if (argc < 2)
	//Si el argc es menor a 2 es decir si solamente he ingresado el twc sin ningun otro dato muestra ayuda de como escribir
	 printf ("./twc [-wl] FILE [FILE...]\n");

for (; m < argc; m++)
{
	//Abrimos el archivo al que vamos aplicar twc
  if (f = fopen(argv[m], "rt"))
  {		
	  		//Variables que llevaran las respectivas sumas de lineas, palabras...
			count_t total_ccount=0;
			count_t total_wcount=0;
			count_t total_lcount=0;
			count_t total_error=0;

			int i,excess=0;
			while (!feof(f))
			{
				bool flag=false;
				i=0;
				int round=0;
				//Preparo para resolver con el numero de hilos por procesador
				for(flag=false; i<NUM_THREADS;i++,round++)
				{
					excess=(fread(thread_data[i].buffer, 1, 30, f));
					thread_data[i].thread_id=i;
					if(excess==30){
						//Creo el hilo
						pthread_create(&thread[i], NULL, thread_function, (void *) &thread_data[i]); 
					}		
 					else{	
						thread_data[i].error=excess;
						//creo el hilo
						pthread_create(&excess_thread,NULL, excess_thread_function, (void*) &thread_data[i]);
						//pongo la bandera en true para detener el for
						flag=true;
						break;
					}
				}
				for(i=0; i<round;i++)
				{
					if(pthread_join(thread[i], NULL)){
					fprintf(stderr, "Error joining thread[%d] \n",i);}
					else{
						//Comienzo a sumar word, line, c y errores
						total_ccount+=thread_data[i].ccount;
						total_wcount+=thread_data[i].wcount;
						total_lcount+=thread_data[i].lcount;
						total_error+=thread_data[i].error;
					
       					}
				}
					if(flag){	/*Joing al ultimo hilo*/
				  			if(pthread_join(excess_thread, NULL)){
								fprintf(stderr, "Error joining Excess thread \n");
								}
							else{        
								total_ccount+=thread_data[i].ccount;
								total_wcount+=thread_data[i].wcount;
								total_lcount+=thread_data[i].lcount;
								total_error+=thread_data[i].error;
						


									}
							}
			}
			//Las llaves previamente usadas en las selecciones me sirven para mostrar solo dichos datos que pidio el usuadio
    if(banW==true){
		//Muestro los caracteres o bits
        printf("%s ----->caracteres:%6lu\n",argv[m],total_ccount);
    }
    if(banL==true){
		//Muestro las lineas del doc
        printf("%s ----->Lineas:%6lu\n",argv[m],total_lcount);

    }
    if(banMix==true){
		//Muestro los caracateres y lineas
        printf("%s ----->caracteres:%6lu Lineas:%6lu\n",argv[m],total_ccount,total_lcount);

    }if(banNa==true){
		//Muestro todos los datos
        printf("%s -----> caracteres:%6lu palabras:%6lu Lineas:%6lu caracspecial: %6lu\n",argv[m],total_ccount,total_wcount,total_lcount,total_error);

    }
//Cierto el archivo
fclose(f);


sum_total_ccount+=total_ccount;
sum_total_wcount+=total_wcount;
sum_total_lcount+=total_lcount;
sum_total_error+=total_error;

}

else
{
	//Si no puedo abrir el archivo, muestro el error
	printf("Error Opening File %s", argv[m]);
}

}

if(m>2)
{
		//printf("total_todos---> caracteres:%6lu palabras:%6lu Lineas:%6lu specialcara: %6lu\n",sum_total_ccount,sum_total_wcount,sum_total_lcount,sum_total_error);


}

}

//Funcion para los hilos
void *thread_function(void *threadarg)
{

   struct thread_data_structure *my_data;
   my_data = (struct thread_data_structure *) threadarg;
	my_data->ccount=0;
	my_data->wcount=0;
	my_data->lcount=0;
	my_data->error=0;

   int k=0;
   		while(k<30)
		{
		
			if(isalpha(my_data->buffer[k])|| my_data->buffer[k]== '.'){

				my_data->ccount++;
			}
			else if(my_data->buffer[k]=='\n')
			{
			my_data->wcount++;

				my_data->lcount++;
				my_data->ccount++;
			}
			else if(my_data->buffer[k]== ' ')
			{

				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
			}
			else
			{
				my_data->error++;
				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;

			}

		//Limpio la salida estandar		
		fflush(stdout);
		//sumo en uno la variable usada en el while
		k++;
		}
}


void *excess_thread_function(void *threadarg)
{
   struct thread_data_structure *my_data;
   my_data = (struct thread_data_structure *) threadarg;
   int excess= my_data->error;
	my_data->ccount=0;
	my_data->wcount=0;
	my_data->lcount=0;
	my_data->error=0;
   int k=0;




   		while(k<excess)
		{
		
			if(isalpha(my_data->buffer[k] || my_data->buffer[k]== '.')){
	
				my_data->ccount++;
			}
			else if(my_data->buffer[k]=='\n')
			{
				my_data->wcount++;
				
				my_data->lcount++;
				my_data->ccount++;
			}
			else if(my_data->buffer[k]== ' ')
			{

				my_data->ccount++;

				my_data->wcount++;
			}
			else
			{
				my_data->error++;

				my_data->ccount++;
				if(isalpha(my_data->buffer[k+1]))
				my_data->wcount++;
				
			}
		fflush(stdout);
		k++;
		}
}

