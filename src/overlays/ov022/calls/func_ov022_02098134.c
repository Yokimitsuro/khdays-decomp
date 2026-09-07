/* ov022: pick the cue for a slot, given what the actor is doing.
 *
 * Three tables of fifteen entries sit end to end, one per group of states, and
 * the slot indexes into whichever the state selects. A slot past the end of the
 * table has no cue at all.
 *
 * Each group then has one override: while the scene is in mode 4, slot 3 gets a
 * fixed cue of its own instead of the table's.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define LAST_SLOT 0xe
#define OVERRIDE_MODE 4
#define OVERRIDE_SLOT 3

extern const short data_ov022_020b2654[];
extern const short data_ov022_020b2672[];
extern const short data_ov022_020b2690[];
extern int func_ov002_0207298c(void);

int func_ov022_02098134(int nState, int nSlot)
{
    int nCue;

    nCue = -1;
    switch (nState) {
    case 0:
    case 5:
    case 0x13:
        if (nSlot <= LAST_SLOT) {
            nCue = data_ov022_020b2654[nSlot];
        }
        if (func_ov002_0207298c() == OVERRIDE_MODE && nSlot == OVERRIDE_SLOT) {
            nCue = 0xc;
        }
        break;
    case 0x11:
        if (nSlot <= LAST_SLOT) {
            nCue = data_ov022_020b2672[nSlot];
        }
        if (func_ov002_0207298c() == OVERRIDE_MODE && nSlot == OVERRIDE_SLOT) {
            nCue = 0x26;
        }
        break;
    default:
        if (nSlot <= LAST_SLOT) {
            nCue = data_ov022_020b2690[nSlot];
        }
        if (func_ov002_0207298c() == OVERRIDE_MODE && nSlot == OVERRIDE_SLOT) {
            nCue = 0x19;
        }
        break;
    }
    return nCue;
}
