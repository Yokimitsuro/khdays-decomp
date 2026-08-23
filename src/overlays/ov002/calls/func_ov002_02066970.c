/*
 * Ov002_SwitchSlotCues - hand the pair cues over from one slot to the other.
 *
 * The table holds two cue pairs: the one the slot being left answers to and
 * the one the slot being entered answers to, each indexed by slot. When the
 * caller asks for them to be heard, the outgoing slot's cue is played first
 * and the incoming slot's second. The new slot is recorded either way.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    int a[2];
} Ov002CuePair;

typedef struct {
    int nUnk00;
    int nUnk04;
    Ov002CuePair leave;
    Ov002CuePair enter;
} Ov002CueTable;

extern const Ov002CueTable data_ov002_0207e460;
extern int *data_ov002_0207f9f0;

extern int func_ov002_02053558(u16 nCue);
extern void func_ov002_020535a4(int hCue);

void func_ov002_02066970(int nSlot, int bPlay)
{
    Ov002CuePair enter;
    Ov002CuePair leave;
    int *ctx;

    ctx = data_ov002_0207f9f0;
    enter = data_ov002_0207e460.enter;
    leave = data_ov002_0207e460.leave;
    if (bPlay != 0) {
        func_ov002_020535a4(func_ov002_02053558((u16)leave.a[ctx[2]]));
        func_ov002_020535a4(func_ov002_02053558((u16)enter.a[nSlot]));
    }
    ctx[2] = nSlot;
}
