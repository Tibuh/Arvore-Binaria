#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int TIPOCHAVE;
typedef int bool;

typedef struct reg
{
    TIPOCHAVE chave;
    struct reg *esq;
    struct reg *dir;
} noh; // nó

typedef noh *pont;

pont inicializarArvore()
{
    return NULL;
}

bool arvoreVazia(pont raiz)
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

pont inserir(pont raiz, pont p)
{
    //se a raiz for null, inserimos la
    if (arvoreVazia(raiz))
        return p;
    else if (raiz->chave == p->chave)
    {
        printf("O elemento %d ja existe na arvore\n", p->chave);
        return raiz;
        //se a chave do elemento a ser inserido for menor que a da raiz, insere na subarvore a esquerda
    }
    else if (p->chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, p);
    //se nao insere na subarvore a esqueda
    else
        raiz->dir = inserir(raiz->dir, p);
    return raiz;
}

pont criaNovoNoh(TIPOCHAVE ch)
{
    //aloca um espaco na memoria
    pont novoNoh = (pont)malloc(sizeof(noh));
    //seta que o ponteido da esquerda e null
    novoNoh->esq = NULL;
    //seta que o ponteiro da direito e null
    novoNoh->dir = NULL;
    //seta o valor a chave
    novoNoh->chave = ch;
    //retorna o noh
    return novoNoh;
}
pont buscar(pont raiz, TIPOCHAVE chave)
{
    //verifica se a raiz e null
    if (raiz == NULL)
        return NULL;
    //verifica se o valor da raiz e igual ao valor passado, se for retorna a raiz
    if (raiz->chave == chave)
        return raiz;
    //verifica se o valor da chave da raiz e maior que o passado, se for faz a recursividade e chama a subarvore esquerda
    if (raiz->chave > chave)
        return buscar(raiz->esq, chave);
    //retorna a arvore direita
    return buscar(raiz->dir, chave);
}

int contagemNumeroNohs(pont raiz)
{
    if (!raiz)
        return 0;
    return contagemNumeroNohs(raiz->esq) + 1 + contagemNumeroNohs(raiz->dir);
}

//imprime raiz, esquesda, direita
void imprimePreOrdem(pont raiz){
    printf("<");
    if(!arvoreVazia(raiz)) {

        printf("%d ",raiz->chave);
        imprimePreOrdem(raiz->esq);
        imprimePreOrdem(raiz->dir);
    }
    printf(">");
}

int altura(pont r) {

    int u, v;
    if (r == NULL) return 0;
    u = altura(r->esq);
    v = altura(r->dir);
    if (u > v) return u+1;
    else return v+1;
}

//imprime esquerda, raiz, direita
void imprimeOrdem(pont raiz)
{
    if (raiz->esq != NULL)
        imprimeOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    if (raiz->dir != NULL)
        imprimeOrdem(raiz->dir);
}

//imprime esquerda, direita, raiz
void imprimePosOrdem(pont raiz)
{
    if (raiz->esq != NULL)
        imprimePosOrdem(raiz->esq);
    if (raiz->dir != NULL)
        imprimePosOrdem(raiz->dir);
    printf("%d ", raiz->chave);
}

void imprime_red (pont h) {
     pont *pilha;
    int t;

    pilha = malloc((1+altura(h)) * sizeof (pont));
    pilha[t=0] = h;
    while (t >= 0) {
       h = pilha[t--];
       if (h->dir != NULL) pilha[++t] = h->dir;
       if (h->esq != NULL) pilha[++t] = h->esq;
       if(h->esq == NULL) printf("%d ", h);

    }
    free(pilha); 
}

