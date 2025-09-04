#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

// Função para inserir os vetores
void insira_vetor(double vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Digite a componente %d do vetor: ", i + 1);
        scanf("%lf", &vetor[i]);
    }
}

// Produto escalar entre dois vetores de mesmo tamanho
double produto_escalar(double v1[], double v2[], int n) {
    double produto = 0.0;
    for (int i = 0; i < n; i++) {
        produto += v1[i] * v2[i];
    }
    return produto;
}

void produto_vetorial(double A[], double B[], double resultado[]) {
    resultado[0] = A[1] * B[2] - A[2] * B[1]; // componente x
    resultado[1] = A[2] * B[0] - A[0] * B[2]; // componente y
    resultado[2] = A[0] * B[1] - A[1] * B[0]; // componente z
}


double produto_misto(double A[], double B[], double C[]) {
    double vetor_vetorial[3];
    produto_vetorial(B, C, vetor_vetorial);  // B x C
    return produto_escalar(A, vetor_vetorial, 3);  // A . (B x C)
}

void projecao(double A[], double B[], double resultado[]) {
    double escalar = produto_escalar(A, B, 3) / produto_escalar(B, B, 3);
    for (int i = 0; i < 3; i++) {
        resultado[i] = escalar * B[i];
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    int op, n;

    do {
        printf("\nCALCULADORA VETORIAL\n");
        printf("\n\t0 - Sair\n\t1 - Produto escalar\n\t2 - Produto vetorial\n\t3 - Produto misto\n\t4 - Projeção\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;

            case 1: {
                printf("Digite o tamanho dos vetores: ");
                scanf("%d", &n);
                
                double v1[n], v2[n];

                printf("Insira os valores do primeiro vetor:\n");
                insira_vetor(v1, n);
                printf("Insira os valores do segundo vetor:\n");
                insira_vetor(v2, n);

                double resultado = produto_escalar(v1, v2, n);
                printf("O produto escalar é: %.2lf\n", resultado);
                break;
            }

            case 2: {
                n = 3;
                double v1[3], v2[3], resultado[3];

                printf("Insira os valores do primeiro vetor (3D):\n");
                insira_vetor(v1, 3);
                printf("Insira os valores do segundo vetor (3D):\n");
                insira_vetor(v2, 3);

                produto_vetorial(v1, v2, resultado);
                printf("Produto vetorial (A x B) = [%.2lf, %.2lf, %.2lf]\n", resultado[0], resultado[1], resultado[2]);
                break;
            }

            case 3: {
                n = 3;
                double A[3], B[3], C[3];

                printf("Insira os valores do vetor A:\n");
                insira_vetor(A, 3);
                printf("Insira os valores do vetor B:\n");
                insira_vetor(B, 3);
                printf("Insira os valores do vetor C:\n");
                insira_vetor(C, 3);

                double resultado = produto_misto(A, B, C);
                printf("Produto misto (A · (B x C)) = %.2lf\n", resultado);
                break;
            }

            case 4: {
                n = 3;
                double A[3], B[3], resultado[3];

                printf("Insira os valores do vetor A:\n");
                insira_vetor(A, 3);
                printf("Insira os valores do vetor B:\n");
                insira_vetor(B, 3);

                projecao(A, B, resultado);
                printf("Projeção de A sobre B = [%.2lf, %.2lf, %.2lf]\n", resultado[0], resultado[1], resultado[2]);
                break;
            }

            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}