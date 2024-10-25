#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
#include "test.h"


int main(int argc,char *argv[])
{
	
	
	if (argc != 2){
	printf("please select AS7341 model!\r\n");
	printf("example: sudo ./main getdata\r\n");
	exit(1);
	}
	
	char *Getd = "data" ,*Getf = "flicker" ,*Syns = "syns",*INT = "int",*pinINT = "pinint",*Clear = "clear"	;	
	char project[20];	
	sscanf(argv[1],"%s",&project);	
	if(*project == *Getd)Getdata_test();
	else if(*project == *Getf)Getflicker_test();
	else if(*project == *Syns)Syns_test();
	else if(*project == *INT) INT_test();
	else if(*project == *pinINT) pinINT_test();
	else if(*project == *Clear) Clear_all();	
	else	printf("error: can not find the project\r\n");	
    return 0;
}
