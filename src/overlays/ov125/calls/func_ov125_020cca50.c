/* c634 init of the ov125 enemy: reset owner status bytes (+0x1c6=0, +0x1c7=-1), drop bit 0 of
 * the +0x388 target's +8 word, cache owner+0xb0 / owner+0x74 / the +0x384 list's +0xad flag
 * into obj[8..10], seed the 16-byte pose block at obj+0x58 from the shared constant vec
 * data_020420f8 and copy it to obj+0x68, then arm the three phase callbacks (slots 1/0/2).
 * The seed is loaded at its declaration, ahead of the byte stores (ROM's early ldm). */
struct vec4 { int a, b, c, d; };
struct w8 { unsigned int lo : 8, rest : 24; };
extern const struct vec4 data_020420f8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov125_020ccd64(void);
extern void func_ov125_020ccb24(void);
extern void func_ov125_020cccf0(void);
void func_ov125_020cca50(int self) {
    int *obj = *(int **)(self + 4);
    struct vec4 seed = data_020420f8;
    *(char *)(*obj + 0x1c6) = 0;
    *(char *)(*obj + 0x1c7) = -1;
    ((struct w8 *)(*(int *)(*obj + 0x388) + 8))->lo &= ~1;
    obj[8] = *obj + 0xb0;
    obj[9] = *obj + 0x74;
    obj[0xa] = *(int *)(*obj + 0x384) + 0xad;
    *(struct vec4 *)(obj + 0x16) = seed;
    *(struct vec4 *)(obj + 0x1a) = *(struct vec4 *)(obj + 0x16);
    func_0203c634(self, 1, &func_ov125_020ccd64);
    func_0203c634(self, 0, &func_ov125_020ccb24);
    func_0203c634(self, 2, &func_ov125_020cccf0);
}
