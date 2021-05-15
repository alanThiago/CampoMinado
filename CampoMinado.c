#include "CampoMinado.h"

char campo[N][N];

void GerarCampo(int n, int dificuldade){
    int i, j;
    int numBombas = (n * n * dificuldade) / 10;

    srand(time(NULL));

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            campo[i][j] = SEM_BOMBA;

    while(numBombas){
        i = rand() % n;
        j = rand() % n;

        if(campo[i][j] == SEM_BOMBA){
            campo[i][j] = BOMBA;
            --numBombas;
        }
    }
}

int NumBombas(int row, int col, int n){
    int numBombas = 0;

    if(row > 0){
        if((col > 0) && ((campo[row-1][col-1] == BOMBA) || (campo[row-1][col-1] == FLAG_BOMBA))) ++numBombas;
        if((col < n-1) && ((campo[row-1][col+1] == BOMBA) || (campo[row-1][col+1] == FLAG_BOMBA))) ++numBombas;
        if((campo[row-1][col] == BOMBA) || (campo[row-1][col] == FLAG_BOMBA)) ++numBombas;
    }
    if((col > 0) && ((campo[row][col-1] == BOMBA) || (campo[row][col-1] == FLAG_BOMBA))) ++numBombas;
    if((col < n-1) && ((campo[row][col+1] == BOMBA) || (campo[row][col+1] == FLAG_BOMBA))) ++numBombas;
    if(row < n-1){
        if((col > 0) && (campo[row+1][col-1]) == BOMBA || (campo[row+1][col-1] == FLAG_BOMBA)) ++numBombas;
        if((col < n-1) && ((campo[row+1][col+1]) == BOMBA || (campo[row+1][col+1] == FLAG_BOMBA))) ++numBombas;
        if((campo[row+1][col] == BOMBA) || (campo[row+1][col] == FLAG_BOMBA)) ++numBombas;
    }
    return numBombas;
}

void AbrirCampo(int row, int col, int n, int *numAbertos){
    if(campo[row][col] == SEM_BOMBA || campo[row][col] == FLAG_SEM_BOMBA){
        *numAbertos -= 1;
        int numBombas = NumBombas(row, col, n);
        if(campo[row][col] == SEM_BOMBA) campo[row][col] = numBombas;
        if(numBombas == 0){
            if(row > 0){
                if((col > 0) && ((campo[row-1][col-1] == SEM_BOMBA) || (campo[row-1][col-1] == FLAG_SEM_BOMBA))) AbrirCampo(row-1, col-1, n, numAbertos);
                if((col < n-1) && ((campo[row-1][col+1] == SEM_BOMBA) || (campo[row-1][col+1] == FLAG_SEM_BOMBA))) AbrirCampo(row-1, col+1, n, numAbertos);
                if((campo[row-1][col] == SEM_BOMBA) || (campo[row-1][col] == FLAG_SEM_BOMBA)) AbrirCampo(row-1, col, n, numAbertos);
            }
            if((col > 0) && ((campo[row][col-1] == SEM_BOMBA) || (campo[row][col-1] == FLAG_SEM_BOMBA))) AbrirCampo(row, col-1, n, numAbertos);
            if((col < n-1) && ((campo[row][col+1] == SEM_BOMBA) || (campo[row][col+1] == FLAG_SEM_BOMBA))) AbrirCampo(row, col+1, n, numAbertos);
            if(row < n-1){
                if((col > 0) && (campo[row+1][col-1]) == SEM_BOMBA || (campo[row+1][col-1] == FLAG_SEM_BOMBA)) AbrirCampo(row+1, col-1, n, numAbertos);
                if((col < n-1) && ((campo[row+1][col+1]) == SEM_BOMBA || (campo[row+1][col+1] == FLAG_SEM_BOMBA))) AbrirCampo(row+1, col+1, n, numAbertos);
                if((campo[row+1][col] == SEM_BOMBA) || (campo[row+1][col] == FLAG_SEM_BOMBA)) AbrirCampo(row+1, col, n, numAbertos);
            }
        }
    }
}

