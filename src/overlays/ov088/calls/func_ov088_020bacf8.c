extern int func_ov022_020ad114(int this);
extern int func_ov022_020ad0c0(int this);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void func_01ff8d18(void *a, void *b);
extern int func_0200526c(int x, int z);
extern void func_ov088_020bb7a0(void);

void *func_ov088_020bacf8(int this, int param_2) {
    void *retval = 0;
    if (param_2 == 0x21) {
        int local[3];
        retval = (void *)func_ov088_020bb7a0;
        if (*(int *)(this + 0x2c2c) != 0) {
            (*(void (**)(int, int))(this + 0x664))(this, 0x30);
        } else {
            (*(void (**)(int, int))(this + 0x664))(this, 0x2f);
        }
        if (func_ov022_020ad114(this) != 0) {
            unsigned short angle;
            int *obj;
            VEC_Subtract((void *)func_ov022_020ad0c0(this), (void *)(this + 0x48c), local);
            if (VEC_Mag(local) != 0) {
                func_01ff8d18(local, local);
            }
            angle = (unsigned short)func_0200526c(-local[0], -local[2]);
            obj = *(int **)(this + 0x20);
            if ((*obj & 0x20) == 0) {
                *(short *)((int)obj + 0x80) = angle + 0x8000;
                *(unsigned short *)((int)obj + 4) |= 0x20;
            }
        }
    }
    return retval;
}
