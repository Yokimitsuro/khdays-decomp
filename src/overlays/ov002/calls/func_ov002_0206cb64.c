typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

/* Which value the mission panel shows.  The fetcher's return says which way
 * that value runs, and Ov002_GetPanelValueBand turns it into the direction of
 * its threshold walk.
 */
enum {
    OV002_METRIC_TIME_LEFT    = 0,  /* the timeout, in hundredths of a second */
    OV002_METRIC_PANEL_TOTAL  = 1,
    OV002_METRIC_TARGET_SHARE = 2,  /* a Q12 percentage of the request's target */
    OV002_METRIC_SEAT_RAW     = 3,
    OV002_METRIC_REMAINING_0  = 4,
    OV002_METRIC_REMAINING_1  = 5,
    OV002_METRIC_REMAINING_2  = 6,
    OV002_METRIC_REMAINING_3  = 7,
    OV002_METRIC_LOCAL_SEAT   = 8
};

extern char *data_ov002_0207fa00;       /* the overlay root context */
extern u8 data_0204c240;                /* g_modeAndDayClock; bit 2 pins the metric */
extern char data_0204c254[];            /* g_ov002PanelThresholds */

extern u64 func_ov002_0206f604(void);   /* the configured timeout, in OS ticks */
extern int func_02030788(void);         /* Session_GetLocalPlayerIndex */
/* The two MSL divides.  The tree calls them by address rather than letting
 * mwcc emit its own _ll_sdiv and _s32_div_f references. */
extern long long func_02020368(long long nValue, unsigned int nDiv, int nUnused);
extern long long func_02020400(int nNum, int nDen);

/* Writes the value the mission panel is showing into *pValue and reports which
 * way that value runs: one for a rising quantity, zero for a falling one.
 * Ov002_GetPanelValueBand turns that into the direction of its threshold walk;
 * Ov002_FillMissionResult ignores it and just takes the value.
 *
 * The metric is the panel's own selector, except while bit 2 of
 * g_modeAndDayClock is set, which pins it to the local seat's own figure.  A
 * metric past the last one writes nothing at all and reports zero.
 *
 * The time limit is turned back from ticks into hundredths of a second by
 * undoing the NitroSDK conversion, (ms * 33514) >> 6, with two 64-bit divides.
 * The share is a Q12 percentage of the request's target, and is zero when
 * there is no target to divide by.
 */
int func_ov002_0206cb64(int *pValue)
{
    char *pRoot;
    int nMetric;
    long long nTicks;
    int nShare;

    pRoot = data_ov002_0207fa00;
    if ((data_0204c240 & 4) != 0) {
        nMetric = OV002_METRIC_LOCAL_SEAT;
    } else {
        nMetric = *(u16 *)&data_0204c254[0xe];
    }

    switch (nMetric) {
    case OV002_METRIC_TIME_LEFT:
        nTicks = func_02020368((long long)func_ov002_0206f604() << 6,
                               0x82ea, 0);
        *pValue = (int)func_02020368(nTicks, 10, 0);
        break;
    case OV002_METRIC_PANEL_TOTAL:
        *pValue = *(int *)(pRoot + 0x8bdc);
        goto rising;
    case OV002_METRIC_TARGET_SHARE:
        if (*(int *)(pRoot + 0x8ca0) == 0) {
            nShare = 0;
        } else {
            nShare = (int)func_02020400(*(int *)(pRoot + 0x8ca8) << 12,
                                        *(int *)(pRoot + 0x8ca0)) * 100 >> 12;
        }
        *pValue = nShare;
        goto rising;
    case OV002_METRIC_SEAT_RAW:
        *pValue = *(int *)(pRoot + 0x8be4);
        goto rising;
    case OV002_METRIC_REMAINING_0:
        *pValue = *(int *)(pRoot + 0x8d84);
        break;
    case OV002_METRIC_REMAINING_1:
        *pValue = *(int *)(pRoot + 0x8d88);
        break;
    case OV002_METRIC_REMAINING_2:
        *pValue = *(int *)(pRoot + 0x8d8c);
        break;
    case OV002_METRIC_REMAINING_3:
        *pValue = *(int *)(pRoot + 0x8d90);
        break;
    case OV002_METRIC_LOCAL_SEAT:
        *pValue = *(int *)(pRoot + func_02030788() * 0x2c + 0x8bf0);
        goto rising;
    }
    return 0;
rising:
    return 1;
}
