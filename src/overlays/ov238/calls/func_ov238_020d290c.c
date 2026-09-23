/* Message handler of the ov238 actor: a spawn message (kind 5, sub 0) attaches its +0x3a4 effect to the
 * actor pose (+0xa0, variant byte 4) into +0x3a8; the base handler always runs. */
typedef unsigned char u8;

extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov238_020d290c(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            *(int *)(self + 0x3a8) = func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(self + 0x3a4), 5,
                                                         self + 0xa0, msg[4], 1);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
