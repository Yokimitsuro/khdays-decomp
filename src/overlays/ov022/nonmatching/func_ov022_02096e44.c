/*
 * [nonmatching: marshal-setup coloring/scheduling: the idx/val computation and the x/src register assignment diverge (r0/r2/r3 swaps) though func_0201ef9c takes leftover r2/r3]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted
 * register allocation / block layout. Left uncarved (byte-exact in the blob).
 */
extern int OS_SPrintf(char *buf, char *fmt, int a, int b);
extern int func_0201ef9c(void *arg0, int arg1);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2cd8;
extern int data_02042a70;

typedef struct { int a; int b; } Pair;

void func_ov022_02096e44(int arg0, int arg1, int arg2, int arg3) {
    char buf[128];
    int idx = *(int *)(arg0 + 0xc) * 4;
    int val = *(int *)((char *)&data_02042a70 + idx);
    int x;
    Pair *src;
    Pair *dst;
    int i;
    OS_SPrintf(buf, (char *)&data_ov022_020b2cd8, val, idx);
    x = func_0201ef9c(buf, 6);
    src = (Pair *)(x + *(int *)(arg0 + 0xc) * 0x34);
    dst = (Pair *)(arg0 + 0x2688);
    i = 6;
    do {
        *dst = *src;
        src = src + 1;
        dst = dst + 1;
        i = i - 1;
    } while (i != 0);
    *(int *)dst = *(int *)src;
    NNSi_FndFreeFromDefaultHeap(x);
}
