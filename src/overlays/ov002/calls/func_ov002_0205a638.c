typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bFirst;
    u8 bSecond;
} Ov002PanelCell;

typedef struct {
    u8 pad0000[0x30];
    u8 bColumns;            /* +0x30 */
    u8 bCursorRow;          /* +0x31 */
    Ov002PanelCell aCells[0x227];   /* +0x32 */
    u8 pad0480[0x28];
    int dwEnabledMask;      /* +0x4a8 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_020575d0(void);

int func_ov002_0205a638(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int bAvailable = 0;

    if (s->bColumns != 0) {
        if (func_ov002_020575d0() != 0) {
            bAvailable = 1;
        } else {
            int i;
            int nCount;

            if (s->dwEnabledMask == 0) {
                return bAvailable;
            }
            nCount = s->bColumns;
            for (i = bAvailable; i < nCount; i++) {
                if (s->aCells[i].bSecond != 0) {
                    bAvailable = 1;
                    break;
                }
            }
        }
    }
    return bAvailable;
}
