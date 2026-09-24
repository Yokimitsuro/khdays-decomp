/* DGT_Hash2SetSource (NitroSDK DGT, SHA-1): feeds `length` bytes of `input` into the SHA-1 context. The
 * 64-bit bit count (Nl/Nh) grows first; a partly filled block is topped up and hashed, whole
 * blocks are hashed straight from a word-aligned input (or through the block buffer one by one
 * when it is not aligned), and the remainder waits in the block buffer. Blocks go through the
 * replaceable process-block hook data_020422d0. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct DGTHash2Context {
    u32 h0, h1, h2, h3, h4;
    u32 Nl;
    u32 Nh;
    u32 num;
    u8 data[64];
    int dummy[2];
} DGTHash2Context;

extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void (*data_020422d0)(DGTHash2Context *context, const void *data, u32 length);   /* SHA-1 block hook */

void func_0200b79c(DGTHash2Context *context, const void *input, u32 length)
{
    const u8 *data = (const u8 *)input;
    u8 *p = context->data;
    u32 l;
    u32 n;

    if (length == 0) {
        return;
    }
    l = context->Nl + (length << 3);
    if (l < context->Nl) {
        context->Nh++;
    }
    context->Nh += length >> 29;
    context->Nl = l;

    if (context->num != 0) {
        if (context->num + length >= 64) {
            n = 64 - context->num;
            MI_CpuCopy8(data, p + context->num, n);
            length -= n;
            data += n;
            data_020422d0(context, p, 64);
            context->num = 0;
        } else {
            MI_CpuCopy8(data, p + context->num, length);
            context->num += length;
            return;
        }
    }
    if (length >= 64) {
        int sw = (int)(length & ~0x3f);

        length -= sw;
        if (((u32)data & 3) == 0) {
            data_020422d0(context, data, sw);
            data += sw;
        } else {
            do {
                MI_CpuCopy8(data, p, 64);
                data += 64;
                data_020422d0(context, p, 64);
                sw -= 64;
            } while (sw > 0);
        }
    }
    context->num = length;
    if (length != 0) {
        MI_CpuCopy8(data, p, length);
    }
}
