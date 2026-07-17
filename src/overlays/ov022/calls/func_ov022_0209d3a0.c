/*
 * MATCHED -- rescued 2026-07-17 from a twice-confirmed "vec3-copy base-order tie".
 * The 3-word `*(vec3*)(p+0x878) = *(vec3*)(p+0x48c)` copy put the src/dst ldm/stm base registers the
 * wrong way round (ROM src->r0, mwcc dst->r0), and NO pointer-local / temp spelling reordered it.
 * THE FIX: write the copy as a FIELD-TO-FIELD struct assignment -- put both vec3s in one Obj struct
 * at their real offsets and do `((Obj*)p)->dst = ((Obj*)p)->src`. The raw double-cast form
 * `*(T*)a = *(T*)b` picks the reversed base order; the field form picks the ROM's. Same crack landed
 * ov208_020cfc04 (an 11-word copy). See codegen-cracks.md.
 */
extern void func_02016ae8(int a, int b, int c, int d);
extern void func_0202aa9c(unsigned short *a);
extern void func_02016c90(int a, int b);
extern unsigned char data_0204c240;

struct vec3_0209d3a0 {
    int a;
    int b;
    int c;
};

struct bits_0209d3a0 {
    unsigned char lo4 : 4;
    unsigned char b4 : 1;
    unsigned char hi3 : 3;
};

struct obj_0209d3a0 {
    char p0[0x48c];
    struct vec3_0209d3a0 src;
    char p1[0x3e0];
    struct vec3_0209d3a0 dst;
};

void func_ov022_0209d3a0(int param_1) {
    int iVar2;
    if ((data_0204c240 & 4) == 0) {
        return;
    }
    if (((struct bits_0209d3a0 *)(param_1 + 0x694))->b4 == 0) {
        return;
    }
    ((struct obj_0209d3a0 *)param_1)->dst = ((struct obj_0209d3a0 *)param_1)->src;
    iVar2 = param_1 + 0x700;
    *(unsigned short *)(param_1 + 0x850) =
        (unsigned short)(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x80) - 0x8000) + 0x8000;
    *(unsigned short *)(param_1 + 0x7d4) = *(unsigned short *)(param_1 + 0x7d4) | 0x20;
    func_02016ae8(*(int *)(param_1 + 0x84c), 1, 0, iVar2);
    func_0202aa9c((unsigned short *)(param_1 + 0x7d4));
    func_02016c90(*(int *)(param_1 + 0x84c), 3);
}
