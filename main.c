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
// Métodos para lectura de parrafos (lógica de negocio)
int lectura(char opc);
void guardarReporte(int cA, int cE, int cI, int cO, int cU, int cEspacio, int cComa, int cPuntoComa, int cPunto);
void mostrarReportes(void);

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
					system("cls");
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
		if ( usuario ) { // Si existe un usuario local loggeado
			printf("\n| 3. Mostrar reportes anteriores         |");
		}
		if ( usuario ) { // Si existe un usuario local loggeado
			printf("\n| 4. Cerrar sesión                       |");
		} else {
			printf("\n| 4. Salir                               |");
		}
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
	case 4: // Menú de búsqueda personalizada
		printf("\n|------------------------------------------------------|");
		printf("\n|                Búsqueda Personalizada                |");
		printf("\n|------------------------------------------------------|");
		printf("\n| 1. Buscar vocal A        || 6. Buscar Espacios       |");
		printf("\n| 2. Buscar vocal E        || 7. Buscar Comas (,)      |");
		printf("\n| 3. Buscar vocal I        || 8. Buscar Puntocomas (;) |");
		printf("\n| 4. Buscar vocal O        || 9. Buscar Puntos (.)     |");
		printf("\n| 5. Buscar vocal U        ||                          |");
		printf("\n|------------------------------------------------------|");
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
	char res; // Auxiliar para guardar respuesta del usuario
	int repetir = 1; // 0: False, 1: True

	// Verificando la opc selecionada
	switch (opc) {
		case '1':
			lectura('G'); // Busqueda generalizada
			break;
		case '2':
			// Busqueda personalizada
			do {
				mostrarMenu(4); // Mostrar menú de Busqueda personalizada
				scanf("\n%c", &res); // Capturando la entrada del teclado
			} while ( lectura(res) ); // Si se ingresa un valor invalido, lectura retornará TRUE
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

// Método para analizar párrafos
int lectura(char opc) {
	FILE *fp = fopen("./files/source.txt", "r"); // Leyendo el archivo source.txt
  int cA = 0, cE = 0, cI = 0, cO = 0, cU = 0; // Contadores de vocales
  int cEspacio = 0, cComa = 0, cPuntoComa = 0, cPunto = 0; // Contadores de caracteres especiales
  int repetir = 0; // 0: False, 1: True
	char c, res; // Variables auxiliares

	// Imprimiendo instrucciones
	printf("\n|----------------------------------------|");
	printf("\n|              Instrucciones             |");
	printf("\n|----------------------------------------|");
	printf("\n| Copiar el texto que se quiere analizar |");
	printf("\n| en la ruta 'files/source.txt'          |");
	printf("\n|----------------------------------------|\n\n");
	system("pause");
	system("cls");

  // Imprimiendo párrafo
	printf("\n|----------------------------------------|");
	printf("\n|                 Lectura                |");
	printf("\n|----------------------------------------|\n\n");

	if (fp == NULL) { // Si el archivo no se puede leer o abrir
		perror("El archivo no está disponible o está vacío\n");
	} else {
		// Recorriendo el archivo caracter por caracter
		while ( (c = fgetc(fp)) != EOF ) { // Mientras no sea el final del archivo
			printf("%c", c); // Imprimir caracter
			switch (opc) {
			case 'G':
				// Búsqueda generalizada de caracteres
				if ( c == 'a'|| c == 'A' ) cA++; // Aumentar contador de A
				else if ( c == 'e' || c == 'E' ) cE++; // Aumentar contador de E
				else if ( c == 'i' || c == 'I' ) cI++; // Aumentar contador de I
				else if ( c == 'o' || c == 'O' ) cO++; // Aumentar contador de O
				else if ( c == 'u' || c == 'U' ) cU++; // Aumentar contador de U
				else if ( c == ' ' ) cEspacio++; // Aumentar contador de Espacios
				else if ( c == ',' ) cComa++; // Aumentar contador de Comas
				else if ( c == ';' ) cPuntoComa++; // Aumentar contador de PuntoComas
				else if ( c == '.' ) cPunto++; // Aumentar contador de Puntos
				break;
			// Búsquedas personalizada de caracteres
			case '1':
				if ( c == 'a'|| c == 'A' ) cA++; // Aumentar contador de A
				break;
			case '2':
				if ( c == 'e' || c == 'E' ) cE++; // Aumentar contador de E
				break;
			case '3':
				if ( c == 'i' || c == 'I' ) cI++; // Aumentar contador de I
				break;
			case '4':
				if ( c == 'o' || c == 'O' ) cO++; // Aumentar contador de O
				break;
			case '5':
				if ( c == 'u' || c == 'U' ) cU++; // Aumentar contador de U
				break;
			case '6':
				if ( c == ' ' ) cEspacio++; // Aumentar contador de Espacios
				break;
			case '7':
				if ( c == ',' ) cComa++; // Aumentar contador de Comas
				break;
			case '8':
				if ( c == ';' ) cPuntoComa++; // Aumentar contador de PuntoComas
				break;
			case '9':
				if ( c == '.' ) cPunto++; // Aumentar contador de Puntos
				break;
			default:
				repetir = 1;
				break;
			}
		}
		fclose(fp); // Cerrar el archivo source.txt

		// Imprimiendo reporte
		printf("\n\n");
		printf("\n|----------------------------------------|");
		printf("\n|                 Reporte                |");
		printf("\n|----------------------------------------|\n\n");
		switch (opc) {
			case 'G':
				printf("Total de <A>: %d\n", cA);
				printf("Total de <E>: %d\n", cE);
				printf("Total de <I>: %d\n", cI);
				printf("Total de <O>: %d\n", cO);
				printf("Total de <U>: %d\n", cU);
				printf("Total de <Espacios en blanco ( )>: %d\n", cEspacio);
				printf("Total de <Comas (,)>: %d\n", cComa);
				printf("Total de <Punto Comas (;)>: %d\n", cPuntoComa);
				printf("Total de <Puntos (.)>: %d\n\n", cPunto);
				break;
			case '1':
				printf("Total de <A>: %d\n", cA);
				break;
			case '2':
				printf("Total de <E>: %d\n", cE);
				break;
			case '3':
				printf("Total de <I>: %d\n", cI);
				break;
			case '4':
				printf("Total de <O>: %d\n", cO);
				break;
			case '5':
				printf("Total de <U>: %d\n", cU);
				break;
			case '6':
				printf("Total de <Espacios en blanco ( )>: %d\n", cEspacio);
				break;
			case '7':
				printf("Total de <Comas (,)>: %d\n", cComa);
				break;
			case '8':
				printf("Total de <Punto Comas (;)>: %d\n", cPuntoComa);
				break;
			case '9':
				printf("Total de <Puntos (.)>: %d\n\n", cPunto);
				break;
		}

		if( usuario ) { // Si hay un usuario loggeado
			printf("\n¿Desea guardar el reporte? [S/N]: ");
				scanf("\n%c", &res);
				if (res == 's' || res == 'S'){
					guardarReporte(cA, cE, cI, cO, cU, cEspacio, cComa, cPuntoComa, cPunto); // Guardar reporte
				}
		}
	}
	system("pausa"); // Haciendo una pausa en el sistema
	return repetir; // Retorna 1 para retir y 0 para romper el ciclo
}

// Método para guardar reporte de los párrafos analizados
void guardarReporte(int cA, int cE, int cI, int cO, int cU, int cEspacio, int cComa, int cPuntoComa, int cPunto) {
	printf("\nReporte guardado exitosamente\n");
}

// Método para mostrar los repostes guardos
void mostrarReportes(void) {

}

// void limpiarPantalla(void)
// {
// 		printf("\n\n");
// 		fflush(stdin);
// 		system("pause");
// 		system("cls");
// }