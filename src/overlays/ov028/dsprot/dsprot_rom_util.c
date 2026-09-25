/* DS Protect 1.10, ROM utilities (ov028 0x0208acf0-0x0208af30): a hand-rolled cartridge ROM
 * read and a CRC-32. Both bodies are encrypted in the ROM; tools/dsprot_encode.py re-encrypts
 * the marked ranges after compilation. Reconstruction after taxicat1/dsprot (branch 1.10),
 * whose spellings are the ones that reproduce the library's obfuscated code. */
#include "dsprot_types.h"
#include "dsprot_ranges.h"

#define KEY_ROM_UTIL_READ   0x1cfc
#define KEY_ROM_UTIL_CRC    0x4f55

#define REG_CARD_MASTER_CNT_OFFSET  0x1a1   /* AUXSPICNT high byte */
#define REG_CARDCNT_OFFSET          0x1a4   /* ROMCTRL */
#define REG_CARD_CMD_OFFSET         0x1a8
#define REG_CARD_DATA_OFFSET        0x100010
#define REG_EXMEMCNT_OFFSET         0x204
#define REG_MI_EXMEMCNT_MP_MASK     0x800   /* 0: ARM9 owns the card bus */
#define CARD_COMMAND_MASK           0x07000000
#define CARD_COMMAND_PAGE           0x01000000
#define CARD_READ_MODE              0x00000000
#define CARD_START                  0x80000000
#define CARD_RESET_HI               0x20000000
#define CARD_DATA_READY             0x00800000
#define CARDMST_ENABLE              0x80
#define CARD_ROM_PAGE_SIZE          0x200
#define MROMOP_G_READ_PAGE          0xb7000000
#define HW_ROM_CTRL_NORMAL          (*(vs32 *)0x027ffe60)   /* card header: port setting */

/* ROMUtil_Read: read `size` bytes of cartridge ROM at `addr` into `dest` by driving the card
 * registers directly (page reads of 0x200 bytes, rounded down to the page). */
void func_ov028_0208acf0(void *dest, u32 addr, s32 size)
{
    u32 registerBase;
    vu8 *cardCmd;
    s32 offset;
    u8 savedCmd[8];
    u16 lockId;
    u16 exmemOriginal;
    u32 data;
    u32 exmemcnt;
    int i;
    s32 cardCtrl;

    lockId = OS_GetLockID();
    CARD_LockRom(lockId);

    DSPROT_RANGE_BEGIN(KEY_ROM_UTIL_READ)

    registerBase = 1;
    registerBase <<= 26;
    cardCmd = (vu8 *)(registerBase + REG_CARD_CMD_OFFSET);

    exmemcnt = 1;
    exmemcnt <<= 26;
    exmemcnt += REG_EXMEMCNT_OFFSET;
    exmemOriginal = *(vu16 *)exmemcnt;
    *(vu16 *)exmemcnt = (*(vu16 *)exmemcnt & ~REG_MI_EXMEMCNT_MP_MASK) | (0 << 11);

    cardCtrl = (HW_ROM_CTRL_NORMAL & ~CARD_COMMAND_MASK)
             | (CARD_COMMAND_PAGE | CARD_READ_MODE | CARD_START | CARD_RESET_HI);
    offset = 0 - (addr & (CARD_ROM_PAGE_SIZE - 1));

    while (*(vu32 *)(registerBase + REG_CARDCNT_OFFSET) & CARD_START) {
        continue;
    }
    *(vu8 *)(registerBase + REG_CARD_MASTER_CNT_OFFSET) = CARDMST_ENABLE;
    for (i = 0; i < 8; i++) {
        savedCmd[i] = cardCmd[i];
    }

    addr += offset;
    while (offset < size) {
        cardCmd[0] = MROMOP_G_READ_PAGE >> 24;
        cardCmd[1] = addr >> 24;
        cardCmd[2] = addr >> 16;
        cardCmd[3] = addr >> 8;
        cardCmd[4] = addr;
        cardCmd[5] = 0;
        cardCmd[6] = 0;
        cardCmd[7] = 0;
        *(vu32 *)(registerBase + REG_CARDCNT_OFFSET) = cardCtrl;
        do {
            if (*(vu32 *)(registerBase + REG_CARDCNT_OFFSET) & CARD_DATA_READY) {
                data = *(vu32 *)(registerBase + REG_CARD_DATA_OFFSET);
                if (offset >= 0 && offset < size) {
                    *(u32 *)((u32)dest + offset) = data;
                }
                offset += 4;
            }
        } while (*(vu32 *)(registerBase + REG_CARDCNT_OFFSET) & CARD_START);
        addr += CARD_ROM_PAGE_SIZE;
    }

    for (i = 0; i < 8; i++) {
        cardCmd[i] = savedCmd[i];
    }
    *(vu16 *)(registerBase + REG_EXMEMCNT_OFFSET) = exmemOriginal;

    DSPROT_RANGE_END(KEY_ROM_UTIL_READ)

    CARD_UnlockRom(lockId);
    OS_ReleaseLockID(lockId);
}

/* ROMUtil_CRC32: reflected CRC-32 over `size` bytes -- with the branch inverted from the usual
 * form (the polynomial is applied when the low bit is CLEAR), as the library ships it. */
u32 func_ov028_0208ae8c(void *buf, u32 size)
{
    int i;
    u32 crc;
    u8 *p;

    DSPROT_RANGE_BEGIN(KEY_ROM_UTIL_CRC)

    p = (u8 *)buf;
    crc = 0xffffffff;
    while (size-- != 0) {
        crc ^= *p++;
        for (i = 0; i < 8; i++) {
            if (crc & 1) {
                crc = crc >> 1;
            } else {
                crc = crc >> 1;
                crc ^= 0xed << 24;   /* 0xedb88320, applied piecewise as in the library */
                crc ^= 0xb8 << 16;
                crc ^= 0x83 << 8;
                crc ^= 0x20;
            }
        }
    }
    crc = ~crc;

    DSPROT_RANGE_END(KEY_ROM_UTIL_CRC)

    return crc;
}
