typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable(void);
extern void OS_WaitVBlankIntr(void);
extern void func_02005630(void);
extern void func_0200566c(void);
extern int func_0200d49c(int mode);
extern void func_0201e374();
extern void func_0201e3cc();
extern void func_0201e428(void);
extern void func_0201e438(void);
extern void func_02020cc8(void *script);
extern int func_02020e58(void *script);
extern void func_02021048(void *script);
extern void func_02030e64(int value);
extern void func_02031574(int value);
extern int func_ov012_0205b280(void);
extern void func_ov012_0205b584(void *context, int delta);
extern void func_ov012_0205b8ac(void);
extern void func_ov024_02084b14(void);
extern int func_ov024_02084db8(void);

void *func_ov012_0205b618(void) {
    char *context;
    int exitSceneId;

    context = (char *)NNSi_FndGetCurrentRootHeap();
    if ((*(u16 *)(context + 2) & 2) == 0) {
        if (*(int *)(context + 0x8bd8) == 2 ||
            *(int *)(context + 0x8bdc) == 2) {
            int previousThreadCount;
            int initialThreadCount;
            int currentThreadCount;
            int loopStatus;
            u32 pressedKeys;
            u16 normalizedKeys;
            u16 *rawKeys;
            u16 *systemFlags;
            u32 keyMask;

            previousThreadCount = OS_IsThreadAvailable();
            initialThreadCount = previousThreadCount;
            loopStatus = func_ov024_02084db8();
            if (loopStatus == 0) {
                rawKeys = (u16 *)0x04000130;
                systemFlags = (u16 *)0x027fffa8;
                keyMask = 0x2fff;
                do {
                    if ((*(u16 *)(context + 2) & 4) != 0) {
                        if (func_ov012_0205b280() != 0) {
                            if ((*(u16 *)(context + 2) & 1) != 0) {
                                func_02021048(context + 4);
                            }
                            break;
                        }
                    } else if (*(u8 *)(context + 0x8be0) == 0) {
                        normalizedKeys = ((*rawKeys | *systemFlags) ^ keyMask) & keyMask;
                        pressedKeys = normalizedKeys & 8;
                        if (*(u32 *)(context + 0x8bec) == 0 && pressedKeys != 0) {
                            *(int *)(context + 0x8be8) = 0;
                            *(u16 *)(context + 2) |= 4;
                        }
                        *(u32 *)(context + 0x8bec) = pressedKeys;
                    }

                    if ((*(u16 *)(context + 2) & 1) != 0 &&
                        func_02020e58(context + 4) == 0) {
                        *(u16 *)(context + 2) &= ~1;
                    }

                    currentThreadCount = OS_IsThreadAvailable();
                    if (previousThreadCount != currentThreadCount) {
                        func_ov012_0205b584(context,
                                            currentThreadCount - initialThreadCount);
                        previousThreadCount = currentThreadCount;
                    }

                    if (*(u8 *)(context + 0x8be0) == 0 &&
                        ((int)(*systemFlags & 0x8000) >> 15) != 0) {
                        func_02005630();
                        func_0200d49c(0);
                        *(u8 *)(context + 0x8be0) = 1;
                    } else if (*(u8 *)(context + 0x8be0) != 0 &&
                               ((int)(*systemFlags & 0x8000) >> 15) == 0 &&
                               func_0200d49c(1) != 0) {
                        *(u8 *)(context + 0x8be0) = 0;
                        func_0201e428();
                        func_0201e374();
                        func_0201e438();
                        func_0201e3cc();
                        func_0200566c();
                    }
                } while (func_ov024_02084db8() == 0);
            }

            if ((*(u16 *)(context + 2) & 4) != 0) {
                while (func_ov012_0205b280() == 0) {
                    OS_WaitVBlankIntr();
                }
                if ((*(u16 *)(context + 2) & 1) != 0) {
                    func_02021048(context + 4);
                }
            }
            func_ov024_02084b14();
            *(int *)(context + 0x8bd8) = *(int *)(context + 0x8bdc) = 3;
            if ((*(u16 *)(context + 2) & 1) != 0) {
                goto brightness_only;
            }
            goto cleanup;
        }
    }

    if (func_02020e58(context + 4) == 0) {
        goto cleanup;
    }

brightness_only:
    func_0201e374(-16);
    func_0201e3cc(-16);
    return 0;

cleanup:
    func_02020cc8(context + 4);
    func_02031574(0);
    func_02030e64(0);
    exitSceneId = *(int *)(context + 0x130);
    if (exitSceneId == 0 || (exitSceneId != 1 && exitSceneId == 2)) {
        *(u16 *)context = 2;
    }
    func_0201e374(-16);
    func_0201e3cc(-16);
    return (void *)func_ov012_0205b8ac;
}