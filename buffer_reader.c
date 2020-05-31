#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main ( int argc, const char *argv[] ) {

  FILE *fp = fopen("./files/source.txt", "r"); // Leyendo el archivo source.txt
  int cA = 0, cE = 0, cI = 0, cO = 0, cU = 0; // Contadores de vocales
  int cEspacio = 0, cComa = 0, cPuntoComa = 0, cPunto = 0; // Contadores de caracteres especiales
  char c;

  printf("\n\nPARRAFO\n");
  while ( (c = fgetc(fp)) != EOF ) {
    printf("%c", c);

    // Búsqueda de caracteres
    if ( c == 'a'|| c == 'A' ) cA++;
    else if ( c == 'e' || c == 'E' ) cE++;
    else if ( c == 'i' || c == 'I' ) cI++;
    else if ( c == 'o' || c == 'O' ) cO++;
    else if ( c == 'u' || c == 'U' ) cU++;
    else if ( c == ' ' ) cEspacio++;
    else if ( c == ',' ) cComa++;
    else if ( c == ';' ) cPuntoComa++;
    else if ( c == '.' ) cPunto++;
  }
  fclose(fp);

  printf("\n\nREPORTE\n");
  printf("Total de <A>: %d\n", cA);
  printf("Total de <E>: %d\n", cE);
  printf("Total de <I>: %d\n", cI);
  printf("Total de <O>: %d\n", cO);
  printf("Total de <U>: %d\n", cU);
  printf("Total de <Espacios en blanco ( )>: %d\n", cEspacio);
  printf("Total de <Comas (,)>: %d\n", cComa);
  printf("Total de <Punto Comas (;)>: %d\n", cPuntoComa);
  printf("Total de <Puntos (.)>: %d\n", cPunto);

  return 0;
}