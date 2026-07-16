/* func_ov006_0204fc78 -- title: is the highlighted menu entry already the active one?
 * True while the scene is locked out (obj+0x4e8 set). Otherwise compares the current
 * selection (obj+0x4e4) against the entry id of the cursor row (obj+0x4b0, stride 6);
 * row 0 always counts as a match. */
extern int func_02030788(void);
extern int data_ov006_020565e4;

#define OBJ (*(int **)&data_ov006_020565e4)

int func_ov006_0204fc78(void) {
    unsigned short row;
    int *obj;
    int same;
    if (OBJ[0x13a] != 0) {
        return 1;
    }
    row = (unsigned short)func_02030788();
    obj = OBJ;
    same = 1;
    if (*(unsigned short *)((char *)obj + 0x4e4) !=
            *(unsigned short *)((char *)obj + row * 6 + 0x4b0) && row != 0) {
        same = 0;
    }
    return same;
}
