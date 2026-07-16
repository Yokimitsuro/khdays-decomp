/* NONMATCHING: correct; the ROM fuses the 3-field null gate into conditional loads/flags that
 * a structural transcription over-expands (same class as func_ov008_020597c4). Grid-cell hover
 * refresh. */
/* func_ov008_02073d88 -- refresh the highlighted grid cell from the pointer, ov008.
 * Only proceeds when the widget has no pending sub-target (obj[0x1a]==0 && obj[0x13e]==0 &&
 * obj[0xc]==0), input is enabled (func_ov008_02051028), and the current page is not 7. It then
 * re-picks the hovered cell (func_ov008_0206fce0); if it changed from the stored one (obj+0x54),
 * stores it and rebuilds the highlight (func_ov008_02072d9c). */
extern int  func_ov008_02051028(void);
extern int  func_ov008_0205b7b4(void);
extern int  func_ov008_0206fce0(int obj, int a, int c, int d);
extern void func_ov008_02072d9c(unsigned int *obj);

void func_ov008_02073d88(unsigned int *obj, int p2, int p3, int p4) {
    unsigned int v = obj[0x1a];
    int b3 = v == 0;
    int b4;
    if (b3) {
        v = obj[0x13e];
    }
    b4 = b3 && v == 0;
    if (b3 && v == 0) {
        b4 = obj[0xc] == 0;
    }
    if (!b4) {
        return;
    }
    if (func_ov008_02051028() == 0) {
        return;
    }
    if (func_ov008_0205b7b4() != 7) {
        unsigned int cell = func_ov008_0206fce0((int)obj, -1, p3, p4);
        if (cell != *(unsigned char *)(obj + 0x15)) {
            *(char *)(obj + 0x15) = (char)cell;
            func_ov008_02072d9c(obj);
        }
    }
}
