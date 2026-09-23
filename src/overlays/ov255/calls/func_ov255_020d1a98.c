/* Message handler of the ov255 partner object (+0x1c): kind-5 messages 0 and 1 play its pairs 0
 * and 1 (+0x3c0 table, kind 0x17) at the message point, 2 and 3 start and stop the +0x3c4 effect;
 * every message then goes to the common handler. */
typedef unsigned char u8;
struct Pair { int res; int handle; };

extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern void func_ov255_020d27cc(int effect);
extern void func_ov255_020d280c(int effect);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

#define PAIRS (*(struct Pair **)(self + 0x3c0))

void func_ov255_020d1a98(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            PAIRS[0].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[0].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 1:
            PAIRS[1].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[1].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 2:
            func_ov255_020d27cc(*(int *)(self + 0x3c4));
            break;
        case 3:
            func_ov255_020d280c(*(int *)(self + 0x3c4));
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