pont buscaNoh(pont raiz, TIPOCHAVE ch, pont *pai)
{
    pont atual = raiz;

    *pai = NULL;

    while (atual)
    {

        if (atual->chave == ch)
            return atual;

        *pai = atual;

        if (ch < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    return NULL;
}

pont removeNoh(pont raiz, TIPOCHAVE ch)
{
    pont pai, no, paiDaDireita, maisADireita;
    //busca o noh a ser removido e marca o pai dele
    no = buscaNoh(raiz, ch, &pai);
    //verifica se o no e null
    if (no == NULL)
        return raiz;

    //verifica se ele possui apenas um descendente
    if (!no->esq || !no->dir)
    {
        if (!no->esq)
            maisADireita = no->dir;
        else
            maisADireita = no->esq;
        //caso tenha dois descendentes
    }
    else
    {
        //marca pai da direita no noh
        paiDaDireita = no;
        //marca o mais a direita do esquerdo
        maisADireita = no->esq;

        //repeticao para marcar o pai do mais a direita do elemento mais a direita da esquerda do no a ser removido
        while (maisADireita->dir)
        {
            paiDaDireita = maisADireita;
            maisADireita = maisADireita->dir;
        }

        //verifica se o pai mais a direita e diferente do no a ser removido
        if (paiDaDireita != no)
        {
            //faz o pai dda direita apontas para o filho mais a direita
            paiDaDireita->dir = maisADireita->esq;
            //aponta para o filho esquerdo do no a ser removido
            maisADireita->esq = no->esq;
        }

        //aponta para o noh a direita do que sera removido
        maisADireita->dir = no->dir;
    }

    //verifica se o que sera removido e a raiz
    if (pai == NULL)
    {

        int guarda = maisADireita->chave;
        removeNoh(raiz, maisADireita->chave);
        raiz->chave = guarda;
        //remove o noh desejado
        //retorna o mais a direita
        return raiz;
    }

    if (ch < pai->chave)
        pai->esq = maisADireita;
    else
        pai->dir = maisADireita;

    free(no);

    return raiz;
}

int balanco (pont r) {
    pont atual = r;

    int bal = altura(atual->dir) - altura(atual->esq);

    if(bal <= 1 && bal >= -1) {
        if(atual->esq != NULL) balanco(atual->esq);
        if(atual->dir != NULL) balanco(atual->dir);
        return 1;
    }else return 0;
}

int balancoBinaria(pont r) {
    pont atual = r;

    printf("%d ", atual->chave);
     if(((atual->esq == NULL) && (atual->dir == NULL)) 
        ||  ((atual->esq == NULL) && (atual->dir->chave > atual->chave))
            || ((atual->esq->chave < atual->chave) && (atual->dir == NULL))
                || ((atual->esq->chave < atual->chave) && (atual->dir->chave > atual->chave))) {
        int bal = altura(atual->dir) - altura(atual->esq);

        if(bal <= 1 && bal >= -1) {
            if(atual->esq != NULL) balancoBinaria(atual->esq);
            if(atual->dir != NULL) balancoBinaria(atual->dir);
            return 1;
        }else return 0;
    }else return 0;
}

void verificaBalanco(pont r){
    int verifica = balancoBinaria(r);

    if(verifica == 1) printf("Arvore balanceada e e uma arvore de busca");
    else printf("Meu xibiu");
}
void main()
{

    pont r = inicializarArvore();
    pont noh = criaNovoNoh(10);
    r = inserir(r, noh);
    noh = criaNovoNoh(6);
    r = inserir(r, noh);
    noh = criaNovoNoh(2);
    r = inserir(r, noh);
    noh = criaNovoNoh(8);
    r = inserir(r, noh);
    noh = criaNovoNoh(15);
    r = inserir(r, noh);
    noh = criaNovoNoh(12);
    r = inserir(r, noh);
    noh = criaNovoNoh(16);
    r = inserir(r, noh);
    noh = criaNovoNoh(11);
    r = inserir(r, noh);
    noh = criaNovoNoh(13);
    r = inserir(r, noh);
    

    
/*     imprimePreOrdem(r);
    printf("\n");
    removeNoh(r, 10);
    printf("%d\n", contagemNumeroNohs(r)); */
    //imprimeOrdem(r);
    printf("\n");
    imprimePreOrdem(r);
    printf("\n");
    printf("%d ", altura(r));
    //imprimePosOrdem(r);
    printf("\n");
    removeNoh(r, 15);
    imprimePreOrdem(r);
    //imprime_red(r);
    //verificaBalanco(r);
}
