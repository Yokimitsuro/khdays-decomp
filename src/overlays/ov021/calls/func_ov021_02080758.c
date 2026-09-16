/* func_ov021_02080758 -- Ov021_EmblemFindPlayer: the first player (0..ov022 020882f8) within
 * reach of the emblem, or -1.  Nothing while the shutdown hook says so (ov002 0206b7a4) or
 * outside a running scene (0206b758).  The reach is 0x3000 in mission 0x3b7 (ov002 0206b84c)
 * and 0x1800 elsewhere; a player counts when its actor (01fffde0) has bit 16 of its 64-bit
 * flags clear, owns a slot (ov022 02088474), sits in the emblem's bucket (the bucket's current
 * piece kind, ov002 02072754) and its seat (ov022 020881f8) is within reach of the emblem's
 * position (+0x2a8, VEC_Distance 01ff8e94). */
typedef unsigned char  u8;
typedef unsigned long long u64;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021PlayerActor {
    u64  nFlags;              /* 0x00: bit 16 = out of play */
} Ov021PlayerActor;

typedef struct Ov021Emblem {
    u8   pad_000[0x10];
    u8   nBucket;             /* 0x010 */
    u8   pad_011[0x2a8 - 0x11];
    VecFx32 position;         /* 0x2a8 */
} Ov021Emblem;

extern int   func_ov002_0206b7a4(void);                               /* the shutdown hook's verdict */
extern int   func_ov002_0206b758(void);                               /* scene running? */
extern int   func_ov002_0206b84c(void);                               /* the mission id */
extern int   func_ov022_020882f8(void);                               /* number of players */
extern Ov021PlayerActor *func_01fffde0(int nPlayer);                  /* the player's actor */
extern int   func_ov022_02088474(int nSeat);                          /* seat -> owner slot */
extern int   func_ov002_02072754(void);                               /* current piece kind */
extern VecFx32 *func_ov022_020881f8(int nSeat);                       /* where the seat is */
extern int   func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                 /* VEC_Distance */

int func_ov021_02080758(Ov021Emblem *pSelf)
{
    int nPlayer;
    int nReach;
    Ov021PlayerActor *pActor;

    if (func_ov002_0206b7a4() == 0 && func_ov002_0206b758() != 0) {
        nReach = func_ov002_0206b84c() == 0x3b7 ? 0x3000 : 0x1800;
        for (nPlayer = 0; nPlayer < func_ov022_020882f8(); nPlayer++) {
            pActor = func_01fffde0(nPlayer);
            if ((pActor->nFlags & 0x10000) == 0 && func_ov022_02088474(nPlayer) >= 0 && pSelf->nBucket == func_ov002_02072754()) {
                if (func_01ff8e94(func_ov022_020881f8(nPlayer), &pSelf->position) <= nReach) {
                    return nPlayer;
                }
            }
        }
    }
    return -1;
}
