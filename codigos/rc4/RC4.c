
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

unsigned char S[256];
unsigned int i, j;

/**
    Intercambiar valores entre i y j
**/
void intercambiar(unsigned char *s, unsigned int i, unsigned int j) 
{
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/**
    KSA - Algoritmo de programacion de claves
**/
void rc4_generar_vector(unsigned char *key, unsigned int key_length) 
{

    //Asignar valores iniciales al Array S[]
    for (i = 0; i < 256; i++)
    {   
        S[i] = i;
    }
 
    //Genera semilla con la clave ingresada
    for (i = j = 0; i < 256; i++) 
    {   
        j = (j + key[i % key_length] + S[i]) & 255;
        intercambiar(S, i, j);
    }
 
    i = j = 0;
}
 
/**
    PRGA - Algoritmo de generacion Pseudo-Aleatoria
**/
unsigned char rc4_salida() 
{
    i = (i + 1) & 255;
    j = (j + S[i]) & 255;

    intercambiar(S, i, j);

    return S[(S[i] + S[j]) & 255];
}

int main(int argc, char **argv) {

    int len_texto,len_clave;
    len_texto=strlen(argv[1]);
    len_clave=strlen(argv[2]);

    /**
        Texto inicial
        Clave de cifrado
    **/
    //Tamaño de cadena = len+fincadena \0
    char texto[len_texto+1];
    char clave[len_clave+1];

    //Format
    memset(texto,0,sizeof(texto));
    memset(clave,0,sizeof(clave));

    //Copiar a variables
    strcpy(texto,argv[1]);
    strcpy(clave,argv[2]);
 
    
    int x;
    rc4_generar_vector(clave, strlen(clave));

    for (x = 0; x < strlen(texto); x++)
    {
        printf("%02X", texto[x] ^ rc4_salida());
    }

    printf("\n");
    
}