/* Message handler of the ov218 actor's +0x3dc effect set: a spawn message (kind 5) starts pair 0 from
 * the payload (kind 5, scale 1.3), attaches pair 1 to the +0x3b0 shadow transform (kind 0x15), or for
 * sub 3 stops pair `byte 4`. The base handler always runs. */
typedef unsigned char u8;
struct EffectPair { int res; int handle; };
struct Ov218Set { char pad[0x3dc]; struct EffectPair pair[4]; };

extern int func_ov107_020c08cc(int model, int parent, int kind, int arg, int weight, void *payload);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_0203c650(int model, int handle);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov218_020cc3f4(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            ((struct Ov218Set *)self)->pair[msg[3]].handle = func_ov107_020c08cc(
                *(int *)(self + 0x3c), ((struct Ov218Set *)self)->pair[msg[3]].res, 5, 0, 0x14cd, msg + 5);
            break;
        case 1:
            ((struct Ov218Set *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), ((struct Ov218Set *)self)->pair[msg[3]].res, 0x15, self + 0x3b0, 0, 1);
            break;
        case 3:
            if (((struct Ov218Set *)self)->pair[msg[4]].handle != 0) {
                func_0203c650(*(int *)(self + 0x3c), ((struct Ov218Set *)self)->pair[msg[4]].handle);
                ((struct Ov218Set *)self)->pair[msg[4]].handle = 0;
            }
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