void InserirRemoverFlag(int row, int col){
    if(campo[row][col] == BOMBA) campo[row][col] = FLAG_BOMBA;
    else if(campo[row][col] == FLAG_BOMBA) campo[row][col] = BOMBA;
    else if(campo[row][col] == SEM_BOMBA) campo[row][col] = FLAG_SEM_BOMBA;
    else campo[row][col] = SEM_BOMBA;
}

void InserirBombasImpressao(int n){
    int i, j;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if((campo[i][j] == BOMBA) || (campo[i][j] == FLAG_BOMBA))
                campo[i][j] = BOMBA_IMPRESSAO;
}

void ImprimirCampo(int n){
    int i, j;

    for(i = 0; i < n; i++){
        printf(" %-3d| ", i+1);
        for(j = 0; j < n; j++){
            if(campo[i][j] >= 0)
                printf(GREEN "%-4d" RESET, campo[i][j]);
            else if((campo[i][j] == SEM_BOMBA) || (campo[i][j] == BOMBA))
                printf(BLUE "%-4c" RESET, '?');
            else if((campo[i][j] == FLAG_BOMBA) || (campo[i][j] == FLAG_SEM_BOMBA))
                printf(MAGENTA "%-4c" RESET, 'F');
            else
                printf(RED "%-4c" RESET, '*');
        }
        printf("\n");
    }
    printf("    ");
    for(i = 0; i < n; i++) printf("----");
    printf("\n      ");
    for(i = 1; i <= n; i++) printf("%-4d", i);
    printf("\n\n");
}

int GetDificuldade(){
    int dificuldade;

    system("clear");
    printf("Insira uma dificuldade [1, 2, 3]: ");
    scanf("%d", &dificuldade);
    while(dificuldade < 1 || dificuldade > 3){
        system("clear");
        printf("Entrada invalida\n");
        printf("Insira uma dificuldade [1, 2, 3]: ");
        scanf("%d", &dificuldade);
    }
    return dificuldade;
}

void GetCoordenadas(int *linha, int *coluna, int n){
    printf("Digite a linha e a coluna desejadas: ");
    scanf("%d %d", linha, coluna);
    while((*linha < 0) || (*linha > n) || (*coluna < 0) || (*coluna > n)){
        printf("Entrada invalida\n");
        printf("Digite a linha e a coluna desejadas: ");
        scanf("%d %d", linha, coluna);
    }
    *linha -= 1; *coluna -= 1;
}

char GetFlag(){
    char flag;

    printf("Inserir ou remover flag? [s/n]: ");
    setbuf(stdin, NULL);
    scanf("%c", &flag);
    while((flag != 's') && (flag != 'n')){
        printf("Entrada invalida\n");
        printf("Inserir ou remover flag? [y/n]: ");
        setbuf(stdin, NULL);
        scanf("%c", &flag);
    }
    return flag;
}

int GetTamanhoCampo(){
    int n;

    system("clear");
    printf("Insira o tamanho do campo: [3...50] ");
    scanf("%d", &n);
    while((n < 3) || (n > 50)){
        system("clear");
        printf("Entrada Invalida\n");
        printf("Insira o tamanho do campo: ");
        scanf("%d", &n);
    }
    return n;
}

void Jogar(){
    int i, j; //coordenadas
    int n; //tamanho do campo
    int dificuldade; //dificuldade do jogo
    int areasLivres; //quantidade de áreas sem bombas restantes
    char flag;

    n = GetTamanhoCampo();
    dificuldade = GetDificuldade();

    GerarCampo(n, dificuldade);
    areasLivres = (n * n) - ((n * n * dificuldade) / 10);

    while(areasLivres){
        system("clear");
        ImprimirCampo(n);
        flag = GetFlag();
        GetCoordenadas(&i, &j, n);

        if(flag == 's')
            InserirRemoverFlag(i, j);
        else if(campo[i][j] == SEM_BOMBA)
            AbrirCampo(i, j, n, &areasLivres);
        else if(campo[i][j] == BOMBA){
            system("clear");
            InserirBombasImpressao(n);
            ImprimirCampo(n);
            printf("VOCE PERDEU! FIM DE JOGO.\n");
            return;
        }
    }

    system("clear");
    InserirBombasImpressao(n);
    ImprimirCampo(n);
    printf("PARABENS! VOCE VENCEU!\n");
}