#include <stdio.h>
#include <stdlib.h> //System
#include <string.h> //gets, strcmp
#include <conio.h>
#define Usuario "c"
#define Clave "proyecto"

#define longitud 80 //Maximo de caracteres permitidos

int main(){
	char usuario[longitud +1], clave [longitud+1];//Variables donde se almacenaran las credenciales de acceso
	int intento =0, ingresa =0; //Variables para validar sesion
	char caracter; //Variable que almacenara la clave que ingresa el usuario al iniciar
	int i=0; //Variable que servira para validar que caracteres ingresa el usuario
	do{
		i=0;
		system("cls");
		printf("\t\t INICIO DE SESION\n\n");
		printf("\t\t-----------------------\n\n");
		printf("\tUsuario: ");
		gets(usuario);  //Obtiene nombre de usuario que ingresa el usuario
		printf("\tClave: ");
		while(caracter = getch()){ //caracter almacena caracteres obtenidos en la funcion getch
		if(caracter==13){ //Valida si el valor ingresado es igual a retorno del carro (enter)
			clave[i]='\0'; //\0 indica fin de una linea de caracteres
			break;
		}else if(caracter==8){//Valida si el valor ingresado es igual a retroceso (delete)
			if(i>0){ //Valida que solo se eliminen los valores almacenados en i
			i--; //Resta la cantidad de caracteres
			printf("\b \b"); //Simula el retroceso o eliminacion de los caracteres ingresados
			} 	
		}else{
			if(i < longitud){ //Valida que el numero de caracteres ingresados no sobrepase la longitud asignada 
			printf("*"); //Simula que oculta los caracteres ingresados en clave
			clave[i]=caracter; //Almacena cada letra o caracter ingresadoen un arreglo
			i++;//Suma la cantidad de caracteres ingresados
			}
		}
		}
		
	//	printf("\nLa clave es: %s", clave);
		
		if(strcmp(usuario, Usuario)==0 && strcmp(clave,Clave)==0){ //Valida que el usuario y clave coincidan 
			ingresa=1; //variable bandera
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
