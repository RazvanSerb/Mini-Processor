#include <stdio.h>

int main() {
    const unsigned int dim_ui = 8 * sizeof(unsigned int);  // dimensiunea in memorie a unei variabile "unsigned int"
    unsigned int inst = 0;
    scanf("%u", &inst);
    unsigned int k = 1;  // in ordine semnificativa (stanga->dreapta), numarul de ordine al bit-ului curent din "inst"
    unsigned int n = 1;
    for (int step = 2; step >= 0; step--) {  // step = (dimensiunea in "inst" a lui "n")-1
        n = n + ((inst >> (dim_ui - k)) & 1) * (1 << step);
        k++;
    }
    printf("%d ", n);
    unsigned int dim_inst = 3 + 2 * n + 4;
    while (k <= dim_inst - 4) {
        unsigned int opbit1 = ((inst >> (dim_ui - k)) & 1);
        k++;
        unsigned int opbit2 = ((inst >> (dim_ui - k)) & 1);
        k++;
        if (opbit1 == 0 && opbit2 == 0)
            printf("+ ");
        if (opbit1 == 0 && opbit2 == 1)
            printf("- ");
        if (opbit1 == 1 && opbit2 == 0)
            printf("* ");
        if (opbit1 == 1 && opbit2 == 1)
            printf("/ ");
    }
    unsigned int dim_operand = 1;
    for (int step = 3; step >= 0; step--) {  // step = (dimensiunea in "inst" a lui "dim_operand")-1
        dim_operand = dim_operand + ((inst >> (dim_ui - k)) & 1) * (1 << step);
        k++;
    }
    printf("%d\n", dim_operand);
    return 0;
}
