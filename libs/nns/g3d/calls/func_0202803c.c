/* SBC CALLDL handler (NitroSystem G3D): unless the render state is skipping (flag 0x100), send the
 * display list at the command's relative offset (bytes 1-4, little endian) with the size in bytes
 * 5-8 to the geometry engine (func_01ff9d90 = NNS_G3dGeSendDL); then step past the 9-byte command. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct NNSG3dRS {
    const u8 *c;        /* 0x00: current SBC command */
    u32 pad04;
    u32 flag;           /* 0x08 */
} NNSG3dRS;

extern void func_01ff9d90(const void *src, u32 size);

void func_0202803c(NNSG3dRS *rs)
{
    if (!(rs->flag & 0x100)) {
        u32 rel = (u32)(rs->c[1] | (rs->c[2] << 8) | (rs->c[3] << 16) | (rs->c[4] << 24));
        u32 size = (u32)(rs->c[5] | (rs->c[6] << 8) | (rs->c[7] << 16) | (rs->c[8] << 24));

        func_01ff9d90(rs->c + rel, size);
    }
    rs->c += 1 + 4 + 4;
}
