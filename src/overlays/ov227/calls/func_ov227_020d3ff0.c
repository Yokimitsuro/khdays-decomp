/* Effect message hook of an ov227 part: a "spawned" message (kind 5) picks by byte 3 -- slot 0
 * anchors effect 0x17 of the +0x390 pair table on the +0xa0 pose (byte 4 as flag), slot 1 spawns
 * it at the packed position (bytes 5..) scaled 0.67. The base hook always runs. */
typedef unsigned char u8;
struct Pair { int res; int handle; };
struct Ov227Part { char pad[0x390]; struct Pair pairs[2]; };

extern int func_ov107_020c09a0(int model, int res, int kind, void *at, u8 flag, int loop);
extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov227_020d3ff0(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            ((struct Ov227Part *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov227Part *)self)->pairs[msg[3]].res, 0x17,
                                    self + 0xa0, msg[4], 0);
            break;
        case 1:
            ((struct Ov227Part *)self)->pairs[msg[3]].handle =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Ov227Part *)self)->pairs[msg[3]].res, 0x17, 0,
                                    0xaaa, msg + 5);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
