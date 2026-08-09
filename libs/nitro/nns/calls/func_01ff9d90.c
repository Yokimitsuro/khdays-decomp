typedef unsigned long u32;

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

extern volatile int data_027e0078;
extern NNSG3dGeBuffer *data_027e0074;
extern int data_027e007c;
extern int data_020422b8;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);
extern void MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 size,
                                      void (*callback)(void *), void *arg);
extern void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 size,
                                  void (*callback)(void *), void *arg);
extern void func_01ff9d84(void *arg);

void func_01ff9d90(const void *src, u32 size)
{
    if (size < 0x100) {
        if (data_027e0078 != 0) {
            if (data_027e0074->idx + (size >> 2) <= 192) {
                MIi_CpuCopyFast(src, &data_027e0074->data[data_027e0074->idx], size);
                data_027e0074->idx += size >> 2;
                return;
            }
            while (data_027e0078 != 0) {
            }
        }

        if (data_027e0074->idx != 0) {
            MIi_CpuSend32(&data_027e0074->data[0], (volatile void *)0x04000400,
                          data_027e0074->idx << 2);
            data_027e0074->idx = 0;
        }
        MIi_CpuSend32(src, (volatile void *)0x04000400, size);
        return;
    }

    while (data_027e0078 != 0) {
    }

    if (data_027e0074->idx != 0) {
        MIi_CpuSend32(&data_027e0074->data[0], (volatile void *)0x04000400,
                      data_027e0074->idx << 2);
        data_027e0074->idx = 0;
    }

    data_027e0078 = 1;
    if (data_027e007c != 0) {
        MI_SendGXCommandAsyncFast((u32)data_020422b8, src, size, func_01ff9d84,
                                  (void *)&data_027e0078);
    } else {
        MI_SendGXCommandAsync((u32)data_020422b8, src, size, func_01ff9d84,
                              (void *)&data_027e0078);
    }
}
