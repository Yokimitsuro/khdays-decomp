/* Message handler of an ov254 helper: on channel-5 messages it attaches effects to the +0x4e8
 * pairs (kind 0x17 at the message's position for slots 0-2, 4 and 6; kind 0x17 on the +0x40c /
 * +0x410 part for slots 7 / 3; kind 5 on its own +0xa0 pose for slot 5, message byte 4 as the
 * variant), knocks itself back in place (0xa), attaches / releases the +0x4e4 sound 0x16d (0xb /
 * 0xc) or forwards byte 4 to the camera's +0x78 handler (0xd); then the base handler runs. */
typedef unsigned char u8;
struct Pairs { char pad[0x4e8]; struct { int res; int handle; } pair[1]; };

extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern void func_ov107_020c0b14(char *self, int a);
extern int func_ov107_020cb040(char *self, int id, int mode, int flag, void *pose);
extern void func_ov107_020cb100(int sub);
extern int OS_IsThreadAvailable_0x020c9848();
extern int func_ov022_02083f0c(void);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov254_020cc7e0(char *self, u8 *msg, int arg)
{
    int obj;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 6:
            ((struct Pairs *)self)->pair[msg[3]].handle =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Pairs *)self)->pair[msg[3]].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 3:
        case 7:
            ((struct Pairs *)self)->pair[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Pairs *)self)->pair[msg[3]].res, 0x17,
                                    (void *)(((int *)(self + 0x40c))[msg[3] != 7] + 4), 0, 0);
            break;
        case 5:
            ((struct Pairs *)self)->pair[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Pairs *)self)->pair[msg[3]].res, 5,
                                    self + 0xa0, msg[4], msg[4] == 1);
            break;
        case 0xa:
            func_ov107_020c0b14(self, 1);
            break;
        case 0xb:
            *(int *)(self + 0x4e4) = func_ov107_020cb040(self, 0x16d, 0x14, 1, self + 0xa0);
            break;
        case 0xc:
            if (*(int *)(self + 0x4e4) != 0) {
                func_ov107_020cb100(*(int *)(self + 0x4e4));
                *(int *)(self + 0x4e4) = 0;
            }
            break;
        case 0xd:
            if (*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x78) != 0) {
                obj = OS_IsThreadAvailable_0x020c9848();
                (*(void (**)(int, int, int))(obj + 0x78))(func_ov022_02083f0c(), msg[4], 0);
            }
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
