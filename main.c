#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
// #include <ctype.h>
// #include <conio.h>

// Creando variables personalizadas para el nodoUsuario
typedef char NAME[25];
typedef char PASSWORD[80];
typedef int ROLE; // 1: local, 2: admin

// Creando la estructura nodoUser
typedef struct nodoUser{
	NAME nombre;
	PASSWORD clave;
	ROLE role;
	struct nodoUser *siguiente;
} USER;

// Creando punteros tipo login para la lista enlazada
USER *primero = NULL;
USER *ultimo = NULL;
USER *usuario = NULL;

/* Creando los prototipos de las funciones */
// Métodos de login
void leerUsuarios(void);
USER *agregarUsuario(NAME nombre, PASSWORD clave, ROLE role);
void eliminarUsuario(NAME nombre);
void mostrarUsuarios(void);
void iniciarSesion(void);
// Métodos de menu
void mostrarMenu(int menu);
int validarMenuInicio(char opc);
int validarMenuLectura(char opc);
int validarMenuAdmin(char opc);
void opcionInvalida(void);

// Método principal del sistema
int main() {
	setlocale(LC_ALL,"Spanish"); // Habilitando caracteres especiales
	leerUsuarios(); // Leyendo los usuarios del sistema

	// Declaración de variables
	char opc; // Guardar la opc seleccionada del menú

	// Menú principal de la app
	do {
		usuario = NULL; // Inicializar usuario loggeado
		mostrarMenu(1); // Mostrando el menu de principal
		scanf("\n%c", &opc); // Capturando la entrada del teclado
	} while ( validarMenuInicio(opc) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE

	return 0; // Finalizando el programa con éxito
}

// Método para agregar a una lista enlasada los usuario del sistema
void leerUsuarios(void) {
	// Declaración de variables
	USER *actual = NULL;
	NAME nombre;
	PASSWORD clave;
	ROLE role;

	FILE *fp = fopen("./files/login.txt", "r"); // Leyendo el archivo login.txt

	if (fp == NULL) { // Si el archivo no se puede leer o abrir
		perror(" Error al leer el archivo login.txt");
	} else {
		// Leyendo cada una de las lineas del archivo
		while( feof(fp) == 0 ){ // Mientra no se llegue al final del archivo
			int celda = 0;
			char linea[500];
			char split[] = ";";
			fscanf(fp," %[^\n]", linea); // Tomar todos los caracteres de la linea leída
			char *valor = strtok( linea, split); // Guardar valores separardos por ";"

			// Recorrer todos los valores separados
			while(valor != NULL){
				switch(celda){ // Obtener cada valor repadado en la variable celda
					case 0:
						strcpy( nombre, valor ); // Copiando el valor obtenido para nombre
						break;
					case 1:
						strcpy( clave, valor ); // Copiando el valor obtenido para clave
						break;
					case 2:
						role = atoi( valor ); // Asignando el valor obtenido para role
						break;
				}
				valor = strtok(NULL,split); // Limpiando el valor separado
				celda++; // Avanzando al siguiente valor separado

			}
			// AGREGANDO USUARIO A LA LISTA ENLAZADA DE USUARIOS
			if( primero == NULL ) { // Verficando si es el primer nodo de la lista
				primero = agregarUsuario(nombre, clave, role); // Creando el primer nodo de la lista
				ultimo = primero; // Creando el ultimo nodo de la lista
			} else {
				ultimo->siguiente = agregarUsuario(nombre, clave, role); // Agregar un nuevo nodo a la lista
				ultimo = ultimo->siguiente; // Actualizando el ultimo nodo de la lista
			}
		}
	}
	fclose(fp); // Cerrando el archivo login.txt
	mostrarUsuarios();
}

// Método para crear nuevos nodos tipo User
USER *agregarUsuario(NAME nombre, PASSWORD clave, ROLE role) {
  USER *nuevoUsuario; // Pointer de tipo USER
  nuevoUsuario = malloc( sizeof(USER)); // Asignando espacio de memoria para el Pointer
  nuevoUsuario->siguiente = NULL; // Evitar que el nodo siguiente apunte a cualquier lado
  strcpy( nuevoUsuario->nombre, nombre );
  strcpy( nuevoUsuario->clave, clave );
  nuevoUsuario->role = role;

  return nuevoUsuario; // Retornando el nuevo login
}

// Método para eliminar nodos de la lista usuarios
void eliminarUsuario(NAME nombre) {
	// logica para eliminar usuario
}

// Método para mostrar la lista de usuarios
void mostrarUsuarios (void) {
  USER *actual = primero; // actual toma el valor del nodo inicial
	int cusuarios = 0; // Contador de usuarios

  printf("\n * Lista de Usuarios * \n");
  // Recorriendo toda la lista de nodos
  while ( actual ) { // Mientras exista un nodo
		cusuarios++; // Aumentando el contador
		printf("\n-> USUARIO %d ", cusuarios);
    printf("\nNombre: %s ", actual->nombre);
		// printf("\nClave: %s ", actual->clave); // No se debe mostrar la clave
		if( actual->role == 1) {
			printf("\nRole: Usuario Local\n");
		} else if ( actual->role == 2) {
			printf("\nRole: Administrador\n");
		}
    actual = actual->siguiente; // actual toma el valor del siguiente nodo
  }
}

// Método para iniciar sesión en el sistema
void iniciarSesion(void) {
	USER *actual = primero; // Obteniendo el primero nodo de la lista
	NAME nombre; // Varible tipo NAME
	PASSWORD clave; // Varible tipo PASSWORD
	int encontrado = 0; // Bandera => 0: false, 1: true
	char res; // Auxiliar para guardar respuestas del usuario

  while ( encontrado == 0 ) {// Mientras no se encuentre el usuario
		system("cls"); // Limpiando la pantalla

		// Titulo de la pantalla
		printf("\n|----------------------------------------|");
		printf("\n|            Inicio de Sesión            |");
		printf("\n|----------------------------------------|\n");

		// Capturando datos del usuario para iniciar sesión
		printf("\nIngrese el nombre de usuario: ");
		scanf("%24s", nombre);
		printf("Ingrese la contraseña: ");
		scanf("%79s", clave);

		// Recorrer la lista de usuario para verificar al usuario
		while ( actual != NULL ) { // Mientras el nodo exista en la lista

			// Comparando nombre y contraseña
			if ( strcmp( actual->nombre, nombre ) == 0 ) { // Comparando el nombre
				if ( strcmp( actual->clave, clave ) == 0 ) { //comparando la contraseña
					encontrado = 1; // Aviso de usuario encontrado
					usuario = actual; // Registrando al usuario loggeado

					// Mostrando mensaje de Bienvenida
					if ( usuario->role == 1) {
						printf("\n Bienvenido %s (Usuario Local) \n", usuario->nombre);
					} else if ( usuario->role == 2) {
						printf("\n Bienvenido %s (Administrador) \n", usuario->nombre);
					}
					system("pause");
				}
			}

			if ( encontrado == 0 ) { // Si no se ha encontrado el usuario
				actual = actual->siguiente; // Pasando al siguiente nodo de la lista
			} else if( encontrado == 1 ) { // Si ya se encontró el usuario
				actual = NULL; // Terminando el ciclo while
			}

		}

		if ( encontrado == 0 ) {
			printf("\nCredenciales incorrectas. ¿Desea intentar de nuevo? [S/N]: ");
			scanf("\n%c", &res);
			if (res == 'n' || res == 'N'){
				encontrado = 1; // Fingir un encontrado para Salir del while
			} else {
				actual = primero;
			}
		}
	}
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
				scanf("\n%c", &res); // Capturando la entrada del teclado
			} while ( validarMenuLectura(res) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE
			break;
		case '2':
			iniciarSesion(); // Iniciar sesión

			// Si existe un usuario registrado, mostrar menú de opciones correspondiente
			if ( usuario ) {
				// Se usan IF independientes para evitar problemas con ROLES inexistentes
				if( usuario->role == 1 ) { // Usuario Local
					do {
						mostrarMenu(2); // Mostrar menú de lectura de archivos
						scanf("\n%c", &res); // Capturando la entrada del teclado
					} while ( validarMenuLectura(res) ); // Si se ingresa un valor invalido, validarMenu retornará TRUE
				}
				if( usuario->role == 2 ) { // Usuario Administrador
					do {
						mostrarMenu(3); // Mostrar menú de administración de usuarios
						scanf("\n%c", &res); // Capturando la entrada del teclado
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
	int repetir = 1; // 0: False, 1: True

	// Verificando la opc selecionada
	switch (opc) {
		case '1':
			// Busqueda general
			break;
		case '2':
			// Busqueda personalizada
			break;
		case '3':
			if( usuario ) { // Si existe un usuario local loggeado
				// Mostrar Reportes
			} else {
				opcionInvalida(); // Mostrar msj de opción no disponible
			}
			break;
		case '4':
			repetir = 0;
			break;
		default:
			opcionInvalida(); // Mostrar msj de opción no disponible
			break;
	}

	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para validar la opción seleccionada en el menú admin
int validarMenuAdmin(char opc) {
	int repetir = 1; // 0: False, 1: True

	// Verificando la opc selecionada
	switch (opc) {
		case '1':
			// Busqueda general
			break;
		case '2':
			// Busqueda personalizada
			break;
		case '3':
			// Cerrar sesión
			repetir = 0;
			break;
		default:
			opcionInvalida(); // Mostrar msj de opción no disponible
			break;
	}

	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para imprimir msj de opción no disponible
void opcionInvalida(void) {
		printf("\nOpción no disponible. Por favor intente de nuevo\n");
		system("pause"); // Hacer una pausa en el sistema
}

// void limpiarPantalla(void)
// {
// 		printf("\n\n");
// 		fflush(stdin);
// 		system("pause");
// 		system("cls");
// }