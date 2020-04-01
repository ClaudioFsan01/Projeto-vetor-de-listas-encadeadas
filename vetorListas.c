

#include <stdio.h>
#include <stdlib.h>

//declara??o de constantes
#define TRUE 1
#define FALSE 0

//declara??o de tipos
typedef struct No {
	int valor;
	struct No* prox;
} TNo;

typedef TNo* TLista;

int verifPos(int numero)
{      
 return (numero%10);
}

TLista pesquisar (TLista *L, int numero)
{
	 int pos = verifPos(numero);
	TLista aux = L[pos];

	while (aux)
	{
		if (aux->valor == numero)
		{
			return aux;
		}
		
		aux = aux->prox;
	}	
	
	return NULL;
}


int inserir (TLista *L, int numero)
{
	TLista aux;
	int pos;

	pos = verifPos(numero);
	
	//verificando se o elemento n?o existe na lista (evitando, assim, repeti??o)
	if (pesquisar(L, numero) == NULL)
	{
		//passo 1: alocar mem?ria para o novo elemento
		aux = (TLista) malloc (sizeof(TNo));
		
		if (aux == NULL)  //se n?o foi poss?vel alocar mem?ria
		{
			return FALSE;
		}
		else
		{
			//passo 2: guardar o valor na nova caixa
			aux->valor = numero;
			
			//passo 3: mandar o prox do novo N? apontar para o at? ent?o primeiro elemento da lista
			aux->prox = L[pos];
			
			//passo 4: fazer o L apontar para o novo elemento
			L[pos] = aux;
			
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

int remover (TLista *L, int numero)
/*Fun??o que remove 'numero' da lista 'L'.
A lista ? passada por refer?ncia, uma vez que o seu valor pode ser alterado
durante o processo de remo??o.
A fun??o retornar? TRUE ou FALSE.*/
{
	TLista aux, aux1, aux2;
	int pos;
	
	pos = verifPos(numero);
	//verificando se a lista n?o est? vazia
	if (L[pos] != NULL)
	{
		if (L[pos]->valor == numero)
		{
			aux = L[pos];
			 L[pos] = aux->prox; //ou *L = (*L)->prox;
			free (aux);
			return TRUE;		
		}
		else
		{	
			aux2 = L[pos];
			aux1 = aux2->prox; //ou aux1 = aux2->prox;
				
			while (aux1) // aux1 != NULL
			{
				if (aux1->valor != numero)
				{
					aux2 = aux2->prox; //ou aux2 = aux1;
					aux1 = aux1->prox;
				}
				else
				{
					aux2->prox = aux1->prox;
					free (aux1);
					return TRUE;
				}
			}	
		}
	}
	//else
	//{
	//	return FALSE; //pois a lista est? vazia
	//}
	return FALSE;  //ou a lista est? vazia ou o elemento n?o foi encontrado
}

int alterar (TLista *L, int velho, int novo)
{
	TLista posN, posV;
	int nExib, posVelho,posNovo;
		      
	 posVelho = verifPos(velho);
	 posNovo = verifPos(novo);
	 
    if(posVelho==posNovo)
	{
		posV = pesquisar (L, velho);
	
	  if (posV) //verificando se o velho existe na lista
	   {
		 posN = pesquisar (L, novo);
	   }
	  if (!posN) //ou if (posN == NULL)    --> verificando se o novo n?o existe na lista
	   {
		 posV->valor = novo;
		 return TRUE;
	   }
    }
	else
	{
	    posV = pesquisar (*L, velho);
	     	
	    if (posV) //verificando se o velho existe na lista
	    {
	    posN = pesquisar (*L, novo);
		}
	    if(!posN)
	    {
	    remover (L, velho);
	    inserir (L, novo);
	     		
	    return TRUE;     		
	     		
		}
	}
        	
	return FALSE; //ou o velho n?o foi encontrado, ou o novo foi encontrado
}


void exibir (TLista *L, int nExib)
{
 if(nExib !=10)
 {
 	
     TLista aux = L[nExib];
	
	  if (!L)
	  {
		printf ("Lista vazia!\n");
	  }
	  else
	  {
	  
	  	
	  	printf ("Lista: %d",nExib );
		while (aux)
		{
			printf ("%d ", aux->valor);
			aux = aux->prox;
		}
		printf ("\n");
	  	
	  	
	    
	  }
 
 
 
 }
 else
 {
 	int i;
 	for(i=0; i<10; i++)
    {
      TLista aux = L[i];
      
       if (!aux)
	  {
		printf ("Lista : %d vazia!\n", i+1);
	  }
	  else
	  {
	  
	  	
	  	printf ("Lista: %d \n", i+1);
		while (aux)
		{
			printf ("%d ", aux->valor);
			aux = aux->prox;
		}
		printf ("\n");  	
	    
	  }
 		
	}
 	
 	
 }    
   
   
  
}

int menu ()
{
	int op;
	
	system ("cls");
	printf ("Menu de op??es:\n\n");
	printf ("(1) Inserir\n(2) Remover\n(3) Alterar\n");
	printf ("(4) Buscar\n(5) Exibir\n(6) Sair\n\n");
	printf ("Entre com a sua op??o: ");
	scanf ("%d", &op);
	
	return op;
}

//main
int main (void)
{
	//declara??o de vari?veis
	TLista L[10];
	int opcao, num1, num2, i, nExib;

	for(i=0; i<10; i++)
	{
     L[i] = NULL;	
	}
	
	do
	{
		//exibindo o menu ao usu?rio
		opcao = menu ();
		
		switch (opcao)
		{
			//inser??o
			case 1: printf ("Entre com o n?mero a ser inserido: ");
			        scanf ("%d", &num1);
			        
			        if (inserir (L, num1) == TRUE) //ou apenas inserir (&L, num1)
			        {
			        	printf ("Elemento inserido!\n");
					}
					else
					{
						printf ("ERRO: Elemento n?o inserido!\n");
					}
					break;
				
			//remo??o
			case 2: printf ("Entre com o n?mero a ser removido: ");
			        scanf ("%d", &num1);
			        
			        if (remover (L, num1)) //ou (remover (&L, num1) == TRUE)
			        {
			        	printf ("Elemento removido!\n");
					}
					else 
					{
						printf ("ERRO: Elemento n?o removido!\n");
					}
					break;
				
			//alterar
			case 3: printf ("Entre com o n?mero a ser alterado: ");
			        scanf ("%d", &num1);
			        
			        printf ("Entre com o novo elemento: ");
			        scanf ("%d", &num2);
			        
			        if (alterar (L, num1, num2))
			        {
			        	printf ("Elemento alterado.\n");
					}
					else
					{
						printf ("ERRO: Elemento n?o alterado!\n");
					}
					break;
				
			//pesquisar
			case 4: printf ("Entre com o n?mero a ser buscado: ");
			        scanf ("%d", &num1);
			        
			        if (pesquisar (L, num1) != NULL)
			        {
			        	printf ("Elemento encontrado!\n");
					}
					else
					{
						printf ("Elemento n?o encontrado!\n");
					}
					break;
				
			//exibir
			case 5: 
			        printf(" Digite o n° da lista q deseja exibir entre (0 à 9) ou \n" 
					" dig 10 para exibir todas as listas \n");
					scanf("%d", &nExib);
					
			        exibir (L, nExib);
			        break;
				
			//sa?da
			case 6: printf ("Fim do programa!");
			        break;
			        
			//op??o invalida// hahaha
			default: printf ("Op??o inv?lida! Tente novamente.");
		}
		
		system ("pause");
	}
	while (opcao != 6);

	return 0;
}

