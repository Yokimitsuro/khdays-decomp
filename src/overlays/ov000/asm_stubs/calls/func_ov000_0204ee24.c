extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_02031600(void *config);
extern void func_02031618(void *mode, int arg);
extern void func_020305d8(void);
extern void func_ov000_020588ec(int a, int b);
extern int func_020235d0(int a, int b);
extern void func_0201e470(int a, int b);
extern int func_ov028_0208b490(int a);
extern int func_ov028_0208b120(int a);
extern int func_ov028_0208b2e0(int a);
extern void func_ov000_0204edcc(void);
extern void func_0201e4a8(int a, int b);
extern void func_02020a78(int a, int b);

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov000DisplayConfig {
    int enabled;
    int visible;
    int reserved0;
    int reserved1;
} Ov000DisplayConfig;

typedef struct Ov000ModeConfig {
    int enabledMode;
    int reserved;
} Ov000ModeConfig;

typedef struct BootModeState {
    u8 flags;
    u8 state;
    u16 elapsed;
    u16 resetWord;
} BootModeState;

typedef struct Ov000BootContext {
    u8 pad_0000[0x4c40];
    int bootRequestPending;
} Ov000BootContext;

extern BootModeState data_0204c240;

asm int func_ov000_0204ee24(void)
{
    stmdb sp!, {r3, r4, r5, lr}
    sub sp, sp, #0x18
    bl NNSi_FndGetCurrentRootHeap
    mov r1, #1
    mov r4, r0
    add r0, sp, #8
    mov r5, #0
    str r1, [sp, #8]
    str r1, [sp, #0xc]
    bl func_02031600
    mov r2, #1
    mov r1, r5
    add r0, sp, #0
    str r2, [sp]
    str r1, [sp, #4]
    bl func_02031618
    bl func_020305d8
    mov r0, r5
    mov r1, r0
    bl func_ov000_020588ec
    add r0, r4, #0x4000
    ldr r0, [r0, #0xc40]
    cmp r0, #0
    beq selector_ready
    mov r0, r5
    mov r1, #9
    bl func_020235d0
    mov r5, r0
selector_ready:
    ldr r0, [pc, #0x88]
    cmp r5, r0
    bne fallback
    ldr r4, [pc, #0x80]
    ldr r2, [pc, #0x80]
    mov r0, #0
    strh r0, [r2, #4]
    mov r1, r4
    strb r0, [r2, #1]
    bl func_0201e470
    mov r0, #0
    bl func_ov028_0208b490
    cmp r0, #0
    beq unload
    mov r0, #0
    bl func_ov028_0208b120
    cmp r0, #0
    beq unload
    mov r0, #0
    bl func_ov028_0208b2e0
    cmp r0, #0
    beq unload
    ldr r1, [pc, #0x3c]
    ldr r0, [pc, #0x34]
    strh r1, [r0, #2]
    bl func_ov000_0204edcc
unload:
    mov r1, r4
    mov r0, #0
    bl func_0201e4a8
    b done
fallback:
    mov r1, r5
    mov r0, #5
    bl func_02020a78
done:
    mvn r0, #1
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, pc}
selector_magic:
    dcd 0x191
overlay_id:
    dcd 0x1c
boot_state:
    dcd data_0204c240
elapsed_limit:
    dcd 0x2710
}
