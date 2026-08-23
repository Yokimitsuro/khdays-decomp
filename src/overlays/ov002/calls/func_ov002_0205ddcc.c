/*
 * Ov002_PanelSelectSource - point the panel at one of the two sources it was
 * created with, and set the flag that goes with it.
 *
 * A negative request means "keep the source we already have". The request is
 * matched against the two words the setup handed over, and a hit becomes the
 * one-based index of the word that matched; a request that matches neither is
 * taken as it stands. Nothing happens at all when the source and the flag are
 * both already what was asked for.
 *
 * The flag is forced off in the restricted state while there is no source, and
 * the ring is rebuilt afterwards - and re-opened when the panel is sitting on
 * mode 0.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0xa];
    int nPrimaryValue;                  /* +0x00c */
    u8 pad0010[4];
    u16 wSource;                        /* +0x014 */
    u16 pad0016;
    u8 pad0018[0x10];
    int aWords[2];                      /* +0x028 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_020575d0(void);
extern void func_ov002_0205ae08(int nSource, int nFlag, int bFirst);
extern void func_ov002_0205bbbc(int nMode);

void func_ov002_0205ddcc(int nSource, int nFlag)
{
    Ov002PanelSession *s;
    int i;
    Ov002PanelSession *pWalk;
    int bFirst;

    s = data_ov002_0207f620;
    i = 0;
    if (nSource < 0) {
        nSource = s->wSource;
    }
    if (nSource != 0) {
        i = 0;
        pWalk = s;
        do {
            if (nSource == pWalk->aWords[0]) {
                nSource = i + 1;
                break;
            }
            i++;
            pWalk = (Ov002PanelSession *)((char *)pWalk + 4);
        } while (i < 2);
    }
    if (i >= 2 || s->wSource == nSource) {
        if (s->nPrimaryValue == nFlag) {
            return;
        }
    }
    s->wSource = (u16)nSource;
    if (func_ov002_020575d0() != 0 && nSource == 0) {
        nFlag = 0;
    }
    s->nPrimaryValue = nFlag;
    func_ov002_0205bbbc(s->bMode);
    if (s->bMode == 0) {
        if (s->bKind == 0) {
            bFirst = 1;
        } else {
            bFirst = 0;
        }
        func_ov002_0205ae08(s->wSource, s->nPrimaryValue, bFirst);
    }
}
