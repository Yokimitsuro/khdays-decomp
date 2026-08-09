typedef unsigned long u32;

typedef struct NNSG3dGeCommandBuffer {
    u32 count;
    u32 words[0xc0];
} NNSG3dGeCommandBuffer;

extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);

extern NNSG3dGeCommandBuffer *data_027e0074;
extern volatile u32 data_027e0078;

void func_01ffa764(u32 command, u32 argument)
{
    NNSG3dGeCommandBuffer *buffer = data_027e0074;
    volatile u32 *busyFlag = &data_027e0078;
    u32 count = buffer->count;

    if (*busyFlag != 0) {
        if (count + 2 <= 0xc0) {
            buffer->words[count] = command;
            buffer->words[count + 1] = argument;
            buffer->count += 2;
            return;
        }

        while (*busyFlag != 0) {
        }
    }

    if (count != 0) {
        MIi_CpuSend32(buffer->words, (volatile void *)0x04000400,
                      count << 2);
        buffer->count = 0;
    }

    *(volatile u32 *)0x04000400 = command;
    *(volatile u32 *)0x04000400 = argument;
}
