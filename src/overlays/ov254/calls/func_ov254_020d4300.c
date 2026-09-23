/* Message handler of an ov254 helper: a "spawned" message (kind 5) of sub-kind 0 starts the +0x390
 * pair's effect (kind 0x17, weight 1.0, the packet's payload) into its handle; the base handler
 * always runs. */
typedef unsigned char u8;
struct Pairs { char pad[0x390]; struct { int res; int handle; } pair[1]; };

extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov254_020d4300(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            ((struct Pairs *)self)->pair[msg[3]].handle =
                func_ov107_020c08cc(*(int *)(self + 0x3c), ((struct Pairs *)self)->pair[msg[3]].res, 0x17, 0, 0x1000, msg + 5);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
