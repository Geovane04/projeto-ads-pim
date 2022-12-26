#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h> // Biblioteca necessária para o uso de Strings em C
#include<math.h>

int menu;

int telalogin(){
	// Declaração das variáveis que receberam o login e a senha do usuário.a
	char user[20], pass[20], linha[100], *result;
	char *login, *senha;
	FILE *arq;
	
	// Recebendo os dados de acesso do usuário (login e senha)
	printf("Digite o nome do usuario: ");
	gets(user);
	printf("Digite a senha do usuario: ");
	gets(pass);
	// Recebendo no ponteiro arq o local onde os registros de logins e senhas autorizados estão armazenados
	arq = fopen("arquivos/logins.txt", "rt");
	// Verificando se deu erro na abertua do arquivo (retorna NULL se der erro na leitura)
	if (arq == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	}
	// Correndo todas as linhas do arquivo até que chegue ao final
	while(!feof(arq)){
		//fgets(nome do vetor onde salvaremos a String lida, a quantidade de caracteres a ser lidos, de onde será lido)
		fgets(linha, 41, arq);
		
		//a função strtok() é utilizanda para separar Strings
		login = strtok(linha,",");
		senha = strtok(NULL,"\n");
		// Comparando os dados de login e senha informados pelo usuário com os dados salvos no arquivo logins.txt
		if(strcmp(login, user) == 0 && strcmp(senha, pass) == 0){
			
			printf("Acesso concedido!\n");
			system("cls");
			return 1;
		}
		
	}
	printf("Login ou senha invalido!\n");
	return 0;
}

bool salvar_cadastro(char dados[300], char tipo){
	FILE *arq;
	char *login, *senha;

	if(tipo == 'C'){
		arq = fopen("arquivos/clientes.txt", "a");
	}else if(tipo == 'V'){
		arq = fopen("arquivos/vendedores.txt", "a");
	}else{
		arq = fopen("arquivos/funcionario.txt", "a");
	}
	
	printf("Salvando...\n");
  	fflush(stdin);
	fputs(dados, arq);
	fputs("\n", arq);
	fclose(arq);
	
	arq = fopen("arquivos/logins.txt", "a");
	fflush(stdin);
	login = strtok(dados,",");
	senha = strtok(NULL,",");
	
	fputs(login, arq);
	fputs(",", arq);
	fputs(senha, arq);
	fputs("\n", arq);
	login = "";
	fclose(arq);
	return true;
}

// Limpar buffer do teclado
int clear_input_buffer(void) {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) /* void */;
    return ch;
}

float valormensal[12], total;
short indice, opcao, mensagem;

void mensagens(short mensagem)
{
 	if(mensagem == 1)
 	{
 		printf(" \n Opcao Invalida! Tente novamente");	
	}
	else if(mensagem == 2)
	{
		printf("  \n Mes Invalido!");
	}
	else if(mensagem == 3)
	{
		printf("  \n Venda adicionada com sucesso!");
	}
	return;
}

void RegistrarVendas()
{
	short mes;
	float venda;
	printf("\n Informe o mes da venda:  ");
	scanf("%d", &mes);
	if(mes<1 || mes > 12)
	{
		mensagem = 1;
		mensagens(mensagem);
		return;
	}
	printf(" \n Informe o valor da venda:   ");
	scanf("%f", &venda);
	valormensal[mes-1] = valormensal[mes -1] + venda;
	mensagem = 3;
	mensagens(mensagem);
	return;
}

