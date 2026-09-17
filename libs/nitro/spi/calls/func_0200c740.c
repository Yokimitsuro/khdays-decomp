typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


/* NitroSDK SPI library, touch panel (tp.c): the ARM9 side of the PXI touch-panel protocol. */
typedef int PXIFifoTag;
typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;
typedef u32 REGType32;
typedef u64 REGType64;   /* the SDK divider registers are written through plain u64 (the pair may merge into stm) */
typedef int TPRequestCommand;
typedef int TPRequestResult;
enum { TP_RESULT_SUCCESS = 0, TP_RESULT_INVALID_PARAMETER, TP_RESULT_ILLEGAL_STATUS, TP_RESULT_EXCLUSIVE, TP_RESULT_PXI_BUSY };
enum { TP_STATE_READY = 0, TP_STATE_SAMPLING, TP_STATE_AUTO_SAMPLING, TP_STATE_AUTO_WAIT_END };
#define SPI_PXI_END_BIT                     0x01000000
#define SPI_PXI_DATA_MASK                   0x0000ffff
#define SPI_PXI_COMMAND_TP_SAMPLING         0x0000
#define SPI_PXI_COMMAND_TP_AUTO_ON          0x0001
#define SPI_PXI_COMMAND_TP_AUTO_OFF         0x0002
#define SPI_PXI_COMMAND_TP_AUTO_SAMPLING    0x0010
#define SPI_PXI_RESULT_SUCCESS              0x0000
#define SPI_PXI_RESULT_INVALID_COMMAND      0x0001
#define SPI_PXI_RESULT_INVALID_PARAMETER    0x0002
#define SPI_PXI_RESULT_ILLEGAL_STATUS       0x0003
#define SPI_PXI_RESULT_EXCLUSIVE            0x0004
#define TP_RAW_MAX  0x1000
#define GX_LCD_SIZE_X 256
#define GX_LCD_SIZE_Y 192
#define TP_CALIBRATE_DOT_SCALE_SHIFT        8
#define TP_CALIBRATE_ORIGIN_SCALE_SHIFT     2
#define HW_TOUCHPANEL_BUF   0x027fffaa   /* this SDK: the touch sample in the system work at HW_SYS_WORK + 0xaa */
#define HW_NVRAM_USER_INFO  0x027ffc80
#define REG_DIVCNT_ADDR     0x04000280
#define REG_DIV_NUMER_ADDR  0x04000290
#define REG_DIV_DENOM_ADDR  0x04000298
#define REG_DIV_RESULT_ADDR 0x040002a0
#define reg_CP_DIVCNT (*(REGType16v *)REG_DIVCNT_ADDR)
#define REG_CP_DIVCNT_BUSY_MASK 0x8000
#define CP_DIV_32_32BIT_MODE 0

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

typedef struct NvTpData {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef void (*TPRecvCallback)(TPRequestCommand command, TPRequestResult result, u16 index);

typedef union SPITpData {
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 dummy : 5;
    } e;
    u32 raw;
    u8 bytes[4];
    u16 halfs[2];
} SPITpData;

typedef struct {
    s32 x0;
    s32 xDotSize;
    s32 xDotSizeInv;
    s32 y0;
    s32 yDotSize;
    s32 yDotSizeInv;
} TPiCalibrateParam;

/* NVRAMConfig.ncd.tp: the factory touch-panel calibration (NVRAMConfig +0x58). */
typedef struct {
    u16 raw_x1;
    u16 raw_y1;
    u8 dx1;
    u8 dy1;
    u16 raw_x2;
    u16 raw_y2;
    u8 dx2;
    u8 dy2;
} NVRAMConfigTp;
typedef struct {
    u8 head[0x58];
    NVRAMConfigTp tp;             /* 0x58 */
} NVRAMConfigNcd;
typedef struct {
    NVRAMConfigNcd ncd;
} NVRAMConfig;

/* tp.c's tpState (data_02046390); this SDK keeps a word ahead of the callback. */
extern struct {
    u32 reserved0;                /* 0x00 */
    TPRecvCallback callback;      /* 0x04 */
    TPData buf;                   /* 0x08 */
    u16 index;                    /* 0x10 */
    u16 frequence;                /* 0x12 */
    TPData *samplingBufs;         /* 0x14 */
    u16 bufSize;                  /* 0x18 */
    u16 reserved1a;               /* 0x1a */
    TPiCalibrateParam calibrate;  /* 0x1c */
    u16 calibrate_flg;            /* 0x34 */
    vu16 state;                   /* 0x36 */
    vu16 err_flg;                 /* 0x38 */
    vu16 command_flg;             /* 0x3a */
} data_02046390;
#define tpState data_02046390

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_Terminate(void);
#define OS_Panic(...) OS_Terminate()
extern u32 func_0200c740(TPCalibrateParam *calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2);
#define TP_CalcCalibrateParam func_0200c740
#define OS_GetSystemWork_nvramUserInfo() ((void *)HW_NVRAM_USER_INFO)

