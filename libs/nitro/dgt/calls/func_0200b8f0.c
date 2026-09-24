/* DGT_Hash2GetDigest (NitroSDK DGT, SHA-1): pads the pending block (0x80, zeros up to the word, zero
 * words up to 14 -- hashing an extra block first when fewer than 8 bytes are left), appends the
 * big-endian bit count (Nh then Nl), hashes it through the block hook data_020422d0 and writes
 * the five state words big-endian into `digest`. The final clear wipes only the 4-byte context
 * pointer itself (sizeof of the parameter, not of the context). */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct DGTHash2Context {
    u32 h0, h1, h2, h3, h4;
    u32 Nl;
    u32 Nh;
    int num;
    u8 data[64];
    int dummy[2];
} DGTHash2Context;

extern void (*data_020422d0)(DGTHash2Context *context, const void *data, u32 length);   /* SHA-1 block hook */
extern void INITi_CpuClear32_0x01ff86fc(u32 data, void *destp, u32 size);   /* MIi_CpuClear32 */

void func_0200b8f0(DGTHash2Context *context, void *digest)
{
    u8 *md = (u8 *)digest;
    u32 *p = (u32 *)context->data;
    u8 *cp;
    int i;
    int n;
    u32 l;

    n = context->num;
    i = n >> 2;
    if ((n & 3) == 0) {
        p[i] = 0;
    }
    cp = context->data;
    cp[n] = 0x80;
    n++;
    while ((n & 3) != 0) {
        cp[n] = 0;
        n++;
    }
    i++;
    if (context->num >= 0x38) {
        for (; i < 16; i++) {
            p[i] = 0;
        }
        data_020422d0(context, p, 64);
        i = 0;
    }
    for (; i < 14; i++) {
        p[i] = 0;
    }
    l = context->Nl;
    cp[0x3f] = (u8)l;
    cp[0x3e] = (u8)(l >> 8);
    cp[0x3d] = (u8)(l >> 16);
    cp[0x3c] = (u8)(l >> 24);
    l = context->Nh;
    cp[0x3b] = (u8)l;
    cp[0x3a] = (u8)(l >> 8);
    cp[0x39] = (u8)(l >> 16);
    cp[0x38] = (u8)(l >> 24);
    data_020422d0(context, p, 64);
    l = context->h0;
    md[0] = (u8)(l >> 24);
    md[1] = (u8)(l >> 16);
    md[2] = (u8)(l >> 8);
    md[3] = (u8)l;
    l = context->h1;
    md[4] = (u8)(l >> 24);
    md[5] = (u8)(l >> 16);
    md[6] = (u8)(l >> 8);
    md[7] = (u8)l;
    l = context->h2;
    md[8] = (u8)(l >> 24);
    md[9] = (u8)(l >> 16);
    md[10] = (u8)(l >> 8);
    md[11] = (u8)l;
    l = context->h3;
    md[12] = (u8)(l >> 24);
    md[13] = (u8)(l >> 16);
    md[14] = (u8)(l >> 8);
    md[15] = (u8)l;
    l = context->h4;
    md[16] = (u8)(l >> 24);
    md[17] = (u8)(l >> 16);
    md[18] = (u8)(l >> 8);
    md[19] = (u8)l;
    context->num = 0;
    INITi_CpuClear32_0x01ff86fc(0, &context, sizeof(context));
}
