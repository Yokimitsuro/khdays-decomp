/* c634 init (chase variant): reset owner status bytes (+0x1c6=0, +0x1c7=-1), cache owner+0xb0
 * into obj[1] and the owner's +0x384 list's +0x3ec entry (+4) into obj[2], seed the three
 * 16-byte pose blocks at obj+0x20 / +0x50 / +0x40 from the shared constant vec data_020420f8,
 * then arm the three phase callbacks (slots 1/0/2). */
struct vec4 { int a, b, c, d; };
extern const struct vec4 data_020420f8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov213_020d0b70(void);
extern void func_ov213_020d0a6c(void);
extern void func_ov213_020d0b10(void);
void func_ov213_020d09a8(int self) {
    int *obj = *(int **)(self + 4);
    struct vec4 seed;
    *(char *)(*obj + 0x1c6) = 0;
    *(char *)(*obj + 0x1c7) = -1;
    obj[1] = *obj + 0xb0;
    obj[2] = *(int *)(*(int *)(*obj + 0x384) + 0x3ec) + 4;
    seed = data_020420f8;
    *(struct vec4 *)(obj + 8) = seed;
    *(struct vec4 *)(obj + 0x14) = seed;
    *(struct vec4 *)(obj + 0x10) = seed;
    func_0203c634(self, 1, &func_ov213_020d0b70);
    func_0203c634(self, 0, &func_ov213_020d0a6c);
    func_0203c634(self, 2, &func_ov213_020d0b10);
}
