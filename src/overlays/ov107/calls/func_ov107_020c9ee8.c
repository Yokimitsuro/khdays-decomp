/* func_ov107_020c9ee8 -- set bit0, clear bit1, set bit2 to arg's low bit in the flag
 * byte at self+4; store val at self+2; notify the collision/select subsystem. */
extern void func_0203b9fc(int a, int b, short c, int d);
extern void func_ov107_020c9ec8();

typedef struct {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
} Flags4;

void func_ov107_020c9ee8(int self, short val, int arg)
{
    Flags4 *f = (Flags4 *)(self + 4);
    f->bit0 = 1;
    f->bit2 = (unsigned char)arg;
    f->bit1 = 0;
    *(short *)(self + 2) = val;
    func_0203b9fc(*(int *)(self + 0x3c), 0, *(short *)(self + 2), 0);
    func_ov107_020c9ec8(self, 0);
}
