#include <stdio.h>
#include <string.h>

char palavraSecreta[20];
char chutes[26];
int tentativas = 0;

void abertura(){
    printf("******************************\n");
    printf("        JOGO DA FORCA         \n");
    printf("******************************\n");
}

void escolhePalavra(){
        sprintf(palavraSecreta, "BANANA");
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < tentativas; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaForca() {

    printf("\n\n\nVoce ja deu %d chutes\n\n", tentativas);

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

    chutes[tentativas] = chute;
}

int enforcado(){
    int erros = 0; 
    for (int  i = 0; i < tentativas; i++){
        int existe = 0;
        for(int j = 0; j < strlen(palavraSecreta); j++){
            if (chutes[i] == palavraSecreta[j]){
                existe = 1;
            }
        }
        
        if (!existe) erros++;
    }
    
    return erros >= 5;
}

int main(){
    int acertou = 0;
    int enforcou = 0;
    
    abertura();
    
    escolhePalavra();
    
    do{
        desenhaForca();
        
        chuta();
        
        tentativas++;
        
    }while(!acertou && !enforcado());
}