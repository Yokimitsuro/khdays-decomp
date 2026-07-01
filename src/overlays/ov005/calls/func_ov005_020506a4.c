extern void MI_CpuFill8();
extern void NNS_FndInitList();
extern void func_020342e8();
extern void func_020343cc();

typedef struct {
    char pad0[8];
    char field8[12];
    char field20[12];
    char field32[16];
    char pad48[0xc8];
    void *field248;
    void *field252;
} Struct;

void func_ov005_020506a4(void *a, void **b) {
    Struct *s = (Struct *)a;
    MI_CpuFill8(s, 0, 0x100);
    if (b == 0) {
        s->field248 = (void *)func_020342e8;
        s->field252 = (void *)func_020343cc;
    } else {
        s->field248 = b[0] ? b[0] : (void *)func_020342e8;
        s->field252 = b[1] ? b[1] : (void *)func_020343cc;
    }
    NNS_FndInitList(s->field8, 0x18);
    NNS_FndInitList(s->field20, 0x18);
    NNS_FndInitList(s->field32, 0x10);
}
