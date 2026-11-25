#include <stdio.h>

#define MAX 100

// uma fila (vetor) para cada categoria
// ini = proximo a ser chamado, fim = proxima posicao livre
int filaU[MAX], iniU = 0, fimU = 0;
int filaP[MAX], iniP = 0, fimP = 0;
int filaN[MAX], iniN = 0, fimN = 0;

char senhaAtual[5];   // senha que esta sendo atendida
int atendendo = 0;    // 1 = tem alguem sendo atendido

// le um numero e so aceita se estiver entre min e max
int lerNumero(char texto[], int min, int max) {
    int n, ok;
    do {
        printf("%s", texto);
        ok = scanf("%d", &n);
        while (getchar() != '\n');   // limpa o buffer
        if (ok != 1 || n < min || n > max)
            printf("Valor invalido!\n");
    } while (ok != 1 || n < min || n > max);
    return n;
}

char lerGenero() {
    char g;
    int ok;
    do {
        printf("Genero (F/M): ");
        ok = scanf("%c", &g);
        while (getchar() != '\n');
        if (ok != 1 || (g != 'F' && g != 'M'))
            printf("Genero invalido!\n");
    } while (ok != 1 || (g != 'F' && g != 'M'));
    return g;
}

// testa o caso mais restritivo primeiro
char classificar(char genero, int idade, int gestante, int lactante, int especial, int obeso) {
    if (idade > 80) return 'U';
    if (gestante || lactante || especial || obeso ||
        (genero == 'F' && idade >= 60) || (genero == 'M' && idade >= 65))
        return 'P';
    return 'N';
}

void emitirSenha(char cat) {
    if (cat == 'U') {
        filaU[fimU] = fimU + 1;
        printf("Senha emitida: U%03d\n", filaU[fimU]);
        fimU++;
    } else if (cat == 'P') {
        filaP[fimP] = fimP + 1;
        printf("Senha emitida: P%03d\n", filaP[fimP]);
        fimP++;
    } else {
        filaN[fimN] = fimN + 1;
        printf("Senha emitida: N%03d\n", filaN[fimN]);
        fimN++;
    }
}

void registrarPaciente() {
    char genero, cat;
    int idade, gestante = 0, lactante = 0, especial, obeso;

    if (fimU == MAX || fimP == MAX || fimN == MAX) {
        printf("Fila cheia!\n");
        return;
    }

    genero = lerGenero();
    idade = lerNumero("Idade: ", 0, 120);
    if (genero == 'F') {   // so pergunta se for mulher
        gestante = lerNumero("Gestante (1-sim, 0-nao): ", 0, 1);
        lactante = lerNumero("Lactante (1-sim, 0-nao): ", 0, 1);
    }
    especial = lerNumero("Necessidade especial (1-sim, 0-nao): ", 0, 1);
    obeso = lerNumero("Obesidade (1-sim, 0-nao): ", 0, 1);

    cat = classificar(genero, idade, gestante, lactante, especial, obeso);
    printf("Categoria: %c\n", cat);
    emitirSenha(cat);
}

void chamarProxima() {
    if (atendendo) {
        printf("Finalize o atendimento da senha %s primeiro!\n", senhaAtual);
        return;
    }
    if (iniU == fimU && iniP == fimP && iniN == fimN) {
        printf("Nao tem ninguem na fila!\n");
        return;
    }

    // urgente primeiro, depois preferencial, depois normal
    if (iniU < fimU) {
        sprintf(senhaAtual, "U%03d", filaU[iniU]);
        iniU++;
    } else if (iniP < fimP) {
        sprintf(senhaAtual, "P%03d", filaP[iniP]);
        iniP++;
    } else {
        sprintf(senhaAtual, "N%03d", filaN[iniN]);
        iniN++;
    }
    atendendo = 1;
    printf("Chamando a senha %s\n", senhaAtual);
}

void finalizarAtendimento() {
    if (!atendendo) {
        printf("Ninguem esta sendo atendido.\n");
        return;
    }
    printf("Atendimento da senha %s finalizado.\n", senhaAtual);
    atendendo = 0;
}

void exibirPainel() {
    int i;
    printf("\n===== PAINEL =====\n");
    if (atendendo)
        printf("Senha atual: %s (categoria %c)\n", senhaAtual, senhaAtual[0]);
    else
        printf("Senha atual: nenhuma\n");

    printf("Proximas: ");
    for (i = iniU; i < fimU; i++) printf("U%03d ", filaU[i]);
    for (i = iniP; i < fimP; i++) printf("P%03d ", filaP[i]);
    for (i = iniN; i < fimN; i++) printf("N%03d ", filaN[i]);

    printf("\nEsperando - U: %d | P: %d | N: %d\n", fimU - iniU, fimP - iniP, fimN - iniN);
}

void exibirMenu() {
    printf("\n--- MENU ---\n");
    printf("1 - Registrar paciente\n");
    printf("2 - Chamar proxima senha\n");
    printf("3 - Finalizar atendimento\n");
    printf("4 - Mostrar painel\n");
    printf("0 - Sair\n");
}

int main() {
    int opcao;
    do {
        exibirMenu();
        opcao = lerNumero("Opcao: ", 0, 4);
        switch (opcao) {
            case 1: registrarPaciente(); break;
            case 2: chamarProxima(); break;
            case 3: finalizarAtendimento(); break;
            case 4: exibirPainel(); break;
            case 0: printf("Saindo...\n"); break;
        }
    } while (opcao != 0);
    return 0;
}
