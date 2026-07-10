extern void func_ov022_02089478(int arg0, int arg1, void *arg2);
extern int func_ov022_020894f8(unsigned int arg0, int arg1);

typedef struct { int a; int b; int c; } Vec3w;

void func_ov022_02097b78(int arg0, int arg1, int arg2, int arg3) {
    if (*(int *)(arg0 + 0x7c0) != 0) {
        Vec3w buf = *(Vec3w *)(arg0 + 0x48c);
        func_ov022_02089478(*(int *)(arg0 + 0x7c0), *(int *)(arg0 + 0x7c4), &buf);
        if (func_ov022_020894f8(*(unsigned int *)(arg0 + 0x7c0), *(int *)(arg0 + 0x7c4)) != 0) {
            *(int *)(arg0 + 0x7c4) = -1;
        }
    }
}
