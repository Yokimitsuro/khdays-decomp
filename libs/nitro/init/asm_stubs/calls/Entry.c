/* NitroSDK original assembly (libraries/init/src/crt0.c: _start). */

extern void func_02000a78(void);
extern void func_020009fc(void);
extern void INITi_CpuClear32_0x0200093c(void);
extern void MIi_UncompressBackward(void);
extern void func_01ff8148(void);
extern void func_020207f0(void);
extern void func_02000b60(void);
extern void func_02020808(void);
extern void main(void);
extern unsigned char data_027e0000[];   /* SDK_AUTOLOAD_DTCM_START */

#define HW_CACHE_LINE_SIZE               0x20
#define HW_COMPONENT_PARAM               0x27fff9c
#define HW_DTCM_SIZE                     0x4000
#define HW_DTCM_SYSRV_OFS_INTR_VECTOR    0x3c
#define HW_OAM                           0x7000000
#define HW_OAM_SIZE                      0x400
#define HW_PLTT                          0x5000000
#define HW_PLTT_SIZE                     0x400
#define HW_PSR_IRQ_MODE                  0x12
#define HW_PSR_SVC_MODE                  0x13
#define HW_PSR_SYS_MODE                  0x1f
#define HW_REG_BASE                      0x4000000
#define HW_RESET_VECTOR                  0xffff0000
#define HW_SVC_STACK_SIZE                0x40
#define REG_IME_OFFSET                   0x208
#define REG_VCOUNT_OFFSET                0x6
#define SDK_IRQ_STACKSIZE                0x800
#define INITi_HW_DTCM                    data_027e0000
#define _start_ModuleParams              0x02000b68
#define do_autoload                      func_020009fc
#define init_cp15                        func_02000a78
#define INITi_CpuClear32                 INITi_CpuClear32_0x0200093c
#define OS_IrqHandler                    func_01ff8148
#define _fp_init                         func_020207f0
#define NitroStartUp                     func_02000b60
#define __call_static_initializers       func_02020808
#define NitroMain                        main

asm void Entry(void)
{
    mov r12, #HW_REG_BASE
    str r12, [r12, #REG_IME_OFFSET]

@wait_vcount_0:
    ldrh r0, [r12, #REG_VCOUNT_OFFSET]
    cmp r0, #0
    bne @wait_vcount_0
    bl init_cp15
    mov r0, #HW_PSR_SVC_MODE
    msr cpsr_c, r0
    ldr r0, = INITi_HW_DTCM
    add r0, r0, #0x3FC0
    mov sp, r0
    mov r0, #HW_PSR_IRQ_MODE
    msr cpsr_c, r0
    ldr r0, = INITi_HW_DTCM
    add r0, r0, #0x3FC0
    sub r0, r0, #HW_SVC_STACK_SIZE
    sub sp, r0, #4
    tst sp, #4
    subeq sp, sp, #4
    ldr r1, = SDK_IRQ_STACKSIZE
    sub r1, r0, r1
    mov r0, #HW_PSR_SYS_MODE
    msr cpsr_csfx, r0
    sub sp, r1, #4
    mov r0, #0
    ldr r1, = INITi_HW_DTCM
    mov r2, #HW_DTCM_SIZE
    bl INITi_CpuClear32
    mov r0, #0
    ldr r1, = HW_PLTT
    mov r2, #HW_PLTT_SIZE
    bl INITi_CpuClear32
    mov r0, #0x0200
    ldr r1, = HW_OAM
    mov r2, #HW_OAM_SIZE
    bl INITi_CpuClear32
    ldr r1, = _start_ModuleParams
    ldr r0, [r1, #20]
    bl MIi_UncompressBackward
    bl do_autoload
    ldr r0, = _start_ModuleParams
    ldr r1, [r0, #12]
    ldr r2, [r0, #16]
    mov r3, r1
    mov r0, #0
@1:
    cmp r1, r2
    strcc r0, [r1], #4
    bcc @1
    bic r1, r3, #HW_CACHE_LINE_SIZE - 1
@cacheflush:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r1, c7, c5, 1
    mcr p15, 0, r1, c7, c14, 1
    add r1, r1, #HW_CACHE_LINE_SIZE
    cmp r1, r2
    blt @cacheflush
    ldr r1, = HW_COMPONENT_PARAM
    str r0, [r1, #0]
    ldr r1, = INITi_HW_DTCM
    add r1, r1, #0x3FC0
    add r1, r1, #HW_DTCM_SYSRV_OFS_INTR_VECTOR
    ldr r0, = OS_IrqHandler
    str r0, [r1, #0]
    bl _fp_init
    bl NitroStartUp
    bl __call_static_initializers
    ldr r1, = NitroMain
    ldr lr, = HW_RESET_VECTOR
    tst sp, #4
    subne sp, sp, #4
    bx r1
}
