/* Re-bind the +0x384 rig's channels 0, 2 and 4 to the +0x310 mode with the +0x311 bit-0 flag and
 * re-init it. */
typedef unsigned char u8;
struct Flag311 { u8 b0 : 1; };

extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);

void func_ov254_020d1aa8(char *self)
{
    func_0203b9fc(*(int *)(self + 0x384), 0, *(signed char *)(self + 0x300 + 0x10), ((struct Flag311 *)(self + 0x311))->b0);
    func_0203b9fc(*(int *)(self + 0x384), 2, *(signed char *)(self + 0x300 + 0x10), ((struct Flag311 *)(self + 0x311))->b0);
    func_0203b9fc(*(int *)(self + 0x384), 4, *(signed char *)(self + 0x300 + 0x10), ((struct Flag311 *)(self + 0x311))->b0);
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
