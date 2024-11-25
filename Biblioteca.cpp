#include <stdio.h>
#include "meuconio.h"
#include "conio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>
#include <locale.h>


#define TAM 50

struct TpLivro {
	int id_livro , ano_publicacao,status;
	char titulo[TAM];
	
};

struct TpAutor {
	int id_autor,status;
	char nome[TAM], nacionalidade[TAM];
};
struct TpEndereco {
	char rua[TAM],bairro[TAM],cidade[TAM],estado[3],pais[TAM]; 
	int numero, cep;
};
struct TpPessoa{
	int id_pessoa,telefone,status;
	char nome[TAM];
	TpEndereco Endere; 
};
struct TpEmprestimo {
	int id_emprestimo,id_livro,id_pessoa,status; 
};

struct TpLivroAutor{
	int id_livro, id_autor, status;
};

//FunÃ§Ãµes
//Painel 
void PainelPrincipal(void);
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF);
void Enter(void);
void exibirParabens(int x, int y);



//Menu
char Menu(void);
char MenuLivro(void);
char MenuAutor(void);
char MenuPessoa(void);
char MenuEmprestimo(void);
char MenuLivroAutor(void);
int MenuExcluir(void);
int  MenuRelatorio(void);





//Cadastros
void CadastroLivro(void);
void CadastroAutor(void);
void CadastroEmprestimo(void);
void CadastrarEndereco(TpEndereco *Endere);
void CadastroPessoa(void);
void CadastroLivroAutor(void);


//Buscas
int BuscaIDLivro(FILE *Livro, int id);
int BuscaIDAutor(FILE *Autor, int id);
int BuscaIDPessoa(FILE *Pessoa, int id);
int BuscaIDEmprestimo(FILE *Empres, int id);
int BuscaIDLivroEmpres(FILE *Empres, int id );


//Busca Binaria
int BuscaBinariaLivro(FILE *Livro, int id);
int BuscaBinariaAutor(FILE *Autor, int id);
int BuscaBinariaPessoa(FILE *Pessoa, int id);
int BuscaBinariaEmprestimo(FILE *Empres, int id);
int BuscaBinariaLivroAutor(FILE *LivAut, int id);


//Odenação direta 
void InsDiretaLivro(FILE *Livro);
void InsDiretaAutor(FILE *Autor);
void InsDiretaLivroAutor(FILE *LivAut);
void InsDiretaEmprestimo(FILE *Empres);
void InsDiretaPessoa(FILE *Pessoa);
void OrdenaNacionalidade (FILE * autor);


//Exibir 
void ExibirPessoas(void);
void ExibirLivros(void);
void ExibirAutores(void);
void ExibirEmprestimos(void);
void ExibirLivroAutor(void);

//Consulta
void ConsultarLivro(void);
void ConsultarAutor(void);
void ConsultarPessoa(void);
void ConsultarEmprestimo(void);
void ConsultarLivroAutor(void);


//Alterar
void AlterarLivro(void);
void AlterarAutor(void);
void AlterarPessoa(void);
void AlterarEmprestimo(void);



//ExclusÃ£o LÃ³gica
void ExclusaoLogicaLivro(void);
void ExclusaoLogicaAutor(void);
void ExclusaoLogicaPessoa(void);
void ExclusaoLogicaEmprestimo(void);
void ExclusaoLogicaLivroAutor(void);


//Exclusao Fisica
void ExclusaoFisicaLivro(void);
void ExclusaoFisicaAutor(void);
void ExclusaoFisicaPessoa(void);
void ExclusaoFisicaEmprestimo(void);
void ExclusaoFisicaLivroAutor(void);


//Executar 
void ExecutarEmprestimo(void);
void ExecutarLivro(void);
void ExecutarLivroAutor(void);
void ExecutarPessoa(void);
void ExecutarAutor(void);
void Executar(void);

//Relatorio
void relatorioEmprestimoPessoa(void);
void exibeLivroAutor(void);
void OrdenaNacionalidade(void);
void RelatorioLetraAutor (void);
void GerarRelatorioEmprestimos(void);
void relatorioCompleto(void);



void Gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// FunÃ§Ã£o para limpar uma Ã¡rea retangular da tela
void limparArea(int x, int y, int largura, int altura) {
    for (int i = 0; i < altura; i++) {
        Gotoxy(x, y + i); 
        for (int j = 0; j < largura; j++) {
            printf(" "); 
        }
    }
}
void limparLinha(int x, int y, int largura) {
    gotoxy(x, y); 
    for (int i = 0; i < largura; i++) {
        printf(" "); 
    }
}
    

int main (void)
{
	
    setlocale(LC_ALL, "pt_BR.UTF-8");
    textcolor(15);
    Executar();
    return 0;
}

void Enter(void)
{
    int i;
    textcolor(15);
    for (i=16; i<31;i++)
    {
        gotoxy(i,9);
        printf ("%c", 95);
    }
    for (i=10; i<14; i++)
    {
        gotoxy(16,i);
        printf ("%c", 124);
    }
    for (i=16;i<20;i++)
    {
        gotoxy(i,14); 
        printf ("%c", 240);
    }
    for (i=15; i<19;i++)
    {
        gotoxy(19,i); 
        printf ("%c", 124);
    }
    for (i=10;i<19;i++)
    {
        gotoxy(30,i); 
        printf ("%c", 124);
    }
    for (i=19;i<31;i++)
    {
        gotoxy(i,19); 
        printf ("%c", 240);
    }
    gotoxy(20,11); printf ("[ENTER]");
    gotoxy(21, 21); printf ("PARA SAIR");
    gotoxy(21,8); printf ("TECLE");
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
    int i;
    textcolor(CorT);
    textbackground(CorF);

    // Desenha os cantos
    gotoxy(CI, LI); printf("%c", 201);  // Canto superior esquerdo.
    gotoxy(CF, LI); printf("%c", 187);  // Canto superior direito.
    gotoxy(CI, LF); printf("%c", 200);  // Canto inferior esquerdo.
    gotoxy(CF, LF); printf("%c", 188);  // Canto inferior direito.

    // Desenha as linhas horizontais (superior e inferior).
    for (i = CI + 1; i < CF; i++) {
        gotoxy(i, LI); printf("%c", 205);
        gotoxy(i, LF); printf("%c", 205);
    }

    // Desenha as linhas verticais (esquerda e direita).
    for (i = LI + 1; i < LF; i++) {
        gotoxy(CI, i); printf("%c", 186);
        gotoxy(CF, i); printf("%c", 186);
    }

    // Desenha o sombreamento para um efeito 3D
    textcolor(8); // Cor cinza para a sombra
    for (i = CI; i <= CF; i++) {
        gotoxy(i, LF + 1); printf("%c", 223); // Linha inferior sombreamento
    }
    for (i = LI; i <= LF; i++) {
        gotoxy(CF + 1, i); printf("%c", 219); // Linha direita sombreamento
    }

    // Reseta a cor do texto e fundo
    textcolor(7);
    textbackground(0);
}

// FunÃ§Ã£o que define o layout do painel principal com melhorias visuais.
void PainelPrincipal(void)
{
    // Moldura principal com fundo cinza escuro e bordas verdes
    Moldura(10, 1, 115, 30, 15, 8);  // Verde para o texto, cinza escuro para o fundo

    // Moldura secundÃ¡ria com fundo preto e bordas cinza claro
    Moldura(11, 2, 114, 4, 7, 0);   // Branco para o texto, fundo preto
    
    textcolor(15); // Define a cor do texto para o tÃ­tulo.
    gotoxy(50, 3); printf("BIBLIOTECA"); // TÃ­tulo no painel.

    // Molduras internas
    Moldura(11, 5, 50, 26, 10, 0); // Verde claro para o texto, fundo preto
    Moldura(11, 27, 114, 29, 15, 7); // Cinza para o texto, fundo cinza claro

    // Campo de mensagem com fundo preto e borda cinza claro
    textcolor(14);
    gotoxy(12, 28);
    printf("MENSAGEM:"); // Campo de mensagem no painel.
}
void exibirParabens(int x, int y) {

   	textcolor(10);
    gotoxy(x, y);    printf("PPPPP   AAAAA   RRRRR   AAAAA   BBBBB   EEEEE   N   N   SSSSS");
    gotoxy(x, y + 1);printf("P   P   A   A   R   R   A   A   B   B   E       NN  N   S");
    gotoxy(x, y + 2);printf("PPPPP   AAAAA   RRRRR   AAAAA   BBBBB   EEEE    N N N   SSSSS");
    gotoxy(x, y + 3);printf("P       A   A   R  R    A   A   B   B   E       N  NN       S");
    gotoxy(x, y + 4);printf("P       A   A   R   R   A   A   BBBBB   EEEEE   N   N   SSSSS");
	                                 
    Sleep(5000);
}

void Executar(void){
	char op;
	PainelPrincipal();
	do{
		limparArea(12, 5, 35, 10);
		op = Menu();
		switch(op){
			case'A':
				ExecutarLivro();
				break;
			case'B':
				ExecutarAutor();
				break;
			case'C':
				ExecutarPessoa();
				break;
			case'D':
				ExecutarEmprestimo();
				break;
			case'E':
				ExecutarLivroAutor();
				break;
			// case 'F':
			// 	Executarrelatorio();
			// 	break;
		}
	}while(op != 27);
}
void ExecutarLivro(void){
	char op;
	do{
		limparArea(12, 5, 35, 10);
		op = MenuLivro();
		switch(op){
			case'A':
				CadastroLivro();
				break;
			case'B':
				ExibirLivros();
				break;
			case'C':
				ConsultarLivro();
				break;
			case'D':
				AlterarLivro();
				break;
			case'E':
				op = MenuExcluir();
				switch(op){
					case 'A':
						ExclusaoLogicaLivro();
						break;
					case 'B':
						ExclusaoFisicaLivro();
						break;
				
				}
				break;

		 }
	}while(op != 27);
}
void ExecutarAutor(void){
	char op;
	do{
		op = MenuAutor();
		switch(op){
			case'A':
				CadastroAutor();
				break;
			case'B':
				ExibirAutores();
				break;
			case'C':
				ConsultarAutor();
				break;
			case'D':
				AlterarAutor();
				break;
			case'E':
				op = MenuExcluir();
				switch(op){
					case 'A':
						ExclusaoLogicaAutor();
						break;
					case 'B':
						ExclusaoFisicaAutor();
						break;
				}
				break;

		}
	}while(op != 27);
}
void ExecutarEmprestimo(void){
	char op;
	do{
		op = MenuEmprestimo();
		switch(op){
			case'A':
				CadastroEmprestimo();
				break;
			case'B':
				ExibirEmprestimos();
				break;
			case'C':
				ConsultarEmprestimo();
				break;
			case'D':
				AlterarEmprestimo();
				break;
			case'E':
				op =MenuExcluir();
				switch(op){
					case 'A':
						ExclusaoLogicaEmprestimo();
						break;
					case 'B':
						ExclusaoFisicaEmprestimo();
						break;
				}
				break;

					
				break;

		}
	}while(op != 27);
}
void ExecutarPessoa(void){
	char op;
	do{
		op = MenuPessoa();
		switch(op){
			case'A':
				CadastroPessoa();
				break;
			case'B':
				ExibirPessoas();
				break;
			case'C':
				ConsultarPessoa();
				break;
			case'D':
				AlterarPessoa();
				break;
			case'E':
				
				op = MenuExcluir();
				switch(op){
					case 'A':
						ExclusaoLogicaPessoa();
						break;
					case 'B':
						ExclusaoFisicaPessoa();
						break;
				}
				break;
		}
	}while(op != 27);
}
void ExecutarLivroAutor(void){
	char op;
	PainelPrincipal();
	do{
		op = MenuLivroAutor();
		switch(op){
			case'A':
				CadastroLivroAutor();
				break;
			case'B':
				ExibirLivroAutor();
				break;
			case'C':
				ConsultarLivroAutor();
				break;			
			case'D':
				limparArea(13, 13, 35, 10);
				op =MenuExcluir();
				switch(op){
					case 'A':
						ExclusaoLogicaLivroAutor();
						break;
					case 'B':
						ExclusaoFisicaLivroAutor();
						break;
						
				}
				break;
		}
	}while(op != 27);
}

void ExecutarRelatorio(void){
	char op ;
	op = MenuRelatorio();
	do {
		switch(op){
			case'A':
			relatorioCompleto();
			break;
			case'B':
			RelatorioLetraAutor();
			break;
			case'C':

			break;
			case'D':
			break;
			case'E':
			break;
			case'F':
			break;
		}
	}while(op != 27);
	
}

//menus

char Menu(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Livro\n");
	gotoxy(17,12);printf("[B]Autor\n");
	gotoxy(17,13);printf("[C]Pessoas\n");
	gotoxy(17,14);printf("[D]Emprestimos\n");
	gotoxy(17,15);printf("[E]Livro-Autor\n");
	gotoxy(17,16);printf("[ESC]Sair\n");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
}
char MenuLivro(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Cadastrar Livro\n");
	gotoxy(17,12);printf("[B]Exibir Livros\n");
	gotoxy(17,13);printf("[C]Consultar Livro\n");
	gotoxy(17,14);printf("[D]Alterar Livro\n");
	gotoxy(17,15);printf("[E]Excluir Livro\n");
	gotoxy(17,16);printf("[ESC]Sair\n");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
}
char MenuAutor(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Cadastrar Autor\n");
	gotoxy(17,12);printf("[B]Exibir Autor\n");
	gotoxy(17,13);printf("[C]Consultar Autor\n");
	gotoxy(17,14);printf("[D]Alterar Autor\n");
	gotoxy(17,15);printf("[E]Excluir Autor\n");
	gotoxy(17,16);printf("[ESC]Sair\n");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
	
}
char MenuPessoa(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Cadastrar Pessoa\n");
	gotoxy(17,12);printf("[B]Exibir Pessoas\n");
	gotoxy(17,13);printf("[C]Consultar Pessoa\n");
	gotoxy(17,14);printf("[D]Alterar Pessoa\n");
	gotoxy(17,15);printf("[E]Excluir Pessoa\n");
	gotoxy(17,16);printf("[ESC]Sair\n");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
}
char MenuEmprestimo(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Cadastrar Emprestimo\n");
	gotoxy(17,12);printf("[B]Exibir Emprestimos \n");
	gotoxy(17,13);printf("[C]Consultar Emprestimo\n");
	gotoxy(17,14);printf("[D]Alterar Emprestimo\n");
	gotoxy(17,15);printf("[E]Excluir Emprestimo\n");
	gotoxy(17,16);printf("[ESC]Sair\n");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
}
char MenuLivroAutor(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]Cadastrar Livro-Autor");
	gotoxy(17,12);printf("[B]Exibir Livros-Autores");
	gotoxy(17,13);printf("[C]Consultar Livro-Autor");
	gotoxy(17,14);printf("[D]Alterar Livro-Autor");
	gotoxy(17,15);printf("[E]Excluir Livro-Autor");
	gotoxy(17,16);printf("[ESC]Sair");
	fflush(stdin);
	gotoxy(21,28);return toupper(getch());
}

