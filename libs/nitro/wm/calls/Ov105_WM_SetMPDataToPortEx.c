

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

/* Ov105_WM_SetMPDataToPortEx -- WM_SetMPDataToPortEx: queue `sendDataSize` bytes for the next
 * MP frame on `port` with priority `prio` to the aids in `destBitmap` (SET_MP_DATA);
 * a parent needs a connected child, the data must not be the MP send buffer itself
 * and must be 1..512 bytes; `callback`/`arg` travel with the request.
 */
WMErrCode Ov105_WM_SetMPDataToPortEx(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio)
{
    WMErrCode result;
    BOOL isParent;
    u16 mpReadyBitmap = 0x0001;
    u16 childBitmap = 0x0001;
    WMArm9Buf *p = Ov105_WMi_GetSystemWork();
    WMStatus *status = p->status;

    result = Ov105_WMi_CheckStateEx(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
    WM_CHECK_RESULT(result);

    DC_InvalidateRange(&(status->aid), 2);
    isParent = (status->aid == 0) ? TRUE : FALSE;

    if (isParent == TRUE) {
        DC_InvalidateRange(&(status->child_bitmap), 2);
        childBitmap = status->child_bitmap;
        DC_InvalidateRange(&(status->mp_readyBitmap), 2);
        mpReadyBitmap = status->mp_readyBitmap;
    }

    if (sendData == NULL) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (childBitmap == 0) {
        return WM_ERRCODE_NO_CHILD;
    }

    DC_InvalidateRange(&(status->mp_sendBuf), 2);

    if ((void *)sendData == (void *)status->mp_sendBuf) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (sendDataSize > WM_SIZE_MP_DATA_MAX) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if (sendDataSize == 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    DC_StoreRange((void *)sendData, sendDataSize);

    result = Ov105_WMi_SendCommand(WM_APIID_SET_MP_DATA, 7,
                                 (u32)sendData,
                                 (u32)sendDataSize,
                                 (u32)destBitmap, (u32)port, (u32)prio, (u32)callback, (u32)arg);
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}
