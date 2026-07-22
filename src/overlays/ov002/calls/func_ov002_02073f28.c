typedef struct { int x, y, z; } VecFx32;

extern int data_ov002_0207fa14;
extern int func_ov002_02074460(int arg0);

void func_ov002_02073f28(int arg0, const VecFx32 *pos) {
    int ctx = *(int *)&data_ov002_0207fa14;
    int idx = func_ov002_02074460(arg0);
    int entry = *(int *)(*(int *)(ctx + 0x44) + idx * 0x18);

    *(VecFx32 *)(entry + 0x104) = *pos;
}
