/* Rebuild the ov252 actor's armour models for damage `level`: the current armour's (+0x310) other pieces
 * record their animation frames (020cd620), every bound slot is released (0202a440) and the +0x88 bank
 * resets, each live piece (+0x39c) rebinds to its model record (020c9440, id + 1), the armour's
 * animation resumes (020cd6b0: piece 1 for 0x2f-0x30, 2 for 0x31-0x34, 3 for 0x35-0x38, else 0), and the
 * five body parts (+0x388..+0x398, slots +0x430..+0x4c0) take their level poses (020cd5a8) below 0x2f
 * (only the first at 0x2e). */
typedef unsigned char u8;
typedef struct { u8 b0 : 1; } Bit0;
typedef struct { char pad0[0xc]; int bound; char pad10[0x14]; } AnimSlot;
struct Ov252Rig { char pad[0x3a0]; AnimSlot slots[4]; };

extern void func_ov252_020cd620(char *actor, signed char which, int *frames);
extern void func_0202a440(AnimSlot *slot);
extern void func_02014b5c(int a, int b);
extern void *func_ov107_020c9440(char *actor, int index);
extern void func_0202a388(AnimSlot *slot, int bank, void *record, int d);
extern void func_ov252_020cd6b0(char *actor, signed char which, int *frames);
extern void func_ov252_020cd5a8(int rig, char *list, void *pose, int flag);

/* Model record of armour kind `k`; every range (piece 0 below 0x2f, 1 below 0x31, 2 below 0x35, 3)
 * maps to k + 1. */
static inline int ArmourModelId(int k)
{
    return k < 0x2f ? k + 1 : k < 0x31 ? k + 1 : k < 0x35 ? k + 1 : k + 1;
}

void func_ov252_020cd808(char *actor, int level)
{
    int bank = *(int *)(*(int *)(actor + 0x384) + 0x88);
    int frames[4] = {0};
    int i;
    signed char k;

    k = *(signed char *)(actor + 0x310);
    if (k < 0x2f) {
        func_ov252_020cd620(actor, 0, frames);
    } else if (k < 0x31) {
        func_ov252_020cd620(actor, 1, frames);
    } else if (k < 0x35) {
        func_ov252_020cd620(actor, 2, frames);
    } else {
        func_ov252_020cd620(actor, 3, frames);
    }
    for (i = 0; i < 4; i++) {
        if (((struct Ov252Rig *)actor)->slots[i].bound != 0) {
            func_0202a440(&((struct Ov252Rig *)actor)->slots[i]);
        }
    }
    func_02014b5c(bank + 0x20, *(int *)(bank + 0x78));
    for (i = 0; i < 4; i++) {
        k = *(signed char *)(actor + i + 0x39c);
        if (k >= 0) {
            func_0202a388(&((struct Ov252Rig *)actor)->slots[i], bank, func_ov107_020c9440(actor, ArmourModelId(k)), 0xc);
        }
    }
    switch (*(signed char *)(actor + 0x310)) {
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
        func_ov252_020cd6b0(actor, 3, frames);
        break;
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
        func_ov252_020cd6b0(actor, 2, frames);
        break;
    case 0x2f:
    case 0x30:
        func_ov252_020cd6b0(actor, 1, frames);
        break;
    default:
        func_ov252_020cd6b0(actor, 0, frames);
        break;
    }
    if (level >= 0x2f) {
        return;
    }
    func_ov252_020cd5a8(*(int *)(actor + 0x388), actor + 0x430, func_ov107_020c9440(actor, level + 0x3b),
                        ((Bit0 *)(actor + 0x311))->b0);
    if (level >= 0x2e) {
        return;
    }
    func_ov252_020cd5a8(*(int *)(actor + 0x38c), actor + 0x454, func_ov107_020c9440(actor, level + 0x6b),
                        ((Bit0 *)(actor + 0x311))->b0);
    func_ov252_020cd5a8(*(int *)(actor + 0x390), actor + 0x478, func_ov107_020c9440(actor, level + 0x9a),
                        ((Bit0 *)(actor + 0x311))->b0);
    func_ov252_020cd5a8(*(int *)(actor + 0x394), actor + 0x49c, func_ov107_020c9440(actor, level + 0xc9),
                        ((Bit0 *)(actor + 0x311))->b0);
    func_ov252_020cd5a8(*(int *)(actor + 0x398), actor + 0x4c0, func_ov107_020c9440(actor, level + 0xf8),
                        ((Bit0 *)(actor + 0x311))->b0);
}
