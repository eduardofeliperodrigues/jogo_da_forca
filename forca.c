#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"
    

char palavraSecreta[tamanhoPalavra];
char chutes[26];
int chutesDados = 0;

void abertura(){
    printf("******************************\n");
    printf("        JOGO DA FORCA         \n");
    printf("******************************\n");
}

void adicionaPalavra(){
    
    char quer;
    
    printf("Voce deseja adicionar uma nova palavra ao jogo? (S/N):");
    scanf(" %c", &quer);
    
    if(quer == 'S'){
        
        char novaPalavra[tamanhoPalavra];
        printf("Qual a nova palavra? ");
        scanf("%s", &novaPalavra);
            
        FILE* file;
        
        file = fopen("palavras.txt", "r+");
        
        if(file ==0){
            printf("Desculpe banco de dados, não disponivel!\n\n");
            exit(1); 
        }
        
        //alterando a quantidade de palavras
        int qtd;
        fscanf(file, "%d", &qtd);
        qtd++;
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", qtd);
        
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%s", novaPalavra);
        
        fclose(file);
        
        
    }
    
}
void escolhePalavra() {
	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);
    
    srand(time(0));
	int randomico = rand() % qtddepalavras;

	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavraSecreta);
	}

	fclose(f);
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaForca() {
    
    int erros = chuteserrados();
    
    printf("  _______         \n");
    printf(" |/      |        \n");
    
    printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    
    printf(" |      %c%c%c    \n", (erros >= 3 ? '\\': ' '),(erros >= 2 ? '|': ' '), (erros >= 3 ? '/': ' '));
    
    printf(" |       %c       \n", (erros >= 2 ? '|' : ' '));
    
    printf(" |      %c %c     \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    
    printf(" |                \n");
    printf("_|___             \n");
    printf("\n\n");

    printf("\nVoce ja deu %d chutes\n\n", chutesDados);

    for(int i = 0; i < strlen(palavraSecreta); i++) {
        
        if(jachutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } 
        else {
            printf(" _ ");
        }

    }
    printf("\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra: ");
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
}

int acertou(){
    for (int i =0; i < strlen(palavraSecreta);i++){
        if (!jachutou(palavraSecreta[i])){
            return 0;
        }
    }
    
    return 1;
}

int chuteserrados(){
    int erros = 0;

	for(int i = 0; i < chutesDados; i++) {
		
		int existe = 0;

		for(int j = 0; j < strlen(palavraSecreta); j++) {
			if(chutes[i] == palavraSecreta[j]) {
				existe = 1;
				break;
			}
		}

		if(!existe) erros++;
	}
    
    return erros;
}

int enforcado() {

	return chuteserrados() >= 5;
}


int main(){
    
    abertura();
    
    escolhePalavra();
    
    do{
        desenhaForca();
        
        chuta();
        
        chutesDados++;
        
    }while(!acertou() && !enforcado());
    
    if(!acertou()){
        printf("\n\nQue pena, voce errou a palavra: %s\n\n", palavraSecreta);
        
    }else{
        printf("\n\nParabens, voce acertou a palavra: %s\n\n", palavraSecreta);
    }
    
}