static inline void CP_SetDivImm32_32_NS_(u32 numer, u32 denom)
{
    *(REGType32 *)REG_DIV_NUMER_ADDR = numer;
    *(REGType64 *)REG_DIV_DENOM_ADDR = denom;
}

static inline void CP_SetDiv32_32(u32 numer, u32 denom)
{
    reg_CP_DIVCNT = CP_DIV_32_32BIT_MODE;
    CP_SetDivImm32_32_NS_(numer, denom);
}

static inline u32 CP_IsDivBusy(void)
{
    return (reg_CP_DIVCNT & REG_CP_DIVCNT_BUSY_MASK);
}

static inline void CP_WaitDiv(void)
{
    while (CP_IsDivBusy()) {
    }
}

static inline s32 CP_GetDivResultImm32(void)
{
    return (s32)(*(REGType32 *)REG_DIV_RESULT_ADDR);
}

static inline s32 CP_GetDivResult32(void)
{
    CP_WaitDiv();
    return CP_GetDivResultImm32();
}

static inline void TPi_CopyTpFromSystemWork(TPData *result)
{
    SPITpData spi_tp;

    spi_tp.halfs[0] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 0);
    spi_tp.halfs[1] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 2);

    result->x = (u16)spi_tp.e.x;
    result->y = (u16)spi_tp.e.y;
    result->touch = (u8)spi_tp.e.touch;
    result->validity = (u8)spi_tp.e.validity;
}

static inline void TPi_ErrorAtPxi(TPRequestCommand command)
{
    tpState.err_flg |= (1 << command);

    if (tpState.callback) {
        (tpState.callback)(command, TP_RESULT_PXI_BUSY, 0);
    }
}

/* func_0200c740 -- NitroSDK tp.c: TP_CalcCalibrateParam. */
u32 func_0200c740 (TPCalibrateParam * calibrate,
                           u16 raw_x1, u16 raw_y1,
                           u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2)
{
    s32 rx_width, dx_width, ry_width, dy_width;
    s32 tmp32;
    OSIntrMode enabled;

#define IN_S16_RANGE(x) ((x) < 0x8000 && (x) >= -0x8000)


    if (raw_x1 >= TP_RAW_MAX || raw_y1 >= TP_RAW_MAX || raw_x2 >= TP_RAW_MAX
        || raw_y2 >= TP_RAW_MAX) {
        return 1;
    }
    if (dx1 >= GX_LCD_SIZE_X || dx2 >= GX_LCD_SIZE_X || dy1 >= GX_LCD_SIZE_Y
        || dy2 >= GX_LCD_SIZE_Y) {
        return 1;
    }
    if (dx1 == dx2 || dy1 == dy2 || raw_x1 == raw_x2 || raw_y1 == raw_y2) {
        return 1;
    }

    rx_width = raw_x1 - raw_x2;
    dx_width = dx1 - dx2;

    enabled = OS_DisableInterrupts();

    CP_SetDiv32_32(((u32)rx_width) << TP_CALIBRATE_DOT_SCALE_SHIFT, (u32)dx_width);

    ry_width = raw_y1 - raw_y2;
    dy_width = dy1 - dy2;

    tmp32 = CP_GetDivResult32();
    CP_SetDiv32_32(((u32)ry_width) << TP_CALIBRATE_DOT_SCALE_SHIFT, (u32)dy_width);

    if (!IN_S16_RANGE(tmp32)) {
        (void)OS_RestoreInterrupts(enabled);
        return 1;
    }
    calibrate->xDotSize = (s16)tmp32;
    tmp32 = (s16)((((s32)(raw_x1 + raw_x2) << TP_CALIBRATE_DOT_SCALE_SHIFT)
                   - ((s32)(dx1 + dx2) * calibrate->xDotSize)) >> (TP_CALIBRATE_DOT_SCALE_SHIFT -
                                                                   TP_CALIBRATE_ORIGIN_SCALE_SHIFT +
                                                                   1));
    if (!IN_S16_RANGE(tmp32)) {
        (void)OS_RestoreInterrupts(enabled);
        return 1;
    }
    calibrate->x0 = (s16)tmp32;

    tmp32 = CP_GetDivResult32();
    (void)OS_RestoreInterrupts(enabled);

    if (!IN_S16_RANGE(tmp32)) {
        return 1;
    }

    calibrate->yDotSize = (s16)tmp32;
    tmp32 = (s16)((((s32)(raw_y1 + raw_y2) << TP_CALIBRATE_DOT_SCALE_SHIFT)
                   - ((s32)(dy1 + dy2) * calibrate->yDotSize)) >> (TP_CALIBRATE_DOT_SCALE_SHIFT -
                                                                   TP_CALIBRATE_ORIGIN_SCALE_SHIFT +
                                                                   1));
    if (!IN_S16_RANGE(tmp32)) {
        return 1;
    }

    calibrate->y0 = (s16)tmp32;

    return 0;
}
