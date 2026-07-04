extern unsigned short func_02020a9c(void);
extern void GFXi_EnqueueCommand(int a, int b, int c, int d);

void func_02023448(int param_1) {
    int mode = (func_02020a9c() & 2) == 0 ? 0xb : 10;
    GFXi_EnqueueCommand(mode, 0, *(int *)(param_1 + 0x94) + 0xc,
                  *(int *)(*(int *)(param_1 + 0x94) + 8));
}
