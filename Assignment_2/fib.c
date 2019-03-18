#include <stdio.h>
#include <string.h>
#define N 1000
#define MAXDIGIT 1000000

// using fib[i-1]+fib[i-2] to compute fib[i]
// because there is too many digit so using string to store and do operation
char *computeFib(char *fib1, char *fib2) {
    char rev1[MAXDIGIT], rev2[MAXDIGIT];
    int i, j, cnt;
    int len1 = strlen(fib1);
    int len2 = strlen(fib2);
    // reverse the string so same decimal place can align
    for (i = 0; i < len1; i++)
        rev1[i] = fib1[len1 - i - 1];
    for (i = 0; i < len2; i++)
        rev2[i] = fib2[len2 - i - 1];
    char ans[30];
    int carry = 0;
    i = 0;
    j = 0;
    cnt = 0;
    // a+b+carry, if >10 then carry to the next decimal place
    while (i < len1 && j < len2) {
        int tmp = rev1[i] - '0' + rev2[j] - '0' + carry;
        ans[cnt++] = (tmp % 10) + '0';
        carry = tmp / 10;
        i++;
        j++;
    }
    while (i < len1) {
        int tmp = rev1[i] - '0' + carry;
        ans[cnt++] = (tmp % 10) + '0';
        carry = tmp / 10;
        i++;
    }
    while (j < len2) {
        int tmp = rev2[j] - '0' + carry;
        ans[cnt++] = (tmp % 10) + '0';
        carry = tmp / 10;
        j++;
    }
    if (carry != 0) ans[cnt++] = carry + '0';
    static char res[MAXDIGIT];
    for (i = 0; i < cnt; i++) res[i] = ans[cnt - i - 1];
    return res;
}

int main() {
    // answer will be direct to fib.txt
    int j;
    FILE *fout = fopen("fib.txt", "w");
    fprintf(fout, "fib[0]=0\n");
    fprintf(fout, "fib[1]=1\n");
    char fib1[MAXDIGIT], fib2[MAXDIGIT];
    // initialize fib[0] and fib[1]
    strcpy(fib1, "0");
    strcpy(fib2, "1");
    int i = 2;
    char *res;
    while (i <= N) {
        res = computeFib(fib1, fib2);
        fprintf(fout, "fib[%d]=%s\n", i, res);
        strcpy(fib1, fib2);
        strcpy(fib2, res);
        i++;
    }
    fclose(fout);
    return 0;
}
