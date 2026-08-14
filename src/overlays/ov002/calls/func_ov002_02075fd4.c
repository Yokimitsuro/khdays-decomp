/* Park the LCD swap bit, or put it back.
 *
 * POWCNT1 bit 15 chooses which screen the main engine drives. Asked to save, this remembers the
 * bit and clears it, but only if nothing is remembered yet, which the -1 sentinel marks. Asked to
 * restore, it merges the remembered bit back in and forgets it again.
 *
 * The register address is held in a pointer rather than cast at every use, which is how the
 * original keeps it live -- and it earns that twice, since the compiler builds the 0x8000 mask by
 * shifting the address 0x04000304 right by eleven, and the -1 sentinel by shifting the 0xffff7fff
 * mask right by sixteen. In the merge, the preserved bits go on the LEFT of the or; the other way
 * round costs two instructions.
 */

typedef unsigned short u16;

extern int data_ov002_0207f408;

void func_ov002_02075fd4(int hide) {
    volatile u16 *reg304 = (volatile u16 *)0x04000304;

    if (hide != 0) {
        if (data_ov002_0207f408 < 0) {
            data_ov002_0207f408 = (*reg304 & 0x8000) >> 15;
            *reg304 = (u16)(*reg304 & ~0x8000);
        }
    } else {
        if (data_ov002_0207f408 >= 0) {
            *reg304 = (u16)((*reg304 & ~0x8000) | (data_ov002_0207f408 << 15));
            data_ov002_0207f408 = -1;
        }
    }
}
