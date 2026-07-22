/* Prepares the 0x8000-byte staging buffer at +0x594, runs func_0201f1a8 into it and, on
 * success, rounds the returned length up to a multiple of four before recording it at +0
 * and +8 and handing over to func_02020b64. */
extern int func_0201f1a8(int a, void *b, int size);
extern int func_02020b64(char *o, int c, int d);

int func_02020c7c(char *o, int a, int c, int d) {
    int n;
    *(int *)(o + 0x590) = 0x8000;
    n = func_0201f1a8(a, o + 0x594, *(int *)(o + 0x590));
    if (n < 0) {
        return 0;
    }
    if (n % 4 != 0) {
        n += 4 - n % 4;
    }
    *(int *)o = n;
    *(int *)(o + 8) = n;
    return func_02020b64(o, c, d);
}
