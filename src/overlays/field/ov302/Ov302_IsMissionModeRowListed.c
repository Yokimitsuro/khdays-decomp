
/* Gate check for a spawn/encounter record at `param_1` against flag word
 * `param_2`: validates the record is active, its zone id is in range and its
 * team matches, then tests several difficulty/level dispatch tables. Returns 1
 * if the record is eligible, else 0. */

#include "game/engine.h"

int Ov302_IsMissionModeRowListed(int param_1, unsigned int param_2) {
    unsigned int bit;
    unsigned int m;

    if (*(unsigned char *)(param_1 + 0x23) == 0) {
        return 0;
    }
    if (*(unsigned short *)(param_1 + 4) >= 0x384) {
        return 0;
    }
    if ((unsigned int)*(unsigned short *)(param_1 + 0xa) != ((param_2 >> 8) & 0xff)) {
        return 0;
    }
    if ((param_2 & 8) != 0 && *(unsigned short *)(param_1 + 2) == 10) {
        return 1;
    }
    if ((param_2 & 3) != 0) {
        unsigned int u = GameState_GetField(0x44e, 3);
        int iv;
        if (6 <= u) {
            iv = 0x191;
        } else {
            iv = GameState_GetField(0, 9);
        }
        if ((int)(unsigned int)*(unsigned short *)(param_1 + 8) >= iv) {
            return 0;
        }
    }
    bit = (param_2 & 0xf) & (1 << (*(unsigned char *)(param_1 + 0x23) - 1));
    m = GameState_GetField((unsigned int)*(unsigned short *)(param_1 + 4) * 4 + 0x92b, 4);
    if ((bit & m) != 0) {
        return 1;
    }
    if ((param_2 & 2) != 0 && *(unsigned char *)(param_1 + 0x23) == 2) {
        unsigned int v = *(unsigned short *)(param_1 + 4);
        if (v > 100) {
            int iv = (int)v;
            int mod = iv % 100;
            if (mod < 0) {
                return 0;
            }
            if (mod >= 0xc8) {
                return 0;
            }
            m = GameState_GetField(mod * 4 + 0x92b, 4);
            if ((bit & m) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
