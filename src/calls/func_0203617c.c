/* func_0203617c -- key auto-repeat, MAIN. Clears the repeat mask (+0x00), scales the repeat delay
 * (+0x02) and interval (+0x04) by the frame-rate mode (func_02023c40: 0 -> 2, 1 -> 3, 2 -> 1) and walks
 * the ten keys of the key table (data_0204222c). A key held now (data_0204c18c) that was pressed this
 * frame (data_0204c190) repeats at once and restarts its counter (+0x06 + key * 2); otherwise, once the
 * time since its press (VBlank count minus the per-key press stamp data_0204c194, indexed through
 * data_02042218) passes the delay, each full interval past the delay beyond the counter's step fires
 * a repeat and the counter becomes the number of intervals elapsed plus one. */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct KeyRepeat {
    u16 mask;                           /* +0x00 */
    u16 delay;                          /* +0x02 */
    u16 interval;                       /* +0x04 */
    u16 count[10];                      /* +0x06 */
} KeyRepeat;

extern const u16 data_0204222c[];       /* key bit per slot */
extern const u16 data_02042218[];       /* press-stamp index per slot */
extern u32 data_0204c194[];             /* VBlank count at each key's press */
extern u16 data_0204c18c;               /* keys held */
extern u16 data_0204c190;               /* keys pressed this frame */

extern int func_02023c40(void);         /* frame-rate mode */
extern u32 OS_IsThreadAvailable(void);  /* VBlank count */
extern u32 func_0202060c(u32 numer, u32 denom);

void func_0203617c(KeyRepeat *kr)
{
    int i;
    u32 now;
    int speed;

    kr->mask = 0;
    switch (func_02023c40()) {
    case 0:
        speed = 2;
        break;
    case 1:
        speed = 3;
        break;
    case 2:
        speed = 1;
        break;
    }
    now = OS_IsThreadAvailable();
    for (i = 0; i < 10; i++) {
        u16 bit = data_0204222c[i];

        if (data_0204c18c & bit) {
            if (data_0204c190 & bit) {
                kr->mask |= bit;
                kr->count[i] = 0;
            } else {
                u32 elapsed = now - data_0204c194[data_02042218[i]];
                u32 delay = kr->delay * speed;

                if (elapsed >= delay) {
                    elapsed -= delay;
                    if (elapsed >= kr->interval * speed * kr->count[i]) {
                        kr->mask |= bit;
                        kr->count[i] = func_0202060c(elapsed, kr->interval * speed) + 1;
                    }
                }
            }
        }
    }
}