int MenuExcluir(void){
	limparArea(13, 13, 35, 10);
	textcolor(15);
	gotoxy(17,11);printf("[A]- Exclusao Logica\n");
	gotoxy(17,12);printf("[B]- Exclusao Fisica\n");
	gotoxy(17,13);printf("[ESC]- Sair             ");
	gotoxy(21,28);return toupper(getch());
}
int  MenuRelatorio(void){
	limparArea(13, 13, 35, 10);
	gotoxy(15,11);printf("[A]Consulta de Cada tabela ");
	gotoxy(15,12);printf("[B]Autor por determinada letra");
	gotoxy(15,13);printf("[C]Livros - determinada palavra");
	gotoxy(15,14);printf("[D]Emprestimos de uma pessoa");
	gotoxy(15,15);printf("[E]Moatrar dados de livro-Autor");
	gotoxy(15,16);printf("[f]Todos os emprestimos");
	gotoxy(15,13);printf("[ESC]- Sair ");
	gotoxy(21,28);return toupper(getch());
}
//Cadastros
void CadastroLivro(void){
	TpLivro Reg;
	FILE *Livro = fopen("Livro.dat","rb+");
	if(Livro == NULL){
		textcolor(4);
		gotoxy(22,30);printf("Erro ao abrir Arquivo!!!");
		Sleep(1.5);
		textcolor(15);
		fclose(Livro);
	}
	else{
		textcolor(6);
		gotoxy(53, 6); printf("--------------------------------------------------------");
		textcolor(6);
		gotoxy(53, 8); printf("--------------------------------------------------------");
		textcolor(3);
		gotoxy(53,7);printf("Digite o id do Livro ou [0] SAIR:");
		textcolor(15);
		gotoxy(86,7);scanf("%d", &Reg.id_livro);
		while(Reg.id_livro != 0){
			if(BuscaIDLivro(Livro,Reg.id_livro)== -1){
				textcolor(3);
				gotoxy(53, 9); printf("TITULO:");
				fflush(stdin);
				textcolor(15);
				gotoxy(60, 9); gets(Reg.titulo);

				textcolor(3);
				gotoxy(53, 10); printf("Ano da publicacao:");
				textcolor(15);
				gotoxy(71, 10); scanf("%d", &Reg.ano_publicacao);

				Reg.status = 1;
				fseek(Livro, 0, 2);
				fwrite(&Reg, sizeof(TpLivro), 1, Livro);
				InsDiretaLivro(Livro);

				textcolor(10);
				gotoxy(22, 28); printf("Livro Cadastrado!!!");
				Sleep(1700);

				limparLinha(28, 22, 50);
			
			}
			else{	
				limparArea(51, 5, 60,10 );
				textcolor(4);
				gotoxy(22,28);printf("ID de livro ja esta cadastrado!!!");
				Sleep(1700);
				limparLinha(21,28 , 50);
			}
			limparArea(51, 5, 60,10 );
			textcolor(6);
			gotoxy(53, 6); printf("--------------------------------------------------------");
			gotoxy(53, 8); printf("--------------------------------------------------------");
			textcolor(3);
			gotoxy(53,7);printf("Digite o id do Livro ou [0] SAIR:\n");
			textcolor(15);
			gotoxy(86,7);scanf("%d", &Reg.id_livro);
			
			
		}
	}
	limparArea(51, 5, 60,10 );
	fclose(Livro);
}

void CadastroAutor(void){
	TpAutor Aut;
	FILE *Autor = fopen("Autor.dat","rb+");
	if(Autor == NULL){
		textcolor(4);
		gotoxy(22,30);printf("Erro ao abrir Arquivo!!!");
		fclose(Autor);
		Sleep(1.5);
		limparLinha(24,28 , 50);
		textcolor(15);
		
	}
	else{
		limparArea(51, 5, 60,10 );
		textcolor(15);
		gotoxy(56,7);printf("Digite o id do Autor ou [0] SAIR:");
		gotoxy(89,7);scanf("%d", &Aut.id_autor);
		while(Aut.id_autor !=0){
			
			if(BuscaIDAutor(Autor,Aut.id_autor) == -1) {
				gotoxy(56,8);printf("Nome:");
				fflush(stdin);
				gotoxy(61,8);gets(Aut.nome);
				gotoxy(56,9);printf("Nacionalidade:");
				fflush(stdin);
				gotoxy(71,9);gets(Aut.nacionalidade);
				Aut.status = 1;
				textcolor(10);
				gotoxy(22,28);printf("Autor Cadastrado!!!");
				fseek(Autor,0,2);
				fwrite(&Aut , sizeof(TpAutor),1,Autor);
				InsDiretaAutor(Autor); 
				Sleep(1800);
				limparLinha(21,28 , 50);
			}
			else{
				textcolor(4);
				gotoxy(22,28);printf("ID de Autor jÃ¡ cadastrado!!!");
				
			}
			
			limparArea(51, 5, 60,10 );
			textcolor(15);
			gotoxy(56,7);printf("Digite o id do Autor ou [0] SAIR:");
			gotoxy(89,7);scanf("%d", &Aut.id_autor);
			limparLinha(21,28 , 50);	
		}
	}
	fclose(Autor);
	limparArea(51, 5, 60,10 );
	
}
void CadastroPessoa(void){
	TpPessoa Pess;
	FILE *Pessoa = fopen("pessoas.dat","rb+");
	if(Pessoa == NULL ){
		textcolor(4);
		gotoxy(22,30);printf("Erro ao abrir Arquivo!!!");
		fclose(Pessoa);
		Sleep(1.5);
		limparLinha(21,28 , 50);
		textcolor(15);
	}
	else{
		textcolor(15);
		gotoxy(56,7);printf("Digite o id da Pessoa ou [0] SAIR: ");
		gotoxy(90,7);scanf("%d", &Pess.id_pessoa);
		while(Pess.id_pessoa != 0){
			if(BuscaIDPessoa(Pessoa, Pess.id_pessoa)== -1){
				
				gotoxy(56,8);printf("Nome:");
				fflush(stdin);
				gotoxy(61,8);gets(Pess.nome);
				gotoxy(54,9);printf("Numero de telefone:");
				gotoxy(78,9);scanf("%d", &Pess.telefone);
				CadastrarEndereco(&Pess.Endere);
				Pess.status = 1;
				textcolor(10);
				gotoxy(22,28);printf("Pessoa cadastrada !!!");
				Sleep(3000);
				fwrite(&Pess, sizeof(TpPessoa),1,Pessoa);
				InsDiretaPessoa(Pessoa);
				limparLinha(21,28 , 50);
			}
			else{
				textcolor(4);
				gotoxy(22,28);printf("ID de pessoa cadastrado");
				Sleep(3000);
				limparLinha(21,28 , 50);
			}
			limparArea(51, 5, 60,15 );
			textcolor(15);
			gotoxy(56,7);printf("Digite o id da Pessoa ou [0] SAIR: ");
			gotoxy(90,7);scanf("%d", &Pess.id_pessoa);		
		}
	}
	fclose(Pessoa);
	limparArea(51, 5, 60,10 );
}

void CadastrarEndereco(TpEndereco *Endere){
	
	gotoxy(53,10);printf("-------------------------EndereÃ§o-----------------------");
	gotoxy(56,11);printf("Rua:");
	fflush(stdin);
	gotoxy(61,11);gets(Endere->rua);
	
	gotoxy(56,12);printf("Bairro:");
	fflush(stdin);
	gotoxy(63,12);gets(Endere->bairro);
	
	gotoxy(56,13);printf("Numero:");
	gotoxy(63,13);scanf("%d", &Endere->numero);

	gotoxy(56,14);printf("Cidade:");
	fflush(stdin);
	gotoxy(63,14);gets(Endere->cidade);
	gotoxy(56,15);printf("Cep:");
	gotoxy(62,15);scanf("%d", &Endere->cep);
	
	gotoxy(56,16);printf("Estado:");
	fflush(stdin);
	gotoxy(63,16);gets(Endere->estado);
	gotoxy(56,17);printf("PaÃ­s:");
	fflush(stdin);
	gotoxy(64,17);gets(Endere->pais);
	gotoxy(53,18);printf("--------------------------------------------------------");
	Sleep(1.7);
}
void CadastroEmprestimo(void){
	TpEmprestimo Emp;
	FILE *Empres,*Livro ,*Pessoa ;
	
	Empres = fopen("Emprestimos.dat","rb+");
	Livro = fopen("Livro.dat","rb");
	Pessoa = fopen("Pessoas.dat","rb");

	if(Empres == NULL || Livro == NULL || Pessoa == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir Arquivo!!!");
		fclose(Empres);
        fclose(Livro);
        fclose(Pessoa);
		Sleep(1.5);
		textcolor(15);
	}
	else{
		gotoxy(56,7);printf("Digite o id do emprestimo: ");
		gotoxy(82,7);scanf("%d", &Emp.id_emprestimo);
		while(Emp.id_emprestimo != 0){
			if(BuscaBinariaEmprestimo(Empres,Emp.id_emprestimo) == -1){
				gotoxy(56,8);printf("ID do livro:");
				gotoxy(68,8);scanf("%d", &Emp.id_livro);
				int pos = BuscaBinariaLivro(Livro, Emp.id_livro);
				int pos1 = BuscaIDLivroEmpres(Empres, Emp.id_livro);
				if( pos != -1 && pos1 == - 1){
					gotoxy(56,9);printf("ID da pessoa:");
					gotoxy(69,9);scanf("%d", &Emp.id_pessoa);
					if(BuscaBinariaPessoa(Pessoa, Emp.id_pessoa) != -1){
						Emp.status = 1; 
						fseek(Empres,0,2);
						fwrite(&Emp , sizeof(TpEmprestimo),1,Empres);
						InsDiretaEmprestimo(Empres);
						textcolor(10);
						gotoxy(22,28);printf("Emprestimo cadastrado!!!");
						Sleep(2000);
						limparLinha(21,28 , 50);
						
					}
					else{
						textcolor(4);
						gotoxy(22,28);printf("Pessoa não encontrada");
						Sleep(2000);
						
			
					}
				}else{
					textcolor(4);
					gotoxy(22,28);printf("Livro não encontrado ou já está emprestado !!!");
					Sleep(2000);
				
				}
			}
			else{
				textcolor(4);
				gotoxy(22,28);printf("ID de emprestimo ja cadastrado!!!");
				Sleep(2000);
				
			}
			limparArea(51, 5, 60,10 );
			textcolor(15);
			gotoxy(56,7);printf("Digite o id do emprestimo: ");
			gotoxy(82,7);scanf("%d", &Emp.id_emprestimo);
			limparLinha(21,28 , 50);
		}
		fclose(Empres);
	    fclose(Livro);
	    fclose(Pessoa);
	}

	limparArea(51, 5, 60,10 );
}

void CadastroLivroAutor(void){
    TpLivroAutor LA;
    FILE *LivAut = fopen("LivroAutor.dat", "ab+");
    FILE *Livro = fopen("Livro.dat", "rb");
    FILE *Autor = fopen("Autor.dat", "rb");

    // VerificaÃ§Ã£o de abertura dos arquivos
    if(LivAut == NULL || Livro == NULL || Autor == NULL){
        textcolor(4);
        gotoxy(22,28); 
        printf("Erro ao abrir Arquivo!!!");
        textcolor(15);
        if (LivAut != NULL) fclose(LivAut);
        if (Livro != NULL) fclose(Livro);
        if (Autor != NULL) fclose(Autor);
        Sleep(1.5);
        limparLinha(21,28 , 50);
        
    }
	else {
    	// VerificaÃ§Ã£o de registros no arquivo de livros e autores
		fseek(Livro, 0, SEEK_END);
		fseek(Autor, 0, SEEK_END);
		if(ftell(Livro) == 0 || ftell(Autor) == 0){
		    textcolor(4);
		    gotoxy(28,28); 
		    printf("NÃ£o tem livros ou autores cadastrados para associar!!!");
		    fclose(Livro);
		    fclose(Autor);
		    textcolor(15);
		    Sleep(1.5);
		    limparLinha(24,28 , 50);
        
    	}
		else{
	    		// Cadastro de associaÃ§Ã£o livro e autor
		    limparArea(51, 5, 60, 10);
		    gotoxy(56,7); 
		    printf("Digite o id do Livro:");
		    gotoxy(56,7); 
		    scanf("%d", &LA.id_livro);
		
		    while(LA.id_livro != 0){
			    if(BuscaIDLivro(Livro, LA.id_livro) != -1){
					gotoxy(56,8); 
					printf("ID do Autor:");
					gotoxy(56,8); 
					scanf("%d", &LA.id_autor);
					if(BuscaIDAutor(Autor, LA.id_autor) != -1){
						LA.status = 1;
						fwrite(&LA, sizeof(TpLivroAutor), 1, LivAut);
						InsDiretaLivroAutor(LivAut);
						textcolor(10);
						gotoxy(22,28); 
						printf("Associação Livro-Autor cadastrada!!!");
						
						Sleep(1500);
						limparLinha(24,28 , 50);
					} else {
						textcolor(4);
						gotoxy(28,28); 
						printf("Autor nÃ£o encontrado");
						Sleep(1.5);
						limparLinha(24,28 , 50);
					}
			    } 
				else {
					textcolor(4);
					gotoxy(28,28); 
					printf("Livro nÃ£o encontrado !!!");
					Sleep(1.5);
					limparLinha(24,28 , 50);
				}
			
				limparArea(51, 5, 60, 10);
				textcolor(15);
				gotoxy(56,7); 
				printf("Digite o id do Livro: ");
				gotoxy(77,7); 
				scanf("%d", &LA.id_livro);
		    }
    
    
		}
	}
    fclose(LivAut);
    fclose(Livro);
    fclose(Autor);
    limparArea(51, 5, 60, 10);
}

//Buscas Exastivas
int BuscaIDLivro(FILE *Livro ,int id) {
   	TpLivro Liv;
	fseek(Livro,0,0);
	fread(&Liv, sizeof(TpLivro),1,Livro);
	while(!feof(Livro) && id != Liv.id_livro)
		fread(&Liv, sizeof(TpLivro), 1,Livro);
	if(id == Liv.id_livro)
		return ftell(Livro) - sizeof(TpLivro);
	else
		return -1;
}

