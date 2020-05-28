#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct registro{
    char user[20];
    char pass[80];

}est;
int agregarUser(void);
void LeerUser(void);
int buscarUser(void);

 main(){

 agregarUser();
   LeerUser();
      buscarUser();
}

int buscarUser(void){
	int c=0;
	char name[20];
	
	FILE * ptr;

 	ptr=fopen("archivo.txt","a+");


    if(ptr==NULL){
        printf("No se pudo crear");
        return 0;
    }
    
    //fwrite(&est, sizeof(est),1,ptr);

    
 printf("Usuario a buscar: ");
 gets(name);
 
    
    while(!feof(ptr)){
    	fread(&est, sizeof(est),1,ptr);
    if(strstr(name,est.user)!=NULL){
    	if(c==0){
    			printf("\nEncontrado: \n user: %s \nPass: %s", est.user,est.pass);
		} c++;
	}
      
	}

    fclose(ptr);

    getch();
	
	
}

void LeerUser(void){
	int c=0;
	
	FILE * ptr;

ptr=fopen("archivo.txt","r");


    if(ptr==NULL){
        printf("No se pudo leer");
        return;
    }

    
    while(!feof(ptr)){
    	fread(&est, sizeof(est),1,ptr);
   // if(c==0){
    		printf("\n user: %s \nPass: %s", est.user,est.pass);
	//}
	//c++;
	}

    fclose(ptr);

    getch();
}


int agregarUser(void){

printf("Usuario: ");
gets(est.user);

printf("Contrasenia: ");
gets(est.pass);


FILE * ptr;

ptr=fopen("archivo.txt","a+");


    if(ptr==NULL){
        printf("No se pudo crear");
        return 0;
    }

    fwrite(&est, sizeof(est),1,ptr);
    printf("\nDatos guardados.");
    fclose(ptr);

    getch();
	
}

