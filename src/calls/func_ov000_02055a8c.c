extern int func_02032450();
extern int NNS_FndRemoveListObject();
extern int NNSi_FndFreeFromDefaultHeap();

void func_ov000_02055a8c(char *a, int *b)
{
    int i;
    int *p;
    int v;

    if (*(int *)(a + 0x4a70) == (int)b) {
        *(int *)(a + 0x4a70) = 0;
    }

    p = b;
    for (i = 0; i < 2; i++) {
        v = p[5];
        if (v != -1) {
            func_02032450(a, v);
        }
        p++;
    }

    NNS_FndRemoveListObject(a + 0x4a38, b);

    if (b != 0) {
        NNSi_FndFreeFromDefaultHeap();
    }
}
