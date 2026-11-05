/* Ov000_ModeSelect_InitObjects -- (re)load the logo confirm-dialog art, ov000. Builds a resource
 * descriptor {char addr, 2, 0, 0, 8, palette addr} from the scene block (*data_ov000_0205ac28,
 * base[0x28]) and hands it to Ov000_InitSubsystemObject, then refreshes the list
 * (Ov000_ForEachListNode) and the caret (Ov000_PlaceModeMarker). */

#include "game/archive.h"
extern char *data_ov000_0205ac28;
extern void Ov000_InitSubsystemObject(void *widget, int *desc);
extern void Ov000_ForEachListNode(void *widget, int arg);
extern void Ov000_PlaceModeMarker(int);
void Ov000_ModeSelect_InitObjects(void) {
    int *base = (int *)data_ov000_0205ac28;
    int desc[6];
    desc[0] = ARCHIVE_HANDLE(base[0xa], 1);
    desc[1] = 2;
    desc[2] = 0;
    desc[3] = 0;
    desc[4] = 8;
    desc[5] = ARCHIVE_HANDLE(base[0xa], 3);
    Ov000_InitSubsystemObject((char *)base + 0x78, desc);
    Ov000_ForEachListNode((char *)base + 0x78, 2);
    Ov000_PlaceModeMarker(2);
}
