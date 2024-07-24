#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define TF 100

struct TpAutores
{
    char sobrenome[TF], nome[TF];
    struct TpAutores *prox;
};

struct TpLivro
{
    struct TpLivro *ant;
    char titulo_livro[TF];
    int ano, paginas;
    struct TpLista_autor *pAutor;
    struct TpLivro *prox;
};

struct TpEditoras
{
    char editora[TF];
    TpLivro *pLivros;
    TpEditoras *prox;
};

struct TpDescritor
{
    TpEditoras *inicio, *fim;
    int qtde;
};

struct TpLista_autor
{
    TpLista_autor *prox;
    TpAutores *autor;
};

struct TpBiblioteca
{
	char autores[TF], titulo_livro[TF], editora[TF];
	int ano, paginas;	
};

// Função que inicializa o descritor
void inicializarDescritor(TpDescritor &desc)
{
    desc.qtde = 0;
    desc.inicio = NULL;
    desc.fim = NULL;
}

// Função que cria caixinha da editoras
TpEditoras *novaCaixaEditoras(char editora[TF])
{
    TpEditoras *caixa;
    caixa = new TpEditoras;
    strcpy(caixa->editora,editora);
    caixa->pLivros = NULL;
    caixa->prox = NULL;
    return caixa;
}

// Função que cria a caixinha para TpLivro
TpLivro *novaCaixaLivro(char titulo_livro[TF], int ano, int paginas)
{
    TpLivro *caixa;
    caixa = new TpLivro;
    caixa->ano = ano;
    caixa->paginas = paginas;
    strcpy(caixa->titulo_livro, titulo_livro);
    caixa->ant = NULL;
    caixa->pAutor = NULL;
    caixa->prox = NULL;
    return caixa;
}

// Função que cria nova caixa para TpLista_autor
TpLista_autor *novaCaixaListaAutor()
{
    TpLista_autor *caixa;
    caixa = new TpLista_autor;
    caixa->autor = NULL;
    caixa->prox = NULL;
    return caixa;
}

// Função que cria a nova caixa para TpAutores
TpAutores *novaCaixaAutores(char sobrenome[TF], char nome[TF])
{
    TpAutores *caixa;
    caixa = new TpAutores;
    strcpy(caixa->nome, nome);
    strcpy(caixa->sobrenome, sobrenome);
    caixa->prox = NULL;
    return caixa;
}

void relatorioLivrosPorEditora(TpDescritor descritor)
{
    TpEditoras *editoraAtual = descritor.inicio;
    
    while(editoraAtual != NULL)
	{
        printf("\nLivros da editora: %s\n", 	editoraAtual->editora);
        
        if(editoraAtual->pLivros==NULL)
			printf("Edirora sem livros!!");
        
        TpLivro *livroAtual = editoraAtual->pLivros;
        while(livroAtual != NULL)
		{
            printf("Titulo: %s\n", livroAtual->titulo_livro);
            printf("Ano: %d\n", livroAtual->ano);
            printf("Paginas: %d\n", livroAtual->paginas);
            
            livroAtual = livroAtual->prox;
        }
        editoraAtual = editoraAtual->prox;
    }
}

void relatorioLivrosPorAutor(TpDescritor desc) 
{
    TpEditoras *editoraAtual = desc.inicio;

    while (editoraAtual != NULL) {
        TpLivro *livroAtual = editoraAtual->pLivros;
			
        while (livroAtual != NULL) {
            TpLista_autor *autorLivro = livroAtual->pAutor;

            while (autorLivro != NULL) {
                TpAutores *autorAtual = autorLivro->autor;

                if (autorAtual != NULL) {
                    printf("\nNome autor: %s, %s", autorAtual->sobrenome, autorAtual->nome);
                    printf("\nTitulo: %s", livroAtual->titulo_livro);
                    printf("\nEditora: %s", editoraAtual->editora);
                    printf("\nAno: %d", livroAtual->ano);
                    printf("\nPaginas: %d\n\n", livroAtual->paginas);
                }
                autorLivro = autorLivro->prox;
            }
            livroAtual = livroAtual->prox;
        }
        editoraAtual = editoraAtual->prox;
    }
}

void autores(TpAutores *Autores)
{
	TpAutores *autor = Autores;
	
	while(autor != NULL)
	{
		printf("\n--------------------------------------------");
		printf("\nSobrenome:%s",autor->sobrenome);
		printf("\nNome:%s",autor->nome);
		
		autor = autor->prox;
	}
}

