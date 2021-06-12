/*
===================================================
             Universidad de la Cañada
            Licenciatura en Informática
        Programación de sistemas   Semestre: 4
    Profesor: M.C Beatriz Adriana Moxo Sabino
        Estudiante: Juan Carlos López Pérez
            PROYECTO ANALIZADOR LÉXICO
====================================================
*/
/*
ENTRADA: archivo fuente en C
SALIDA: lista de tokens encontrados + nombre de los componentes léxicos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define N 22



//structs
typedef struct {
    char cLexico[50];
}componente;

typedef struct {
    int contadorToken;
}contador;
int contadorTam=0;

//arreglo de estructuras para almacenar los tokens detectados
componente listaComponentes[N];
contador listaContadores[N];

//variables globales
char caracter;
char *letra;
bool ban = false;

//menu
void menu()
{   char opcion;
    do {
        printf("\n\n\t=== MENU ===");
        printf("\n\t1. Leer codigo fuente y mostrar lista de token y componentes lexicos");
        printf("\n\t2. Ver lista de tokens y componentes encontrados");
        printf("\n\t3. Salir");
        printf("\n\tOpcion:");
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
                lector_simbolos(listaContadores, listaComponentes);
                break;
            case 2:
                if(ban == false)
                {   int respuesta;
                    printf("\n\tNo se ha leido un codigo Fuente. \n\t ¿Desea Leer uno? \n\t 1. SI \t 2. NO \n\tOpcion:");
                    scanf("%s",&respuesta);
                    if(respuesta == 1)
                        lector_simbolos(listaContadores, listaComponentes);
                    else
                        menu();
                }
                else
                {   verLista();
                }
                break;
        }

    }while(opcion != 3);
    getchar();
}
//lista de componentes y contadores (eliminados de momento)

//analizado de simbolos en archivo fuente
void lector_simbolos( contador listaContadores[], componente ListaComponentes[])
{
    FILE * archivo = fopen("programaFuenteE3.txt", "rb");
    if(archivo == NULL ){
        printf("Error al leer el archivo");
        ban = false;
    }
    else
    {
        //variables auxiliares para contabilizar cada token
        int delimitador=0, menor_que=0, mayor_que=0, abre_parentesis=0, cierra_parentesis=0, coma=0, abre_llave=0;
        int cierra_llave=0, operador_asignacion=0, operador_suma=0, comilla=0, puntoYcoma=0, operador_multiplicacion=0;

        //IMPRESION DE TOKENS ENCONTRADOS || SIMBOLOS
        printf("\n\tSE HAN ENCONTRADO LOS SIGUIENTES TOKENS Y COMPONENTES LEXICOS\n\t");

        printf("\n\t[Cantidad] [token] [Componente Lexico]\n");

        //reconocimiento de simbolos
        while(feof(archivo) == 0 ) {
            caracter = fgetc(archivo);
            if(caracter == '#'){delimitador++; printf("\n\t[1][#][Delimitador] ", delimitador); }
            if(caracter == '<'){ menor_que++; printf("\n\t[1][<][menor que] ", menor_que); }
            if(caracter == '>'){ mayor_que++; printf("\n\t[1][>][mayor que] ", mayor_que); }
            if(caracter == '('){ abre_parentesis++; printf("\n\t[1][(][apertura parentesis] ", abre_parentesis); }
            if(caracter == ')'){ cierra_parentesis++; printf("\n\t[1][)][cierre parentesis] ", cierra_parentesis);}
            if(caracter == ','){ coma++; printf("\n\t[1][,][coma] ", coma); }
            if(caracter == '{'){ abre_llave++; printf("\n\t[1][{][llave apertura] ", abre_llave);}
            if(caracter == '}'){ cierra_llave++; printf("\n\t[1][}][cierre llave] ", cierra_llave); }
            if(caracter == '='){ operador_asignacion++; printf("\n\t[1][=][Operador de asignacion] ", operador_asignacion); }
            if(caracter == '+'){ operador_suma++; printf("\n\t[1][+][Operador de suma] ", operador_suma);}
            if(caracter == '"'){ comilla++; printf("\n\t[1][\"][comilla] ", comilla); }
            if(caracter == ';'){ puntoYcoma++; printf("\n\t[1][;][punto y coma] ", puntoYcoma);}

            //contador para el número de caracteres leídos en el archivo fuente
            contadorTam++;
        }

        fclose(archivo);

        //listaContadores[2].contadorToken = delimitador; //problemas con asignacion de valores al arreglo de contadores

        //SE LLAMA AL PROCEDIMIENTO PARA IDENTIFICAR LOS TOKENS COMPUESTOS
        identificadorPatron();
        ban = true;
    }
}
//procedimiento para detectar tokens compuestos
void identificadorPatron()
{   char *arreglo[contadorTam];
    //**************
    //--VARIABLES CONTADOR
    //**************
    int comentario_largo=0, comentario_corto=0, palabra_reservada=0, incremento=0, decremento=0;

    //lectura del archivo
    FILE * archivo = fopen("programaFuenteE3.txt", "rb");

    if(archivo == NULL ){
            printf("Error al leer el archivo");
            ban = false;
    }
    else {
        //se copia en arreglo los caracteres del codigo fuente
        for(int i=0;i<contadorTam && feof(archivo) ==0;i++) {
        caracter = fgetc(archivo);
        arreglo[i] = caracter;
        }
    }

    //*********************************************
    /*
    //IMRPRESION DE CODIGO FUENTE ALMACENADO EN ARREGLO
    int i=0;
    while(i< contadorTam){
        printf("\n\t%c\n",arreglo[i]);
        i++;
    }
    //*********************************************
    */

    fclose(archivo);

    char *convertir;

    //***************
    //--Analizadores
    //***************

    for(int i=0;i<contadorTam;i++) {
        //analizador comentario largo
        if(arreglo[i] == '/' && arreglo[i+1] == '*'){
            comentario_largo++;

            letra = arreglo[i];
            char *letraAux, *letraBefore;
            letraBefore=arreglo[i-1];
            letraAux = arreglo[i+1];

            printf("\n\t[%d][",comentario_largo);
            //*****************************************************
            //corregir error, donde falta el slah para completar
            //******************************************************
            while(letraBefore != ' ' && letra != '*' && letraAux !='/'){
                letra = arreglo[i];
                letraAux = arreglo[i+1];
                letraBefore=arreglo[i-1];
                printf("%c",letra);
                i++;
            }
            printf("%c][Comentario largo] \n",letraAux);
        }
        //analizador comentario corto
        if(arreglo[i] == '/' && arreglo[i+1] == '/'){
            comentario_corto++;
            letra = arreglo[i];

            printf("\n\t[%d][",comentario_corto);
            for(letra = arreglo[i]; letra != '\n'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Comentario corto] ");
        }
        //palabra reserada librerias
        int libreria_stdio_Reservado=0;
        if(arreglo[i] == 's' && arreglo[i+1] == 't' && arreglo[i+2] == 'd' && arreglo[i+3] == 'i' && arreglo[i+4] == 'o' && arreglo[i+5] == '.' && arreglo[i+6] == 'h')
        {   libreria_stdio_Reservado++;
            letra = arreglo[i];
            printf("\n\t[%d][",libreria_stdio_Reservado);
            for(letra = arreglo[i];letra != 'h'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra Reservada] ");
        }
        int reservado_include=0;
        if(arreglo[i] == 'i' && arreglo[i+1] == 'n' && arreglo[i+2] == 'c' && arreglo[i+3] == 'l' && arreglo[i+4] == 'u' && arreglo[i+5] == 'd' && arreglo[i+6] == 'e')
        {   reservado_include++;
            letra = arreglo[i];

            printf("\n\t[%d][",reservado_include);
            for(letra = arreglo[i];letra != 'e'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }
         int contador_main=0;
         if(arreglo[i] == 'm' && arreglo[i+1] == 'a' && arreglo[i+2] == 'i' && arreglo[i+3] == 'n')
        {   contador_main++;
            letra = arreglo[i];

            printf("\n\t[%d][",contador_main);
            for(letra = arreglo[i];letra != 'n'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }

         int contador_void=0;
         if(arreglo[i] == 'v' && arreglo[i+1] == 'o' && arreglo[i+2] == 'i' && arreglo[i+3] == 'd')
        {   contador_void++;
            letra = arreglo[i];

            printf("\n\t[%d][",contador_void);
            for(letra = arreglo[i];letra != 'd'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }
         //ARREGLAR ERROR EN INT
         int contador_int=0;
         if(arreglo[i] == 'i' && arreglo[i+1] == 'n' && arreglo[i+2] == 't'  && arreglo[i+3] != 'f')
        {   contador_int++;
            letra = arreglo[i];

            printf("\n\t[%d][",contador_int);
            for(letra = arreglo[i];letra != 't'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }

         int contador_and=0;
         if(arreglo[i] == '&' && arreglo[i+1] == '&')
        {   contador_and++;

            printf("\n\t[%d][",contador_and);
            printf("&&");
            printf("][operador de comparacion] ");
         }
         int contador_else=0;
         if(arreglo[i] == 'e' && arreglo[i+1] == 'l' && arreglo[i+2] == 's' && arreglo[i+3] == 'e')
        {   contador_else++;
            letra = arreglo[i];
            char *letraAux;
            letraAux=arreglo[i+1];

            printf("\n\t[%d][",contador_else);
            for(letra = arreglo[i];letraAux != ' '; i++)
            {   letra = arreglo[i];
                letraAux=arreglo[i+1];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }
         int contador_return=0;
         if(arreglo[i] == 'r' && arreglo[i+1] == 'e' && arreglo[i+2] == 't' && arreglo[i+3] == 'u' && arreglo[i+4] == 'r' && arreglo[i+5] == 'n')
        {   contador_return++;
            letra = arreglo[i];

            printf("\n\t[%d][",contador_return);
            for(letra = arreglo[i];letra != 'n'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }
         if(arreglo[i] == '+' && arreglo[i+1] == '+'){
            incremento++;
            printf("\n\t[1][++][incremento]");
         }
         if(arreglo[i] == '-' && arreglo [i+1] == '-'){
            decremento++;
            printf("\n\t[1][--][decremento]");
         }

         //NÚMEROS 0-9
         int num = arreglo[i];
         identificadorNumeros(num);

         if(arreglo[i] == '0'){
            printf("\n\t[1][0][numero]");
         }

         //printf
         int printf_contador=0;
         if(arreglo[i] == 'p' && arreglo[i+1] == 'r' && arreglo[i+2] == 'i'  && arreglo[i+3] == 'n' && arreglo[i+4] == 't'  && arreglo[i+5] == 'f')
         {   printf_contador++;
            letra = arreglo[i];

            printf("\n\t[1][");
            for(letra = arreglo[i];letra != 'f'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }

         //cadena
         int cadena=0;
         if(arreglo[i] == 'p' && arreglo[i+1] == 'r' && arreglo[i+2] == 'i'  && arreglo[i+3] == 'n' && arreglo[i+4] == 't'  && arreglo[i+5] == 'f' && arreglo[i+6] == '(' && arreglo[i+7] == '"')
         {   cadena++;
            letra = arreglo[i];

            printf("\n\t[1][");
            for(letra = arreglo[i];letra != '"'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Cadena] ");
         }

         int ifs=0;
         if(arreglo[i] == 'i' && arreglo[i+1] == 'f')
         {   ifs++;
            letra = arreglo[i];

            printf("\n\t[1][");
            for(letra = arreglo[i];letra != 'f'; i++)
            {   letra = arreglo[i];
                printf("%c",letra);
            }
            printf("][Palabra reservada] ");
         }

         int saltoLinea=0;
         int m=92;
         if(arreglo[i] == '"' && arreglo[i+1] == '%c' && arreglo[i+2] == 'n',m)
         {  saltoLinea++;
            //impresion del slash invertido listo
            printf("\n\t[1][%cn][Salto de línea] ",m);
         }
    }
    //reestablecer el contador
    contadorTam = 0;
}

//case para detectar los numeros de una sola cifra
int identificadorNumeros (int num) {
    switch(num){
        case -1: printf("\n\t[1][-1][numero]"); break;
        case 1: printf("\n\t[1][1][numero]"); break;
        case 2: printf("\n\t[1][2][numero]"); break;
        case 3: printf("\n\t[1][3][numero]"); break;
        case 4: printf("\n\t[1][4][numero]"); break;
        case 5: printf("\n\t[1][5][numero]"); break;
        case 6: printf("\n\t[1][6][numero]"); break;
        case 7: printf("\n\t[1][7][numero]"); break;
        case 8: printf("\n\t[1][8][numero]"); break;
        case 9: printf("\n\t[1][9][numero]"); break;
    }
    return num;
}

//procedimiento para ver la lista generada
void verLista() {
    printf("\n\n\t LISTA DE TOKENS Y COMPONENTES LÉXICOS ENCONTRADOS \n");
}

//cuerpo principal
int main()
{   //llamada a la función principal
    menu();
    return 0;
}
