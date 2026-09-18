/* Animation switch of the ov298 enemy (and its ov297 twin): the +0x384 item plays the +0x310
 * animation with the +0x311 bit-0 blend, and for kinds 1-4 the +0x388 item's channels 0/2/1
 * play animation kind - 1 with the given blend before it refreshes. */
typedef unsigned char u8;
struct Bits311 { u8 bit0 : 1; };

extern void func_0203b9fc(int item, int channel, short anim, u8 blend);
extern void func_0203c7ac(int item, int a);

void func_ov297_020d3cb4(char *actor, int kind, u8 blend)
{
    int anim = -1;

    func_0203b9fc(*(int *)(actor + 0x384), 0, *(signed char *)(actor + 0x310), ((struct Bits311 *)(actor + 0x311))->bit0);
    func_0203c7ac(*(int *)(actor + 0x384), 0);
    switch (kind) {
    case 1:
        anim = 0;
        break;
    case 2:
        anim = 1;
        break;
    case 3:
        anim = 2;
        break;
    case 4:
        anim = 3;
        break;
    }
    if (anim < 0) {
        return;
    }
    func_0203b9fc(*(int *)(actor + 0x388), 0, anim, blend);
    func_0203b9fc(*(int *)(actor + 0x388), 2, anim, blend);
    func_0203b9fc(*(int *)(actor + 0x388), 1, anim, blend);
    func_0203c7ac(*(int *)(actor + 0x388), 0);
}