int BuscaIDAutor(FILE *Autor, int id) {
   	TpAutor Aut;
	fseek(Autor,0,0);
	fread(&Aut, sizeof(TpAutor),1,Autor);
	while(!feof(Autor) && id != Aut.id_autor)
		fread(&Aut, sizeof(TpAutor), 1,Autor);
	if(id == Aut.id_autor)
		return ftell(Autor) - sizeof(TpAutor);
	else
		return -1;
}

int BuscaIDPessoa(FILE *Pessoa, int id) {
   	TpPessoa Pess;
	fseek(Pessoa,0,0);
	fread(&Pess, sizeof(TpPessoa),1,Pessoa);
	while(!feof(Pessoa) && id != Pess.id_pessoa)
		fread(&Pess, sizeof(TpPessoa), 1,Pessoa);
	if(id == Pess.id_pessoa)
		return ftell(Pessoa) - sizeof(TpPessoa);
	else
		return -1;
}

int BuscaIDEmprestimo(FILE *Empres, int id) {
   	TpEmprestimo Emp;
	fseek(Empres,0,0);
	fread(&Emp, sizeof(TpEmprestimo),1,Empres);
	while(!feof(Empres) && id != Emp.id_emprestimo)
		fread(&Emp, sizeof(TpEmprestimo), 1,Empres);
	if(id == Emp.id_emprestimo)
		return ftell(Empres) - sizeof(TpEmprestimo);
	else
		return -1;
}

int BuscaIDLivroAutor(FILE *LivAut, int id ) {
   	TpLivroAutor LA;
	fseek(LivAut,0,0);
	fread(&LA, sizeof(TpLivroAutor),1,LivAut);
	while(!feof(LivAut) && id != LA.id_livro)
		fread(&LA, sizeof(TpLivroAutor), 1,LivAut);
	if(id == LA.id_livro)
		return ftell(LivAut)- sizeof(TpLivroAutor);
	else
		return -1;
}

int BuscaIDLivroEmpres(FILE *Empres, int id ) {
   	TpEmprestimo Emp;
	fseek(Empres,0,0);
	fread(&Emp, sizeof(TpEmprestimo),1,Empres);
	while(!feof(Empres) && id != Emp.id_livro)
		fread(&Emp, sizeof(TpEmprestimo), 1,Empres);
	if(id == Emp.id_livro)
		return ftell(Empres)- sizeof(TpEmprestimo);
	else
		return -1;
}

//Exibir
void ExibirLivros(void) {
    TpLivro Liv;
    int linha = 6;
    FILE *Livro = fopen("Livro.dat", "rb");
    if (Livro == NULL) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir Arquivo!!!");
        fclose(Livro);
        Sleep(3000);
        limparLinha(21, 28, 50);
        textcolor(15);
    } 
	else {
        fread(&Liv, sizeof(TpLivro), 1, Livro);
        while (!feof(Livro)) {
            // Verifica se o livro nÃ£o foi excluÃ­do (status != 0)
            if (Liv.status != 0) {
				textcolor(linha / 2);
                gotoxy(52, linha );
                printf("ID: %d", Liv.id_livro);
                gotoxy(52, linha +1);
                printf("Titulo: %s", Liv.titulo);
                gotoxy(52, linha + 2);
                printf("Ano: %d", Liv.ano_publicacao);
                gotoxy(52, linha + 3);
				textcolor(5);
                printf("------------------------------------------------------------");
                Sleep(2000); // Ajuste o tempo conforme necessÃ¡rio
               	linha +=4;
            }
             if(linha == 26){
        		linha = 6;
        		limparArea(51, 5, 61, 20);
	        }
            fread(&Liv, sizeof(TpLivro), 1, Livro); 
        }
    }
    fclose(Livro);
    Sleep(1.7);
	limparArea(51, 5, 60, 20);
}
void ExibirAutores(void){
    TpAutor Aut;
    FILE *Autor = fopen("Autor.dat", "rb");
    
    if (Autor == NULL) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir arquivo de autores!!!");
        Sleep(1500);
        limparLinha(24, 28, 50);
        textcolor(15);
    }
    else {
        // Verificando se o arquivo estÃ¡ vazio
        fseek(Autor, 0, SEEK_END);
        if (ftell(Autor) == 0) {
            textcolor(4);
            gotoxy(22, 28);
            printf("Nenhum autor cadastrado!");
            Sleep(1500);
            limparLinha(24, 28, 50);
            fclose(Autor);
            textcolor(15);
            
        }
		else{
	        // Volta para o inÃ­cio do arquivo para comeÃ§ar a leitura
	        fseek(Autor, 0, SEEK_SET);
	        limparArea(51, 5, 60, 10);
	        textcolor(15);
	        int linha = 6; // Define onde a lista comeÃ§a na tela
			fread(&Aut, sizeof(TpAutor), 1, Autor);
	        while (!feof(Autor)) {
				textcolor(linha / 2);
	            if (Aut.status == 1) { // Se o autor estÃ¡ ativ
					textcolor(linha / 2);
	                gotoxy(52, linha+1);
	                printf("ID: %d", Aut.id_autor);
	                gotoxy(52, linha + 2);
	                printf("Nome: %s", Aut.nome);
	                gotoxy(52, linha + 3);
	                printf("Nacionalidade: %s", Aut.nacionalidade);
	                gotoxy(52, linha + 4 );
					textcolor(5);
	            	printf("---------------------------------------------------");
	            	linha +=5;
	            	Sleep(3000);
	            	if(linha == 26){
	            		linha = 6;
	            		limparArea(51, 5, 61, 20);
	            	}
	            	
	        	}
	        	fread(&Aut, sizeof(TpAutor), 1, Autor);
        	}	
			gotoxy(52, linha);printf("-----------------------Fim-------------------------");
			Sleep(1500);
		}
	}
	fclose(Autor);
	textcolor(15);
	limparArea(51, 5, 58, 20);
}
void ExibirPessoas(void) {
    TpPessoa Pess;
    FILE *Pessoa = fopen("pessoas.dat", "rb");

    if (Pessoa == NULL ) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir Arquivo!!!");
        fclose(Pessoa);
        Sleep(1.5);
        limparLinha(21, 28, 50);
        textcolor(15);
    } 
	else {
		int linha = 1;
		fread(&Pess, sizeof(TpPessoa), 1, Pessoa);
    	while(!feof(Pessoa)){
    		if(Pess.status != 0){
    			gotoxy(52, linha+5);
		        printf("ID: %d", Pess.id_pessoa);
		        gotoxy(52, linha+6);
		        printf("Nome: %s", Pess.nome);
		        gotoxy(52, linha+7);
		        printf("Telefone: %d", Pess.telefone);
				textcolor(5);
		        gotoxy(52,linha+8);printf("-------------------------Endereco-----------------------");
				textcolor(15);
		        gotoxy(52,linha+9);
		        printf("Rua: %s", Pess.Endere.rua);
		        gotoxy(52, linha+10);
		        printf("Bairro: %s", Pess.Endere.bairro);
		        gotoxy(52, linha+11);
		        printf("Numero: %d", Pess.Endere.numero);
		        gotoxy(52, linha+12);
		        printf("Cidade: %s", Pess.Endere.cidade);
		        gotoxy(52, linha+13);
		        printf("Cep: %d", Pess.Endere.cep);
		        gotoxy(52, linha+14);
		        printf("Estado: %s",Pess.Endere.estado);
		        gotoxy(52, linha+15);
		        printf("Pais: %s", Pess.Endere.pais);
				textcolor(5);
		       	gotoxy(52,linha+16);printf("--------------------------------------------------------");
    		}
	        Sleep(5000);
	        fread(&Pess, sizeof(TpPessoa), 1, Pessoa); 
	        limparArea(51, 5, 61, 20);
	    }
	        
	        
    }
    fclose(Pessoa);
    Sleep(1.7);
    limparArea(51, 5, 60, 20);
}
void ExibirEmprestimos(void) {
    TpEmprestimo Emp;
    TpLivro Liv;
    TpPessoa Pess;
    FILE *Empres = fopen("Emprestimos.dat", "rb");
    FILE *Livro = fopen("Livro.dat", "rb");
   	FILE * Pessoa = fopen("Pessoas.dat", "rb");

    if (Empres == NULL || Livro == NULL || Pessoa == NULL) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir Arquivo!!!");
		fclose(Empres);
		fclose(Livro);
		fclose(Pessoa);
        Sleep(3000);
		limparLinha(21, 28, 50);
        textcolor(15);
       
    }
	else{
		fseek(Empres, 0, 0);
		int linha = 6; 
		fread(&Emp, sizeof(TpEmprestimo), 1, Empres);
		textcolor(15);
		while (!feof(Empres)) {
			gotoxy(22,28);printf("ta entrando ");
			Sleep(2000);
			if(Emp.status ==1){
				int pos = BuscaBinariaLivro(Livro, Emp.id_livro);
				fseek(Livro, pos * sizeof(TpLivro), 0);
				fread(&Liv, sizeof(TpLivro), 1, Livro);
				pos = BuscaBinariaPessoa(Pessoa, Emp.id_pessoa);
				fseek(Pessoa, pos * sizeof(TpPessoa), 0);
				fread(&Pess, sizeof(TpPessoa),1,Pessoa);
				if (Pess.status == 1 && Liv.status == 1 ) {
					gotoxy(56, linha);
					printf("------------------------------------------");
					gotoxy(56, linha + 1);
					printf("ID EMPRESTIMO: %d", Emp.id_emprestimo);
					gotoxy(56, linha + 2);
					printf("LIVRO: %s", Liv.titulo);
					gotoxy(52, linha + 3);printf("ANO PUBLICADO: %d",Liv.ano_publicacao); 
					gotoxy(56, linha + 4);
					printf("PESSOA: %s", Pess.nome);
					gotoxy(52,linha + 5);
					printf("TELEFONE: %d", Pess.telefone);
					gotoxy(56, linha+ 6);
					printf("------------------------------------------");
					linha += 7; 
					Sleep(5000);
				}	
			}
			if(linha == 34){
				linha = 6;
				limparArea(51, 5, 58, 20);
			}
			fread(&Emp, sizeof(TpEmprestimo), 1, Empres); 
		}
	    
    }
    fclose(Empres);
    fclose(Livro);
    fclose(Pessoa);
    limparArea(51, 5, 58, 20);
}
void ExibirLivroAutor(void) {
    TpLivroAutor LA;
    TpLivro Liv;
    TpAutor Aut;
    int linha = 6;
    FILE *LivAut = fopen("LivroAutor.dat", "rb");
    FILE *Livro = fopen("Livro.dat", "rb");
    FILE *Autor = fopen("Autor.dat", "rb");

    if (LivAut == NULL || Livro == NULL || Autor == NULL) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir Arquivo!!!");
        fclose(LivAut);
        fclose(Livro);
        fclose(Autor);
        Sleep(3000);
        limparLinha(21, 28, 50);
        textcolor(15);
    } else {
        fread(&LA, sizeof(TpLivroAutor), 1, LivAut);
        while (!feof(LivAut)) {
            if (LA.status != 0) {
                fseek(Livro, (LA.id_livro - 1) * sizeof(TpLivro), 0);
                fread(&Liv, sizeof(TpLivro), 1, Livro);
                
                fseek(Autor, (LA.id_autor - 1) * sizeof(TpAutor), 0);
                fread(&Aut, sizeof(TpAutor), 1, Autor);

                gotoxy(52, linha);
                printf("ID Livro: %d", Liv.id_livro);
                gotoxy(52, linha + 1);
                printf("Titulo Livro: %s", Liv.titulo);
                gotoxy(52, linha + 2);
                printf("Ano: %d", Liv.ano_publicacao);
                gotoxy(52, linha + 3);
                printf("ID Autor: %d", Aut.id_autor);
                gotoxy(52, linha + 4);
                printf("Nome Autor: %s", Aut.nome);
                gotoxy(52, linha + 5);
                printf("-----------------------------------");
                Sleep(2000);
                linha += 6;
            }
            if (linha == 26) {
                linha = 6;
                limparArea(51, 5, 61, 20);
            }
            fread(&LA, sizeof(TpLivroAutor), 1, LivAut);
        }
		gotoxy(52,linha);printf("-----------------------FIM----------------------------");
    }

    fclose(LivAut);
    fclose(Livro);
    fclose(Autor);
    Sleep(1.7);
    limparArea(51, 5, 61, 20);
}