TpAutores* inserirAutor(TpAutores *listaA)
{
    TpBiblioteca biblioteca;
    FILE *ptr = fopen("livros.dat", "rb");
    
    if(ptr == NULL)
    	printf("\nErro na abertura do arquivo!\n");
    else 
	{
        while(fread(&biblioteca, sizeof(TpBiblioteca), 1, ptr)) 
		{
	        int i = 0;
	        while(biblioteca.autores[i] != '\0')
			{
	            int cont = 0;
	            char nome[TF], sobrenome[TF];
	            
	            while (biblioteca.autores[i] != ',' && biblioteca.autores[i] != '\0')
	                sobrenome[cont++] = biblioteca.autores[i++];
	            
	            sobrenome[cont] = '\0';
	
	            if(biblioteca.autores[i] == ',') i++;
	
	            cont = 0;
	            while (biblioteca.autores[i] != ';' && biblioteca.autores[i] != '\0')
	                nome[cont++] = biblioteca.autores[i++];
	            
	            nome[cont] = '\0';
	
	            if(biblioteca.autores[i] == ';') i++;
	
	            TpAutores *autor = novaCaixaAutores(sobrenome, nome);
	            if(autor == NULL)
				{
	                printf("\nErro na alocação de memória!\n");
	                fclose(ptr);
	                return listaA;
	            }
	            
	            autor->prox = listaA;
	            listaA = autor;
	        }
        }
        fclose(ptr);
    }
    
    
    return listaA;
}

TpLista_autor *ListaDeAutores(TpBiblioteca biblioteca, TpAutores *ListaA)
{	
	int i=0, j=0, num=1;
	char sobrenome[TF], nome[TF];

	TpAutores *auxListaA = ListaA;
	TpAutores *cabecaAuxListaA = auxListaA;
	TpLista_autor *ncLA,*cabecaLista=NULL,*ultimoLista=NULL;
	
	while(biblioteca.autores[i] != '\0')
	{
		if(biblioteca.autores[i] == ';')
			num++;
		
		i++;
	}
	
	while(num > 0)
	{
		auxListaA = cabecaAuxListaA;
		int cont=0;
		while(biblioteca.autores[j] != ',')
		{
			
			sobrenome[cont] = biblioteca.autores[j];
			j++;
			cont++;
		}
		sobrenome[cont] = '\0';
		
		j++;
		cont=0;
			
		while(biblioteca.autores[j] != ';' && biblioteca.autores[j] != '\0')
		{	
			nome[cont] = biblioteca.autores[j];
			j++;
			cont++;
		}
		nome[cont] = '\0';
		
		while(auxListaA != NULL && (strcmp(auxListaA->sobrenome,sobrenome) != 0 && strcmp(auxListaA->nome,nome) != 0))
		{
			auxListaA = auxListaA -> prox;//++;
		}
		
		ncLA = novaCaixaListaAutor();

		if(cabecaLista == NULL)
		    cabecaLista = ncLA;
	/*	else
			{
				ncLA->prox = cabecaLista;
				cabecaLista = ncLA;
			}*/
		
		
		if(ultimoLista != NULL)
		    ultimoLista->prox = ncLA;
		
		ultimoLista = ncLA;
		
		ncLA->autor = auxListaA;
		ncLA->prox = NULL;
		
		j++;
		num--;
	}
	return cabecaLista;
}

TpLivro *inserirLivro(TpBiblioteca biblioteca, TpAutores *ListaA)
{
    TpLivro *ncL = novaCaixaLivro(biblioteca.titulo_livro, biblioteca.ano, biblioteca.paginas);
    ncL->pAutor = ListaDeAutores(biblioteca, ListaA);
    return ncL;
}

void inserirOrdenadoEditora(TpDescritor &desc, TpEditoras *novaEditora)
{
    TpEditoras *atual = desc.inicio;
    TpEditoras *anterior = NULL;

    while(atual != NULL && strcmp(atual->editora, novaEditora->editora) < 0)
	{
        anterior = atual;
        atual = atual->prox;
    }

    if(anterior == NULL)
	{
        novaEditora->prox = desc.inicio;
        desc.inicio = novaEditora;
        if (desc.fim == NULL) 
            desc.fim = novaEditora;
        
    }
	else
	{
        anterior->prox = novaEditora;
        novaEditora->prox = atual;
        if (anterior == desc.fim)
            desc.fim = novaEditora;
    }

    desc.qtde++;
}

