/* func_ov253_020cca7c -- point the object at the angle its facing byte (+0x450) names: the byte is
 * scaled by 0x6488 (a quarter turn per unit / 4) and applied to the transform at +0xa0, then the
 * hit box at +0x3a8 and the base handler are told about the change.
 * The `/ 4` is a SIGNED divide -- that is the ROM's `asr #1 ; add lsr #30 ; asr #2` triple, not a
 * shift. */
extern void func_0203c9b4(int dst, void *src, int v);
extern void func_0202a818(int a, int b);
extern void func_ov107_020c6980(int obj, int arg);
extern int data_02042264;

void func_ov253_020cca7c(int obj, int arg) {
    func_0203c9b4(obj + 0xa0, &data_02042264,
                  *(signed char *)(obj + 0x450) * 0x6488 / 4);
    func_0202a818(*(int *)(*(int *)(obj + 0x3a8) + 0x88), arg);
    func_ov107_020c6980(obj, arg);
}