void ExibirRelatorio()
{
	short mes = 0;
	printf("\n*****************************\n");
	printf("\n* Relatorio de Vendas Anual *\n");
	printf("\n*****************************\n");
	printf("\n* Mes *               Venda *\n");
	printf("\n*****************************\n");
	while(mes <12)
	{
		printf("\n* %2d  *  %*.*f *\n", mes+1, 18, 2, valormensal[mes]);
		total = total + valormensal[mes];
		mes++;
	}
	printf("\n*****************************\n");
	printf("\n*  Total    *  %*.*f *\n", 18, 2, total);
	printf("\n*****************************\n\n");
	total = 0;
	return;
}
// Tela de cadastro de cliente, vendedor e funcionários
void tela_cadastros(){
	
	char nomeC[50], nomeV[50], registroF[50];
	char senhaC[50], senhaV[50], senhaF[50];
	char cpfC[20], cpfV[20], cpfF[20];
	char idadeC[2], idadeV[2], idadeF[2];
	char enderecoC[70], enderecoV[70], enderecoF[70];
	float preco;
	char salvar[300] = "";
	int validar = 0;
	
	do{
	
	system("cls");
	printf("========Bem vindo ao Hot Buy======== \n");
	printf("  Menu de Cadastros e Relatorios \n"); 
	printf(" 1-Cadastro de Cliente \n");
	printf(" 2-Cadastro de Vendedor \n"); 
	printf(" 3-Cadastro de funcionario \n");
	printf(" 4-Relatorios \n");
	printf(" 5-Calcular Lucro do Produto \n"); 
	printf(" 6-Relatorio Anual de Vendas \n");
	printf(" 7-Voltar \n");
	printf(" Digite a opcao desejada \n");   
	scanf("%d", &menu);
		
	switch(menu){
		case 1:
			clear_input_buffer();
			system("cls");
			printf("Cadastro de Cliente \n");
			printf("Nome completo:  \n");
			gets(nomeC);
			printf("Senha:\n");
			gets(senhaC);
			printf("Cpf:\n");
			gets(cpfC);
			printf("Idade:\n");
			gets(idadeC);
			printf("Endereco:\n");
			gets(enderecoC);

			//Concatenando Dados
			strcat(salvar, nomeC);
			strcat(salvar, ",");
			strcat(salvar, senhaC);
			strcat(salvar, ",");
			strcat(salvar, cpfC);
			strcat(salvar, ",");
			strcat(salvar, idadeC);
			strcat(salvar, ",");
			strcat(salvar, enderecoC);
			
			salvar_cadastro(salvar, 'C');
			validar = 1;
		break;
		
		case 2:
			clear_input_buffer();
			system("cls");
			printf("Cadastro de Vendedor \n");
			printf("Nome completo:  \n");
			gets(nomeV);
			printf("Senha:\n");
			gets(senhaV);
			printf("Cpf:\n");
			gets(cpfV);
			printf("Idade:\n");
			gets(idadeV);
			printf("Endereco:\n");
			gets(enderecoV);
				
			//Concatenando Dados
			strcat(salvar, nomeV);
			strcat(salvar, ",");
			strcat(salvar, senhaV);
			strcat(salvar, ",");
			strcat(salvar, cpfV);
			strcat(salvar, ",");
			strcat(salvar, idadeV);
			strcat(salvar, ",");
			strcat(salvar, enderecoV);
				
			salvar_cadastro(salvar, 'V');
			validar = 1;
		break;
			
		case 3:
			clear_input_buffer();
			system("cls");
			printf("Cadastro de Funcionario \n");
			printf("Registro do Funcionario:  \n");
			gets(registroF);
			printf("Senha:\n");
			gets(senhaF);
			printf("Cpf:\n");
			gets(cpfF);
			printf("Idade:\n");
			gets(idadeF);
			printf("Endereco:\n");
			gets(enderecoF);
				
			//Concatenando Dados
			strcat(salvar, registroF);
			strcat(salvar, ",");
			strcat(salvar, senhaF);
			strcat(salvar, ",");
			strcat(salvar, cpfF);
			strcat(salvar, ",");
			strcat(salvar, idadeF);
			strcat(salvar, ",");
			strcat(salvar, enderecoF);
				
			salvar_cadastro(salvar, 'F');
			validar = 1;
		break;
			
		case 4:
			printf("Relatorios de vendas \n");
				
			FILE *arq;
				 
	  	 	char texto_linha[300]; 
	  	 	arq = fopen("arquivos/relatório de vendas.txt", "w"); 
	  	    printf("Digite o relatorio:  \n"); 
	  	 	fflush(stdin); 
	  	 	scanf("%[^\n]s", &texto_linha); 
	  		fputs(texto_linha, arq); 
	  	    fputs("\n", arq); 
	  	    fclose(arq);
	  	    validar = 1;
	  	    
	  	break;
	  	case 5:
	  		float preco, vendido, amt;
	  			printf("Preço do produto:  \n");
                scanf("%f", &preco);
                printf("Preço do item vendido: \n");
                scanf("%f", &vendido);
                if(vendido>preco)
                {
                	amt=vendido - preco;
                	printf(" Lucro de: %f \n", amt);	
				}
			    else if(preco>vendido)
				{
				   amt=preco - vendido;
			       printf(" Prejuízo de: %f \n", amt);
				}	
			    else
			    {
			     	printf(" Sem Lucro ou Prejuízo \n.");
				}
				system("pause"); 
				
		break;
		case 6:
			system("cls");
			printf("Area de Relatorio Anual de Vendas \n");
			printf("1- Registrar vendas \n");
			scanf("%d", &menu);
				while(1)
	{
		system("cls");
		printf("1-Registrar Vendas \n");
		printf("2-Relatorio de Vendas Anuais\n");
		printf("0-Voltar a tela inicial\n");
		
		scanf("%d", &opcao);
		if(opcao == 0)
		{
			return;
		}
		else if(opcao == 1)
		{
			RegistrarVendas();
		}
		else if(opcao == 2)
		{
			ExibirRelatorio();
		}
		else	
		{
			mensagem = 1;
			mensagens(mensagem);
		}
		system("pause");
	}
		break;
		case 7:
		validar = 1;
}


	
}while(validar == 0);
	system("cls"); 
}

