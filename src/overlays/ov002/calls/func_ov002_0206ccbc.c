typedef unsigned char u8;
typedef unsigned int u32;

/* Ghidra models this as Ov002PanelThresholds at g_ov002PanelThresholds;
   the delink names the same address data_0204c254. */
typedef struct Ov002PanelThresholds {
    char pad000[0x10];
    u32 aThresh[3];                 /* +0x10 */
} Ov002PanelThresholds;

extern u8 data_0204c240;                /* g_modeAndDayClock; bit 1 gates this */
extern Ov002PanelThresholds data_0204c254;

extern int func_ov002_0206cb64(u32 *pOut);  /* fetch the value to band */

/* Bands the fetched value against the three thresholds and hands back which
 * band it falls in, or -1 when the mode does not band at all.
 *
 * Which way the comparison runs depends on what the fetch reports: a non-zero
 * report means the thresholds descend, so the first one at or below the value
 * wins, and a zero report means they ascend, so the first one at or above it
 * does. Falling off the end of either walk leaves -1.
 */
int func_ov002_0206ccbc(void)
{
    u32 nValue;
    int nBand;
    int i;

    /* The -1 is taken first: written the other way round, mwcc derives it
       from the zero it has just materialised and emits a sub instead of
       the mvn the ROM has. */
    nBand = -1;
    nValue = 0;
    if ((data_0204c240 & 2) != 0) {
        if (func_ov002_0206cb64(&nValue) != 0) {
            for (i = 0; i < 3; i++) {
                if (data_0204c254.aThresh[i] <= nValue) {
                    nBand = i;
                    break;
                }
            }
        } else {
            for (i = 0; i < 3; i++) {
                if (data_0204c254.aThresh[i] >= nValue) {
                    nBand = i;
                    break;
                }
            }
        }
    }
    return nBand;
}
