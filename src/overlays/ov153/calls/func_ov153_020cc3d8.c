extern void func_ov107_020c4924(void);
extern void func_0203c9d0(void *dst, void *src);

typedef struct { int f[11]; } Block44;

void func_ov153_020cc3d8(char *obj) {
    Block44 *dst = (Block44 *)(obj + 0x39c);
    Block44 *src = (Block44 *)((char *)*(int **)(obj + 0x38c) + 4);
    func_ov107_020c4924();
    *dst = *src;
    func_0203c9d0(dst, obj + 0xa0);
}
