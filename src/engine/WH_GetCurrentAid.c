/* WH_GetCurrentAid -- the wireless helper (wh.c): this console's AID in the
 * connection, sMyAid. */

extern unsigned short data_027e0064;

unsigned short WH_GetCurrentAid(void) {
    return data_027e0064;
}
