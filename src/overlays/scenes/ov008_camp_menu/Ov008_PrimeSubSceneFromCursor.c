/* Ov008_PrimeSubSceneFromCursor -- prime the menu sub-scene from the current cursor plus a difficulty.
 * Snapshots the current cursor triple (Ov008_GetSharedRecord); a negative argument clears the
 * sub-scene, otherwise it selects page `arg`, stamps the difficulty byte into the high half
 * of the triple's second short, and hands the triple over.
 *
 * The snapshot is a STRUCT COPY, not three element assignments: the ROM issues both of the
 * first two halfword loads before either store, which is the shape mwcc gives a 6-byte
 * struct assignment and not the shape it gives element-by-element copies (those pair each
 * load with its own store, in the opposite order). */

#include "game/engine.h"

extern unsigned short *Ov008_GetSharedRecord(void);
extern void  Ov008_StoreSeatCampRecord(unsigned short *init);
extern void  Ov008_SetCtxField9678(int page);

typedef struct { unsigned short a, b, c; } Cursor0205714c;

void Ov008_PrimeSubSceneFromCursor(int arg) {
    Cursor0205714c init;
    unsigned short *cur;

    Session_GetLocalPlayerIndex();
    cur = Ov008_GetSharedRecord();
    init = *(Cursor0205714c *)cur;

    if (arg < 0) {
        Ov008_StoreSeatCampRecord(0);
        return;
    }
    Ov008_SetCtxField9678(arg);
    *((char *)&init + 3) = (char)arg;
    Ov008_StoreSeatCampRecord((unsigned short *)&init);
}