void inserirEditoras(TpBiblioteca biblioteca, TpDescritor &desc, TpAutores *ListaA) {    
    FILE *ptr = fopen("livros.dat", "rb");
    
    if(ptr == NULL)
        printf("\nErro na abertura do arquivo!\n");
	else
	{   
		TpEditoras *ncE = NULL;
        TpLivro *listaL = NULL;
        TpLivro *ncL = NULL;

        while(fread(&biblioteca, sizeof(TpBiblioteca), 1, ptr)) 
		{
			TpEditoras *atual = desc.inicio;
			TpEditoras *editoraExistente = NULL;
			while(atual!=NULL)
			{
				if(strcmp(atual->editora,biblioteca.editora)==0)
					editoraExistente = atual;
				
				atual = atual->prox;
			}
			if(editoraExistente == NULL)
			{
				ncE = novaCaixaEditoras(biblioteca.editora);
           		inserirOrdenadoEditora(desc, ncE);
           		editoraExistente = ncE;
			}
			ncL = novaCaixaLivro(biblioteca.titulo_livro, biblioteca.ano, biblioteca.paginas);
			ncL->pAutor = ListaDeAutores(biblioteca, ListaA);
			if(editoraExistente -> pLivros == NULL)
				editoraExistente->pLivros= ncL;
			else
			{
				TpLivro *ultimoLivro = editoraExistente->pLivros;
				while(ultimoLivro->prox!=NULL)
					ultimoLivro= ultimoLivro->prox;
				
				ultimoLivro->prox = ncL;
				ncL->ant = ultimoLivro;
				
			}
        }
        fclose(ptr);
    }
    printf("\nAlocacao dinamica feita com sucesso\n");
}

void excluirLivro(TpDescritor *desc, char nome[TF])
{
    TpEditoras *editoraAtual = desc->inicio;
    TpLivro *livroAux = NULL;

    while(editoraAtual != NULL)
	{
        livroAux = editoraAtual->pLivros;
        
        while(livroAux != NULL)
		{
            if(strcmp(livroAux->titulo_livro, nome) == 0)
			{

                if(livroAux->ant == NULL)
				{
                    editoraAtual->pLivros = livroAux->prox;
                    if(livroAux->prox != NULL) 
                        livroAux->prox->ant = NULL;
                }
				else
				{
                    livroAux->ant->prox = livroAux->prox;
                    if(livroAux->prox != NULL)
                        livroAux->prox->ant = livroAux->ant;
                }

                delete(livroAux);
                printf("Livro excluido com sucesso da editora %s!\n", editoraAtual->editora);

				/*
                if(editoraAtual->pLivros == NULL)
				{
                    TpEditoras *editoraAnterior = NULL;
                    TpEditoras *editoraAux = desc->inicio;

                    while(editoraAux != NULL)
					{
                        if(editoraAux == editoraAtual)
						{
                            if (editoraAnterior == NULL)
                                desc->inicio = editoraAux->prox;
                            else
                                editoraAnterior->prox = editoraAux->prox;

                            printf("Editora %s excluida por nao possuir mais livros!\n", editoraAtual->editora);
                            delete(editoraAux);
                        }
                        editoraAnterior = editoraAux;
                        editoraAux = editoraAux->prox;
                    }
                    //editoraAtual->pLivros = NULL;
                }
                */
            }
            livroAux = livroAux->prox;
        }
        editoraAtual = editoraAtual->prox;
    }
}

void excluirArqBin(char nome[TF])
{
	TpBiblioteca biblioteca;
	FILE *ptr = fopen("livros.dat","rb");
	FILE *ptrTemp = fopen("livrosTemp.dat","wb");
	
	if(ptr == NULL)
		printf("\n\nErro na abertura do arquivo binario!\n");
	else
	{
	    //fazendo exclusão do arquivo de produtos
	    fread(&biblioteca,sizeof(TpBiblioteca),1,ptr);
		while(!feof(ptr))
		{
			if(strcmp(nome, biblioteca.titulo_livro) != 0)
				fwrite(&biblioteca,sizeof(TpBiblioteca),1,ptrTemp);
			
			fread(&biblioteca,sizeof(TpBiblioteca),1,ptr);
		}
		fclose(ptr);
		fclose(ptrTemp);
		remove("livros.dat");
		rename("livrosTemp.dat","livros.dat");
	}
}

