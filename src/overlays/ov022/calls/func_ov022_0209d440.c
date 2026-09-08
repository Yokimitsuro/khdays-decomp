/* Ov022_ChargeGaugeForHit -- take the gauge back off the local player when a hit
 * lands on them.
 *
 * Only the local player pays, only while the mode bit is set, and not at all
 * once the session has moved on. What is charged is a rate on whatever the
 * player still holds: a downed player pays a flat rate that grows with the
 * difficulty, and a standing one pays a rate rolled out of a hundred, which the
 * first mode only reaches on a hit worth more than a fifth of the player's
 * total, while the second mode always pays the same middling rate.
 *
 * The rate is applied to the gauge, never rounding down to nothing, and what was
 * actually taken is reported, capped at a hundred so it fits the packet.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                          /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                         /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                      /* 0x0016 */
};

extern u8 data_0204c240;
extern u8 data_0204c248[];

extern int func_02030788(void);
extern int func_ov002_0206b828(void);
extern int func_ov002_0206bdcc(int nId, int nKind);
extern void func_ov002_0206bbb8(int nId, int nKind, int nDelta);
extern unsigned int func_020307f4(int nRange);
extern void func_ov022_0208a0b4(unsigned int nId, int nKind, int nAmount);

#define MODE_GAUGE 4
#define GAUGE_KIND 7

#define RATE_DOWN_EASY 0x800
#define RATE_DOWN_HARD 0x1000
#define RATE_LOW 0x29
#define RATE_MID 0xcd
#define RATE_HIGH 0x148
#define RATE_FLAT 0x7b

#define ROLL_FLOOR 0x46
#define ROLL_LOW 0x57
#define ROLL_MID 0x60

#define REPORT_CAP 100

void func_ov022_0209d440(struct Actor *pActor, int nDamage, int nDirect)
{
    int nAmount;
    int nRate;
    int nRoll;
    u8 nDifficulty;

    nRate = 0;
    if (func_02030788() != 0) {
        return;
    }
    if ((data_0204c240 & MODE_GAUGE) == 0) {
        return;
    }
    if (func_ov002_0206b828() != 0) {
        return;
    }
    nDifficulty = data_0204c248[0xa];
    nAmount = func_ov002_0206bdcc(pActor->nId, GAUGE_KIND);
    if (pActor->nHp == 0) {
        if (nDifficulty == 1) {
            nRate = RATE_DOWN_EASY;
        } else if (nDifficulty == 2) {
            nRate = RATE_DOWN_HARD;
        }
    } else if (data_0204c248[9] != 1) {
        if (data_0204c248[9] == 2) {
            nRate = RATE_FLAT;
        }
    } else {
        nRoll = func_020307f4(100);
        if (nDirect != 0) {
            if (nRoll >= ROLL_FLOOR) {
                if (nRoll <= ROLL_LOW) {
                    nRate = RATE_LOW;
                } else if (nRoll <= ROLL_MID) {
                    nRate = RATE_MID;
                } else {
                    nRate = RATE_HIGH;
                }
            }
        } else {
            if (nRoll >= ROLL_FLOOR && nDamage > (int)pActor->nHpMax / 5) {
                if (nRoll <= ROLL_LOW) {
                    nRate = RATE_LOW;
                } else if (nRoll <= ROLL_MID) {
                    nRate = RATE_MID;
                } else {
                    nRate = RATE_HIGH;
                }
            }
        }
    }
    if (nAmount <= 0) {
        return;
    }
    if (nRate == 0) {
        return;
    }
    nAmount = (nRate * nAmount + 0xfff) >> 12;
    if (nAmount <= 0) {
        nAmount = 1;
    }
    func_ov002_0206bbb8(pActor->nId, GAUGE_KIND, -nAmount);
    if (nAmount > REPORT_CAP) {
        nAmount = REPORT_CAP;
    }
    func_ov022_0208a0b4(pActor->nId, 0, nAmount);
}
