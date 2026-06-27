extern int GFXi_EnqueueCommand(int a, int b, int c, int d);

typedef struct {
    char _0[0xc];
    int field_c;
    int field_10;
    int field_14;
    int *field_18;
} S_020300f8;

int func_020300f8(S_020300f8 *p) {
    return GFXi_EnqueueCommand(p->field_14, p->field_10, p->field_18[0x20 / 4], p->field_c);
}