void importarLivros()
{
    FILE *texto = fopen("livros.txt", "r");
    FILE *binario = fopen("livros.dat", "wb");
    if(texto == NULL || binario == NULL)
        printf("Erro ao abrir os arquivos!\n");
    else
    {
    	TpBiblioteca biblioteca;
	
	    while(fscanf(texto, "%[^|]|%[^|]|%[^|]|%d|%d\n", biblioteca.autores, biblioteca.titulo_livro, biblioteca.editora, &biblioteca.ano, &biblioteca.paginas) != EOF)
	        fwrite(&biblioteca, sizeof(TpBiblioteca), 1, binario);
	
	    printf("\nArquivo importado com sucesso\n");
	    fclose(binario);
	    fclose(texto);
    }
}

void relatorioAutorSemLivro(TpAutores *autores, TpDescritor desc)
{
	TpLivro *livro;
	TpLista_autor *listaA;
	TpEditoras *editora = desc.inicio;
	TpAutores *autor = autores;

	int nenhumLivroEncontrado = 1;//flag
	int semlivros = 0, opcao;
	
	
	while(autor!=NULL)
	{	
		editora = desc.inicio;
		while(editora!=NULL && semlivros==0)
		{
			
			livro = editora->pLivros;
			while(livro!=NULL && semlivros==0) 
			{
				
				listaA = livro->pAutor;
				while(listaA!=NULL && listaA->autor!=autor)
				{
					listaA = listaA->prox;
				}
				if(listaA!=NULL)
					semlivros = 1;
				
				livro = livro->prox;  
			}
			editora = editora->prox;
		}
		if(semlivros==0)
		{
			printf("\nNenhum livro encontrado para %s %s\n", autor->nome, autor->sobrenome);
			nenhumLivroEncontrado = 0;
		}
		autor = autor->prox;
		semlivros = 0;
	}
	
	if(nenhumLivroEncontrado)
	{
		printf("Todos os autores tem pelo menos um livro associado.\n");
	}
}

void menu()
{
    printf("\n##Escolha uma opcao##\n");
    printf("1. Importar livros do arquivo de texto para binario\n");
    printf("2. Alocar na memoria\n");
    printf("3. Excluir livros\n");
    printf("4. Relatorio de livros por editora\n");
    printf("5. Relatorio de Livros por Autor\n");
    printf("6. Relatorio de Autores que nao possuem livros\n");
    printf("0. Encerrar programa\n"); 
}

int main(void)
{
    int opcao;
    char nome[TF];
    TpDescritor desc;
    inicializarDescritor(desc);
    
    TpBiblioteca biblioteca;
    
    TpAutores *listaA = NULL;
    TpLista_autor *listaLA = NULL;
    
    do
	{
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao)
		{
            case 1:
                printf("\nOpcao 1 selecionada\n");
                importarLivros();
                getch();
				clrscr();
                break;
                
            case 2:
                printf("\nOpcao 2 selecionada: Alocar dinamicamente\n");
                listaA = inserirAutor(listaA);
                inserirEditoras(biblioteca, desc, listaA);
                getch();
              	clrscr();
                break;
                
            case 3:
                printf("\nOpcao 3 selecionada: Exclusao de livro\n");
                printf("\nDigite o nome(COMPLETO) do livro para exclusao: ");
                fflush(stdin);
                gets(nome);
                excluirLivro(&desc, nome);
                excluirArqBin(nome);
                printf("\nLivro excluido da alocacao dinamica e do arquivo binario!\n");
                getch();
              	clrscr();
                break;
                
            case 4: 
                printf("\nOpcao 4 selecionada: Relatorios de livros por editora\n");
                relatorioLivrosPorEditora(desc);
                getch();
                clrscr();
                break;
                
            case 5: 
                printf("\nOpcao 5 selecionada: Relatorio de Livros por Autor\n");
                relatorioLivrosPorAutor(desc);
                getch();
                clrscr();
                break;
            
            case 6:
                printf("\nOpcao 6 selecionada: Relatorio de Autores que nao possuem livros\n");
			    relatorioAutorSemLivro(listaA,desc);
                getch();
                clrscr();
                break;
                
            case 0:
                printf("Programa encerrado\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                getch();
                clrscr();
                break;
        }
    }while (opcao != 0);

    return 0;
}
