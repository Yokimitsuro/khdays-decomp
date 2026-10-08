

/* NitroSDK WM (wireless manager) library, ARM9 side, as linked into ov105. */

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/wm.h"

#define PXI_FIFO_TAG_WM         10
#define PXI_PROC_ARM7           1
#define MI_DMA_MAX_NUM          3

                  /* 0x40 = WM_PARENT_PARAM_SIZE */

/* The ARM7-owned status block; only the offsets the ARM9 side reads are named. */

/* wm_system.c file statics, one .bss block: wmInitialized (u16) then wm9buf. */
extern u16 data_ov105_020bfa20;
#define wmInitialized data_ov105_020bfa20
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

extern WMArm9Buf *Ov105_WMi_GetSystemWork(void);      /* WMi_GetSystemWork */
extern WMErrCode Ov105_WMi_CheckInitialized(void);       /* WMi_CheckInitialized */
extern WMErrCode Ov105_WMi_CheckIdle(void);       /* WMi_CheckIdle */
extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);   /* WMi_CheckStateEx */
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);   /* WMi_SendCommand */
extern WMErrCode Ov105_WMi_SendCommandDirect(void *data, u32 length);   /* WMi_SendCommandDirect */
extern void Ov105_WMi_SetCallbackTable(WMApiid id, WMCallbackFunc callback);   /* WMi_SetCallbackTable */
extern int Ov105_WM_GetMPSendBufferSize(void);             /* WM_GetMPSendBufferSize */
extern int Ov105_WM_GetMPReceiveBufferSize(void);             /* WM_GetMPReceiveBufferSize */
extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *dst, u32 size);   /* MIi_CpuClear32 */
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);
#define MI_CpuClear32(dst, size) INITi_CpuClear32_0x01ff86fc(0, (dst), (size))
#define MI_CpuCopy32(src, dst, size) MIi_CpuCopy32((src), (dst), (size))

/* Ov105_WM_MeasureChannel -- WM_MeasureChannel: ask the ARM7 to measure the occupancy of
 * `channel` for `measureTime` ms (MEASURE_CHANNEL) with the given CCA mode and energy
 * detection threshold; IDLE only.
 */
WMErrCode Ov105_WM_MeasureChannel(WMCallbackFunc callback, u16 ccaMode, u16 edThreshold, u16 channel, u16 measureTime)
{
    WMErrCode result;
    WMArm9Buf *p = Ov105_WMi_GetSystemWork();

    result = WMi_CheckState(WM_STATE_IDLE);
    WM_CHECK_RESULT(result);

    Ov105_WMi_SetCallbackTable(WM_APIID_MEASURE_CHANNEL, callback);

    {
        WMMeasureChannelReq Req;

        Req.apiid = WM_APIID_MEASURE_CHANNEL;
        Req.ccaMode = ccaMode;
        Req.edThreshold = edThreshold;
        Req.channel = channel;
        Req.measureTime = measureTime;

        result = Ov105_WMi_SendCommandDirect(&Req, sizeof(Req));
        WM_CHECK_RESULT(result);
    }

    return WM_ERRCODE_OPERATING;
}
