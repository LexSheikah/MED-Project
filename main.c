#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

// Creando apodos para las variables a utilizar en el nodo Login
typedef char USER[25];
typedef char PASSWORD[80];
typedef int ROLE; // 1: local, 2: admin

// Creando la estructura nodoLogin
typedef struct nodoLogin{
	USER usuario;
	PASSWORD clave;
	ROLE role;
	struct LOGIN *siguiente;
	struct LOGIN *anterior;
}LOGIN;

// Creando punteros tipo login para la lista enlazada
LOGIN *primero = NULL;
LOGIN *ultimo = NULL;
LOGIN *usuario = NULL;

// Creando los prototipos de las funciones
void leerUsuario(void);
void mostrarMenu(int menu);
int validarMenuInicio(char opc);
int validarMenuLectura(char opc);
int validarMenuAdmin(char opc);
void opcionInvalida(void);
void validarUsuario(void);

// Método principal de la aplicación
int main() {
	setlocale(LC_ALL,"Spanish");

	/* DECLARACION DE VARIABLES */
	char opc; // Guardar la opc seleccionada del menú

	/* LEYENDO LOS USUARIOS DEL SISTEMA */
	leerUsuario();

	/* INICIO DEL PROGRAMA... */
	do {
		mostrarMenu(1); // Mostrando el menu de principal
		scanf("%c", &opc); // Capturando la entrada del teclado
	} while ( validarMenuInicio(opc) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE

	return 0;
}

// Método para agregar a una lista enlasada los usuario del sistema
void leerUsuario(void) {
	// leer archivo .csv
	// Crear lista enlazada de usuarios
}

// Método para imprimir en pantalla los menus de la app
void mostrarMenu(int menu){

	system("cls");
	switch (menu) {
	case 1: // Menú principal
		printf("\n|----------------------------------------|");
		printf("\n|             MENÚ PRINCIPAL             |");
		printf("\n|----------------------------------------|");
		printf("\n| 1. Ingresar como visitante             |");
		printf("\n| 2. Iniciar sesión                      |");
		printf("\n| 3. Salir                               |");
		printf("\n|----------------------------------------|");
		printf("\n\n Escoja una opción: ");
		break;
	case 2: // Menú de lectura de archivo para usuario Invitado y Local
		printf("\n|----------------------------------------|");
		printf("\n|           LECTURA DE ARCHIVO           |");
		printf("\n|----------------------------------------|");
		printf("\n| 1. Búsqueda general                    |");
		printf("\n| 2. Búsqueda personalizada              |");
		if ( usuario ) { // Si existe un usuario local registrado
			printf("\n| 3. Mostrar reportes anteriores         |");
		}
		printf("\n| 4. Cerrar sesión                       |");
		printf("\n|----------------------------------------|");
		printf("\n\n Escoja una opción: ");
		break;
	case 3: // Menú de administración de usuario para usuarios administradores
		printf("\n|----------------------------------------|");
		printf("\n|          ADMINISTRAR USUARIOS          |");
		printf("\n|----------------------------------------|");
		printf("\n| 1. Agregar usuario                     |");
		printf("\n| 2. Eliminar usuario                    |");
		printf("\n| 3. Cerrar sesión                       |");
		printf("\n|----------------------------------------|");
		printf("\n\n Escoja una opción: ");
		break;
	default:
		break;
	}
}

// Método para validar la opción seleccionada en el menú inicio
int validarMenuInicio(char opc) {
	char res; // Auxiliar para guardar respuestas del usuario
	int repetir = 1; // 0: False, 1: True


	switch (opc) {
		case '1':
			do {
				mostrarMenu(2); // Mostrar menú de lectura de archivos
				scanf("%c", &res); // Capturando la entrada del teclado
			} while ( validarMenuLectura(res) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE
			break;
		case '2':
			validarUsuario(); // Iniciar sesión

			// Si existe un usuario registrado, mostrar menú de opciones correspondiente
			if ( usuario ) {
				// Se usan IF independientes para evitar problemas con ROLES inexistentes
				if( usuario->role == 1 ) { // Usuario Local
					do {
						mostrarMenu(2); // Mostrar menú de lectura de archivos
						scanf("%c", &res); // Capturando la entrada del teclado
					} while ( validarMenuLectura(res) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE
				}
				if( usuario->role == 2 ) { // Usuario Administrador
					do {
						mostrarMenu(3); // Mostrar menú de administración de usuarios
						scanf("%c", &res); // Capturando la entrada del teclado
					} while ( validarMenuAdmin(res) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE
				}
			}
			break;
		case '3':
			exit(0); // Cerrando el programa
			break;
		default:
			opcionInvalida(); // Mostrar msj de opción no disponible
			break;
	}

	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para validar la opción seleccionada en el menú lectura
int validarMenuLectura(char opc) {
	int repetir = 0; // 0: False, 1: True
	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para validar la opción seleccionada en el menú admin
int validarMenuAdmin(char opc) {
	int repetir = 0; // 0: False, 1: True
	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para imprimir msj de opción no disponible
void opcionInvalida(void) {
		printf("\nOpción no disponible. Por favor intente de nuevo\n");
		system("pause"); // Hacer una pausa en el sistema
}

void validarUsuario(void) {
	int encontrado = 0; // 0: false, 1: true
	char res; // Auxiliar para guardar respuestas del usuario
	printf("\nValidando usuario...");

	// Se repite mientra encontrado == 0
	while ( !encontrado ) {
		// obtener usuario y contraseña
		// Recorrer lista enlazada LOGIN
		// Comparar usuario y contraseña
		// Guardar usuario en el sistema (nombre, role)

		// Si existe un usuario, activar bandera de encontrado
		if ( usuario ) {
			encontrado = 1;
		} else {
			printf("\nCredenciales incorrectas. ¿Desea intentar de nuevo? [S/N]: ");
			scanf("%c", &res);
			if (res == 'n' || res == 'N')
			encontrado = 1; // Fingir un encontrado para Salir del while
		}
	}
}

// void limpiarPantalla(void)
// {
// 		printf("\n\n");
// 		fflush(stdin);
// 		system("pause");
// 		system("cls");
// }