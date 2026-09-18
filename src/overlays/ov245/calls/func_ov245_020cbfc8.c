/* func_ov245_020cbfc8 -- wing pose: for each of the two +0x388 wings, copies bit 1 of the
 * +0x384 body's +0x5c into the wing's +0x5c, builds the +0x4d0 angle rotation about 02042270
 * (0202f188), combines it with the +0x450 anchor's +4 rotation (0202ef54) into the wing's +0x30
 * placement (0203c9d0) and sets its translation to the anchor's +0x14 (0203ca30). */
struct Bit1 { int bit0 : 1, bit1 : 1; };
struct Ov245Wings {
    char pad[0x388];
    int wings[2];
};

extern void func_0202f188(void *out, void *tbl, int angle);
extern void func_0202ef54(void *out, void *a, void *b);
extern void func_0203c9d0(int placement, void *rotation);
extern void func_0203ca30(int placement, void *translation);
extern char data_02042270[];

void func_ov245_020cbfc8(int unused, char *self) {
    int rot[4];
    int i;

    for (i = 0; i < 2; i++) {
        ((struct Bit1 *)(((struct Ov245Wings *)self)->wings[i] + 0x5c))->bit1 =
            ((struct Bit1 *)(*(int *)(self + 0x384) + 0x5c))->bit1;
        func_0202f188(rot, data_02042270, ((int *)(self + 0x4d0))[i]);
        func_0202ef54(rot, rot, (void *)(((int *)(self + 0x450))[i] + 4));
        func_0203c9d0(((struct Ov245Wings *)self)->wings[i] + 0x30, rot);
        func_0203ca30(((struct Ov245Wings *)self)->wings[i] + 0x30, (void *)(((int *)(self + 0x450))[i] + 0x14));
    }
}
