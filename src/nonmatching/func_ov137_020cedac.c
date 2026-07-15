/* NONMATCHING (scheduling tie, 10-member byte-identical family ov137/138/158/159/160/
 * 228/229/233/246/247): body + hw60 bitfield math are exact, but the ROM stages the
 * 3-word data_02041dc8 block in r0-r2 across the whole function (ldm early / stm late)
 * and defers the call-arg setup; mwcc keeps the ldm/stm adjacent and hoists the args.
 * c634 handler: owner hw60 hi-byte bit0 clear then |=0x82, clear bit0 of low byte at
 * *(owner+0x388)+8, copy shared 3-word constant into obj[2..4], dispatch func_0203c634. */
extern void func_0203c634(int self, int index, void *cb);
extern int data_02041dc8[3];
extern void func_ov137_020cee5c(void);
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int b:8; };
struct three { int a, b, c; };
void func_ov137_020cedac(int self) {
    int *obj = *(int **)(self + 4);
    ((struct hw60 *)(*obj + 0x60))->hi &= ~1;
    ((struct hw60 *)(*obj + 0x60))->hi |= 0x82;
    *(struct three *)(obj + 2) = *(struct three *)data_02041dc8;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b &= ~1;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov137_020cee5c);
}
