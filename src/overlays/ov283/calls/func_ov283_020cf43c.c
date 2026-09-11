typedef struct {
    void *p0;
    int *vecB;
    char pad[0x14 - 8];
    int field_14;
    int field_18;
} A;

extern void VEC_Subtract(int *a, int *b, int *out);
extern int func_020050b4(int x, int z);

void func_ov283_020cf43c(A *a, void *b) {
    void *p1 = a->p0;
    void *p2 = *(void **)((char *)p1 + 0x38c);
    void *p3 = *(void **)((char *)p2 + 0x390);
    int *vecA = (int *)((char *)p3 + 0x190);
    int out[3];
    int angle;

    VEC_Subtract(vecA, a->vecB, out);
    angle = func_020050b4(out[0], out[2]);
    a->field_18 = angle;
    a->field_14 = angle;
    *(unsigned char *)((char *)a->p0 + 0x1c7) = 1;
}