void ConsultarLivro(void){
	TpLivro Liv;
	TpAutor Aut;
	TpLivroAutor LA;
	FILE *Livro = fopen("Livro.dat","rb");
	FILE *LivAut = fopen("LivroAutor.dat","rb");
	FILE *Autor = fopen("Autor.dat","rb");
	if(Livro == NULL || Autor == NULL || LivAut == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir arquivo!!!");
		fclose(Livro);
		fclose(LivAut);
		fclose(Autor);
		Sleep(2000);
		limparLinha(21, 28, 50);
	}else{
		fseek(Livro,0,2);
		if(ftell(Livro) == 0){
			textcolor(4);
			gotoxy(22,28);
			printf("Nao tem nenhum livro cadastrado!!!");
			fclose(Livro);
			fclose(LivAut);
			fclose(Autor);
			Sleep(2000);
			limparLinha(21, 28, 50);
		}
		else {
			limparArea(51, 5, 61, 20);
			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7);printf("Digite o ID do livro:");
			gotoxy(74,7);scanf("%d", &Liv.id_livro);
			while(Liv.id_livro != 0){
				int pos = BuscaIDLivro(Livro,Liv.id_livro);
				if( pos != -1){
					fseek(Livro, pos, 0);
					fread(&Liv, sizeof(TpLivro),1, Livro);
					if(Liv.status == 1){
						limparArea(51, 5, 61, 20);
						textcolor(10);
						gotoxy(52,7);printf("----------------------Livro encontrado---------------------");
						textcolor(15);
						gotoxy(55,8);printf("Livro: %s",Liv.titulo);
						gotoxy(55,9);printf("Ano publicado: %d",Liv.ano_publicacao);
						textcolor(10);
						gotoxy(52,10);printf("----------------------------------------------------------");
						fseek(LivAut,0,0);
						fread(&LA, sizeof(TpLivroAutor),1,LivAut);
						while(!feof(LivAut)){
							if(Liv.id_livro == LA.id_livro){
								pos = BuscaBinariaAutor(Autor, LA.id_autor);
								fseek(Autor,pos * sizeof(TpAutor),0);
								fread(&Aut, sizeof(TpAutor),1,Autor);
								textcolor(10);
								gotoxy(52,11);printf("---------AUTOR FOI ENCONTRADO ASSOCIADO AO LIVRO-----------");
								gotoxy(52,12);printf("NOME: %s",Aut.nome);
								gotoxy(52,13);printf("Nacionalidade: %s",Aut.nacionalidade);
							}
							fread(&LA, sizeof(TpLivroAutor),1,LivAut);
						}
						Sleep(2000);
					}
				}else{
					textcolor(4);
					gotoxy(22,28);printf("Livro não encontrado!!!");
					Sleep(2000);
					limparLinha(21, 28, 50);
				}
				limparArea(51, 5, 61, 20);
				textcolor(5);
				gotoxy(52,6);printf("----------------------------------------------------------");
				gotoxy(52,8);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(55,7);printf("Digite o ID do livro:");
				gotoxy(77,7);scanf("%d", &Liv.id_livro);
			}
		}
	}
	fclose(Livro);
	fclose(LivAut);
	fclose(Autor);
	limparArea(51, 5, 60, 10);

}
void ConsultarAutor(){
	TpAutor Aut;
	FILE *Autor = fopen ("Autor.dat","rb");
	if(Autor == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir arquivo!!!");
		fclose(Autor);
		Sleep(2000);
		limparLinha(21,28 , 50);
	}
	else{
		
		fseek(Autor, 0, SEEK_END);
        if (ftell(Autor) == 0) {
            textcolor(4);
            gotoxy(22, 28);
            printf("Nenhum autor cadastrado!");
            fclose(Autor);
			Sleep(1500);
            limparLinha(24, 28, 50);
            textcolor(15);
        }
		else{
			limparArea(51, 5, 61, 20);
			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7);printf("Digite o id do Livro ou [0] SAIR:");
			gotoxy(85,7);scanf("%d", &Aut.id_autor);
			while(Aut.id_autor != 0){
				int pos = BuscaIDAutor(Autor, Aut.id_autor);
				if(pos != -1){
					fseek(Autor,pos,0);
					fread(&Aut, sizeof(TpAutor),1,Autor);
					if(Aut.status == 1){
						textcolor(10);
						gotoxy(52,9);printf("-------------------------------------------------------------");
						textcolor(15);
						gotoxy(52,10);printf("Nome: %s",Aut.nome);
						gotoxy(52,11);printf("Nacionalidade: %s",Aut.nacionalidade);
						textcolor(10);
						gotoxy(52,12);printf("-------------------------------------------------------------");
						Sleep(2000);
						//precisa fazer uma busca no livro Auotor e buscar todos os dados desse Autor e printar e sempre verificar se esta com status 1
					}
					
				}else{
					textcolor(4);
					printf("Autor nÃ£o encontrado!!!");
					Sleep(2000);
            		limparLinha(24, 28, 50);
				}
				limparArea(51, 5, 61, 20);
				textcolor(5);
				gotoxy(52,6);printf("----------------------------------------------------------");
				gotoxy(52,8);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(52,7);printf("Digite o id do Livro ou [0] SAIR:");
				gotoxy(85,7);scanf("%d", &Aut.id_autor);
			}

		}
	}
	fclose(Autor);
	Sleep(2000);
	limparArea(51, 5, 60, 20);

}
/// Fazer os consultar igual os de cima Usar outras busca para o consultar Fazer a busca Binaria para arquivo , mas primeiro Ã© preciso fazer entrando ordenado que ainda nÃ£o foi imprementado no cÃ³digo
 void ConsultarPessoa(){
	TpPessoa Pess;
	FILE *Pessoa = fopen("Pessoas.dat","rb");
	if(Pessoa == NULL){
		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo");
		fclose(Pessoa);
		Sleep(2000);
		limparLinha(24, 28, 50);
	}
	else{
		fseek(Pessoa,0,2);
		if(ftell(Pessoa)==0){
			textcolor(4);
			gotoxy(22,28);printf("Não tem Pessoas cadastradas para consultar!!!");
			Sleep(2000);
			limparLinha(24, 28, 50);
		}
		else{
			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7);printf("Digite o ID da pessoa:");
			gotoxy(74,7);scanf("%d", &Pess.id_pessoa);
			while(Pess.id_pessoa !=0){
				int pos = BuscaBinariaPessoa(Pessoa, Pess.id_pessoa);
				if(pos != -1){
					fseek(Pessoa,pos*sizeof(TpPessoa),0);
					fread(&Pess, sizeof(TpPessoa),1, Pessoa);
					if(Pess.status == 1){
						textcolor(5);
						gotoxy(52,9);printf("----------------------Pessoa encontrada--------------------");
						textcolor(15);
						gotoxy(52,10);printf("Nome: %s",Pess.nome);
						gotoxy(52,11);printf("Telefone: %d",Pess.telefone);
						textcolor(5);
						gotoxy(52,12);printf("--------------------------Endereço------------------------");
						textcolor(15);
						gotoxy(52,13);printf("Rua: %s", Pess.Endere.rua);
						gotoxy(52,14);printf("Numero: %d",Pess.Endere.numero);
						gotoxy(52,15);printf("Bairro: %s", Pess.Endere.bairro);
						gotoxy(52,16);printf("Cidade: %s", Pess.Endere.cidade);
						gotoxy(52,17);printf("Cep: %d", Pess.Endere.cep);
						gotoxy(52,18);printf("Estado: %s", Pess.Endere.estado);
						gotoxy(52,19);printf("Pais: %s", Pess.Endere.pais);
						textcolor(5);
						gotoxy(52,8);printf("----------------------------------------------------------");
						textcolor(15);
						//Fazer uma busca de livros se ele fez algum emprestimo cadastrados no nome dele 
						gotoxy(22,28);getch();
						limparArea(51, 5, 60, 20);
						
					}else{
						textcolor(4);
						gotoxy(22,28);printf("Pessoa não cadastrada!!!");
						Sleep(2000);
					}
					
				}
				else{
					textcolor(4);
					gotoxy(22,28);printf("Pessoa não cadastrada!!!");
					Sleep(2000);
				}
				textcolor(15);
				limparLinha(24, 28, 50);
				limparArea(51, 5, 61, 20);
				gotoxy(52,6);printf("----------------------------------------------------------");
				gotoxy(52,8);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(52,7);printf("Digite o ID da pessoa:");
				gotoxy(74,7);scanf("%d", &Pess.id_pessoa);
			}
		}
	}
	fclose(Pessoa);
	limparArea(51 ,5, 61, 20);
 }
 void ConsultarEmprestimo(){
	TpEmprestimo Emp;
	TpPessoa Pess;
	TpLivro Liv;
	FILE *Emprestimo = fopen("Emprestimo.dat","rb");
	FILE * Livro = fopen("Livro.dat", "rb");
	FILE * Pessoa = fopen("Pessoas.dat", "rb");
	if(Emprestimo == NULL || Pessoa == NULL || Livro == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir arquivo!!");
		fclose(Emprestimo);
		fclose(Livro);
		fclose(Pessoa);
		Sleep(2000);
		limparLinha(21, 28, 50);
	}else	{
		fseek(Emprestimo,0,2);
		if(ftell(Emprestimo)==0){
			textcolor(4);
			gotoxy(22,28);printf("Não há emprestimo cadastrado !!!");
			fclose(Emprestimo);
			fclose(Livro);
			fclose(Pessoa);
			Sleep(2000);
			limparLinha(21, 28, 50);
		}else{

			gotoxy(52,7);printf("Digite o ID do emrpestimo:");
			gotoxy(79,7);scanf("%d", &Emp.id_emprestimo);
			while(Emp.id_emprestimo != 0){
				int pos = BuscaIDEmprestimo(Emprestimo,Emp.id_emprestimo);
				if(pos != -1){
					fseek(Emprestimo,pos,0);
					fread(&Emp ,sizeof(TpEmprestimo),1,Emprestimo);
					pos = BuscaIDPessoa(Pessoa, Emp.id_pessoa);
					fseek(Pessoa,pos,0);
					fread(&Pess, sizeof(TpPessoa),1,Pessoa);
					pos = BuscaIDLivro(Livro,Emp.id_livro);
					fseek(Livro,pos,0);
					fread(&Liv, sizeof(TpLivro),1,Livro);

					if(Emp.status == 1){
						gotoxy(52,7);printf("------------------Emprestimo Encontrado------------------");
						gotoxy(52, 8); printf("Nome: %s", Pess.nome);
						gotoxy(52, 8); printf("Nome: %s", Liv.titulo);
					}else{
						textcolor(4);
						gotoxy(22,28);printf("Emprestimo não encontrado");
						Sleep(2000);
					}

				}else{
					textcolor(4);
					gotoxy(22,28);printf("Emprestimo não encontrado");
					Sleep(2000);
					
				}
				limparLinha(21, 28, 50);
				limparArea(51, 5, 60, 20);
				gotoxy(52,7);printf("Digite o ID do emrpestimo:");
				gotoxy(79,7);scanf("%d", &Emp.id_emprestimo);
				
			}
		}
	}
	fclose(Emprestimo);
	fclose(Livro);
	fclose(Pessoa);
 }
void ConsultarLivroAutor(){
	TpLivro Liv;
	TpAutor Aut;
	TpLivroAutor LA;
	FILE *LivAut = fopen("LivroAutor.dat","rb");
	FILE *Livro = fopen("Livro.dat","rb");
	FILE *Autor = fopen("Autor.dat","rb");

	if(Livro == NULL || Autor == NULL || LivAut == NULL){
		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo");
		fclose(Livro);
		fclose(LivAut);
		fclose(Autor);
		Sleep(2000);
		limparLinha(21, 28, 50);
	} else {
		fseek(Livro,0,2);
		if(ftell(Livro)==0){
			textcolor(4);
			gotoxy(22,28); printf("Não há livros cadastrados para consular!");
			Sleep(2000);
			limparLinha(21, 28, 50);
		} else {
			gotoxy(52,7); printf("Digite o ID do Livro:");
			gotoxy(74,7); scanf("%d", &Liv.id_livro);
			
			while(Liv.id_livro !=0){
				int pos = BuscaIDLivroAutor(LivAut, Liv.id_livro);
				if(pos != -1){
					fseek(LivAut,pos,0);
					fread(&LA, sizeof(TpLivroAutor),1,LivAut);
					pos = BuscaIDLivro(Livro, Liv.id_livro);
					fseek(Livro,pos,0);
					fread(&Liv, sizeof(TpLivro), 1, Livro);
					pos = BuscaIDAutor(Autor, LA.id_autor);
					fseek(Autor,pos,0);
					fread(&LA, sizeof(TpLivroAutor),1,Autor);
					if(Liv.status == 1){
						gotoxy(52,8);printf("----------------------Livro encontrado--------------------------");
						gotoxy(52,9);printf("Título: %s",Liv.titulo);
                        gotoxy(52, 10); printf("Nome autor: %s", Aut.nome );
						gotoxy(22,28); getch();
						limparArea(53, 5, 58, 20);
					} else {
						textcolor(4);
						gotoxy(22,28);printf("Livro não cadastrado!");
						Sleep(2000);
					}
					
				} else {
					textcolor(4);
					gotoxy(22,28);printf("Livro não cadastrado!");
					Sleep(2000);
				}
				textcolor(15);
				limparArea(53, 5, 58, 20);
				gotoxy(52,7); printf("Digite o ID do Livro: ");
				gotoxy(74,7); scanf("%d", &Liv.id_livro);
			}
		}
	}
	fclose(Livro);
	limparArea(53, 5, 58, 20);
 }
