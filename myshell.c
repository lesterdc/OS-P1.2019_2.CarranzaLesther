/*Proyecto shell de SO del segundo parcial del 2019
De Lesther David Carranza G. Escuela Superior Politecnica del Litoral*/
#include <stdio.h>
#include <string.h> //strcmp
#include <stdlib.h> //exit()
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pthread.h>


#define MAXCOM 1000 //Este sera el numero maximo de letras que sera soportado
#define MAXLIST 100 // este sera el numero maximo de comandos soportados

#define clear() printf("\033[H\033[J") //esto es para limpiar la shell usando secuencias de escape

//Esta es una funcion de bienvenida de mi shell, es para darle toque propio

//Esta es la funcion de inicio del shell
void init_shell(){
    //limpio antes todo lo que haya estado
    clear();
    printf("\n\n\n\n***********************"
        "************************"); 
    printf("\n\n\n\t******Mi primera Shell******"); 
    printf("\n\n\t-Proyecto de SO Lesther Carranza-"); 
    printf("\n\n\t\t+Opciones\n\n\t\t*help\n\n\t\t*hello\n\n\t\t*cd\n\n\t\t*twc\n\n\t\t*exit\n");
    printf("\n\n\n\n************************"
        "***********************\n");
    char* username = getenv("USER"); //aqui obtenemos el usuario 
    printf("\n\n\nUSER is: @%s", username);  //Lo imprimimos
    printf("\n"); 
    sleep(1); 
    //clear(); 
}

//esta funcion se encarga de tomar las entradas
int takeInput(char* str){
    char* buf;
    buf = readline("\nSO<201601374>sh% "); //Esto es como que quiero que se vea la toma de datos
    if(strlen(buf) !=0){
        add_history(buf);
        //Copio el buf
        strcpy(str,buf);
        return 0;
    }else{
        return 1;
    }
}


//Esta es la funcion para imprimir el actual directorio (pwd)
void printDir(){
    char cwd[1024];
    //aqui obtengo el actual directorio con el cual trabajo
    getcwd(cwd,sizeof(cwd));
    //Aqui lo imprimo en pantalla
    printf("\nDir: %s",cwd);
}

//Esta es la funcion donde se ejecutaran los comandos del sistema
void execArgs(char** parsed){
    //Comenzamos haciendo un fork 
    pid_t pid = fork();
    if(pid == -1){
        printf("\nFallo en la creacion de un hijo");
        return;
    }else if(pid == 0){
        if(execvp(parsed[0],parsed)<0){
            printf("\nNo se pudo ejecutar el comando");
        }
        exit(0);
    }else{
        //Espera a que el hijo termine
        wait(NULL);
        return;
    }
}

//Funcion donde el comando pipe del sistema es ejecutado
void execArgsPiped(char** parsed, char** parsedpipe) { 

    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nPipe no pudo ser inicializado"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nNo se pudo hacer fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // El hijo 1 se esta ejecutando  
        close(pipefd[0]); 
        //Creo una copia del descriptor
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nNo se pudo ejecutar el comando 1...."); 
            exit(0); 
        } 
    } else { 
        // El padre se encuentra ejecutando 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nNo se pudo hacer fork"); 
            return; 
        } 
  
        // El hijo 2 se esta ejecutando

        if (p2 == 0) { 
            close(pipefd[1]); 
            //creo una copia del descriptor
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                printf("\nNo se pudo ejecutar el comando 2...."); 
                exit(0); 
            } 
        } else { 
            // El padre esta ejecutando, se encuentra esperando a los 2 hijos
            wait(NULL); 
            wait(NULL); 
        } 
    } 
}


//Esta es solo una funcion para imprimir una ayuda
void openHelp(){
    
    puts("\n***BIENVENIDO A LA AYUDA DE MI SHELL***"
        "\nProyecto de SO de Lesther Carranza"
        "\nEstos son los comandos que hasta ahora tiene mi shell pero tambien puede usar los comandos locales:"
        "\n>cd"
        "\n>ls"
        "\n>twc"
        "\n>exit"); 
  
    return; 
}

//Comando twc 





//Aqui comenzamos con los comandos que describi en la pantalla de ayuda
int ownCmdHandler(char** parsed){
    char *args[]={"./twc"};
    int NoOfOwnCmds = 5, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
    //Este es el arreglo de funciones que yo doy disponibles
    //(aparte de las que puedo llamar externamente)
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "twc";

    for (i = 0; i<NoOfOwnCmds;i++){
        if(strcmp(parsed[0],ListOfOwnCmds[i])==0){
            switchOwnArg=i+1;
            break;
        }
    }

    switch(switchOwnArg){
        case 1:
            printf("\nHasta la proxima\n");
            //Aqui hago esperar un momento para lograr visualizar el mensaje previo
            sleep(1);
            clear();
            exit(0);
        case 2:
        //Aqui hago cambiar el directorio por lo que ingrese en pantalla
            chdir(parsed[1]);
            return 1;
        case 3:
            //La funcion de ayuda de mi shell
            openHelp();
            return 1;
        case 4:
            //Esta es una funcion de saludo que le agregue a mi shell
            username=getenv("USER"); //con getenv obtengo la varible USER que es del mismo sistema
            printf("\nHola %s.\nEste es mi proyecto de SO\n"
            "Escribe help para mas informacion de la shell...\n",username);
            return 1;
        case 5:
        //Mustro como utilizar el comando twc
            printf("./twc [-wl] FILE [FILE...]\n");
            return 1;
        default:
            break;
    }
    return 0;
}


//Esta es una funcion para buscar el pipe
int parsePipe(char* str, char** strpiped){
    int i;
    for(i = 0; i<2; i++){
        //si encuentro el caracter | reconocera el pipe
        strpiped[i] = strsep(&str, "|");
        if(strpiped[i]==NULL)
            break;
    }
    if(strpiped[i]==NULL)
        return 0; //Esto es si el pipe no es encontrado
    else
    {
        return 1;
    }
}

//Funcion para hacer el parsin de los comandos
void parseSpace(char* str, char** parsed){
    int i;
    for(i = 0;i<MAXLIST;i++){
        parsed[i]=strsep(&str," ");
        if(parsed[i]==NULL)
            break;
        if(strlen(parsed[i])==0)
            i--;
    }
}

//Esta funcion se encarga de poder realizar todo el pipe
int processString(char* str,char** parsed, char** parsedpipe){
    char* strpiped[2];
    int piped = 0;
    //busco si hay pipe
    piped = parsePipe(str,strpiped);
    //si es pipe hago el parsing
    if(piped){
        parseSpace(strpiped[0],parsed);
        parseSpace(strpiped[1],parsedpipe);
    }else{
        parseSpace(str,parsed);
    }
    if(ownCmdHandler(parsed))
        return 0;
    else
    {
        return 1+piped;
    }
}

//Funcion principal
int main(){
    
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    //Inicializo el shell
    init_shell();
    //Se mantendra en un loop infinito hasta que llame las respectivas funciones para terminar
    while(1){
        //Imprime la linea de shell que defini antes
        printDir();
        //toma los datos de ingreso
        if(takeInput(inputString))
            continue;
        //Procesos
        execFlag = processString(inputString,parsedArgs,parsedArgsPiped);
        //execFlag me retornara un cero si no hay comandos
        //1 si es un comando simple
        //2 si incluye el comando pipe

        //ejecutar

        if(execFlag ==1)
            execArgs(parsedArgs);
        if(execFlag==2)
            execArgsPiped(parsedArgs,parsedArgsPiped);
    }
    return 0;
}