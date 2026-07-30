/* func_ov026_02085aa4 -- Ov008_UpdateTouchState (248 B, 2 relocs).
 * Polls the touch panel (func_02024da4 fills up to 4 points, returns the count) and drives the
 * menu's touch press/hold state at ctx + 0xc118. Scans the points from the highest index for the
 * first active fresh press (valid == 1 && flags == 0). Then:
 *   - press found while already active (0xc118 != 0): begins a hold -- clears 0xc118, sets the
 *     hold flag 0xc11c, and snapshots the current coordinate pair (0xc120/0xc124) into the
 *     previous slots (0xc128/0xc12c);
 *   - press found while idle and not holding: latches 0xc118 = 1;
 *   - no press: clears both 0xc118 and 0xc11c.
 * If nothing is active or held afterwards it returns; otherwise it writes the found point's
 * coordinates into the current slot (0xc120/0xc122). */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct TouchPoint {
    u16 x;       /* 0x0 */
    u16 y;       /* 0x2 */
    u16 valid;   /* 0x4: 1 when this point is active */
    u16 flags;   /* 0x6: 0 for a fresh press */
} TouchPoint;

typedef struct XY {
    u16 x;
    u16 y;
} XY;

extern char *data_ov026_02091368;
extern int   func_02024da4(TouchPoint *pts);

void func_ov026_02085aa4(void)
{
    TouchPoint pts[4];
    char *ctx = data_ov026_02091368;
    TouchPoint *found = 0;
    int i = func_02024da4(pts) - 1;

    for (; i >= 0; i--) {
        if (pts[i].valid == 1 && pts[i].flags == 0) {
            found = &pts[i];
            break;
        }
    }
    if (found != 0) {
        if (*(int *)(ctx + 0xc118) != 0) {
            *(int *)(ctx + 0xc118) = 0;
            *(int *)(ctx + 0xc11c) = 1;
            *(XY *)(ctx + 0xc128) = *(XY *)(ctx + 0xc120);
            *(XY *)(ctx + 0xc12c) = *(XY *)(ctx + 0xc124);
        } else if (*(int *)(ctx + 0xc11c) == 0) {
            *(int *)(ctx + 0xc118) = 1;
        }
    } else {
        *(int *)(ctx + 0xc118) = 0;
        *(int *)(ctx + 0xc11c) = 0;
    }
    if (*(int *)(ctx + 0xc118) == 0 && *(int *)(ctx + 0xc11c) == 0) {
        return;
    }
    *(u16 *)(ctx + 0xc120) = found->x;
    *(u16 *)(ctx + 0xc122) = found->y;
}