void AlterarLivro(){
	TpLivro Liv;
 	FILE * alteraLiv = fopen("Livro.dat","rb+");
 	if(alteraLiv==NULL){
 		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo!");
		fclose(alteraLiv);
		Sleep(2000);
		limparLinha(21, 28, 50);
 	} else {
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
		gotoxy(52,7); printf("ID do Livro:");
		gotoxy(64,7); scanf("%d", &Liv.id_livro);
 		while(Liv.id_livro !=0){
 			int pos = BuscaBinariaLivro(alteraLiv, Liv.id_livro);
 			if(pos==-1) {
				textcolor(4);
 				gotoxy(22,28);printf("Livro nao cadastrado\n");
				Sleep(2000);
				limparLinha(21, 28, 50);
			} else {
 				fseek(alteraLiv, pos *sizeof(TpLivro) , 0);
				fread(&Liv ,sizeof(TpLivro),1, alteraLiv);
				textcolor(5);
				gotoxy(52,9);printf("----------------------------------------------------------");
				textcolor(15);
			 	gotoxy(52,10); printf("ID: %d ", Liv.id_livro);
				gotoxy(52,11); printf("TITULO:%s",Liv.titulo);
				textcolor(5);
				gotoxy(52,12);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(52,13);printf("----------------------------------------------------------");
			 	gotoxy(52,14); printf("Deseja alterar?:");
				gotoxy(68,14);
			 	if(toupper(getche())=='S') {
					gotoxy(52,15); printf("Novo titulo:");
					fflush(stdin);
					Gotoxy(63,14);gets(Liv.titulo);
					fseek(alteraLiv, pos*sizeof(TpLivro),0);
					fwrite(&Liv, sizeof(TpLivro),1 , alteraLiv);
					textcolor(10);
					gotoxy(22,28); printf("Dados alterados!");
					fseek(alteraLiv, pos*sizeof(TpLivro),0);
					fread(&Liv, sizeof(TpLivro), 1, alteraLiv);
					textcolor(5);
					gotoxy(52,16);printf("----------------------------------------------------------");
					textcolor(15);
					gotoxy(52,17); printf("ID:%d ", Liv.id_livro);
					gotoxy(52,18); printf("TITULO:%s",Liv.titulo);
					textcolor(5);
					gotoxy(52,19);printf("----------------------------------------------------------");
					Sleep(2000);
			 	}else{
					textcolor(4);
					gotoxy(22,28);printf("Operacao finalizada!!!");
					Sleep(2000);
					limparLinha(21, 28, 50);
				}
 			}
			limparLinha(21, 28, 50);
			textcolor(15);
			limparArea(51, 5, 61, 20);
 			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7); printf("ID do Livro:");
			gotoxy(64,7); scanf("%d", &Liv.id_livro);
 		}
 		fclose(alteraLiv);
 	}
	limparArea(51, 5, 61, 20);
	fclose(alteraLiv);
}
void AlterarAutor(){
	int pos;
	TpAutor autor;
 	FILE * alteraAutor = fopen("Autor.dat","rb+");
	
 	if(alteraAutor==NULL){
 		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo!");
		fclose(alteraAutor);
		Sleep(2000);
		limparLinha(24, 28, 50);
 	} else {
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
 		gotoxy(52,7); printf("ID do Autor:");
 		gotoxy(64,7); scanf("%d", &autor.id_autor);
 		while(autor.id_autor !=0){
 			pos=BuscaBinariaAutor(alteraAutor, autor.id_autor);
 			if(pos==-1) {
				textcolor(4);
 				printf("Autor nao cadastrado\n");
				Sleep(2000);
				limparLinha(24, 28, 50);
 			} else {
 				fseek(alteraAutor, pos*sizeof(TpAutor), 0);
				fread(&autor ,sizeof(TpAutor),1, alteraAutor);

			 	textcolor(5);
				gotoxy(52,9);printf("----------------------------------------------------------");
				textcolor(15);
			 	gotoxy(52,10); printf("ID: %d ", autor.id_autor);
				gotoxy(52,11); printf("TITULO:%s",autor.nome);
				gotoxy(52,12); printf("NACIONALIDADE:%s",autor.nacionalidade);

				textcolor(5);
				gotoxy(52,13);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(52,15);printf("----------------------------------------------------------");
				textcolor(4);
			 	gotoxy(52,14); printf("Deseja alterar?");
				textcolor(15);
				gotoxy(68,14);
			 	if(toupper(getche())=='S') {
					gotoxy(52,16); printf("Novo nome:");
					fflush(stdin);
					gotoxy(63,16);gets(autor.nome);
					gotoxy(52,17); printf("Nacionalidade:");
					fflush(stdin);
					gotoxy(66,17);gets(autor.nacionalidade);
					fseek(alteraAutor, pos*sizeof(TpAutor),0);
					fwrite(&autor, sizeof(TpAutor),1 , alteraAutor);
					textcolor(10);
					gotoxy(22,28);printf("Dados alterados!");
					limparLinha(24, 28, 50);
					fseek(alteraAutor, pos*sizeof(TpAutor),0);
					fread(&autor, sizeof(TpAutor), 1, alteraAutor);
					textcolor(10);
					gotoxy(52,18);printf("----------------------------------------------------------");
					textcolor(15);
					gotoxy(52,19); printf("ID: %d ", autor.id_autor);
					gotoxy(52,20); printf("TITULO:%s",autor.nome);
					gotoxy(52,21); printf("NACIONALIDADE: %s",autor.nacionalidade);
					textcolor(10);
					gotoxy(52,22);printf("----------------------------------------------------------");
					
			 	}
 			}
			Sleep(2000);
			textcolor(15);
			limparArea(51, 5, 61, 20);
 			gotoxy(52,7); printf("ID do Autor:\n");
 			gotoxy(64,7); scanf("%d", &autor.id_autor);
 		}
 		fclose(alteraAutor);
 	}
	limparArea(51, 5, 61, 20);
	fclose(alteraAutor);
 	
}
void AlterarPessoa(){
	int pos;
	TpPessoa pessoa;
 	FILE * alteraPessoa = fopen("Pessoas.dat","rb+");
 	if(alteraPessoa==NULL){
 		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo!");
		fclose(alteraPessoa);
		Sleep(2000);
		limparLinha(24, 28, 50);
 	} else {
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
 		gotoxy(52,7); printf("ID da pessoa:");
 		gotoxy(65,7); scanf("%d", &pessoa.id_pessoa);
 		while(pessoa.id_pessoa !=0){
 			pos=BuscaBinariaPessoa(alteraPessoa, pessoa.id_pessoa);
 			if(pos==-1) {
				textcolor(4);
 				printf("Pessoa nao cadastrado\n");
				Sleep(2000);
				limparLinha(24, 28, 50);
 			} else {
 				fseek(alteraPessoa, pos*sizeof(TpPessoa), 0);
				fread(&pessoa ,sizeof(TpPessoa),1, alteraPessoa);
				gotoxy(52,9);printf("----------------------------------------------------------");
				textcolor(15);
			 	gotoxy(52,10); printf("ID: %d ", pessoa.id_pessoa);
				gotoxy(52,11); printf("NOME:%s",pessoa.nome);
				gotoxy(52,12); printf("TELEFONE: %d",pessoa.telefone);

				textcolor(5);
				gotoxy(52,13);printf("----------------------------------------------------------");
				textcolor(15);
				gotoxy(52,15);printf("----------------------------------------------------------");
				textcolor(4);
			 	gotoxy(52,14); printf("Deseja alterar?:");
				gotoxy(68,14);
			 	if(toupper(getche())=='S') {
					textcolor(15);
					gotoxy(52,16); printf("Novo nome:");
					fflush(stdin);
					gotoxy(62,16);gets(pessoa.nome);
					gotoxy(52,17);printf("Novo Telefone:");
					gotoxy(66,17);scanf("%d", &pessoa.telefone);
					fseek(alteraPessoa, pos*sizeof(TpPessoa),0);
					fwrite(&pessoa, sizeof(TpPessoa),1 , alteraPessoa);
					gotoxy(52,10); printf("Dados alterados!");
					fseek(alteraPessoa, pos*sizeof(TpPessoa),0);
					fread(&pessoa, sizeof(TpPessoa), 1, alteraPessoa);
					gotoxy(52,19);printf("----------------------------------------------------------");
					textcolor(15);
					gotoxy(52,20); printf("ID: %d ", pessoa.id_pessoa);
					gotoxy(52,21); printf("NOME:%s",pessoa.nome);
					gotoxy(52,22); printf("TELEFONE: %d",pessoa.telefone);
					textcolor(5);
					gotoxy(52,23);printf("----------------------------------------------------------");
					textcolor(15);
						
			 	}
 			}
			Sleep(2000);
			textcolor(15);
			limparArea(51, 5, 61, 20);
 			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7); printf("ID da pessoa:");
			gotoxy(65,7); scanf("%d", &pessoa.id_pessoa);
 		}
 		fclose(alteraPessoa);
 	}
	fclose(alteraPessoa);
 	getch();
}

