#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(){
 	FILE *archive;
 	char crts[100];
 	archive = fopen("DHT11.BIN","r");																//Se abre el archive						
 	
 	if (archive == NULL){																			//Comprobacion
 	std::cout << "Archivo no encotrado\n\n";
		exit(1) ;	
	} else{
 	    while (feof(archive) == 0){																	//Se imprimen los datos
 			fread(crts, sizeof (char), 1, archive);
	std::cout << "%s",crts;

 		}     
    }
    fclose(archive);
    system("PAUSE");
	return 0;
}