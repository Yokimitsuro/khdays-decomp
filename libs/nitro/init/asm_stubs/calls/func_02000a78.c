/* NitroSDK original assembly (libraries/init/src/crt0.c: init_cp15). */

extern void MIi_UncompressBackward(void);
extern unsigned char data_027e0000[];   /* SDK_AUTOLOAD_DTCM_START */

#define HW_BIOS                          0xffff0000
#define HW_C1_CACHE_ROUND_ROBIN          0x4000
#define HW_C1_DCACHE_ENABLE              0x4
#define HW_C1_DTCM_ENABLE                0x10000
#define HW_C1_DTCM_LOAD_MODE             0x20000
#define HW_C1_EXCEPT_VEC_UPPER           0x2000
#define HW_C1_ICACHE_ENABLE              0x1000
#define HW_C1_ITCM_ENABLE                0x40000
#define HW_C1_ITCM_LOAD_MODE             0x80000
#define HW_C1_LD_INTERWORK_DISABLE       0x8000
#define HW_C1_PROTECT_UNIT_ENABLE        0x1
#define HW_C1_SB1_BITSET                 0x78
#define HW_C6_PR_128KB                   0x20
#define HW_C6_PR_128MB                   0x34
#define HW_C6_PR_16KB                    0x1a
#define HW_C6_PR_16MB                    0x2e
#define HW_C6_PR_1GB                     0x3a
#define HW_C6_PR_1MB                     0x26
#define HW_C6_PR_256KB                   0x22
#define HW_C6_PR_256MB                   0x36
#define HW_C6_PR_2GB                     0x3c
#define HW_C6_PR_2MB                     0x28
#define HW_C6_PR_32KB                    0x1c
#define HW_C6_PR_32MB                    0x30
#define HW_C6_PR_4GB                     0x3e
#define HW_C6_PR_4KB                     0x16
#define HW_C6_PR_4MB                     0x2a
#define HW_C6_PR_512KB                   0x24
#define HW_C6_PR_512MB                   0x38
#define HW_C6_PR_64KB                    0x1e
#define HW_C6_PR_64MB                    0x32
#define HW_C6_PR_8KB                     0x18
#define HW_C6_PR_8MB                     0x2c
#define HW_C6_PR_ENABLE                  0x1
#define HW_C9_TCMR_16KB                  0xa
#define HW_C9_TCMR_32MB                  0x20
#define HW_CTRDG_ROM                     0x8000000
#define HW_DTCM                          ((u32)SDK_AUTOLOAD_DTCM_START)
#define HW_IOREG                         0x4000000
#define HW_ITCM_IMAGE                    0x1000000
#define HW_MAIN_MEM_MAIN                 0x2000000
#define HW_MAIN_MEM_SHARED               0x27ff000
#define HW_MAIN_MEM_SUB                  0x27e0000
#define SDK_AUTOLOAD_DTCM_START          data_027e0000
#define INITi_HW_DTCM                    data_027e0000

asm void func_02000a78 (void)
{
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, = HW_C1_ICACHE_ENABLE | HW_C1_DCACHE_ENABLE        \
	          | HW_C1_ITCM_ENABLE | HW_C1_DTCM_ENABLE          \
	          | HW_C1_ITCM_LOAD_MODE | HW_C1_DTCM_LOAD_MODE    \
	          | HW_C1_LD_INTERWORK_DISABLE                     \
	          | HW_C1_PROTECT_UNIT_ENABLE

	bic r0, r0, r1
	mcr p15, 0, r0, c1, c0, 0
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 0
	mcr p15, 0, r0, c7, c6, 0
	mcr p15, 0, r0, c7, c10, 4

#define SET_PROTECTION_A(id, adr, siz)        ldr r0, = (adr | HW_C6_PR_ ## siz | HW_C6_PR_ENABLE)
#define SET_PROTECTION_B(id, adr, siz)        mcr p15, 0, r0, c6, id, 0
#define REGION_BIT(a, b, c, d, e, f, g, h)     (((a) << 0) | ((b) << 1) | ((c) << 2) | ((d) << 3) | ((e) << 4) | ((f) << 5) | ((g) << 6) | ((h) << 7))
#define REGION_ACC(a, b, c, d, e, f, g, h)     (((a) << 0) | ((b) << 4) | ((c) << 8) | ((d) << 12) | ((e) << 16) | ((f) << 20) | ((g) << 24) | ((h) << 28))
#define NA      0
#define RW      1
#define RO      5

	SET_PROTECTION_A(c0, HW_IOREG, 64MB)
	SET_PROTECTION_B(c0, HW_IOREG, 64MB)

	SET_PROTECTION_A(c1, HW_MAIN_MEM_MAIN, 8MB)
	SET_PROTECTION_B(c1, HW_MAIN_MEM_MAIN, 8MB)

	SET_PROTECTION_A(c2, HW_MAIN_MEM_SUB, 128KB)
	SET_PROTECTION_B(c2, HW_MAIN_MEM_SUB, 128KB)

	SET_PROTECTION_A(c3, HW_CTRDG_ROM, 128MB)
	SET_PROTECTION_B(c3, HW_CTRDG_ROM, 128MB)

	ldr r0, = SDK_AUTOLOAD_DTCM_START
	orr r0, r0, #HW_C6_PR_16KB
	orr r0, r0, #HW_C6_PR_ENABLE
	SET_PROTECTION_B(c4, HW_DTCM, 16KB)

	SET_PROTECTION_A(c5, HW_ITCM_IMAGE, 16MB)
	SET_PROTECTION_B(c5, HW_ITCM_IMAGE, 16MB)

	SET_PROTECTION_A(c6, HW_BIOS, 32KB)
	SET_PROTECTION_B(c6, HW_BIOS, 32KB)

	SET_PROTECTION_A(c7, HW_MAIN_MEM_SHARED, 4KB)
	SET_PROTECTION_B(c7, HW_MAIN_MEM_SHARED, 4KB)


	mov r0, #HW_C9_TCMR_32MB
	mcr p15, 0, r0, c9, c1, 1
	ldr r0, = INITi_HW_DTCM
	orr r0, r0, #HW_C9_TCMR_16KB
	mcr p15, 0, r0, c9, c1, 0
	mov r0, #REGION_BIT(0, 1, 0, 0, 0, 0, 1, 0)
	mcr p15, 0, r0, c2, c0, 1
	mov r0, #REGION_BIT(0, 1, 0, 0, 0, 0, 1, 0)
	mcr p15, 0, r0, c2, c0, 0
	mov r0, #REGION_BIT(0, 1, 0, 0, 0, 0, 0, 0)
	mcr p15, 0, r0, c3, c0, 0
	ldr r0, = REGION_ACC(RW, RW, NA, NA, NA, RW, RO, NA)
	mcr p15, 0, r0, c5, c0, 3
	ldr r0, = REGION_ACC(RW, RW, NA, RW, RW, RW, RO, RW)
	mcr p15, 0, r0, c5, c0, 2
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, = HW_C1_ICACHE_ENABLE | HW_C1_DCACHE_ENABLE | HW_C1_CACHE_ROUND_ROBIN    \
	          | HW_C1_ITCM_ENABLE | HW_C1_DTCM_ENABLE                                \
	          | HW_C1_SB1_BITSET | HW_C1_EXCEPT_VEC_UPPER                            \
	          | HW_C1_PROTECT_UNIT_ENABLE

	orr r0, r0, r1
	mcr p15, 0, r0, c1, c0, 0
	bx lr
}
