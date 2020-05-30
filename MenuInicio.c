#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
//#define Usuario "c"
//#define Clave "proyecto"

#define longitud 80

typedef struct Proyecto{
	char Usuario[80];
	char Clave[80];
	struct Proyecto *siguiente;
}Proyecto;


Proyecto *primero = NULL;
Proyecto *ultimo = NULL;

void menuInicio(void);
void opcionInvalida(void);
void limpiarPantalla(void);
int login(void);
int opcion;


main(){
	setlocale(LC_ALL,"Spanish");
	menuInicio();
	
}


void menuInicio(void){


 system("cls");
do{
 opcion=0;
	
	menu:
	printf("\n|----------------------------------------|");
	printf("\n|          MENÚ DE ACCESO                |");
	printf("\n|----------------------------------------|");
	printf("\n| 1. Ingresar como visitante             |");
	printf("\n| 2. Iniciar sesion                      |");
	printf("\n| 3. Salir                               |");
	printf("\n|----------------------------------------|");
	printf("\n\n Escoja una opcion: ");
	scanf("%d", &opcion);	
	
	switch(opcion){
		case 1:
			{	
			printf("Soy un visitante");
			limpiarPantalla();
			break;
			}
		case 2:
			{
		//	printf("Iniciare sesion"); 
			login();
			limpiarPantalla();
			break;
			}
		case 3:
	
		if(opcion==3){
			int salir;
		system("cls");
		printf("\n|------------------------------|");
		printf("\n| Desea salir del programa?    |");
		printf("\n|------------------------------|");
		printf("\n| 1. Si                        |");
		printf("\n| 2. No                        |");
		printf("\n|------------------------------|");
		printf("\n\nEscoja una opcion: ");
	    scanf("%d", &salir);
			
			switch(salir){
	          case 1:{
	          		printf("EL PROCESO HA FINALIZADO.\n\nADIOS.");
				break;
			  }
			  case 2:{
			         system("cls");
			  	      goto menu;
			  	     
				break;
			  }
			  default:{
			opcionInvalida();
			  	
				break;
			  }
			}
			
		}
			break;
		default:
         	opcionInvalida();
     	break;		
		}
}	while(opcion !=3 );
	
}
	
void opcionInvalida(void)
{
		printf("El valor ingresado no es correcto\n");
       	printf("\n\n");
		printf("Por favor vuelva a ingresarlo, muchas gracias\n");
		limpiarPantalla();
}

void limpiarPantalla(void)
{
		printf("\n\n");
		fflush(stdin);
		system("pause");
		system("cls");
}

int login(void){
if(opcion==2){
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
		scanf("%s", &usuario);//Obtiene nombre de usuario que ingresa el usuario
		
		printf("\tClave: ");
		while(caracter = getch()){ //caracter almacena caracteres obtenidos en la funcion getch
		if(caracter==13){ //Valida si el valor ingresado es igual a retorno del carro (enter)
			clave[i]='\0'; //\0 indica fin de una linea de caracteres
			break;
		}else if(caracter==8){ //Valida si el valor ingresado es igual a retroceso (delete)
			if(i>0){ // los valores almacenados en i
			i--; //Resta la cantidad de caracteres
			printf("\b \b"); //Simula el retroceso o eliminacion de los caracteres ingresados
			} 
			
		}else{
			if(i < longitud){ //Valida que el numero de caracteres ingresados no sobrepase la longitud asignada 
			printf("*");//Simula que oculta los caracteres ingresados en clave
			clave[i]=caracter;//Almacena cada letra o caracter ingresadoen un arreglo
			i++;//Suma la cantidad de caracteres ingresados
			}
		}
		}
		
	//	printf("\nLa clave es: %s", clave);
		
		if(strcmp(usuario, primero->Usuario)==0 && strcmp(clave,primero->Clave)==0){
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

	
}
				
	return 0;
}


