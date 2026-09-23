/* Send the 14-byte "kind 5, command 0xd" message for the actor's +2 id with the given argument
 * byte through the shared queue (02031384, channel 1). */
typedef unsigned char u8;
typedef unsigned short u16;
struct Msg14 { u16 h[7]; };

extern void func_02031384(int channel, void *msg, int size);

void func_ov254_020cd920(int *self, int arg)
{
    struct Msg14 msg;
    u16 *p = (u16 *)&msg;

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[0] = *(u16 *)(self[0] + 2);
    ((u8 *)p)[2] = 5;
    ((u8 *)p)[3] = 0xd;
    ((u8 *)&msg)[4] = arg;
    func_02031384(1, p, 0xe);
}
