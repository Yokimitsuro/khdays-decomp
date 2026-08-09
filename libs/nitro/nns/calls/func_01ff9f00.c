typedef unsigned long u32;

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

extern NNSG3dGeBuffer *data_027e0074;
extern volatile int data_027e0078;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);

void func_01ff9f00(u32 op, const u32 *args, u32 numWords)
{
    NNSG3dGeBuffer *buffer = data_027e0074;
    int busyValue = data_027e0078;
    u32 idx = buffer->idx;

    if (busyValue != 0) {
        if (idx + 1 + numWords <= 192) {
            buffer->data[idx++] = op;
            if (numWords > 0) {
                MIi_CpuCopyFast(args, &data_027e0074->data[idx], numWords << 2);
                idx += numWords;
            }
            data_027e0074->idx = idx;
            return;
        }
        while (data_027e0078 != 0) {
        }
    }

    if (idx != 0) {
        MIi_CpuSend32(&buffer->data[0], (volatile void *)0x04000400, idx << 2);
        data_027e0074->idx = 0;
    }

    *(volatile u32 *)0x04000400 = op;
    MIi_CpuSend32(args, (volatile void *)0x04000400, numWords << 2);
}
