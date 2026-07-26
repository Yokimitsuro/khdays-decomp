/* func_ov011_0205cad8 -- refresh whatever the scene is currently showing.
 *
 * Phases 3 and 4 have their own single refresh path; every other phase redraws the two
 * halves separately.
 *
 * It has to be a switch. Written as `nPhase == 3 || nPhase == 4` mwcc spots that the two
 * values are adjacent and turns the test into a range check -- add #0xfd, and #0xff,
 * cmp #1, bhi -- which is one instruction longer than the ROM's cmp/cmpne/bne pair. A
 * switch with two fallthrough labels keeps the comparisons literal. */
typedef unsigned char u8;

typedef struct Ov011Scene {
    u8 pad_00000[0x10945];
    u8 nPhase;
} Ov011Scene;

typedef struct Ov011Globals {
    int         pad_00;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;

extern void func_ov011_0205c884(void);
extern void func_ov011_0205c6fc(int nHalf);

void func_ov011_0205cad8(void)
{
    switch (data_ov011_0205e960.pScene->nPhase) {
    case 3:
    case 4:
        func_ov011_0205c884();
        return;
    }
    func_ov011_0205c6fc(0);
    func_ov011_0205c6fc(1);
}
