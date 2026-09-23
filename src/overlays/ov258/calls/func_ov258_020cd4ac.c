/* Damage handler of the ov258 actor: the hit's damage (020c89e8, into +0x28) comes off the health
 * (+0x21a, clamped to 0..max); at 0 health the next move is 9. Returns 1. */
extern int func_ov107_020c89e8(char *self, char *hit);

int func_ov258_020cd4ac(char *self, int attacker, char *hit)
{
    int *state = *(int **)(self + 0x214);
    int hp;

    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    hp = *(short *)(self + 0x21a) - *(int *)(hit + 0x28);
    *(short *)(self + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(self + 0x218) ? *(short *)(self + 0x218) : hp);
    if (*(short *)(self + 0x21a) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
    }
    return 1;
}
