/* Message handler of the ov218 actor: a spawn message (kind 5) starts the +0x39c effect pair of sub 0
 * from the payload (kind 5, variant byte 4, scale 1.3), knocks the actor back and clears +0x394, or
 * for sub 1 starts the flash helper (020cf0fc) into pair 1. The base handler always runs. */
typedef unsigned char u8;
struct EffectPair { int res; int handle; };
struct Ov218Effects { char pad[0x39c]; struct EffectPair pair[2]; };

extern int func_ov107_020c08cc(int model, int parent, int kind, int arg, int weight, void *payload);
extern void func_ov107_020c0b14(char *self, int a);
extern int func_ov218_020cf0fc(char *self);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov218_020ce2bc(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            ((struct Ov218Effects *)self)->pair[msg[3]].handle = func_ov107_020c08cc(
                *(int *)(self + 0x3c), ((struct Ov218Effects *)self)->pair[msg[3]].res, 5, msg[4], 0x14cd, msg + 5);
            func_ov107_020c0b14(self, 1);
            *(int *)(self + 0x394) = 0;
            break;
        case 1:
            ((struct Ov218Effects *)self)->pair[msg[3]].handle = func_ov218_020cf0fc(self);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
