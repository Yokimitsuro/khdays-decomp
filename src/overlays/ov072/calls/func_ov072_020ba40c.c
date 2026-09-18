/* Fire attempt of the ov032 enemy (and its byte-identical twins): clears bit 7 of the +0x24
 * flags, raises bit 16 of both 64-bit effect words (+0x464, +0x46c) on the local player's
 * session, marks the actor unrestricted (bit 46) with a cleared +0x58 unless bit 2 of +0x24
 * is set, then asks the +0x668 handler whether the shot fires. A fired shot sets bit 49,
 * restarts the model's animation unless its bit 5 is set, raises bit 1 of the +0x464 word on
 * the local session, clears the six velocity words and reports the state through 020a35f4
 * (after the +0x664 handler when bit 2 of +0x24 is set). */
struct ActorBits {
    unsigned char bUnk0 : 1;
    unsigned char bFired : 1;
};

extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_0202af1c(int *p);
extern int func_ov022_020a35f4(char *self, int mode);

int func_ov072_020ba40c(char *self)
{
    int nRet = 0;

    *(int *)(self + 0x24) &= ~0x80;
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    ((struct ActorBits *)(self + 0x694))->bFired = (*(int (**)(char *))(self + 0x668))(self);
    if (((struct ActorBits *)(self + 0x694))->bFired) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        if ((**(int **)(self + 0x20) & 0x20) == 0) {
            func_0202af1c(*(int **)(self + 0x20) + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2ULL;
        }
    }
    if (((struct ActorBits *)(self + 0x694))->bFired) {
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4ULL;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            nRet = func_ov022_020a35f4(self, 0);
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
        } else {
            nRet = func_ov022_020a35f4(self, 2);
        }
    }
    return nRet;
}
