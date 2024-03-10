#include <stdio.h>
#define NMAX 8

void operands_elimpos(unsigned int *operands, unsigned int *len_operands, unsigned int pos) {
    for (unsigned int i = pos; i < (*len_operands); i++)
        operands[i] = operands[i + 1];
    (*len_operands)--;
 } 

void operators_elimpos(char *operators, unsigned int *len_operators, unsigned int pos) {
    for (unsigned int i = pos; i < (*len_operators); i++)
        operators[i] = operators[i + 1];
    (*len_operators)--;
}

int main() {
    const unsigned int dim_ui = 8 * sizeof(unsigned int);  // dimensiunea in memorie a unei variabile "unsigned int"
    const unsigned short dim_us = 8 * sizeof(unsigned short);  // dimensiunea in memorie a unei variabile "unsigned short"
    unsigned int inst = 0;
    scanf("%u", &inst);
    unsigned int k = 1;  // in ordine semnificativa (stanga->dreapta), numarul de ordine al bit-ului curent din "inst"
    unsigned int n = 1;
    for (int step = 2; step >= 0; step--) {  // step = (dimensiunea in "inst" a lui "n")-1
        n = n + ((inst >> (dim_ui - k)) & 1) * (1 << step);
        k++;
    }
    unsigned int dim_inst = 3 + 2 * n + 4;
    char operators[NMAX];  // vectorul care retine operatorii
    unsigned int len_operators = 0;  // lungimea curenta a vectorului de operators
    while (k <= dim_inst - 4) {
        unsigned int opbit1 = ((inst >> (dim_ui - k)) & 1);
        k++;
        unsigned int opbit2 = ((inst >> (dim_ui - k)) & 1);
        k++;
        if (opbit1 == 0 && opbit2 == 0)
            operators[len_operators] = '+';
        if (opbit1 == 0 && opbit2 == 1)
            operators[len_operators] = '-';
        if (opbit1 == 1 && opbit2 == 0)
            operators[len_operators] = '*';
        if (opbit1 == 1 && opbit2 == 1)
            operators[len_operators] = '/';
        len_operators++;
    }
    operators[len_operators] = '\0';
    unsigned int dim_operand = 1;
    for (int step = 3; step >= 0; step--) {  // step = (dimensiunea in "inst" a lui "dim_operand")-1
        dim_operand = dim_operand + ((inst >> (dim_ui - k)) & 1) * (1 << step);
        k++;
    }
    unsigned int nr_us = ((n + 1) * dim_operand) / dim_us;  // numarul de unsigned short-uri ce trebuiesc citite
    if (((n + 1) * dim_operand) % dim_us != 0)
        nr_us++;
    unsigned int operands[NMAX + 1] = {0};  // vectorul care retine operanzii
    unsigned int len_operands = 0;  // lungimea curenta a vectorului de operands
    int step = (int)(dim_operand - 1);
    for (int i = 1; i <= nr_us; i++) {
        unsigned short x = 0; scanf("%hu", &x);
        unsigned int kx = 1;  // in ordine semnificativa (stanga->dreapta), numarul de ordine al bit-ului curent din "x"
        while (kx <= dim_us) {
            while (step >= 0) {
                operands[len_operands] = operands[len_operands] + (((x >> (dim_us - kx)) & 1) * (1 << step));
                step--;
                kx++;
                if (kx > dim_us)
                    break;
            }
            if (step < 0) {
                len_operands++;
                if (len_operands == n + 1)
                    break;
                step = (int)(dim_operand - 1);
            }
        }
    }
    for (unsigned int i = 0; i < len_operators; i++) {
        if (operators[i] == '*') {
            operands[i] = operands[i] * operands[i + 1];
            operands_elimpos(operands, &len_operands, i + 1) ;
            operators_elimpos(operators, &len_operators, i);
            i--;
        } else if (operators[i] == '/') {
            operands[i] = operands[i] / operands[i + 1];
            operands_elimpos(operands, &len_operands, i + 1) ;
            operators_elimpos(operators, &len_operators, i);
            i--;
        }
    }
    int result = (int)(operands[0]);
    for (int i = 0; i < len_operators; i++) {
        if (operators[i] == '+')
            result = result + (int)(operands[i + 1]);
        if (operators[i] == '-')
            result = result - (int)(operands[i + 1]);
    }
    printf("%d\n", result);
    return 0;
}
