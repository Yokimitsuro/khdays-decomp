/* Hardware registers and the memory map, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_HW_H
#define NITRO_HW_H

#include "nitro/types.h"


enum {
    HW_ITCM = 0x01ff8000,
    HW_ITCM_SIZE = 0x8000,
    HW_DTCM_SIZE = 0x4000
};

#define HW_ROM_HEADER_BUF 0x027ffe00

#define HW_MAIN_MEM 0x02000000

#define HW_CARD_ROM_HEADER      0x027FFA80

#define HW_CARD_ROM_HEADER_SIZE 0x160

#define HW_CPU_CLOCK_ARM9 67027964

#define REG_CARDCNT            0x040001a4

#define REG_CARD_DATA_ADDR     0x04100010

#define reg_CARD_DATA (*(vu32 *)REG_CARD_DATA_ADDR)

#define REG_CARD_CONTROL (*(vu32 *)0x040001a4)

#define REG_EXMEMCNT_ADDR 0x04000204

#define REG_IME_ADDR      0x04000208

#define REG_PAUSE_ADDR    0x04000300

#define REG_OS_PAUSE_CHK_MASK 0x0001

#define REG_MI_EXMEMCNT_ROM1st_SHIFT 2

#define REG_MI_EXMEMCNT_ROM1st_MASK  0x000c

#define REG_MI_EXMEMCNT_ROM2nd_SHIFT 4

#define REG_MI_EXMEMCNT_ROM2nd_MASK  0x0010

#define REG_MI_EXMEMCNT_EP_SHIFT     15

#define REG_MI_EXMEMCNT_EP_MASK      0x8000

#define HW_CTRDG_ROM 0x08000000

#define HW_CTRDG_MODULE_INFO_BUF        (HW_MAIN_MEM + 0x007ffc30)

#define HW_SET_CTRDG_MODULE_INFO_ONCE   (HW_MAIN_MEM + 0x007fff9a)

#define HW_IS_CTRDG_EXIST               (HW_MAIN_MEM + 0x007fff9b)

#define HW_WM_BOOT_BUF            0x027ffc40

#define REG_DIVCNT          (*(vu16 *)0x04000280)

#define REG_DIV_NUMER       (*(vu64 *)0x04000290)

#define REG_DIV_DENOM       (*(vs64 *)0x04000298)

#define REG_DIV_RESULT      (*(vs64 *)0x040002a0)

#define REG_SQRTCNT         (*(vu16 *)0x040002b0)

#define REG_SQRT_RESULT     (*(vu32 *)0x040002b4)

#define REG_SQRT_PARAM      (*(u64 *)0x040002b8)

#define REG_DISP3DCNT_ADDR      0x04000060

#define REG_BG0CNT_ADDR         0x04000008

#define REG_BG0OFS_ADDR         0x04000010

#define REG_CLEAR_COLOR_ADDR    0x04000350

#define REG_CLEAR_DEPTH_ADDR    0x04000354

#define REG_CLRIMAGE_OFFSET_ADDR 0x04000356

#define REG_FOG_COLOR_ADDR      0x04000358

#define REG_FOG_OFFSET_ADDR     0x0400035c

#define REG_EDGE_COLOR_0_L_ADDR 0x04000330

#define REG_FOG_TABLE_0_ADDR    0x04000360

#define REG_MTX_MODE_ADDR       0x04000440

#define REG_POLYGON_ATTR_ADDR   0x040004a4

#define REG_TEXIMAGE_PARAM_ADDR 0x040004a8

#define REG_TEXPLTT_BASE_ADDR   0x040004ac

#define REG_SHININESS_ADDR      0x040004d0

#define REG_END_VTXS_ADDR       0x04000504

#define REG_GXSTAT_ADDR         0x04000600

#define REG_G3X_DISP3DCNT_THS_MASK 0x0002

#define REG_G3X_DISP3DCNT_AAE_MASK 0x0010

#define REG_G3X_DISP3DCNT_ATE_MASK 0x0004

#define REG_G3X_DISP3DCNT_RO_MASK  0x1000

#define REG_G3X_DISP3DCNT_GO_MASK  0x2000

#define REG_G3X_DISP3DCNT_THS_SHIFT 1

#define REG_G3X_GXSTAT_SE_MASK  0x00008000

#define REG_G3X_GXSTAT_GE_MASK  0x08000000

#define REG_G3X_GXSTAT_FI_MASK  0xc0000000

#define REG_G3X_GXSTAT_FI_SHIFT 30

#define REG_G2_BG0CNT_PRIORITY_MASK 0x0003

#define REG_G3X_ALPHA_TEST_REF_MASK 0x001f

#define REG_ALPHA_TEST_REF_ADDR 0x04000340

#define REG_G3_POLYGON_ATTR_PLTT_SHIFT 0

#define REG_G3_POLYGON_ATTR_PM_SHIFT 4

#define REG_G3_POLYGON_ATTR_ALPHA_SHIFT 16

#define REG_G3_POLYGON_ATTR_ID_SHIFT 24

#define REG_G2_BLDCNT_EFFECT_MASK 0x00c0

#define REG_GX_DISPCNT_BG_MASK        0x40000000

#define REG_GX_DISPCNT_O_MASK         0x80000000

#define REG_GXS_DB_DISPCNT_BG_MASK    0x40000000

#define REG_GXS_DB_DISPCNT_O_MASK     0x80000000

#define REG_G3X_DISP3DCNT_TME_MASK    0x0001

#define REG_G3X_DISP3DCNT_PRI_MASK    0x4000

#define REG_GX_MASTER_BRIGHT_E_MOD_SHIFT 14

#define REG_GX_MASTER_BRIGHT_E_MOD_MASK 0xc000

#define REG_GX_MASTER_BRIGHT_E_VALUE_MASK 0x001f

#define HW_LCDC_VRAM     0x06800000

#define HW_VRAM_A_SIZE   0x20000

#define HW_VRAM_B_SIZE   0x20000

#define HW_VRAM_C_SIZE   0x20000

#define HW_VRAM_D_SIZE   0x20000

#define HW_VRAM_E_SIZE   0x10000

#define HW_VRAM_F_SIZE   0x4000

#define HW_LCDC_VRAM_A   (HW_LCDC_VRAM)

#define HW_LCDC_VRAM_B   (HW_LCDC_VRAM_A + HW_VRAM_A_SIZE)

#define HW_LCDC_VRAM_C   (HW_LCDC_VRAM_B + HW_VRAM_B_SIZE)

#define HW_LCDC_VRAM_D   (HW_LCDC_VRAM_C + HW_VRAM_C_SIZE)

#define HW_OBJ_VRAM         0x06400000

#define HW_DB_OBJ_VRAM      0x06600000

#define HW_LCDC_VRAM_E      0x06880000

#define HW_LCDC_VRAM_F      0x06890000

#define HW_LCDC_VRAM_G      0x06894000

#define HW_IOREG 0x04000000

#define REG_DISPCNT_OFFSET 0x000

#define REG_GX_DISPCNT_VRAM_MASK 0x000c0000

#define REG_GX_DISPCNT_MODE_SHIFT 16

#define REG_GX_DISPCNT_MODE_MASK 0x00030000

#define REG_GX_DISPCNT_BG02D3D_SHIFT 3

#define REG_GX_DISPCNT_BG02D3D_MASK 0x00000008

#define REG_GX_DISPCNT_BGMODE_SHIFT 0

#define REG_GX_DISPCNT_BGMODE_MASK 0x00000007

#define HW_CACHE_LINE_SIZE 32

#define HW_COMPONENT_PARAM               0x27fff9c

#define HW_DTCM_SYSRV_OFS_INTR_VECTOR    0x3c

#define HW_OAM                           0x7000000

#define HW_OAM_SIZE                      0x400

#define HW_PLTT                          0x5000000

#define HW_PLTT_SIZE                     0x400

#define HW_PSR_IRQ_MODE                  0x12

#define HW_PSR_SVC_MODE                  0x13

#define HW_PSR_SYS_MODE                  0x1f

#define HW_RESET_VECTOR                  0xffff0000

#define HW_SVC_STACK_SIZE                0x40

#define REG_IME_OFFSET                   0x208

#define REG_VCOUNT_OFFSET                0x6

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

#define HW_DTCM                          ((u32)SDK_AUTOLOAD_DTCM_START)

#define HW_ITCM_IMAGE                    0x1000000

#define HW_MAIN_MEM_MAIN                 0x2000000

#define HW_MAIN_MEM_SHARED               0x27ff000

#define HW_MAIN_MEM_SUB                  0x27e0000

#define HW_REG_BASE                 0x04000000

#define REG_DMA0SAD_ADDR            (HW_REG_BASE + 0x0b0)

#define REG_GXFIFO_ADDR             (HW_REG_BASE + 0x400)

#define REG_MI_DMA0CNT_E_MASK       0x80000000

#define HW_BG_PLTT ((void *)0x05000000)

#define HW_DB_BG_PLTT ((void *)0x05000400)

#define HW_C7_CACHE_SET_NO_SHIFT     30

#define HW_DCACHE_SIZE               0x1000

#define HW_PSR_IRQ_DISABLE           0x80

#define HW_PSR_IRQ_FIQ_DISABLE       0xc0

#define HW_C1_PROTECT_UNIT_ENABLE    0x00000001

#define HW_PSR_CPU_MODE_MASK         0x1f

#define HW_PSR_ARM_STATE             0x0

#define HW_PSR_THUMB_STATE           0x20

#define HW_PSR_FIQ_DISABLE           0x40

#define HW_ITCM_END                  0x02000000

#define REG_EXMEM_CNT (*(volatile u16 *)0x04000204)

#define HW_MAIN_MEM_MAIN_END 0x023e0000

#define HW_MAIN_MEM_DEBUGGER 0x02700000

#define HW_ITCM_ARENA_HI_DEFAULT 0x02000000

#define HW_SHARED_ARENA_HI_DEFAULT 0x027ff680

#define HW_WRAM 0x037f8000

#define HW_DTCM_IRQ_STACK_END 0x027e3f80

#define HW_DTCM_SVC_STACK     0x027e3f80

#define HW_DTCM_SVC_STACK_ADDR (HW_DTCM + 0x3f80)

#define HW_DTCM_IRQ_STACK_END_ADDR (HW_DTCM + 0x3f80)

#define HW_NVRAM_USER_INFO 0x027ffc80

#define HW_MAIN_MEM_SYSTEM 0x027ffc00

#define HW_BUTTON_XY_BUF   0x027fffa8

#define REG_TM0CNT_L_OFFSET 0x100

#define REG_IF_OFFSET 0x214

#define REG_OS_IE_T0_SHIFT 3

#define REG_OS_TM0CNT_H_E_MASK 0x0080

#define REG_OS_TM0CNT_H_I_MASK 0x0040

#define REG_TM0CNT_L_ADDR         0x04000100

#define REG_TM0CNT_H_ADDR         0x04000102

#define REG_IF       (*(volatile u32 *)0x04000214)

#define REG_TM0CNT_H (*(volatile u16 *)0x04000102)

#define REG_TM0CNT_L (*(volatile u16 *)0x04000100)

#define REG_PXI_FIFO_CNT_E_MASK         0x8000

#define REG_PXI_FIFO_CNT_ERR_MASK       0x4000

#define REG_PXI_FIFO_CNT_RECV_EMP_MASK  0x0100

#define REG_PXI_FIFO_CNT_SEND_FULL_MASK 0x0002

#define HW_RTC_BUF                  0x027ffde8   /* OSSystemWork.real_time_clock[8] */

