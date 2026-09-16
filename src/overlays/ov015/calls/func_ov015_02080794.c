/* func_ov015_02080794 -- Ov015_SpotFacingForInteraction: the spot's facing word (+0x28)
 * while the spot is live (bit 1 of +0x40) and the local player's actor is in interaction
 * state 0xc; 0 otherwise.  Sibling of func_ov015_0208075c, which hands out the spot's
 * position (+0x1c) under the same test. */
typedef unsigned char u8;

extern int func_01fffe14(void);                         /* the local peer */
extern void *func_01fffde0(int nPlayer);                /* the player's actor */
extern int func_ov022_020ad61c(void *pActor, int nState); /* the actor is in interaction state nState */

typedef struct Ov015Spot {
    u8  pad_00[0x1c];
    int aPosition[3];         /* 0x1c */
    int nFacing;              /* 0x28 */
    u8  pad_2c[0x40 - 0x2c];
    u8  nFlags;               /* 0x40: bit 1 = the spot is live */
} Ov015Spot;

int func_ov015_02080794(Ov015Spot *pSpot)
{
    if (pSpot->nFlags & 2) {
        if (func_ov022_020ad61c(func_01fffde0(func_01fffe14()), 0xc)) {
            return pSpot->nFacing;
        }
    }
    return 0;
}
