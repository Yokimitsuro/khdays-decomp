/* All four forms from codegen-cracks.md: the -1 at +0x1c7 is a SIGNED char store, the
 * `&= ~1` at +8 is a byte BITFIELD, and the hw60 `hi |= 6` takes the EXPLICIT form. */
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov146_020ccd78(void);
extern void func_ov146_020cc8f0(void);
extern void func_ov146_020ccae4(void);

void func_ov146_020cc838(int self) {
    int *obj = *(int **)(self + 4);
    unsigned short w;

    *(signed char *)(*obj + 0x1c6) = 0;
    *(signed char *)(*obj + 0x1c7) = -1;
    ((Byte8 *)(*(int *)(*obj + 0x3ac) + 8))->lo &= ~1;
    obj[3] = *obj + 0xb0;
    w = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    func_0203c634(self, 1, &func_ov146_020ccd78);
    func_0203c634(self, 0, &func_ov146_020cc8f0);
    func_0203c634(self, 2, &func_ov146_020ccae4);
}