#define REG_POWCNT_OFFSET 0x304

#define REG_POWCNT_ADDR (HW_REG_BASE + REG_POWCNT_OFFSET)

#define REG_GX_POWCNT_LCD_MASK 0x0001

#define REG_IF_ADDR 0x04000214

#define REG_DISPCNT_ADDR 0x04000000

#define REG_DB_DISPCNT_ADDR 0x04001000

#define REG_GXS_DB_DISPCNT_MODE_MASK 0x00010000

#define HW_VBLANK_COUNT_BUF 0x027ffc3c

#define HW_SYSTEM_CLOCK 33513982

#define REG_PMIC_CTL_ADDR 0

#define REG_PMIC_OP_CTL_ADDR 2

#define HW_TOUCHPANEL_BUF   0x027fffaa   /* this SDK: the touch sample in the system work at HW_SYS_WORK + 0xaa */

#define REG_DIVCNT_ADDR     0x04000280

#define REG_DIV_NUMER_ADDR  0x04000290

#define REG_DIV_DENOM_ADDR  0x04000298

#define REG_DIV_RESULT_ADDR 0x040002a0

#define REG_CP_DIVCNT_BUSY_MASK 0x8000

#define REG_BG1CNT_ADDR    0x0400000a

#define REG_BG2CNT_ADDR    0x0400000c

