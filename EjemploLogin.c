#include <stdio.h>
#include <stdlib.h> //System
#include <string.h> //gets, strcmp
#include <conio.h>
#define Usuario "c"
#define Clave "proyecto"

#define longitud 80

int main(){
	char usuario[longitud +1], clave [longitud+1];
	int intento =0, ingresa =0;
	char caracter;
	int i=0;
	do{
		i=0;
		system("cls");
		printf("\t\t INICIO DE SESION\n\n");
		printf("\t\t-----------------------\n\n");
		printf("\tUsuario: ");
		gets(usuario);
		printf("\tClave: ");
		while(caracter = getch()){
		if(caracter==13){
			clave[i]='\0';
			break;
		}else if(caracter==8){
			if(i>0){
			i--;
			printf("\b \b"); 
			} 
			
		}else{
			if(i < longitud){
			printf("*");
			clave[i]=caracter;
			i++;
			}
		}
		}
		
	//	printf("\nLa clave es: %s", clave);
		
		if(strcmp(usuario, Usuario)==0 && strcmp(clave,Clave)==0){
			ingresa=1;
		}else{
			printf("\n\tUsuario y/o clave son incorrectos\n");
			intento++;
			getchar();
			
		}
	}while(intento < 3 && ingresa ==0);
	if(ingresa==1){
		printf("\n\n\tBienvenido");
	}else{
		printf("Ha sobrepasado el numero de intentos maximos permitidos.");
	}

				
	return 0;
}
