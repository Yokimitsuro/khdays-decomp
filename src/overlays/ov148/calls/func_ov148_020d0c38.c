/* Four forms from codegen-cracks.md, all needed:
 *  - hw60 `hi |= 0x80` uses the EXPLICIT extract/reassemble (no lsl#0x10/lsr#0x10 pair);
 *  - hw60 `hi &= ~0xc` uses the BITFIELD (it does have the pair). The two opposite forms
 *    back to back, exactly as in ov119 020ccef4.
 *  - the `&= ~1` at +8 is a BYTE field, so it needs a real bitfield type;
 *  - func_ov107_020c0b90 takes the vec BY VALUE. */
struct vec { int x, y, z; };
typedef struct { unsigned short lo : 8, hi : 8; } Hw60;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;

extern void func_ov107_020c5af8();
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract();
extern int  func_020050b4(int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern struct vec data_02041dc8;
extern void func_ov148_020d0d84(void);

void func_ov148_020d0c38(int self) {
    int *obj = *(int **)(self + 4);
    int v[3];
    int target;
    unsigned short w;

    w = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    ((Hw60 *)(*obj + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*obj + 0x1ae) |= 1;
    ((Byte8 *)(*(int *)(*obj + 0x38c) + 8))->lo &= ~1;
    func_ov107_020c5af8(*obj, 0, 0x48, *obj + 0x74);
    func_ov107_020c0b90(*obj, 2, data_02041dc8, 0);
    *(int *)(*obj + 0x394) = func_ov107_020cab14(*obj, 0);
    target = *(int *)(*obj + 0x394);
    if (target != 0) {
        VEC_Subtract(target + 0x74, *obj + 0x74, v);
        obj[0xe] = func_020050b4(v[0], v[2]);
        obj[0xd] = obj[0xe];
    }
    obj[0x10] = 0;
    *(signed char *)((int)obj + 0x45) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov148_020d0d84);
}