void AlterarEmprestimo(){
	TpEmprestimo emprestimo;
	FILE *alteraEmprestimo = fopen("Emprestimo.dat","rb+");
	FILE *Livro = fopen("livros.dat","rb+");
 	if(alteraEmprestimo==NULL){
 		textcolor(4);
		gotoxy(22,28); printf("Erro ao abrir arquivo!");
		fclose(alteraEmprestimo);
		Sleep(2000);
		limparLinha(24, 28, 50);
 	} else {
 		gotoxy(52,7); printf("ID do Emprestimo:");
 		gotoxy(74,7); scanf("%d", &emprestimo.id_emprestimo);
 		while(emprestimo.id_emprestimo !=0){
 			 int pos=BuscaIDEmprestimo(alteraEmprestimo, emprestimo.id_emprestimo);
 			if(pos==-1) {
				textcolor(4);
 				printf("Emprestimo nao encontrado\n");
				Sleep(2000);
				limparLinha(24, 28, 50);
 			} else {
 				fseek(alteraEmprestimo, pos, 0);
				fread(&emprestimo ,sizeof(TpEmprestimo), 1, alteraEmprestimo);
			 	gotoxy(52,8); printf("ID: %d | ID_Livro: %d", emprestimo.id_emprestimo, emprestimo.id_emprestimo);
			 	gotoxy(52,7); printf("Deseja alterar?");
			 	if(toupper(getche())=='S') {
					gotoxy(52,9); printf("Novo ID Livro:  ");
					gotoxy(63,9);scanf("%d", &emprestimo.id_livro);
					if(BuscaIDLivro(Livro, emprestimo.id_livro)!= -1){
						fseek(alteraEmprestimo, pos,0);
						fwrite(&emprestimo, sizeof(TpEmprestimo),1 , alteraEmprestimo);
						gotoxy(52,10); printf("Dados alterados!");
						fseek(alteraEmprestimo, pos,0);
						fread(&emprestimo, sizeof(TpEmprestimo), 1, alteraEmprestimo);
						gotoxy(52,8); printf("ID: %d | ID_Livro: %d", emprestimo.id_pessoa , emprestimo.id_livro);
					}else{
						textcolor(4);
						printf("Livro não encontrado!!!!");
						limparLinha(24, 28, 50);
					}
			 	}
 			}
			Sleep(2000);
			textcolor(15);
			limparArea(51, 5, 61, 20);
 			gotoxy(52,7); printf("ID do Emprestimo:\n");
 			gotoxy(74,7); scanf("%d", &emprestimo.id_emprestimo);
 		}
 		fclose(alteraEmprestimo);
 	}
 	fclose(Livro);
	fclose(alteraEmprestimo);;
}

 void ExclusaoLogicaLivro(void){
 	TpLivro Liv;
	FILE *Livro = fopen("Livro.dat","rb+");
	if(Livro == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir arquivo!!!");
		fclose(Livro);
		Sleep(2000);
		limparLinha(21, 28, 50);
	}else {
		limparArea(51, 5, 61, 20);
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
		gotoxy(52,7);printf("Digite o ID que deseja excluir (0 para sair):");
		gotoxy(97,7);scanf("%d", &Liv.id_livro);
		while(Liv.id_livro !=0){
			int pos = BuscaBinariaLivro(Livro, Liv.id_livro);
			if(pos != -1){
				fseek(Livro,pos *sizeof(TpLivro), 0);
				fread(&Liv , sizeof(TpLivro),1,Livro);
				textcolor(10);
				gotoxy(52,9);printf("--------------------Livro encontrado-------------------------");
				textcolor(15);
				gotoxy(52,10);printf("ID: %d", Liv.id_livro);
				gotoxy(52,11);printf("TITULO: %s",Liv.titulo);
				gotoxy(52,12);printf("ANO DA PUBLICACAO: %d", Liv.ano_publicacao);
				textcolor(10);
				gotoxy(52,13);printf("-----------------------------------------------------------");
				textcolor(4);
				gotoxy(52,14);printf("Deseja excluir [S]/[N]?");
				textcolor(15);
				gotoxy(76,14);
				if(toupper(getch()) == 'S'){
					Liv.status = 0;
					textcolor(10);
					gotoxy(22,28);printf("Livro excluido");
					fseek(Livro, pos *sizeof(TpLivro),0);
					fwrite(&Liv, sizeof(TpLivro),1,Livro);
					Sleep(2000);
					limparLinha(21, 28, 50);
					limparArea(51, 5, 61, 20);
				}else{
					textcolor(4);
					gotoxy(22,28);printf("Operacao finalizada!!!");
					Sleep(2000);
					limparLinha(21, 28, 50);
				}

			}else{
				textcolor(4);
				gotoxy(22,28);printf("Livro não encontrado!!!");
				Sleep(2000);
				limparLinha(21, 28, 50);
			}
			limparArea(51, 5, 61, 20);
			textcolor(5);
			gotoxy(52,6);printf("----------------------------------------------------------");
			gotoxy(52,8);printf("----------------------------------------------------------");
			textcolor(15);
			gotoxy(52,7);printf("Digite o ID que deseja excluir (0 para sair):");
			gotoxy(97,7);scanf("%d", &Liv.id_livro);

		}
	}
	limparArea(51, 5, 61, 20);
	fclose(Livro);

}
void ExclusaoLogicaAutor(){
	TpAutor Aut;
	FILE *Autor =fopen("Autor.dat","rb+");
	if(Autor == NULL){
		textcolor(4);
		gotoxy(22,28);printf("Erro ao abrir arquivo!!!");
		fclose(Autor);
		Sleep(2000);
		limparLinha(21, 28, 50);
	}else{
		limparArea(51, 5, 61, 20);
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
		gotoxy(52,7);printf("Digite o ID que deseja excluir (0 para sair):");
		gotoxy(97,7);scanf("%d", &Aut.id_autor);
		while(Aut.id_autor !=0){
			int pos = BuscaBinariaAutor(Autor , Aut.id_autor);
			if(pos != -1){
				fseek(Autor,pos*sizeof(TpAutor), 0);
				fread(&Aut, sizeof(TpAutor),1,Autor);
				textcolor(10);
				if(Aut.status == 1 ){
					gotoxy(52,9);printf("--------------------Autor encontrado-------------------------");
					textcolor(15);
					gotoxy(52,10);printf("ID: %d", Aut.id_autor);
					gotoxy(52,11);printf("NOME: %s",Aut.nome);
					gotoxy(52,12);printf("NACIONALIDADE: %s", Aut.nacionalidade);
					textcolor(10);
					gotoxy(52,13);printf("-----------------------------------------------------------");
					textcolor(4);
					gotoxy(52,14);printf("Deseja excluir [S]/[N]?");
					textcolor(15);
					gotoxy(76,14);
					if(toupper(getch()) == 'S'){
						Aut.status = 0;
						textcolor(10);
						gotoxy(22,28);printf("Autor excluido");
						fseek(Autor, pos*sizeof(TpAutor),0);
						fwrite(&Aut, sizeof(TpAutor),1,Autor);
						exibirParabens(52,17);
						limparLinha(21, 28, 50);
						limparArea(51, 5, 61, 20);
					}else{
						textcolor(4);
						gotoxy(22,28);printf("Operacao finalizada!!!");
						Sleep(2000);
						limparLinha(21, 28, 50);
					}

				}else{
					textcolor(4);
					gotoxy(22,28);printf("Autor não encontrado!!!");
					Sleep(2000);
					limparLinha(21, 28, 50);
				}
				
				
			}else{
				textcolor(4);
				gotoxy(22,28);printf("Autor não encontrado!!!");
				Sleep(2000);
				limparLinha(21, 28, 50);
			}
			textcolor(15);
			limparArea(51, 5, 61, 20);
			gotoxy(52,7);printf("Digite o ID que deseja excluir (0 para sair):");
			gotoxy(97,7);scanf("%d", &Aut.id_autor);
			
		}
		fclose(Autor);

	}
	fclose(Autor);
	limparArea(51, 5, 61, 20);
	
}
void ExclusaoLogicaPessoa() {
    TpPessoa Pess;
    FILE *Pessoa = fopen("Pessoas.dat", "rb+");
    
    if (Pessoa == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir arquivo!!!");
        fclose(Pessoa);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
		limparArea(51, 5, 61, 20);
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
        gotoxy(52, 7); printf("Digite o ID que deseja excluir (0 para sair):");
        gotoxy(98, 7); scanf("%d", &Pess.id_pessoa);
        while (Pess.id_pessoa != 0) {
            int pos = BuscaBinariaPessoa(Pessoa, Pess.id_pessoa);
            if (pos != -1) {
                fseek(Pessoa, pos * sizeof(TpPessoa), SEEK_SET);
                fread(&Pess, sizeof(TpPessoa), 1, Pessoa);
                
                textcolor(10);
                gotoxy(52, 8); printf("--------------------Pessoa encontrada--------------------");
                textcolor(15);
                gotoxy(52, 10); printf("ID: %d", Pess.id_pessoa);
                gotoxy(52, 11); printf("Nome: %s", Pess.nome);
                gotoxy(52, 12); printf("Telefone: %d", Pess.telefone);
				textcolor(10);
                gotoxy(52, 13); printf("-------------------------------------------------------");
				textcolor(4);
                gotoxy(52, 14); printf("Deseja excluir [S]/[N]?");
                gotoxy(76, 14);
                
                if (toupper(getch()) == 'S') {
                    Pess.status = 0;
                    fseek(Pessoa, pos * sizeof(TpPessoa), 0);
                    fwrite(&Pess, sizeof(TpPessoa), 1, Pessoa);
                    textcolor(10);
                    gotoxy(22, 28); printf("Pessoa excluída!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                } else {
                    textcolor(4);
                    gotoxy(22, 28); printf("Operação finalizada!!!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                }
            } else {
                textcolor(4);
                gotoxy(22, 28); printf("Pessoa não encontrada!!!");
                Sleep(2000);
                limparLinha(21, 28, 50);
            }

            textcolor(15);
            limparArea(51, 5, 61, 20);
            gotoxy(52, 7); printf("Digite o ID que deseja excluir (0 para sair):");
            gotoxy(98, 7); scanf("%d", &Pess.id_pessoa);
        }
        fclose(Pessoa);
    }
	fclose(Pessoa);
    limparArea(51, 5, 61, 20);
}

void ExclusaoLogicaEmprestimo() {
    TpEmprestimo Emp;
    FILE *Empres = fopen("Emprestimos.dat", "rb+");

    if (Empres == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir arquivo!!!");
        fclose(Empres);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
        gotoxy(52, 7); printf("Digite o ID do empréstimo que deseja excluir (0 para sair):");
        gotoxy(94, 7); scanf("%d", &Emp.id_emprestimo);

        while (Emp.id_emprestimo != 0) {
            int pos = BuscaBinariaEmprestimo(Empres, Emp.id_emprestimo);
            if (pos != -1) {
                fseek(Empres, pos * sizeof(TpEmprestimo), SEEK_SET);
                fread(&Emp, sizeof(TpEmprestimo), 1, Empres);

                textcolor(10);
                gotoxy(52, 8); printf("------------------Empréstimo encontrado-----------------");
                textcolor(15);
                gotoxy(52, 10); printf("ID Empréstimo: %d", Emp.id_emprestimo);
                gotoxy(52, 11); printf("ID Livro: %d", Emp.id_livro);
                gotoxy(52, 12); printf("ID Pessoa: %d", Emp.id_pessoa);
                gotoxy(52, 13); printf("-------------------------------------------------------");
                gotoxy(52, 14); printf("Deseja excluir [S]/[N]?");
                gotoxy(76, 14);

                if (toupper(getch()) == 'S') {
                    Emp.status = 0;
                    fseek(Empres, pos * sizeof(TpEmprestimo), SEEK_SET);
                    fwrite(&Emp, sizeof(TpEmprestimo), 1, Empres);
                    textcolor(10);
                    gotoxy(22, 28); printf("Empréstimo excluído!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                } else {
                    textcolor(4);
                    gotoxy(22, 28); printf("Operação finalizada!!!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                }
            } else {
                textcolor(4);
                gotoxy(22, 28); printf("Empréstimo não encontrado!!!");
                Sleep(2000);
                limparLinha(21, 28, 50);
            }

            textcolor(15);
            limparArea(51, 5, 61, 20);
            gotoxy(52, 7); printf("Digite o ID do empréstimo que deseja excluir (0 para sair):");
            gotoxy(94, 7); scanf("%d", &Emp.id_emprestimo);
        }
        fclose(Empres);
    }
    limparArea(51, 5, 61, 20);
}

void ExclusaoLogicaLivroAutor() {
    TpLivroAutor LA;
    FILE *LivAut = fopen("LivroAutor.dat", "rb+");

    if (LivAut == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir arquivo!!!");
        fclose(LivAut);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
        gotoxy(52, 7); printf("Digite o ID da associação Livro-Autor que deseja excluir (0 para sair):");
        gotoxy(102, 7); scanf("%d", &LA.id_livro);

        while (LA.id_livro != 0) {
            int pos = BuscaIDLivroAutor(LivAut, LA.id_livro);
            if (pos != -1) {
                fseek(LivAut, pos * sizeof(TpLivroAutor), SEEK_SET);
                fread(&LA, sizeof(TpLivroAutor), 1, LivAut);
                textcolor(10);
                gotoxy(52, 8); printf("-----------Associação Livro-Autor encontrada-----------");
                textcolor(15);
                gotoxy(52, 10); printf("ID Livro: %d", LA.id_livro);
                gotoxy(52, 11); printf("ID Autor: %d", LA.id_autor);
                gotoxy(52, 13); printf("-------------------------------------------------------");
                gotoxy(52, 14); printf("Deseja excluir [S]/[N]?");
                gotoxy(76, 14);

                if (toupper(getch()) == 'S') {
                    LA.status = 0;
                    fseek(LivAut, pos * sizeof(TpLivroAutor), SEEK_SET);
                    fwrite(&LA, sizeof(TpLivroAutor), 1, LivAut);
                    textcolor(10);
                    gotoxy(22, 28); printf("Associação Livro-Autor excluída!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                } else {
                    textcolor(4);
                    gotoxy(22, 28); printf("Operação finalizada!!!");
                    Sleep(2000);
                    limparLinha(21, 28, 50);
                }
            } else {
                textcolor(4);
                gotoxy(22, 28); printf("Associação não encontrada!!!");
                Sleep(2000);
                limparLinha(21, 28, 50);
            }

            textcolor(15);
            limparArea(51, 5, 61, 20);
            gotoxy(52, 7); printf("Digite o ID da associação Livro-Autor que deseja excluir (0 para sair):");
            gotoxy(96, 7); scanf("%d", &LA.id_livro);
        }
        fclose(LivAut);
    }
    limparArea(51, 5, 61, 20);
}

void ExclusaoFisicaLivro() {
    TpLivro Livro;
	int Aux;
    FILE *ArquivoLivro = fopen("Livro.dat", "rb");
    if (ArquivoLivro == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir o arquivo!!!");
        fclose(ArquivoLivro);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
		textcolor(5);
		gotoxy(52,6);printf("----------------------------------------------------------");
		gotoxy(52,8);printf("----------------------------------------------------------");
		textcolor(15);
        gotoxy(52, 7); printf("Digite o ID do livro que deseja excluir (0 para sair):");
        gotoxy(106, 7); scanf("%d", &Aux);

        int pos = BuscaBinariaLivro(ArquivoLivro, Aux);
        if (pos == -1) {
            textcolor(4);
            gotoxy(22, 28); printf("Livro não encontrado!!!");
            Sleep(2000);
            limparLinha(21, 28, 50);
        } else {
			textcolor(10);
            gotoxy(52, 9); printf("-------------------Livro encontrado----------------------");
			gotoxy(52,12);printf("----------------------------------------------------------");
            fseek(ArquivoLivro, pos * sizeof(TpLivro), 0);
            fread(&Livro, sizeof(TpLivro), 1, ArquivoLivro);
			textcolor(15);
            gotoxy(52, 10); printf("ID Livro: %d", Livro.id_livro);
            gotoxy(52, 11); printf("Título: %s", Livro.titulo);
			textcolor(4);
            gotoxy(52, 14); printf("Deseja excluir? [S] ou [N]");
			textcolor(15);
            gotoxy(78, 14);
            if (toupper(getch()) == 'S') {
                FILE *Temp = fopen("Temp.dat", "wb");
                if (Temp == NULL) {
                    textcolor(4);
                    gotoxy(22, 28); printf("Erro ao criar arquivo temporário!");
					fclose(Temp);
                    Sleep(2000);
					limparLinha(21, 28, 50);
                } else {
                   	fseek(ArquivoLivro, 0, 0);
 					fread(&Livro, sizeof(TpLivro), 1, ArquivoLivro);
                    while (!feof(ArquivoLivro)) {
                        if (Livro.id_livro != Aux )
                            fwrite(&Livro, sizeof(TpLivro), 1, Temp);
						fread(&Livro, sizeof(TpLivro),1,ArquivoLivro);
                    }
                    fclose(ArquivoLivro);
                    fclose(Temp);
                    remove("Livro.dat");
                    rename("Temp.dat", "Livro.dat");
                    textcolor(10);
					exibirParabens(52,17);
                    gotoxy(22, 28); printf("Livro excluído com sucesso!");
                    Sleep(2000);
                }
            } else {
                textcolor(4);
                gotoxy(22, 28); printf("Operação cancelada!");
                Sleep(2000);
            }
        }
        limparLinha(21, 28, 50);
    }
	fclose(ArquivoLivro);
	limparArea(51, 5, 61, 20);
}

void ExclusaoFisicaAutor() {
    TpAutor Autor;
	int Aux;
    FILE *ArquivoAutor = fopen("Autor.dat", "rb");

    if (ArquivoAutor == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir o arquivo!!!");
        fclose(ArquivoAutor);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
        textcolor(5);
        gotoxy(52, 6); printf("----------------------------------------------------------");
        gotoxy(52, 8); printf("----------------------------------------------------------");
        textcolor(15);
        gotoxy(52, 7); printf("Digite o ID do autor que deseja excluir (0 para sair):");
        gotoxy(106, 7); scanf("%d", &Aux);
        int pos = BuscaBinariaAutor(ArquivoAutor, Aux);
        if (pos == -1) {
            textcolor(4);
            gotoxy(22, 28); printf("Autor não encontrado!!!");
            Sleep(2000);
            limparLinha(21, 28, 50);
        } else {
            textcolor(10);
            gotoxy(52, 9); printf("-------------------Autor encontrado-------------------");
			gotoxy(52,12);printf("----------------------------------------------------------");
            fseek(ArquivoAutor, pos * sizeof(TpAutor), 0);
            fread(&Autor, sizeof(TpAutor), 1, ArquivoAutor);
            textcolor(15);
            gotoxy(52, 10); printf("ID Autor: %d", Autor.id_autor);
            gotoxy(52, 11); printf("Nome: %s", Autor.nome);
            textcolor(4);
            gotoxy(52, 14); printf("Deseja excluir? [S] ou [N]");
            gotoxy(78, 14);

            if (toupper(getch()) == 'S') {
                FILE *Temp = fopen("Temp.dat", "wb");
                if (Temp == NULL) {
                    textcolor(4);
                    gotoxy(22, 28); printf("Erro ao criar arquivo temporário!");
                    fclose(Temp);
                    Sleep(2000);
                } else {
                    fseek(ArquivoAutor, 0, 0);
                    fread(&Autor, sizeof(TpAutor), 1, ArquivoAutor);
                    while (!feof(ArquivoAutor)) {
                        if (Autor.id_autor != Aux) {
                            fwrite(&Autor, sizeof(TpAutor), 1, Temp);
                        }
                        fread(&Autor, sizeof(TpAutor), 1, ArquivoAutor);
                    }
                    fclose(ArquivoAutor);
                    fclose(Temp);
                    remove("Autor.dat");
                    rename("Temp.dat", "Autor.dat");
					exibirParabens(52,17);
                    textcolor(10);
                    gotoxy(22, 28); printf("Autor excluído com sucesso!");
                    Sleep(2000);
                }
            } else {
                textcolor(4);
                gotoxy(22, 28); printf("Operação cancelada!");
                Sleep(2000);
            }
        }
        limparLinha(21, 28, 50);
		
    }
	fclose(ArquivoAutor);
	limparArea(51, 5, 61, 20);
}


void ExclusaoFisicaPessoa() {
    TpPessoa Pess;
	int Aux;
    FILE *ExcluiPessoa = fopen("Pessoas.dat", "rb");

    if (ExcluiPessoa == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir o arquivo!!!");
        fclose(ExcluiPessoa);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
		textcolor(5);
        gotoxy(52, 6); printf("----------------------------------------------------------");
        gotoxy(52, 8); printf("----------------------------------------------------------");
        textcolor(15);
        gotoxy(52, 7); printf("Digite o ID que deseja excluir (0 para sair):");
        gotoxy(97, 7); scanf("%d", &Aux);

        int pos = BuscaBinariaPessoa(ExcluiPessoa, Aux);
        if (pos == -1) {
            textcolor(4);
            gotoxy(22, 28); printf("Pessoa não encontrada!!!");
            Sleep(2000);
            limparLinha(21, 28, 50);
        } else {
            fseek(ExcluiPessoa, pos * sizeof(TpPessoa), 0);
            fread(&Pess, sizeof(TpPessoa), 1, ExcluiPessoa);
			if(Pess.status == 1){
				gotoxy(52,9);printf("----------------------Pessoa encontrada--------------------");
				textcolor(15);
				gotoxy(52,10);printf("Nome: %s",Pess.nome);
				gotoxy(52,11);printf("Telefone: %d",Pess.telefone);
				textcolor(5);
				gotoxy(52,12);printf("--------------------------Endereço------------------------");
				textcolor(15);
				gotoxy(52,13);printf("Rua: %s", Pess.Endere.rua);
				gotoxy(52,14);printf("Numero: %d",Pess.Endere.numero);
				gotoxy(52,15);printf("Bairro: %s", Pess.Endere.bairro);
				gotoxy(52,16);printf("Cidade: %s", Pess.Endere.cidade);
				gotoxy(52,17);printf("Cep: %d", Pess.Endere.cep);
				gotoxy(52,18);printf("Estado: %s", Pess.Endere.estado);
				gotoxy(52,19);printf("Pais: %s", Pess.Endere.pais);
				textcolor(5);
				gotoxy(52,8);printf("----------------------------------------------------------");
				textcolor(4);
				gotoxy(52, 20); printf("Deseja excluir? [S] ou [N]");
				gotoxy(79, 20);
				
				if (toupper(getch()) == 'S') {
					FILE *Temp = fopen("Temp.dat", "wb");
					if (Temp == NULL) {
						textcolor(4);
						gotoxy(22, 28); printf("Erro ao criar arquivo temporário!");
						fclose(Temp);
						Sleep(2000);
					} else {
						fseek(ExcluiPessoa, 0, SEEK_SET);
						fread(&Pess, sizeof(TpPessoa), 1, ExcluiPessoa);
						while (!feof(ExcluiPessoa)) {
							if (Pess.id_pessoa != Aux) {
								fwrite(&Pess, sizeof(TpPessoa), 1, Temp);
							}
							fread(&Pess, sizeof(TpPessoa), 1, ExcluiPessoa);
						}
						fclose(ExcluiPessoa);
						fclose(Temp);
						remove("Pessoas.dat");
						rename("Temp.dat", "Pessoas.dat");
						textcolor(10);
						gotoxy(22, 28); printf("Pessoa excluída com sucesso!");
						Sleep(2000);
					}
				}else {
					textcolor(10);
					gotoxy(22, 28); printf("Operação cancelada!");
					Sleep(2000);
           		 }
                
            } else{
				textcolor(4);
				gotoxy(22, 28); printf("Pessoa não encontrada!!!");
				Sleep(2000);
				limparLinha(21, 28, 50);
			}
        }
        limparLinha(21, 28, 50);
    }
	fclose(ExcluiPessoa);
	limparArea(51, 5, 61, 20);
}



void ExclusaoFisicaEmprestimo() {
    TpEmprestimo Emprestimo;
    FILE *ArquivoEmprestimo = fopen("Emprestimos.dat", "rb");

    if (ArquivoEmprestimo == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir o arquivo!!!");
        fclose(ArquivoEmprestimo);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
        gotoxy(52, 7); printf("Digite o ID do empréstimo que deseja excluir (0 para sair):");
        gotoxy(94, 7); scanf("%d", &Emprestimo.id_emprestimo);

        int pos = BuscaBinariaEmprestimo(ArquivoEmprestimo, Emprestimo.id_emprestimo);
        if (pos == -1) {
            textcolor(4);
            gotoxy(22, 28); printf("Empréstimo não encontrado!!!");
            Sleep(2000);
            limparLinha(21, 28, 50);
        } else {
            gotoxy(52, 8); printf("-------------------Empréstimo encontrado-------------------");
            fseek(ArquivoEmprestimo, pos * sizeof(TpEmprestimo), SEEK_SET);
            fread(&Emprestimo, sizeof(TpEmprestimo), 1, ArquivoEmprestimo);
            gotoxy(52, 10); printf("ID Empréstimo: %d | ID Livro: %d | ID Pessoa: %d", 
                                    Emprestimo.id_emprestimo, Emprestimo.id_livro, Emprestimo.id_pessoa);
            gotoxy(52, 14); printf("Deseja excluir? [S] ou [N]");
            gotoxy(76, 14);

            if (toupper(getch()) == 'S') {
                FILE *Temp = fopen("Temp.dat", "wb");
                if (Temp == NULL) {
                    textcolor(4);
                    gotoxy(22, 28); printf("Erro ao criar arquivo temporário!");
                    fclose(Temp);
                    Sleep(2000);
                } else {
                    fseek(ArquivoEmprestimo, 0, SEEK_SET);
                    fread(&Emprestimo, sizeof(TpEmprestimo), 1, ArquivoEmprestimo);
                    while (!feof(ArquivoEmprestimo)) {
                        if (Emprestimo.id_emprestimo != pos) {
                            fwrite(&Emprestimo, sizeof(TpEmprestimo), 1, Temp);
                        }
                        fread(&Emprestimo, sizeof(TpEmprestimo), 1, ArquivoEmprestimo);
                    }
                    fclose(ArquivoEmprestimo);
                    fclose(Temp);
                    remove("Emprestimos.dat");
                    rename("Temp.dat", "Emprestimos.dat");
                    gotoxy(22, 28); printf("Empréstimo excluído com sucesso!");
                    Sleep(2000);
                }
            } else {
                gotoxy(22, 28); printf("Operação cancelada!");
                Sleep(2000);
            }
        }
        limparLinha(21, 28, 50);
    }
	limparArea(51, 5, 61, 20);
}
void ExclusaoFisicaLivroAutor() {
    TpLivroAutor LivroAutor;
    FILE *ArquivoLivroAutor = fopen("LivroAutor.dat", "rb");

    if (ArquivoLivroAutor == NULL) {
        textcolor(4);
        gotoxy(22, 28); printf("Erro ao abrir o arquivo!!!");
        fclose(ArquivoLivroAutor);
        Sleep(2000);
        limparLinha(21, 28, 50);
    } else {
        gotoxy(52, 7); printf("Digite o ID do autor do livro que deseja excluir (0 para sair):");
        gotoxy(94, 7); scanf("%d", &LivroAutor.id_autor);

        int pos = BuscaIDLivroAutor(ArquivoLivroAutor, LivroAutor.id_autor);
        if (pos == -1) {
            textcolor(4);
            gotoxy(22, 28); printf("Autor do livro não encontrado!!!");
            Sleep(2000);
            limparLinha(21, 28, 50);
        } else {
            gotoxy(52, 8); printf("---------------Autor do Livro encontrado---------------");
            fseek(ArquivoLivroAutor, pos * sizeof(TpLivroAutor), SEEK_SET);
            fread(&LivroAutor, sizeof(TpLivroAutor), 1, ArquivoLivroAutor);
            gotoxy(52, 10); printf("ID Autor: %d | ID Livro: %d", LivroAutor.id_autor, LivroAutor.id_livro);
            gotoxy(52, 14); printf("Deseja excluir? [S] ou [N]");
            gotoxy(76, 14);

            if (toupper(getch()) == 'S') {
                FILE *Temp = fopen("Temp.dat", "wb");
                if (Temp == NULL) {
                    textcolor(4);
                    gotoxy(22, 28); printf("Erro ao criar arquivo temporário!");
                    fclose(Temp);
                    Sleep(2000);
                } else {
                    fseek(ArquivoLivroAutor, 0, SEEK_SET);
                    fread(&LivroAutor, sizeof(TpLivroAutor), 1, ArquivoLivroAutor);
                    while (!feof(ArquivoLivroAutor)) {
                        if (LivroAutor.id_autor != pos) {
                            fwrite(&LivroAutor, sizeof(TpLivroAutor), 1, Temp);
                        }
                        fread(&LivroAutor, sizeof(TpLivroAutor), 1, ArquivoLivroAutor);
                    }
                    fclose(ArquivoLivroAutor);
                    fclose(Temp);
                    remove("LivroAutor.dat");
                    rename("Temp.dat", "LivroAutor.dat");
                    gotoxy(22, 28); printf("Autor do livro excluído com sucesso!");
                    Sleep(2000);
                }
            } else {
                gotoxy(22, 28); printf("Operação cancelada!");
                Sleep(2000);
            }
        }
        limparLinha(21, 28, 50);
    }
	limparArea(51, 5, 61, 20);
}


int BuscaBinariaLivro(FILE *Livro , int id){
	TpLivro Liv;
	int inicio , meio, fim;
	fseek(Livro, 0, 2);
	fim = ftell(Livro) / sizeof(TpLivro) - 1;
	inicio = 0;
	meio = fim / 2 ;
	fseek(Livro , meio* sizeof(TpLivro) , 0);
	fread(&Liv, sizeof(TpLivro),1,Livro);

	while(inicio < fim && id != Liv.id_livro){
		if(Liv.id_livro < id)
			inicio = meio + 1;
		else
			fim = meio;

		meio = (inicio + fim ) / 2;
		fseek(Livro, meio *sizeof(TpLivro), 0);
		fread(&Liv, sizeof(TpLivro),1,Livro);
	}
	if(id == Liv.id_livro)
		return  meio ;
	else
		return -1 ;
}

int BuscaBinariaAutor(FILE *Autor, int id) {
    TpAutor Aut;
    int inicio, meio, fim;

    fseek(Autor, 0, SEEK_END);
    fim = ftell(Autor) / sizeof(TpAutor) - 1;
    inicio = 0;
    meio = (inicio + fim) / 2;
    
    fseek(Autor, meio * sizeof(TpAutor), SEEK_SET);
    fread(&Aut, sizeof(TpAutor), 1, Autor);

    while (inicio < fim && id != Aut.id_autor) {
        if (Aut.id_autor < id)
            inicio = meio + 1;
        else
            fim = meio;

        meio = (inicio + fim) / 2;
        fseek(Autor, meio * sizeof(TpAutor), SEEK_SET);
        fread(&Aut, sizeof(TpAutor), 1, Autor);
    }

    if (id == Aut.id_autor)
        return meio;
    else
        return -1;
}

int BuscaBinariaPessoa(FILE *Pessoa, int id) {
    TpPessoa Pes;
    int inicio, meio, fim;

    fseek(Pessoa, 0, SEEK_END);
    fim = ftell(Pessoa) / sizeof(TpPessoa) - 1;
    inicio = 0;
    meio = (inicio + fim) / 2;

    fseek(Pessoa, meio * sizeof(TpPessoa), SEEK_SET);
    fread(&Pes, sizeof(TpPessoa), 1, Pessoa);

    while (inicio < fim && id != Pes.id_pessoa) {
        if (Pes.id_pessoa < id)
            inicio = meio + 1;
        else
            fim = meio;

        meio = (inicio + fim) / 2;
        fseek(Pessoa, meio * sizeof(TpPessoa), SEEK_SET);
        fread(&Pes, sizeof(TpPessoa), 1, Pessoa);
    }

    if (id == Pes.id_pessoa)
        return meio;
    else
        return -1;
}

int BuscaBinariaEmprestimo(FILE *Emprestimos, int id) {
    TpEmprestimo Emp;
    int inicio, meio, fim;

    fseek(Emprestimos, 0, SEEK_END);
    fim = ftell(Emprestimos) / sizeof(TpEmprestimo) - 1;
    inicio = 0;
    meio = (inicio + fim) / 2;

    fseek(Emprestimos, meio * sizeof(TpEmprestimo), SEEK_SET);
    fread(&Emp, sizeof(TpEmprestimo), 1, Emprestimos);

    while (inicio < fim && id != Emp.id_emprestimo) {
        if (Emp.id_emprestimo < id)
            inicio = meio + 1;
        else
            fim = meio;

        meio = (inicio + fim) / 2;
        fseek(Emprestimos, meio * sizeof(TpEmprestimo), SEEK_SET);
        fread(&Emp, sizeof(TpEmprestimo), 1, Emprestimos);
    }

    if (id == Emp.id_emprestimo)
        return meio;
    else
        return -1;
}

// // Fazer as oderanaÃ§Ãµes
void InsDiretaLivro(FILE *Livro) {
    TpLivro Liv1, Liv2;
    long p;

    // Obter a posição do último registro inserido
    fseek(Livro, 0, 2);
    p = ftell(Livro) - sizeof(TpLivro);

    // Iterar para ordenar os registros
    while (p > 0) {
        // Ler o registro atual
        fseek(Livro, p, 0);
        fread(&Liv1, sizeof(TpLivro), 1, Livro);

        // Ler o registro anterior
        fseek(Livro, p - sizeof(TpLivro), 0);
        fread(&Liv2, sizeof(TpLivro), 1, Livro);
        // Comparar os IDs
        if(Liv1.id_livro < Liv2.id_livro){
            // Trocar os registros no arquivo
            fseek(Livro, p, 0);
            fwrite(&Liv2, sizeof(TpLivro), 1, Livro);

            fseek(Livro, p - sizeof(TpLivro), 0);
            fwrite(&Liv1, sizeof(TpLivro), 1, Livro);

            // Atualizar a posição para continuar
            p -= sizeof(TpLivro);
        }
		else{
			p -= sizeof(TpLivro);
		} 

    }
}
void InsDiretaAutor(FILE *Autor){
	TpAutor Aut1, Aut2;
	if(Autor == NULL){
		textcolor(4);
		gotoxy(22,30);printf("Erro ao abrir Arquivo!!!");
		fclose(Autor);
		Sleep(1.5);
		limparLinha(24,28 , 50);
		textcolor(15);
	}else{
		fseek(Autor,0,2);
		
		int p = ftell(Autor) - sizeof(TpAutor);

		while(p > 0){
			fseek(Autor,p,0);
			fread(&Aut1, sizeof(TpAutor),1, Autor);

			fseek(Autor, p - sizeof(TpAutor), 0 );
			fread(&Aut2, sizeof(TpAutor),1, Autor);

			if(Aut1.id_autor < Aut2.id_autor) {
				fseek(Autor, p , 0);
				fwrite(&Aut2, sizeof(TpAutor),1,Autor);

				fseek(Autor,p - sizeof(TpAutor), 0);
				fwrite(&Aut1, sizeof(TpAutor),1,Autor);

				p -= sizeof(TpAutor);
			}else{
				p -=sizeof(TpAutor);
			}

		}
	}
}
void InsDiretaPessoa(FILE *Pessoa) {
    TpPessoa Pess1, Pess2;
    long p;

    fseek(Pessoa, 0, 2);
    p = ftell(Pessoa) - sizeof(TpPessoa);

    while (p > 0) {
        fseek(Pessoa, p, 0);
        fread(&Pess1, sizeof(TpPessoa), 1, Pessoa);

        fseek(Pessoa, p - sizeof(TpPessoa), 0);
        fread(&Pess2, sizeof(TpPessoa), 1, Pessoa);

        if (Pess1.id_pessoa < Pess2.id_pessoa) {
            fseek(Pessoa, p, 0);
            fwrite(&Pess2, sizeof(TpPessoa), 1, Pessoa);

            fseek(Pessoa, p - sizeof(TpPessoa), 0);
            fwrite(&Pess1, sizeof(TpPessoa), 1, Pessoa);

            p -= sizeof(TpPessoa);
        } else {
            p -= sizeof(TpPessoa);
        }
    }
}
void InsDiretaEmprestimo(FILE *Empres) {
    TpEmprestimo Emp1, Emp2;
    long p;

    fseek(Empres, 0, 2);
    p = ftell(Empres) - sizeof(TpEmprestimo);

    while (p > 0) {
        fseek(Empres, p, 0);
        fread(&Emp1, sizeof(TpEmprestimo), 1, Empres);

        fseek(Empres, p - sizeof(TpEmprestimo), 0);
        fread(&Emp2, sizeof(TpEmprestimo), 1, Empres);

        if (Emp1.id_emprestimo < Emp2.id_emprestimo) {
            fseek(Empres, p, 0);
            fwrite(&Emp2, sizeof(TpEmprestimo), 1, Empres);

            fseek(Empres, p - sizeof(TpEmprestimo), 0);
            fwrite(&Emp1, sizeof(TpEmprestimo), 1, Empres);

            p -= sizeof(TpEmprestimo);
        } else {
            p -= sizeof(TpEmprestimo);
        }
    }
}
void InsDiretaLivroAutor(FILE *LivAut) {
    TpLivroAutor LA1, LA2;
    long p;

    fseek(LivAut, 0, 2);
    p = ftell(LivAut) - sizeof(TpLivroAutor);

    while (p > 0) {
        fseek(LivAut, p, 0);
        fread(&LA1, sizeof(TpLivroAutor), 1, LivAut);

        fseek(LivAut, p - sizeof(TpLivroAutor), 0);
        fread(&LA2, sizeof(TpLivroAutor), 1, LivAut);

        if (LA1.id_livro < LA2.id_livro) {
            fseek(LivAut, p, 0);
            fwrite(&LA2, sizeof(TpLivroAutor), 1, LivAut);

            fseek(LivAut, p - sizeof(TpLivroAutor), 0);
            fwrite(&LA1, sizeof(TpLivroAutor), 1, LivAut);

            p -= sizeof(TpLivroAutor);
        } else {
            p -= sizeof(TpLivroAutor);
        }
    }
}

 // Relatorio 
 void relatorioEmprestimoPessoa(void) {
    int pos, localizou, linha;
    TpPessoa Pess;
    TpEmprestimo Emp;
    TpLivro Liv;

    FILE *pessoa = fopen("Pessoas.dat", "rb");
    FILE *emprestimo = fopen("Emprestimo.dat", "rb");
    FILE *livro = fopen("Livro.dat", "rb");

    fseek(pessoa, 0, 2);
    if (ftell(pessoa) / sizeof(TpPessoa) == 0) {
        textcolor(4);
        printf("Não há cadastrados!");
        Sleep(2000);
        limparLinha(24, 28, 50);
    } else {
        gotoxy(52, 7);
        printf("ID da pessoa: ");
        gotoxy(63, 7);
        scanf("%d", &Pess.id_pessoa);

        while (Pess.id_pessoa != 0) {
            pos = BuscaBinariaPessoa(pessoa, Pess.id_pessoa);

            if (pos == -1) {
                textcolor(4);
                printf("Pessoa nao cadastrada");
                Sleep(2000);
                limparLinha(24, 28, 50);
            } else {
                fseek(pessoa, pos * sizeof(TpPessoa), SEEK_SET);
                fread(&Pess, sizeof(TpPessoa), 1, pessoa);

                gotoxy(52, 8);
                printf("Dados do Emprestimo");
                gotoxy(52, 9);
                printf("ID: %d", Pess.id_pessoa);
                gotoxy(52, 10);
                printf("Nome: %s", Pess.nome);

                localizou = 0;
                fseek(emprestimo, 0, SEEK_SET);
                while (fread(&Emp, sizeof(TpEmprestimo), 1, emprestimo)) {
                    if (Emp.id_pessoa == Pess.id_pessoa) {
                        localizou = 1;
                        fseek(livro, 0, SEEK_SET);
                        while (fread(&Liv, sizeof(TpLivro), 1, livro)) {
                            if (Liv.id_livro == Emp.id_livro) {
                                linha = 12;
                                gotoxy(52, linha + 1);
                                printf("ID Emprestimo: %d", Emp.id_emprestimo);
                                gotoxy(52, linha + 2);
                                printf("Livro: %s", Liv.titulo);
                                gotoxy(52, linha + 3);
                                printf("Ano: %d", Liv.ano_publicacao);
                                Sleep(3000);
                                limparArea(51, 5, 61, 20);
                            }
                        }
                    }
                }

                if (localizou != 1) {
                    textcolor(4);
                    gotoxy(22, 28);
                    printf("Nenhum emprestimo registrado!");
                    Sleep(1500);
                }
            }
            getch();
            limparLinha(24, 28, 50);
            printf("ID da pessoa: ");
            scanf("%d", &Pess.id_pessoa);
        }
    }
    fclose(pessoa);
    fclose(emprestimo);
    fclose(livro);
    limparArea(51, 5, 61, 20);
}



void exibeLivroAutor(void) {
    TpAutor Aut;
    TpLivro Liv;
    TpLivroAutor LivAut;
    int auxId, pos;

    FILE *autor = fopen("Autor.dat", "rb");
    FILE *livro = fopen("Livro.dat", "rb");
    FILE *livroAutor = fopen("LivroAutor.dat", "rb");

    if (autor == NULL || livro == NULL || livroAutor == NULL) {
        textcolor(4);
        gotoxy(22, 28);
        printf("Erro ao abrir o arquivo\n");
        if (autor) fclose(autor);
        if (livro) fclose(livro);
        if (livroAutor) fclose(livroAutor);
        Sleep(2000);
        limparLinha(24, 28, 50);
    } else {
        fseek(livro, 0, SEEK_END);
        if (ftell(livro) == 0) {
            textcolor(4);
            gotoxy(22, 28);
            printf("Não há livros cadastrados para consultar!");
            Sleep(2000);
            limparLinha(24, 28, 50);
        } else {
            gotoxy(52, 7);
            printf("Digite o ID do Autor: ");
            gotoxy(74, 7);
            scanf("%d", &auxId);

            while (auxId != 0) {
                fseek(livroAutor, 0, SEEK_SET);
                fread(&LivAut, sizeof(TpLivroAutor), 1, livroAutor);

                while (!feof(livroAutor)) {
                    if (auxId == LivAut.id_autor) {
                        pos = BuscaBinariaLivro(livro, LivAut.id_livro);
                        if (pos != -1) {
                            fseek(livro, pos * sizeof(TpLivro), SEEK_SET);
                            fread(&Liv, sizeof(TpLivro), 1, livro);

                            pos = BuscaBinariaAutor(autor, LivAut.id_autor);
                            if (pos != -1) {
                                fseek(autor, pos * sizeof(TpAutor), SEEK_SET);
                                fread(&Aut, sizeof(TpAutor), 1, autor);

                                gotoxy(52, 8);
                                printf("ID Livro: %d", Liv.id_livro);
                                gotoxy(52, 9);
                                printf("Titulo Livro: %s", Liv.titulo);
                                gotoxy(52, 10);
                                printf("Ano: %d", Liv.ano_publicacao);
                                gotoxy(52, 11);
                                printf("ID Autor: %d", Aut.id_autor);
                                gotoxy(52, 12);
                                printf("Nome Autor: %s", Aut.nome);
                                gotoxy(52, 13);
                                printf("-----------------------------------");

                                Sleep(2000);
                                limparLinha(8, 13, 50); // Limpar a área de exibição
                            }
                        }
                    }
                    fread(&LivAut, sizeof(TpLivroAutor), 1, livroAutor);
                }

                textcolor(15);
                gotoxy(52, 7);
                printf("Digite o ID do Autor (ou [0] para sair): ");
                gotoxy(74, 7);
                scanf("%d", &auxId);
            }
        }
    }

    fclose(autor);
    fclose(livro);
    fclose(livroAutor);
}

void OrdenaNacionalidade (FILE * autor)
{
 TpAutor aut1, aut2;
 int Qtd, a, b;
 fseek(autor,0,2);
 Qtd=ftell(autor) / sizeof(TpAutor);
 for(a=0;a<Qtd-1;a++)
  for(b=a+1;b<Qtd;b++)
  {
   fseek(autor,a*sizeof(TpAutor),0);
   fread(&aut1,sizeof(TpAutor),1,autor);
   fseek(autor,b*sizeof(TpAutor),0);
   fread(&aut2,sizeof(TpAutor),1,autor);
   if(stricmp(aut1.nacionalidade,aut2.nacionalidade)>0){
    fseek(autor,a*sizeof(TpAutor),0);
    fwrite(&aut2,sizeof(TpAutor),1,autor);
    fseek(autor,b*sizeof(TpAutor),0);
    fwrite(&aut1,sizeof(TpAutor),1,autor);
   }
  }
}

// void RelatorioLetraAutor(void) {
//     int achou;
//     char aux;
//     TpAutor Aut;

//     FILE *autor = fopen("Autor.dat", "rb+");

//     if(autor == NULL) {
//         textcolor(4);
//         gotoxy(37, 13);
//         printf("Erro ao abrir o arquivo de autores!\n");
//     }else{
// 	limparArea(51, 5, 61, 20);
//     textcolor(2);
//     gotoxy(40, 10);
//     printf("RELATORIO AUTORES");
//     textcolor(15);
    
//     fseek(autor, 0, SEEK_END);
//     if (ftell(autor) / sizeof(TpAutor) == 0) {
//         gotoxy(37, 13);
//         textcolor(4);
//         printf("Nao ha cadastro de autores!!");
//         getch();
//         textcolor(15);
//     } else {
//         // OrdenaNacionalidade(autor); // Chame a função para ordenar autores, se necessário
//         gotoxy(37, 12);
//         printf("Digite a letra inicial do autor: ");
//         scanf(" %c", &aux);
        
//         while (aux != '0') {
//             achou = 0;
//             int y = 14;
//             fseek(autor, 0, SEEK_SET);
//             fread(&Aut, sizeof(TpAutor), 1, autor);

//             while (!feof(autor)) {
//                 if (toupper(aux) == toupper(Aut.nome[0])) {
//                     achou = 1;
//                     gotoxy(37, y);
//                     printf("Autor: %s | Nacionalidade: %s", Aut.nome, Aut.nacionalidade);
//                     y++;
//                 }
//                 fread(&Aut, sizeof(TpAutor), 1, autor);
//             }

//             if (achou != 1) {
//                 gotoxy(37, 15);
//                 textcolor(4);
//                 printf("Autor nao cadastrado!!");
//                 textcolor(15);
//             }
            
//             getch();
//             limparLinha(24, 28, 50);
//             gotoxy(52, 12);
//             printf("Digite a letra inicial do autor: ");
//             scanf(" %c", &aux);
//         }
// 	}

//     fclose(autor);
// }

// void GerarRelatorioEmprestimos(void){
//     TpPessoa Pess;
//     TpEmprestimo Emp;
//     TpLivro LivroReg;

//     FILE *Pessoa = fopen("Pessoas.dat", "rb");
//     FILE *Empres = fopen("Emprestimos.dat", "rb");
//     FILE *Livro = fopen("Livros.dat", "rb");

//     if (Pessoa == NULL || Empres == NULL || Livro == NULL) {
//         textcolor(4);
//         gotoxy(22, 28);
//         printf("Erro ao abrir o arquivo\n");
//         Sleep(2000);
//         limparLinha(24, 28, 50);
//         if (Pessoa) fclose(Pessoa);
//         if (Empres) fclose(Empres);
//         if (Livro) fclose(Livro);
        
//     }

//     Limpararea(51, 5, 61, 20);
//     gotoxy(52, 7);
//     printf("Relatório de Empréstimos por Pessoa:\n");

//     while (fread(&Pess, sizeof(TpPessoa), 1, Pessoa) == 1) {
//         if (Pess.status == 1) {  // Apenas pessoas ativas
//             gotoxy(52, 9);
//             printf("ID Pessoa: %d", Pess.id_pessoa);
//             gotoxy(52, 10);
//             printf("Nome: %s", Pess.nome);
//             gotoxy(52, 11);
//             printf("Empréstimos:");

//             int encontrouEmprestimos = 0;
//             fseek(Empres, 0, SEEK_SET);

//             while (fread(&Emp, sizeof(TpEmprestimo), 1, Empres) == 1) {
//                 if (Emp.status == 1 && Emp.id_pessoa == Pess.id_pessoa) {
//                     encontrouEmprestimos = 1;

//                     fseek(Livro, 0, SEEK_SET);
//                     while (fread(&LivroReg, sizeof(TpLivro), 1, Livro) == 1) {
//                         if (LivroReg.id_livro == Emp.id_livro) {
//                             gotoxy(52, 12);
//                             printf("ID Empréstimo: %d", Emp.id_emprestimo);
//                             gotoxy(52, 13);
//                             printf("Livro: %s", LivroReg.titulo);
//                             gotoxy(52, 14);
//                             printf("Ano Publicação: %d", LivroReg.ano_publicacao);
                            
//                         }
//                     }
//                 }
//             }

//             if (!encontrouEmprestimos) {
//                 gotoxy(52, 15);
//                 textcolor(4);
//                 printf("Nenhum empréstimo registrado!");
//                 textcolor(15);
//             }

//             Sleep(2000);
//            limparArea(51, 5, 61, 20); /
//         }
//     }

//     fclose(Pessoa);
//     fclose(Empres);
//     fclose(Livro);
// }

// void relatorioCompleto(void) {
//     TpPessoa Pess;
//     TpEmprestimo Emp;
//     TpLivro Liv;

//     FILE *pessoa = fopen("Pessoas.dat", "rb");
//     FILE *emprestimo = fopen("Emprestimo.dat", "rb");
//     FILE *livro = fopen("Livro.dat", "rb");

//     if (!pessoa || !emprestimo || !livro){
//         textcolor(4);
// 	 	printf("Erro ao abrir o arquivo\n");
// 		fclose(excluiEmprestimo);
// 		Sleep(2000);
// 		limparLinha(24, 28, 50);
// 	 	fclose(excluiEmprestimo);
// 	} else {
// 		printf("RELATÓRIO COMPLETO DE DADOS\n");

//     	fseek(pessoa, 0, SEEK_SET);
//     	while (fread(&Pess, sizeof(TpPessoa), 1, pessoa)) {
//         printf("ID Pessoa: %d\n", Pess.id_pessoa);
//         printf("Nome: %s\n", Pess.nome);

//         int emprestimosEncontrados = 0;
//         fseek(emprestimo, 0, SEEK_SET);
//         while (fread(&Emp, sizeof(TpEmprestimo), 1, emprestimo)) {
//             if (Emp.id_pessoa == Pess.id_pessoa) {
//                 emprestimosEncontrados = 1;
//                 printf("Empréstimo ID: %d", Emp.id_emprestimo);
//                 printf("Data do Empréstimo: %s", Emp.data_emprestimo);

//                 fseek(livro, 0, SEEK_SET);
//                 while (fread(&Liv, sizeof(TpLivro), 1, livro)) {
//                     if (Liv.id_livro == Emp.id_livro) {
//                         printf("Livro ID: %d", Liv.id_livro);
//                         printf("Título: %s", Liv.titulo);
//                         printf("Autor: %s", Liv.autor);
//                     }
//                 }
//             }
//         }

//         if (!emprestimosEncontrados) {
//             textcolor(4);
// 			printf("Nenhum empr´stimo encontrado");
// 			fclose(excluiEmprestimo);
// 			Sleep(2000);
// 			limparLinha(24, 28, 50);
// 			fclose(excluiEmprestimo);
//         }
//     }

//     fclose(pessoa);
//     fclose(emprestimo);
//     fclose(livro);
// 	}

    
// }
