/*
 ============================================================================
 Name        : BalancearArvoreAVL.c
 Author      : Izabelle Otoni
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
 #include <stdlib.h>
 #define max(a, b) (((a) > (b)) ? (a) : (b))
 // Estrutura
 struct no {
   int codigo;
   struct no *direita;
   struct no *esquerda;
 };

 // Novo tipo
 typedef struct no arvore;

 // Prototipos
 arvore *criarNo();
 arvore *inserir(arvore *arv, int codigo);
 void percorreIn(arvore *arv);
 void pesquisar(arvore **atual, arvore **pai, int codigo);
 int encontrarMaiorEsquerda(arvore **pai, arvore **maior, int contador);
 int encontrarMenorDireita(arvore **pai, arvore **menor, int contador);
 int altura(arvore *pontNo);
 int fator(arvore *pontNo);
 arvore *rotacaoEsqEsq(arvore *pontNo);
 arvore *rotacaoEsqDir(arvore *pontNo);
 arvore *rotacaoDirDir(arvore *pontNo);
 arvore *rotacaoDirEsq(arvore *pontNo);
 arvore *balancearNo(arvore *pontNo);
 arvore *balancearArvore (arvore *pai);

 int main(void) {
   setbuf(stdout, NULL);
   // Criar a arvore vazia
   //arvore *pai = NULL;
   arvore *arv = NULL;
   //arvore *atual = NULL;
   int menu = -1;
   int codigo = 0;

   do {
     printf(
         "\n1 - Inserir"
         "\n2 - Excluir"
         "\n3 - Imprimir"
         "\n0 - Finalizar"
         "\nDigite sua opção:");
     fflush(stdin);
     scanf("%i", &menu);

     switch (menu) {
     case 1:
       printf("Digite o valor para inserir na árvore: ");

       fflush(stdin);
       scanf("%i", &codigo);
       arv = inserir(arv, codigo);
       arv = balancearNo(arv);
       arv = balancearArvore(arv);
       break;

     case 2:
       printf("Digite o valor para excluir na árvore: ");

       break;
     case 3:
       percorreIn(arv);
       break;
     }

   } while (menu != 0);

   return 0;
 }

 arvore *criarNo(int codigo) {
   arvore *novo = (arvore *)malloc(sizeof(arvore));
   novo->codigo = codigo;
   novo->direita = NULL;
   novo->esquerda = NULL;

   return novo;
 }

 arvore *inserir(arvore *arv, int codigo) {
   if (arv == NULL) {
     arv = criarNo(codigo);
   } else if (codigo > arv->codigo) {
     arv->direita = inserir(arv->direita, codigo);
   } else {
     arv->esquerda = inserir(arv->esquerda, codigo);
   }
   return arv;
 }

 void percorreIn(arvore *arv) {
   if (arv != NULL) {
     percorreIn(arv->esquerda);
     printf("\nCodigo - %d\tNo - %p\tEsquerda - %p\tDireita %p \n", arv->codigo, arv, arv->esquerda, arv->direita);
     percorreIn(arv->direita);
   }
 }

 void pesquisar(arvore **atual, arvore **pai, int codigo) {
   if (atual != NULL) {                // Caso recursivo
     if (codigo > (*atual)->codigo) {  // Caminho para a direita
       *pai = *atual;
       *atual = (*atual)->direita;
       pesquisar(atual, pai, codigo);
     } else if (codigo < (*atual)->codigo) {  // Caminho para a direita
       *pai = *atual;
       *atual = (*atual)->esquerda;
       pesquisar(atual, pai, codigo);
     }
   }
 }
  int encontrarMaiorEsquerda(arvore **pai, arvore **maior, int contador) {
   if ((*maior)->direita != NULL) {
     *pai = *maior;
     *maior = (*maior)->direita;
     return encontrarMaiorEsquerda(pai, maior, contador + 1);
   } else {
     return contador;
   }
 }

 int encontrarMenorDireita(arvore **pai, arvore **menor, int contador) {
   if ((*menor)->esquerda != NULL) {
     *pai = *menor;
     *menor = (*menor)->esquerda;

     return encontrarMenorDireita(pai, menor, contador + 1);
   } else {
     return contador;
   }
 }
  int altura(arvore *pontNo) {
   int alturaEsq = 0;
   int alturaDir = 0;

   if (pontNo->esquerda) alturaEsq = altura(pontNo->esquerda);

   if (pontNo->direita) alturaDir = altura(pontNo->direita);

   return max(alturaDir, alturaEsq) + 1;
 }

 int fator(arvore *pontNo) {
   int fator = 0;

   if (pontNo->esquerda) fator += altura(pontNo->esquerda);

   if (pontNo->direita) fator -= altura(pontNo->direita);

   return fator;
 }
  arvore *rotacaoEsqEsq(arvore *pontNo) {  // joelho tendendo à esquerda
   arvore *pontTemp = pontNo;  // atribui o valor original a uma temporaria
   arvore *pontEsq = pontTemp->esquerda;  // esq passa a ser o valor da esquerda da variavel temporaria
   pontTemp->esquerda = pontEsq->direita;  // a esquerda da temporaria passa a ser a direira da esquerda anterior
   pontEsq->direita = pontTemp;  // a direita da esquerda anterior pega o valor da temporaria.

   return pontEsq;
 }

 arvore *rotacaoEsqDir(arvore *pontNo) {  // joelho tendendo à esquerda
   arvore *pontTemp = pontNo; // atribui o valor original a uma temporaria
   arvore *pontEsq = pontTemp->esquerda;  // atribui o valor da esquerda da temporaria para outra variavel
   arvore *pontDir = pontEsq->direita;  // atribui o valor à direita do valor à esquerda da variavel original.
   pontTemp->esquerda = pontDir->direita;  // a esquerda da temporaria passa a ser a direita da direita
   pontEsq->direita = pontDir->esquerda;  // a direita da esquerda da temporaria passa a ser a esquerda  da direita
   pontDir->esquerda = pontEsq;  // a esquerda da direita passa a ser o valor da esquerda da temporaria
   pontDir->direita = pontTemp;  // a direita da direita passa a ser a temporaria original.

   return pontDir;
 }

 arvore *rotacaoDirEsq(arvore *pontNo) {  // joelho tendendo à direita
   arvore *pontTemp =pontNo;  // atribui o valor original a uma temporaria
   arvore *pontDir =pontTemp->direita;  // a variavel passa a ser a direita da variavel temporaria
   arvore *pontEsq = pontDir->esquerda;  // a esquerda passa a ser a esquerda da variavel direita, que era a direita da temporaria
   pontTemp->direita = pontEsq->esquerda;  // a direita da temporaria passa a ser a esquerda da variavel Esquerda
   pontDir->esquerda = pontEsq->direita;  // a esquerda da direita passa a ser a direita da esquerda
   pontEsq->direita = pontDir;  // a direita da esquerda passa a ser a direita
   pontEsq->esquerda =pontTemp;  // a esquerda da esquerda passa a ser a temporaria inicial

   return pontEsq;
 }

 arvore *rotacaoDirDir(arvore *pontNo) {  // joelho tendendo à direita
   arvore *pontTemp =pontNo;  // atribui o valor original a uma temporaria
   arvore *pontDir =pontTemp->direita;  // a direita passa a ser a direita da temporaria
   pontTemp->direita = pontDir->esquerda;  // a direita da temporaria passa a ser a esquerda da direita
   pontDir->esquerda = pontTemp; // a esquerda da direita passa a ser a temporaria que era a var original.

   return pontDir;
 }

 arvore *balancearNo(arvore *pontNo){
	 arvore * noBalanceado = NULL;

	 if (pontNo->esquerda)
		 pontNo->esquerda = balancearNo(pontNo->esquerda);
	 if (pontNo->direita)
		 pontNo->direita = balancearNo(pontNo->direita);

	 int fatorBal = fator (pontNo);

	 if (fatorBal >= 2){

		 //Pesando para esquerda
		 if (fator (pontNo->esquerda) <= -1)
			 noBalanceado = rotacaoEsqDir(pontNo);
		 else
			 noBalanceado = rotacaoEsqEsq(pontNo);
	 }
	 else if (fatorBal <= -2) {

		 //Pesando para direita
		 if(fator (pontNo->direita) >= 1)
			 noBalanceado = rotacaoDirEsq(pontNo);
		 else
			 noBalanceado = rotacaoDirDir(pontNo);
	 }
	 else{
		 noBalanceado = pontNo;
	 }

	 return noBalanceado;

 }

 arvore *balancearArvore (arvore *pai){
	 arvore *novaRaiz = NULL;
	 novaRaiz = balancearNo(pai);

	 if (novaRaiz != pai){
		 pai = novaRaiz;
	 }
	 return pai;
 }


