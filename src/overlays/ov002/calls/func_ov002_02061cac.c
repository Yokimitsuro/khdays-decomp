/*
 * Ov002_PushMarkerNumber - hand a number to one of the three marker slots.
 *
 * The ring is walked from its head looking for a slot that is not carrying
 * anything; the first free one takes the number. When all three are busy the
 * oldest is overwritten and the head moves on, so the newest number always gets
 * a slot.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x1204];
    int aMarkerValue[3];
    int nMarkerHead;
} Ov002MarkerScene;

extern int data_ov002_0207f628;

extern void func_ov002_02061c58(int nSlot, int nValue);

void func_ov002_02061cac(int nValue)
{
    int i;
    int nSlot;
    Ov002MarkerScene *s;

    s = *(Ov002MarkerScene **)&data_ov002_0207f628;
    if (s == 0) {
        return;
    }

    nSlot = s->nMarkerHead;
    for (i = 0; i < 3; i++) {
        if (s->aMarkerValue[nSlot % 3] == 0) {
            func_ov002_02061c58(nSlot % 3, nValue);
            break;
        }
        nSlot++;
    }

    if (i == 3) {
        func_ov002_02061c58(s->nMarkerHead, nValue);
        s->nMarkerHead = (s->nMarkerHead + 1) % 3;
    }
}
