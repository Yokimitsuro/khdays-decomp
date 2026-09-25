/* ov016 .data 0x02082758-0x020827c0: the tail of the kickable per-kind rows (data_ov016_02082748,
 * 20 bytes per kind, read by Ov016_KickableCreate func_ov016_02082020).  dsd split the table at
 * 0x02082758, inside row 0, so this object starts with row 0's last two halfwords and carries
 * rows 1-5 (row 5 is empty): the step handler, two parameters and the three speeds. */

typedef struct Ov016KickableKindRow {
    void (*pfnStep)(void);    /* 0x00 */
    int nParamA;              /* 0x04 */
    int nParamB;              /* 0x08 */
    short nSpeedA;            /* 0x0c */
    short nSpeedB;            /* 0x0e */
    short nSpeedC;            /* 0x10 */
    short nPad12;             /* 0x12 */
} Ov016KickableKindRow;

extern void func_ov016_02081d2c(void);  /* Ov016_KickableStep */

struct {
    short nRow0SpeedC;
    short nRow0Pad;
    Ov016KickableKindRow rows[5];
} data_ov016_02082758 = {
    0, 0,
    {
        { func_ov016_02081d2c, 0x333, 0, 0x0b33, 0x0e66, 0, 0 },
        { func_ov016_02081d2c, 0x333, 0, 0x0e66, 0x0f9a, 0, 0 },
        { func_ov016_02081d2c, 0x333, 0, 0x0e66, 0x0f9a, 0, 0 },
        { func_ov016_02081d2c, 0x333, 0, 0x0e66, 0x0f9a, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
    },
};
