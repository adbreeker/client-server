#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <regex.h>
#include <stdbool.h>
#define _GNU_SOURCE

//#define PORT htons(21212)

const char* typwiad(char wiad[1024], int typ){
	bool flagwiad = false;
	char korektor[] = " ";
	char *schowek;
	bool i = false;
	char *podflaga;
	int licznik = 0;
	int check = 1;

	schowek = strtok (wiad, korektor);
	printf("schowek 1: %s\n",schowek);
	while (schowek != NULL){
		if (strchr(schowek, '!') && i == false){
			  flagwiad = true;
		}
		else if (i == true && flagwiad == true){
			if(typ ==1 || typ==4){
				strcat(podflaga,schowek); //przypisanie podfladze litery od ktorych sie maja zaczynac slowa
			}
			if(typ ==2 || typ==3){
				strcat(podflaga,schowek); // przypisanie podfladze znaku <+/-> i liczby dlugosci LUB liczby i liczby
			}
			strcat(podflaga," ");
		}
		else if(flagwiad==false){
			printf (" twoja wiadomosc byla niepoprawna\n");
			break;
		}
		schowek = strtok (NULL, korektor);
		i = true;
	}
    return podflaga;
}

int komenda(char wiad[1024]){
  int czy;
  int komenda;
  /*if(strncmp(wiad,"!h",2)==0){
	komenda = 0;
  }
  else*/
	if(strncmp(wiad,"!l",2)==0){
	  komenda = 1;
  }
  else if(strncmp(wiad,"!m",2)==0){
	  komenda = 2;
  }
  else if(strncmp(wiad,"!k",2)==0){
	  komenda = 3;
  }
  else if(strncmp(wiad,"!p",2)==0){
	  komenda = 4;
  }
  return komenda;
}
void typl(const char* podflaga){
	FILE* plik1;
	FILE* plik2;
	plik1 = fopen("slowa.txt","r");
	plik2 = fopen("plik.txt","w");
	if (plik1 == NULL){
        printf("Potomny: blad przy otwarciu pliku\n");
        return;
    }
	if (plik2 == NULL){
        printf("Potomny: blad przy tworzeniu pliku\n");
        return;
    }
	char c;
	char slowo[100];
	c = podflaga[2];
	printf("c: %c",c);
	while(fgets(slowo,sizeof(slowo),plik1)){
		char *p = strchr(slowo, c);
		if (p-slowo==0){
			fputs(slowo, plik2);
		}

	}


	fclose(plik1);
	fclose(plik2);
}
void typp(){

	FILE* plik1;
	FILE* plik2;
	plik1 = fopen("slowa1.txt","r");
	plik2 = fopen("plik.txt","w");
	if (plik1 == NULL){
        printf("Potomny: blad przy otwarciu pliku\n");
        return;
    }
	if (plik2 == NULL){
        printf("Potomny: blad przy tworzeniu pliku\n");
        return;
    }
	bool palindrom;
	int i=0;
    char slowo[100+1];
	while(fgets(slowo,sizeof(slowo),plik1))
    {
        printf("%s \n", slowo);
        palindrom = true;



        for(int i=0;i<((strlen(slowo)-2)/2);i++)
        {

            if(slowo[i]!=slowo[(strlen(slowo))-2-(1+i)])
            {
                palindrom = false;
            }
        }
        if(palindrom == true)
        {
			fputs(slowo, plik2);
		}


    }

	fclose(plik1);
	fclose(plik2);
}
void typk(const char* podflaga){
	FILE* plik1;
	FILE* plik2;
	plik1 = fopen("slowa.txt","r");
	plik2 = fopen("plik.txt","w");
	if (plik1 == NULL){
        printf("Potomny: blad przy otwarciu pliku\n");
        return;
    }
	if (plik2 == NULL){
        printf("Potomny: blad przy tworzeniu pliku\n");
        return;
    }
    char* p = strchr(podflaga,' ');
    char c[10];
    int limitalfa=0;
    int limitslowa=0;
    int i=0;
    for (int j=2; j<p-podflaga;j++){
	    c[i]=podflaga[j];
	    i++;
	}
	limitalfa = atoi(c);
	i=0;
	for (int j=p-podflaga; j<strlen(podflaga);j++){
	    c[i]= podflaga[j];
	    i++;
	}
	limitslowa = atoi(c);
	char slowo[100];

	while(fgets(slowo,sizeof(slowo),plik1)){
        int repeat = 0;
        for(int j=1; j<strlen(slowo);j++)
        {
            if((slowo[j]<'a' || slowo[j]>'z') || (slowo[j-1]<'a' || slowo[j-1]>'z') ){
                repeat=limitalfa;
                break;
            }
            else{
                if(slowo[j]<slowo[j-1]){
                    repeat++;
                }
            }
        }
        if(repeat<=limitalfa && strlen(slowo)>=limitslowa+2){
			fputs(slowo, plik2);
		}
    }
fclose(plik1);
fclose(plik2);
}
void ObsluzPolaczenie(int gn){
    char wiadomosc[1024],sciezka[512];
    long dl_pliku, wyslano, wyslano_razem, przeczytano;
    struct stat fileinfo;
    FILE* plik;
    unsigned char bufor[1024];

	const char* help = "!!!Witaj w programie slownika do gier!!!\n\nOto krótka instrukcja obslugi: \n- aby otrzymac slowa zaczynajace sie od danej litery użyj komendy \"!l <wybrana litera>\" \n- aby otrzymac slowa o dlugosci maksymalnie/minimalnie ilus liter uzyj komendy \"!m <+/-> <wybrana długosc>\" \n- aby otrzymać słowa alfabetycznie kolejne użyj komendy \"!k <maksymalne odtworzenia alfabetu> <minimalna długość słowa>\" \n- aby otrzymać slowa palindromy o minimalnej dlugosci \"!p\"\n- instrukcja obslugi \"!h\"\n";

    send(gn, help, strlen(help),0);
    memset(wiadomosc, 0, 1024);
	/*
	printf("\n\n\n!!!Witaj w programie slownika do gier!!!\n\n");
	printf("Oto krótka instrukcja obslugi: \n");
	printf("- aby otrzymac slowa zaczynajace sie od danej litery użyj komendy \"!l <wybrana litera>\" \n");
	printf("- aby otrzymac slowa o dlugosci maksymalnie/minimalnie ilus liter uzyj komendy \"!m <+/-> <wybrana długosc>\" \n");
	printf("- aby otrzymać słowa alfabetycznie kolejne użyj komendy \"!k <maksymalne odtworzenia alfabetu> <minimalna długość słowa>\" \n");
	printf("- aby otrzymać slowa palindromy o minimalnej dlugosci \"!p <minimalna dlugosc slowa>\"\n")
	printf("- instrukcja obslugi \"!h\"\n");
	printf("- zamkniecie programu \"!q\"\n");
	*/
	while(1){
		if (recv(gn, wiadomosc, 1024, 0) <= 0){
			printf("Potomny: blad przy odczycie wiadomosci\n");
			return;
		}
		printf("wiadomosc przed wszystkim: %s\n",wiadomosc);
		if(strncmp(wiadomosc,"!h",2)==0){
            send(gn,"--sh",4,0);
            send(gn,help , strlen(help),0);
		}
		else{
			int command = komenda(wiadomosc);
			printf("wiadomosc przed podflaga: %s\n",wiadomosc);
			printf("komenda: %i\n",command);
			const char* podflaga;
			podflaga = typwiad(wiadomosc, command);

			printf("wiadomosc po podfladze: %s\n",wiadomosc);
			printf("komenda: %i\n",command);
			printf("podflaga: %s\n",podflaga);
			if (command == 1){
				typl(podflaga); }
			//else if (command == 2){
			//	typk(podflaga); }
			else if (command == 3){
				typk(podflaga); }
			else if (command == 4){
				typp(); }

			plik = fopen("plik.txt","r");
			if (plik == NULL){
				printf("Potomny: blad przy otwarciu pliku\n");
				return;
			}

			printf("Potomny: Klient wyslal wiadomosc o tresci: %s\n",wiadomosc);

			if (stat("plik.txt", &fileinfo) < 0){
				printf("Potomny: nie moge pobrac informacji o pliku\n");
				return;
			}
			if (fileinfo.st_size == 0){
				printf("Potomny: rozmiar pliku 0\n");

			}

			printf("Potomny: dlugosc pliku: %d\n", fileinfo.st_size);

            if(fileinfo.st_size>1024)
            {
                send(gn,"--ln",4,0);
            }
            else
            {
                send(gn,"--sh",4,0);
            }
			dl_pliku = htonl((long) fileinfo.st_size);

//			if (send(gn, &dl_pliku, sizeof(long), 0) != sizeof(long)){
//				printf("Potomny: blad przy wysylaniu wielkosci pliku\n");
//				return;
//			}

			dl_pliku = fileinfo.st_size;
			wyslano_razem = 0;
			//plik = fopen("plik.txt", "rb");
			if (plik == NULL){
				printf("Potomny: blad przy otwarciu pliku\n");
				return;
			}

            if(dl_pliku>0)
            {
                while (wyslano_razem < dl_pliku){
				przeczytano = fread(bufor, 1, 1024, plik);
				wyslano = send(gn, bufor, przeczytano, 0);
				if (przeczytano != wyslano)
					break;
				wyslano_razem += wyslano;
				printf("Potomny: wyslano %d bajtow\n", wyslano_razem);
                }
            }
            else
            {
                send(gn,"Brak odpowiadających wyników",30,0);
            }


			if (wyslano_razem == dl_pliku)
				printf("Potomny: plik wyslany poprawnie\n");
			else
				printf("Potomny: blad przy wysylaniu pliku\n");
			fclose(plik);
		}
	}
	return;
}
void wyczyscplik(){
	remove("plik.txt");
}
int main(void){
    int port, netport;
    int gn_nasluch, gn_klienta; // gniazda
    int connection_limiter = 2; //ograniczenie liczby polaczen
    struct sockaddr_in adr;
    socklen_t dladr = sizeof(struct sockaddr_in);

    //zamiana i podanie portu do nasluchu
    printf("Podaj numer portu: ");
    scanf("%d",&port);
    netport = htons(port);

    //tworzenie polaczenia
    gn_nasluch = socket(PF_INET, SOCK_STREAM, 0);
    adr.sin_family = AF_INET;
    adr.sin_port = netport;
    adr.sin_addr.s_addr = INADDR_ANY;
    memset(adr.sin_zero, 0, sizeof(adr.sin_zero));

    if (bind(gn_nasluch, (struct sockaddr*) &adr, dladr) < 0)
    {
        printf("Glowny: bind nie powiodl sie\n");
        return 1;
    }

    listen(gn_nasluch, 10); // nasluchuje do 10 klientow

    int licznik = 0; // do ograniczania liczby klientow
    while(1){
        dladr = sizeof(struct sockaddr_in);



        gn_klienta = accept(gn_nasluch, (struct sockaddr*) &adr, &dladr);


        if (gn_klienta < 0){
            printf("Glowny: accept zwrocil blad\n");
            continue;
        }

        printf("Glowny: polaczenie od %s:%u\n",
            inet_ntoa(adr.sin_addr),
            ntohs(adr.sin_port)
            );

        printf("Glowny: tworze proces potomny\n");
        licznik += 1;
        printf("licznik: %d\n", licznik);
        if (fork() == 0){
            /* proces potomny */
            printf("Potomny: zaczynam obsluge\n");
            ObsluzPolaczenie(gn_klienta);
            licznik -= 1;
            printf("Potomny: zamykam gniazdo\n");
            close(gn_klienta);
            printf("Potomny: koncze proces\n");
			wyczyscplik();
            exit(0);
        }
        else{
            if(licznik >= connection_limiter){
                licznik -= 1;
				wait(NULL);
            }
            /* proces macierzysty */
            printf("Glowny: wracam do nasluchu\n");

            continue;
        }

    }
    return 0;
}
