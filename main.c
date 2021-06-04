#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>

#define LED1 4 //16
#define LED2 5 //18
#define LED3 6 //22

int main() {
	if(wiringPiSetup() == -1)
		return -1;
	
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	
	while(1) {
		char str_temp[1024];
		int p[3][2] = {0,};
	
		FILE *pFile = fopen("weather.csv","r");
	
		if (pFile != NULL){
			int j = 0;
			while ( !feof(pFile) ){
				fgets(str_temp, 1024,pFile);
				char *ptr = strtok(str_temp ,",");
				int k = 0;
				while ( ptr != NULL){
					if (j != 0 && j != 4){
						printf("atoi : %d ", atoi(ptr));
						p[j-1][k] = atoi(ptr);
						k++;
					}
					printf("%s ", ptr);
					ptr = strtok(NULL, ",");
				}
				j++;
				
			}
		}
		fclose(pFile);
	
		
printf("\n");
		for (int i = 0; i < 3; i++){
			for (int j = 0 ; j < 2 ; j++){
				printf("%d ", p[i][j]);
			}
			printf("\n");
		}
		
		int seoulTemp = p[2][0];
		int seoulHumi = p[2][1];
		printf("seoulTemp: %d\nseoulHumi: %d\n", seoulTemp, seoulHumi);

		float discomfort = (seoulTemp*9)/5 - 0.55*(1-seoulHumi/100)*(((seoulTemp*9)/5)-26)+32;
		
		printf("discomfort: %f",discomfort);
		
		if(discomfort > 80){
			digitalWrite(LED1, HIGH);
			digitalWrite(LED2, LOW);
			digitalWrite(LED3, LOW);
		}
		else if(discomfort > 70){
			digitalWrite(LED1, LOW);
			digitalWrite(LED2, HIGH);
			digitalWrite(LED3, LOW);
		}
		else if(discomfort < 70){
			digitalWrite(LED1, LOW);
			digitalWrite(LED2, LOW);
			digitalWrite(LED3, HIGH);
		}
		
		delay(36000);
	}
	return 0;
}

