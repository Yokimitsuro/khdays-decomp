/* Rebind the ov146 actor's +0x388 animation slot to record `id` + 0xc of its +0x3b4 set in the +0x384
 * rig's +0x88 bank, then play layer 0 (and layer 2 for kinds 8/9, +0x310) with `loop` and reset the
 * rig pose. */
typedef struct { char data[0x24]; } AnimSlot;

extern void func_0202a440(AnimSlot *slot);
extern void func_02014b5c(int a, int b);
extern void *func_ov107_020c9440(int set, int index);
extern void func_0202a388(AnimSlot *slot, int bank, void *record, int d);
extern void func_0203b9ac(int rig, AnimSlot *slot);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);

void func_ov146_020ce564(char *actor, int id, int loop)
{
    int bank = *(int *)(*(int *)(actor + 0x384) + 0x88);

    func_0202a440((AnimSlot *)(actor + 0x388));
    func_02014b5c(bank + 0x20, *(int *)(bank + 0x78));
    func_0202a388((AnimSlot *)(actor + 0x388), bank, func_ov107_020c9440(*(int *)(actor + 0x3b4), id + 0xc), 0xc);
    func_0203b9ac(*(int *)(actor + 0x384), (AnimSlot *)(actor + 0x388));
    func_0203b9fc(*(int *)(actor + 0x384), 0, 0, loop);
    if (!(*(signed char *)(actor + 0x310) != 8 && *(signed char *)(actor + 0x310) != 9)) {
        func_0203b9fc(*(int *)(actor + 0x384), 2, 0, loop);
    }
    func_0203c7ac(*(int *)(actor + 0x384), 0);
}
