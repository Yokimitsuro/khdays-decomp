/* Per-frame cue of the ov266 enemy's sub-state: the +0x5dc timer accumulates the owner's rate;
 * between 0xaa0 and 0xd48 reaction 0x15e mode 4 fires once (latched at +0x5e0) at the given
 * point, and between 0x2a8 and 0x550 mode 5 fires once (latched at +0x5e1). */
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);

void func_ov267_020d1d38(int *node, unsigned char *actor, void *at)
{
    *(int *)(actor + 0x5dc) += *(int *)(node[0] + 0x2c);
    if (*(int *)(actor + 0x5dc) >= 0xaa0 && *(int *)(actor + 0x5dc) <= 0xd48 && actor[0x5e0] == 0) {
        func_ov107_020c5af8((int)actor, 0x15e, 4, at);
        actor[0x5e0] = 1;
    }
    if (*(int *)(actor + 0x5dc) >= 0x2a8 && *(int *)(actor + 0x5dc) <= 0x550 && actor[0x5e1] == 0) {
        func_ov107_020c5af8((int)actor, 0x15e, 5, at);
        actor[0x5e1] = 1;
    }
}
