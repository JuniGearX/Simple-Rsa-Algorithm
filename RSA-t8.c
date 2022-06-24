///Junisare V. Silvosa
///ITE14-PXW1

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

long int num_m[300], en_text[300], num_n[300];
//arrays where the encrypted data is stored

long int n, phi, i;
long e[100], d[100], flag;
//initialization and array for the needed value of the RSA

char text[300];
//string where the text for encryption is stored

void read_write_file(int ch)
{
		char filename[80]="";
		printf("\n\tEnter a Filename or File Address(example.txt) a file): ");
			scanf("%s", &filename);

		FILE *fptr1;
			fptr1 = fopen(filename, "r");
		if(fptr1 == NULL){
			printf("\n!!!UNABLE TO OPEN FILE!!!\n");
			printf("PLEASE CHECK IF THE FILE EXIST OR CREATE A NEW ONE.");
			main();
		}
		if(fgets(text, 300, fptr1) != NULL){
			printf("\t\t=>");
			puts(text);
		}

		for(i=0; text[i]!= NULL; i++){
			num_m[i] = text[i];
		}

		fclose(fptr1);
}
//read the a txt file for encryption

void display_keys()
{
	int i;
	printf("\nPrivate Key:");
		printf("\n\tN value:%ld", n);
		printf("\n\tE value:%ld", e[0]);

	printf("\nPublic Key:");
		printf("\n\tD value:%ld", d[0]);

	printf("\nPossible value of E and D\n");
		for(i=0;i<15;i++)
			printf("\n%ld\t%ld",e[i],d[i]);
}
//display all keys for encryption

int check_prime(long int pr)
{
	int i,j;
	j = sqrt(pr);

	for(i=2; i<=j; i++){
		if(pr%i==0){
			return 0;
		}
	}
	return 1;
}

long int find_d(long int e)
{
	long int k=1;

	while(1){
		k = k+phi;
		if(k%e == 0){
			return (k/e);
		}
	}
}


void find_e(long int pr1, long int pr2)
{
	flag = 0;
	int k=0;
	for(i=2; i<phi; i++){
		if(phi%i == 0)
			continue;
		flag = check_prime(i);

		if(flag==1 && i!=pr1 && i!=pr2){
			e[k] = i;
			flag = find_d(e[k]);

			if(flag>0){
				d[k]=flag;
				k++;
			}
		}
		if(k==99){
			break;
		}
	}
}



long int find_n(long int pr1, long int pr2)
{
	long int n;
	n = pr1 * pr2;

	return n;
}

long int find_phi(long int pr1, long int pr2)
{
	long int phi;
	phi = (pr1-1)*(pr2-1);

	return phi;
}

void rsa_encrypt(long int pr1, long int pr2)
{
	n = find_n(pr1, pr2);
	phi = find_phi(pr1, pr2);
	find_e(pr1, pr2);

	long int ascii1, ascii2, key, len, k, j;

	key = e[0];
	i = 0;
	len = strlen(text);

	while(i != len){
		ascii1 = num_m[i];
		ascii1 = ascii1 - 65;
		k = 1;

		for(j=0; j<key; j++){
			k = k*ascii1;
			k = k%n;
		}
		num_n[i] = k;
		ascii2 = k+65;
		en_text[i] = ascii2;
			i++;
	}
	en_text[i] = -1;
		printf("\nEncrypted Text: ");
			for(i=0; en_text[i]!=-1; i++){
				printf("%c", en_text[i]);
			}
	display_keys();
}

void rsa_decrypt()
{
	long int ascii1, ascii2, key, k, j;

	key = d[0];
	i = 0;

	while(en_text[i] != -1){
		ascii2 = num_n[i];
		k=1;

		for(j=0; j<key; j++){
			k = k*ascii2;
			k = k%n;
		}
		ascii1 = k+65;
		num_m[i] = ascii1;
			i++;
	}
	num_m[i] = -1;
		printf("\n\nDecrypted Text: ");
			for(i=0; num_m[i]!=-1; i++){
				printf("%c", num_m[i]);
			}
}

void main(){
	do{
		int choice, choice_2, i, len;
		long int prime_1, prime_2;

		printf("\nRSA Algorithm Menu");
		printf("\n\t1.Start\n\t2.Exit\n\t=>>");
			scanf("%d", &choice);

		switch(choice)
		{
		case 1:
			printf("\n\n\t1.Enter a file\n\t2.Enter a string\n\t=>>");
				scanf("%d", &choice_2);

			if(choice_2 == 1){
				read_write_file(choice);
			}
			if(choice_2 == 2){
				printf("\nEnter Text:\n\t=>>");
					scanf(" %[^\n]s", &text);
						for(i=0; text[i]!= NULL; i++){
							num_m[i] = text[i];
						}
			}
			do{
				printf("\nEnter First prime: ");
					scanf("%d", &prime_1);
						flag = check_prime(prime_1);
							if(flag == 0){
								printf("\n\nInputed number is not a prime");
							}

				printf("\nEnter Second prime: ");
					scanf("%d", &prime_2);
						flag = check_prime(prime_2);
							if(flag==0 || prime_1 == prime_2){
								printf("\n\nInputed number is not a prime");
							}
			}while(flag==0 || prime_1==prime_2);
				rsa_encrypt(prime_1, prime_2);
				getch();
				rsa_decrypt(len);
				printf("\n\n");
			break;

		case 2:
			exit(1);
			break;
		}
	}while(1);

}
