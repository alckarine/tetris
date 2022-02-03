#include <stdio.h>

#define ALTURA_TABULEIRO 10
#define LARGURA_TABULEIRO 10

/* Funcao: atualiza_posicao
 *
 * Parametros:
 *     *l: apontador para a largura do bloco que ira cair
 *     *a: apontador para a altura do bloco que ira cair
 *     *x: apontador para a posicao horizontal inicial do bloco que ira cair
 *   desl: deslocamento horizontal a ser aplicado ao bloco (positivo para direita, negativo para a esquerda)
 *    rot: 1 se deve rotacionar o bloco, 0 caso contrario
 *
 * Retorno:
 *   NULL
 */
void atualiza_posicao(int *l, int *a, int *x, int desl, int rot) {
    int aux =0, larg, posx;

    /*fazendo a rotação*/
    if(rot==1){
        aux = *a;
        *a = *l;
        *l = aux;
    }
    larg = *l;
    posx = *x;

    /*fazendo o deslocamento para direita*/
    if (desl>0){
       if((posx+(larg-1)+desl)>9){*x = 10-(*l);}
       else{*x = *x + desl;}
    }

    /*fazendo deslocamento para esquerda*/
    if(desl<0){
        if(posx+desl<0){*x=0;}
        else{*x = *x + desl;}
    }

}

/* Funcao: encontra_y
 *
 * Parametros:
 *    mat: matriz representando o tabuleiro
 *      l: largura do bloco que ira cair
 *      x: posicao horizontal do bloco que ira cair
 *
 * Retorno:
 *   altura final y do canto inferior esquerdo do bloco apos
 *   este descer o maximo possivel
 */
int encontra_y(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int x) {
    int i=0, j=0, y=0, soma=0;
    for(i=9;i>(-1);i--){
        for(j=x;j<(x+l);j++){
            if(mat[i][j]==0){soma++;}
        }
        if(soma<l){y = i+1; break;}
        if(soma==l && i==0){y=0;}
        soma = 0;
    }
    return y;
}

/* Funcoes: posicao_final_valida
 *
 * Parametros:
 *      a: altura do bloco que caiu
 *      y: altura final do bloco que caiu
 *
 * Retorno:
 *   1 se o bloco naquela posicao estiver contido dentro do tabuleiro, ou 0 caso contrario.
 */
int posicao_final_valida(int a,  int y) {
    if((y+a-1)<10){return 1;}
    else {return 0;}
}

/* Funcoes: posiciona_bloco
 *
 * Parametros:
 *    mat: matriz do tabuleiro
 *      l: largura do novo bloco
 *      a: altura do novo bloco
 *      x: posicao horizontal do novo bloco
 *      y: altura final do novo bloco
 *
 *      Deve preencher com 1s as novas posições ocupadas pelo bloco que caiu
 * Retorno:
 *   NULL
 */
void posiciona_bloco(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int a, int x, int y) {
    int i, j;

    for(i=x;i<(x+l);i++){
        for(j=y;j<(y+a);j++){
            mat[j][i]=1;
        }
    }
}

/* Funcoes: atualiza_matriz
 *
 * Parametros:
 *    mat: matriz do tabuleiro
 *
 *         Deve remover as linhas totalmente preenchidas do tabuleiro copiando
 *         linhas posicionadas acima.
 * Retorno:
 *   retorna o numero de linhas totalmente preenchidas que foram removidas apos
 *   a atualizacao do tabuleiro.
 */
int atualiza_matriz(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO]) {
    int i=0, j, k, p, ponto=0, soma=0;

    while(i<10){

        for(j=0;j<10;j++){
          if(mat[i][j]==1){soma++;}
        }

        if(soma==10){
           ponto++;
           for(k=i;k<9;k++){
             for(p=0;p<10;p++){
                mat[k][p]=mat[k+1][p];
             }
           }
           for(p=0;p<10;p++){
                mat[9][p]=0;
             }
        }
        else{i++;}

        soma = 0;
    }
    return ponto;
}






void atualiza_posicao(int *l, int *a, int *x, int desl, int rot);
int encontra_y(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int x);
int posicao_final_valida(int a,  int y);
void posiciona_bloco(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int a, int x, int y);
int atualiza_matriz(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO]);

int main() {
    int n;
    int l, a, x, desl, rot, y, valido, pontos = 0;
    int i, j, k;

    int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO];

    for (j = 0; j < ALTURA_TABULEIRO; j++) {
        for (i = 0; i < LARGURA_TABULEIRO; i++) {
            matriz[j][i] = 0;
        }
    }

    scanf("%d", &n);

    for (k = 0; k < n; k++) {
        scanf("%d %d %d %d %d", &l, &a, &x, &desl, &rot);

        atualiza_posicao(&l, &a, &x, desl, rot);
        y = encontra_y(matriz, l, x);
        valido = posicao_final_valida(a, y);

        if (valido) {
            posiciona_bloco(matriz, l, a, x, y);
            pontos += atualiza_matriz(matriz);

            printf("bloco %d\n", k);
            printf("%d pontos\n", pontos);

            for (j = ALTURA_TABULEIRO - 1; j >= 0; j--) {
                for (i = 0; i < LARGURA_TABULEIRO; i++) {
                    printf("%d", matriz[j][i]);
                }

                printf("\n");
            }
        } else {
            break;
        }
    }

    return 0;
}
