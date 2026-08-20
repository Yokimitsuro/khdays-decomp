typedef unsigned short u16;

extern long long func_02020400(int nValue, unsigned char nUnit);
extern /* Retire a timed element.
 *
 * Unbinds its animation tracks and disables its scene node when it owns a
 * table, then rewrites bit 0 of its game state field from the track index,
 * clears the phase back to counting down and reloads the countdown from the
 * owner's limit.
 *
 * The helper at 0x02020400 returns a 64 bit value and only its high word is
 * used, which is why the original looks as though it leaves a register unset
 * at the first call inside the branch.
 *
 * The write-back is spelled the opposite way round to the ARM members of this
 * family: here the shift up by 16 must be computed before the second query,
 * with the shift down by 15 after it, and the index term has to sit on the
 * left of the or so it is evaluated first. */
void func_ov002_0207c618(short *pTable, int nTime, int nMode);
extern void func_0202af2c(u16 *pNode);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_020235e8(u16 nId, unsigned char nSlot, u16 wState);

/* Retire a timed element.
 *
 * Unbinds its animation tracks and disables its scene node when it owns a
 * table, then rewrites bit 0 of its game state field from the track index,
 * clears the phase back to counting down and reloads the countdown from the
 * owner's limit.
 *
 * The helper at 0x02020400 returns a 64 bit value and only its high word is
 * used, which is why the original looks as though it leaves a register unset
 * at the first call inside the branch.
 *
 * The write-back is spelled the opposite way round to the ARM members of this
 * family: here the shift up by 16 must be computed before the second query,
 * with the shift down by 15 after it, and the index term has to sit on the
 * left of the or so it is evaluated first. */
void func_ov002_0207903c(char *pElement)
{
    char *pOwner;
    unsigned int nState;
    unsigned int nRaw;
    unsigned int nNew;
    u16 wNew;
    unsigned int nLimit;
    long long qPos;

    qPos = func_02020400(*(unsigned char *)(pElement + 0x1b8) << 1,
                         *(unsigned char *)(pElement + 0x1ba));

    pOwner = *(char **)(pElement + 8);

    if ((*(u16 *)(pElement + 0x12) & 4) != 0) {
        func_ov002_0207c618((short *)(pElement + 0x3c), (int)(qPos >> 32), 0);
        func_0202af2c((u16 *)(pElement + 0x3c));
        *(unsigned char *)(pElement + 0x1bb) |= 1;
    }

    nState = ((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                   *(unsigned char *)(pElement + 0x16))
                             & 0xfffe) << 15) >> 16;
    nNew = ((*(unsigned char *)(pElement + 0x1b8) & 1) | (nState & ~1)) << 16;

    nRaw = func_020235d0(*(u16 *)(pElement + 0x14),
                         *(unsigned char *)(pElement + 0x16));
    wNew = (u16)((nNew >> 15) | (nRaw & 0xffff0001));

    func_020235e8(*(u16 *)(pElement + 0x14),
                  *(unsigned char *)(pElement + 0x16), wNew);

    *(unsigned char *)(pElement + 0x1b9) = 0;

    nLimit = *(u16 *)(pOwner + 0x7c);
    if (nLimit != 0) {
        *(unsigned int *)(pElement + 0x1b0) = nLimit << 12;
    }
}
