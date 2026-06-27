extern int GFXi_EnqueueCommand(void *a, int b, int c, int d);
extern void *data_02041fac[];

int func_02024b04(int idx, void *p, int arg2, int arg3) {
    return GFXi_EnqueueCommand(data_02041fac[idx], arg2, (int)((char *)p + 0xc), arg3);
}
