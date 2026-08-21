typedef unsigned short u16;

extern void func_0202bf18(char *pObj, int bFade, int nDuration);

/* Turn an element's fade on or off.
 *
 * The two fade bits in the element's flag word are set or cleared together and
 * the duration is stored beside them; turning the fade on also clears the
 * object's hold bit. The render object only hears about it once it is live,
 * which is the bit tested at the end - the same status byte the helper itself
 * touches, since the object sits at offset 0x1c and its status byte at 8.
 */
void func_ov002_0207a784(char *pElement, int bFade, short nDuration)
{
    if (bFade) {
        *(u16 *)(pElement + 0x12) |= 0x100;
        *(u16 *)(pElement + 0x12) |= 0x200;
        *(short *)(pElement + 0x1a2) = nDuration;
        *(unsigned char *)(pElement + 0x24) &= ~0x20;
    } else {
        *(u16 *)(pElement + 0x12) &= ~0x100;
        *(u16 *)(pElement + 0x12) &= ~0x200;
        *(short *)(pElement + 0x1a2) = 0;
    }

    if ((*(unsigned char *)(pElement + 0x24) & 4) != 0) {
        func_0202bf18(pElement + 0x1c,
                      (*(u16 *)(pElement + 0x12) & 0x100) != 0,
                      *(short *)(pElement + 0x1a2));
    }
}
