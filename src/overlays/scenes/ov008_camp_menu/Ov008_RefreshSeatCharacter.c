/* Rewrite seat `slot`'s character word (data_020429c8[seat] + 4): if the seat is occupied, build
 * the two-word record { its first word, its character } on the stack, the character from
 * Ov008_GetSeatCharacter (0x13 for a Roxas whose camp record has the dual wield's bit), and
 * copy it into the seat's table entry. An empty seat is left alone.
 *
 * Parked as a "+4B frame-layout tie -- the ROM stores param_4 into the struct's 3rd word via the
 * prologue push {r3,r4,r5,lr}, the r3 push doubles as the store". It does not. `push {r3, ...}`
 * is mwcc's stack ALIGNMENT PADDING: r4, r5 and lr are three words, so it pushes a fourth
 * register to keep the frame 8-byte aligned, and r3 is simply the cheapest one to hand. Reading
 * that pushed r3 as data invented both a fourth parameter and a third array element; with the
 * record two words long and the function taking one argument, it matches exactly. */

#include "game/engine.h"

extern int  Slot4_GetIfOccupied(int slot);
extern int  Ov008_GetSeatCharacter(int slot);

void Ov008_RefreshSeatCharacter(int slot) {
    int info[2];
    if (Slot4_GetIfOccupied(slot) != 0) {
        int nCharacter = Ov008_GetSeatCharacter(slot);
        info[0] = *(int *)Slot4_GetIfOccupied(slot);
        info[1] = nCharacter;
        CopyToSlotTable8((short *)info, slot);
    }
}
