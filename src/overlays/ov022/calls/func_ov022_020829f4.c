typedef unsigned char u8;
typedef unsigned int u32;

extern u32 OVERLAY_106_ID[1];
#define FS_OVERLAY_ID_ov106 ((u32)(u32)&OVERLAY_106_ID)

typedef struct Ov022RegistrationBuffer {
    u8 payload[0x44];
    int handle;
} Ov022RegistrationBuffer;

typedef struct Ov022RegistrationState {
    u8 pad000[8];
    int handle;
} Ov022RegistrationState;

extern void func_ov022_02082960(void);
extern void func_0201e470(int arg0, int arg1);
extern int func_02023930(void *registrationClass,
                         Ov022RegistrationBuffer *buffer);
extern void func_ov002_02078ef8(void);
extern u8 data_ov022_020b28bc[];
extern int data_ov106_020b8aa0;
extern Ov022RegistrationState data_ov022_020b2e60;

void func_ov022_020829f4(void) {
    Ov022RegistrationBuffer buffer;

    func_ov022_02082960();
    func_0201e470(0, FS_OVERLAY_ID_ov106);
    {
        u32 remaining;
        const u8 *src;
        u8 *dst;

        src = data_ov022_020b28bc;
        dst = buffer.payload;
        remaining = 0x18;

        do {
            *dst = *src;
            src++;
            dst++;
            remaining--;
        } while (remaining != 0);
    }
    buffer.handle = 0;
    data_ov022_020b2e60.handle =
        func_02023930(&data_ov106_020b8aa0, &buffer);
    func_ov002_02078ef8();
}