void tela_produtos(){
	
	int validar = 0;
	do{
		printf("========Bem vindo ao Hot Buy======== \n");
		printf("        Menu de produtos  \n"); 
		printf(" 1-Cadastrar produto \n");
		printf(" 2-Procurar produto  \n");
		printf(" 3-Voltar   \n");
		printf(" Digite a opcao desejada \n");   
		scanf("%d", &menu);  
		
		switch(menu){
	  	case 1:
	  		system("cls");
			FILE *arq; 
	
	  	 	char texto_linha[450]; 
	  	 	char texto_linha2[450]; 
	  	 	char texto_linha3[450]; 
	  	 	char texto_linha4[450];
	
	  	 	arq = fopen("arquivos/registro de produtos.txt", "a"); 
	  	    printf("Digite os seguintes requisitos:  \n"); 
	  	    fflush(stdin); 
	          	printf("Nome do produto: \n");
	  	 		scanf("%[^\n]s", &texto_linha); 
	  	 		fflush(stdin); 
	        	printf("Tipo do produto:\n");
	        	printf("1-Alimentos\n");
	        	printf("2-Eletrodomesticos\n");
	        	printf("3-Autos\n");
	  	 		scanf("%[^\n]s", &texto_linha2); 
	  	 		fflush(stdin); 
	            printf("Qualidade e Descricao: \n");
	  	 		scanf("%[^\n]s", &texto_linha3); 
	  	 		fflush(stdin); 
	            printf("Valor do produto: \n");
	  	 		scanf("%[^\n]s", &texto_linha4); 
	
	  	 		fputs(texto_linha, arq); 
	  	 		fputs(",", arq);
	  	 		fputs(texto_linha2, arq);
	  	 		fputs(",", arq);
	  	 		fputs(texto_linha3, arq);
	            fputs(",", arq);
	            fputs(texto_linha4, arq);
	            fputs("\n", arq); 
	
	    		fclose(arq); 
	        	validar = 1;
			break;    
		case 2:
			system("cls");
			FILE *file;
			file = fopen("arquivos/registro de produtos.txt", "r"); 
	        if (file == NULL) {
				printf("Não foi possível localizar o arquivo. \n");
				getchar();
				exit(0);
			 }
	  	 	     
			char produtos[200];
				
			while(fgets(produtos, 100, file) != NULL) {
				printf("%s", produtos);
			}
	  	 	fclose(file);
	        system("pause");
	    break;
	    case 3:
	    	validar = 1;
	    	break;
		}
		system("cls");
	}while(validar == 0);
}

void tela_principal()
   {
	int validar = 0;
	do{
		printf("========Bem vindo ao Hot Buy========\n");
		printf("    Menu Principal \n");
		printf(" 1-Menu de Cadastros e Relatorios \n");
		printf(" 2-Menu de Produtos \n");
		printf(" 3-Encerrar Sessao \n");
		scanf("%d", &menu);
		system("cls");
		switch(menu){
			case 1:
				tela_cadastros();
				validar = 0;
			break;
			case 2:
			    tela_produtos();
			    validar = 0;
			break;
			case 3:
			     printf("Sessao encerrada \n");
				 validar = 1;
			break;
		}
	
	}while(validar == 0);
}


int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int validar;
	
	//do{
	//	validar = telalogin();
	//}while(validar == 0);
	
	tela_principal();
	
	system("pause");
	return menu;
}
