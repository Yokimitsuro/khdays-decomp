/* DS Protect 1.10, flashcart check (ov028 0x0208af30-0x0208b040): CRC six ROM pages. A real
 * cartridge mirrors reads below 0x8000 into 0x8000 + (addr & 0x1ff), so pages 0, 0x200 and
 * 0x400 must equal the one at 0x8000 while 0x8200 and 0x8400 differ; a flashcart reads them
 * all as they are. Reconstruction after taxicat1/dsprot (branch 1.10). */
#include "dsprot_types.h"
#include "dsprot_ranges.h"

#define KEY_ROM_TEST        0x1729
#define ROM_PAGE_SIZE       0x200

/* ROMTest_IsBad */
u32 func_ov028_0208af30(void)
{
    u32 crcs[7];            /* one more than used: the frame layout needs it */
    u8 page[ROM_PAGE_SIZE];
    u32 result;
    int i;
    u32 romAddr;

    result = 0;
    romAddr = 0;
    for (i = 0; i < 6; i++) {
        func_ov028_0208acf0(&page[0], romAddr, ROM_PAGE_SIZE);
        crcs[i] = func_ov028_0208ae8c(&page[0], ROM_PAGE_SIZE);
        if (i == 2) {
            romAddr = 1;
            romAddr <<= 15;
        } else {
            romAddr += ROM_PAGE_SIZE;
        }
    }

    DSPROT_RANGE_BEGIN(KEY_ROM_TEST)
    /* expected: 0 == 1 == 2 == 3, and 3 differs from 4 and from 5 */
    for (i = 0; i < 3; i++) {
        if (crcs[i] != crcs[3]) {
            result = 1;
            goto exit;
        }
    }
    if (crcs[3] == crcs[4] && crcs[3] == crcs[5]) {
        result = 1;
    }
exit:
    for (i = 0; i < ROM_PAGE_SIZE; i++) {
        page[i] = 0;
    }
    DSPROT_RANGE_END(KEY_ROM_TEST)

    return result;
}