#define REG_BG3CNT_ADDR    0x0400000e

#define REG_DB_BG0CNT_ADDR 0x04001008

#define REG_DB_BG1CNT_ADDR 0x0400100a

#define REG_DB_BG2CNT_ADDR 0x0400100c

#define REG_DB_BG3CNT_ADDR 0x0400100e

#define REG_BG0CNT_OFFSET    0x0008

#define REG_BG1CNT_OFFSET    0x000a

#define REG_DB_BG0CNT_OFFSET 0x1008

#define REG_DB_BG1CNT_OFFSET 0x100a

#define REG_G2_BG0CNT_BGPLTTSLOT_MASK 0x2000

#define REG_G3_POLYGON_ATTR_ALPHA_MASK 0x001f0000

#define REG_G3_POLYGON_ATTR_FR_MASK 0x00000080

#define REG_G3_POLYGON_ATTR_BK_SHIFT 6

#define REG_G3_POLYGON_ATTR_BK_MASK 0x00000040

#define REG_G3_POLYGON_ATTR_LE_SHIFT 0

#define REG_G3_POLYGON_ATTR_LE_MASK 0x0000000f

#define REG_G3_POLYGON_ATTR_ID_MASK 0x3f000000

#define REG_G3_POLYGON_ATTR_PM_MASK 0x00000030

#define REG_G3_TEXIMAGE_PARAM_TGEN_MASK 0xc0000000

#define REG_G3_TEXIMAGE_PARAM_FT_MASK 0x00080000

#define REG_G3_TEXIMAGE_PARAM_FS_MASK 0x00040000

#define REG_G3_TEXIMAGE_PARAM_RT_MASK 0x00020000

#define REG_G3_TEXIMAGE_PARAM_RS_MASK 0x00010000

#define REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT 30

#define REG_G3_TEXIMAGE_PARAM_TEXFMT_SHIFT 26

#define REG_G3_TEXIMAGE_PARAM_TEXFMT_MASK 0x1c000000

#endif
