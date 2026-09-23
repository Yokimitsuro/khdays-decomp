/* Rebuild the ov238 actor's two-part animation for its current kind (+0x310): the kind is recorded in
 * the front (+0x390, below 0x16) or back (+0x391) slot byte and that part's frame is sampled from the
 * +0x388 rig's +0x88 bank (track 3 / 0); bound slots are released, the bank resets and each live
 * part binds its model record (020c9440: kind + 1, back part 0x12). The current part plays on its
 * track with the +0x311 loop bit, and the other live part resumes at the sampled frame. */
typedef unsigned char u8;
typedef struct { u8 b0 : 1; } Bit0;
typedef struct { char pad0[0xc]; int bound; char pad10[0x14]; } AnimSlot;
struct Ov238Rig { char pad[0x394]; AnimSlot slots[2]; };

extern int func_0202aee0(int bank, int track);
extern void func_0202a440(AnimSlot *slot);
extern void func_02014b5c(int a, int b);
extern void *func_ov107_020c9440(char *actor, int index);
extern void func_0202a388(AnimSlot *slot, int bank, void *record, int d);
extern void func_0203b9ac(int rig, AnimSlot *slot);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_01fff774(int bank, int track, int frame);
extern void func_0203c7ac(int rig, int a);

void func_ov238_020d0128(char *actor)
{
    signed char kind = *(signed char *)(actor + 0x310);
    int bank = *(int *)(*(int *)(actor + 0x388) + 0x88);
    int frame;
    int i;
    signed char k;

    if (kind < 0x16) {
        *(signed char *)(actor + 0x390) = kind;
        frame = func_0202aee0(bank, 3);
    } else {
        *(signed char *)(actor + 0x391) = kind;
        frame = func_0202aee0(bank, 0);
    }
    for (i = 0; i < 2; i++) {
        if (((struct Ov238Rig *)actor)->slots[i].bound != 0) {
            func_0202a440(&((struct Ov238Rig *)actor)->slots[i]);
        }
    }
    func_02014b5c(bank + 0x20, *(int *)(bank + 0x78));
    for (i = 0; i < 2; i++) {
        k = *(signed char *)(actor + i + 0x390);
        if (k >= 0) {
            func_0202a388(&((struct Ov238Rig *)actor)->slots[i], bank,
                          func_ov107_020c9440(actor, k < 0x16 ? k + 1 : 0x12), 0xc);
        }
    }
    if (*(signed char *)(actor + 0x310) == 0x16) {
        func_0203b9ac(*(int *)(actor + 0x388), &((struct Ov238Rig *)actor)->slots[1]);
        func_0203b9fc(*(int *)(actor + 0x388), 3, 0, ((Bit0 *)(actor + 0x311))->b0);
        if (*(signed char *)(actor + 0x390) >= 0) {
            *(AnimSlot **)(*(int *)(actor + 0x388) + 0x8c) = &((struct Ov238Rig *)actor)->slots[0];
            func_0203b9fc(*(int *)(actor + 0x388), 0, 0, *(u8 *)(*(int *)(actor + 0x388) + 0xa8));
            func_01fff774(bank, 0, frame);
        }
    } else {
        func_0203b9ac(*(int *)(actor + 0x388), &((struct Ov238Rig *)actor)->slots[0]);
        func_0203b9fc(*(int *)(actor + 0x388), 0, 0, ((Bit0 *)(actor + 0x311))->b0);
        if (*(signed char *)(actor + 0x391) >= 0) {
            *(AnimSlot **)(*(int *)(actor + 0x388) + 0x8c) = &((struct Ov238Rig *)actor)->slots[1];
            func_0203b9fc(*(int *)(actor + 0x388), 3, 0, *(u8 *)(*(int *)(actor + 0x388) + 0xab));
            func_01fff774(bank, 3, frame);
        }
    }
    func_0203c7ac(*(int *)(actor + 0x388), 0);
}
