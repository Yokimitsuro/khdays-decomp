

#include "nitro/types.h"
#include "nitro/card.h"
#include "nitro/hw.h"

#define reg_CARD_MASTERCNT (*(vu8 *)0x040001a1)
#define reg_CARD_CMD       (*(vu8 *)0x040001a8)
#define reg_CARD_CNT       (*(vu32 *)0x040001a4)

void func_01ff84b8(u32 source, void *destination, s32 length)
{
    vu32 *const cachedGameCode = (vu32 *)0x027ffe60;
    const u32 control =
        (*cachedGameCode & ~CARD_CTRL_CMD_MASK) |
        (CARD_CTRL_CMD_PAGE | CARD_CTRL_READ | CARD_CTRL_START |
         CARD_CTRL_RESET_HI);
    s32 position = -(s32)(source & 511);

    while (reg_CARD_CNT & CARD_CTRL_START) {
    }
    reg_CARD_MASTERCNT = CARD_MASTER_SELECT_ROM | CARD_MASTER_ENABLE;

    for (source = (u32)(source + position); position < length;
         source += 512) {
        (&reg_CARD_CMD)[0] = CARD_CMD_READ_PAGE;
        (&reg_CARD_CMD)[1] = (u8)(source >> 24);
        (&reg_CARD_CMD)[2] = (u8)(source >> 16);
        (&reg_CARD_CMD)[3] = (u8)(source >> 8);
        (&reg_CARD_CMD)[4] = (u8)source;
        (&reg_CARD_CMD)[5] = 0;
        (&reg_CARD_CMD)[6] = 0;
        (&reg_CARD_CMD)[7] = 0;

        reg_CARD_CNT = control;
        for (;;) {
            u32 status = reg_CARD_CNT;

            if (status & CARD_CTRL_READY) {
                const u32 data = reg_CARD_DATA;

                if (position >= 0 && position < length) {
                    *(u32 *)((u32)destination + position) = data;
                }
                position += sizeof(u32);
            }

            if (!(status & CARD_CTRL_START)) {
                break;
            }
        }
    }
}
