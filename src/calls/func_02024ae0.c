extern int GFXi_EnqueueCommand(void *a, int b, int c, int d);
extern void *data_02041f8c[];

int func_02024ae0(int idx, void *p, int arg2, int arg3) {
    return GFXi_EnqueueCommand(data_02041f8c[idx], arg2, *(int *)((char *)p + 0x14), arg3);
}
