/* SBC CALLDL handler (NitroSystem G3D): unless the render state is skipping (flag 0x100), send the
 * display list at the command's relative offset (bytes 1-4, little endian) with the size in bytes
 * 5-8 to the geometry engine (NNS_G3dGeSendDL = NNS_G3dGeSendDL); then step past the 9-byte command. */

#include "nitro/types.h"

typedef struct NNSG3dRS {
    const u8 *c;        /* 0x00: current SBC command */
    u32 pad04;
    u32 flag;           /* 0x08 */
} NNSG3dRS;

extern void NNS_G3dGeSendDL(const void *src, u32 size);

void NNSi_G3dFuncSbc_CALLDL(NNSG3dRS *rs)
{
    if (!(rs->flag & 0x100)) {
        u32 rel = (u32)(rs->c[1] | (rs->c[2] << 8) | (rs->c[3] << 16) | (rs->c[4] << 24));
        u32 size = (u32)(rs->c[5] | (rs->c[6] << 8) | (rs->c[7] << 16) | (rs->c[8] << 24));

        NNS_G3dGeSendDL(rs->c + rel, size);
    }
    rs->c += 1 + 4 + 4;
}
