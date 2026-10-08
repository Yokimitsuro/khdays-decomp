

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

/* Ov105_WMi_StartMP -- WMi_StartMP: start the MP (multi-poll) protocol from PARENT /
 * CHILD: a child must be in power-save mode 1, MP must not be running, the receive
 * buffer a multiple of 64 and the send buffer of 32 bytes, both large enough unless
 * the size pre-check is disabled; the request carries the buffers (receive size in
 * halfwords), a zeroed MP parameter block and the temporary parameters.
 */
WMErrCode Ov105_WMi_StartMP(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, WMMPTmpParam *tmpParam)
{
    WMErrCode result;
    WMArm9Buf *p = Ov105_WMi_GetSystemWork();
    WMStatus *status = p->status;

    result = Ov105_WMi_CheckStateEx(2, WM_STATE_PARENT, WM_STATE_CHILD);
    WM_CHECK_RESULT(result);

    DC_InvalidateRange(&(status->aid), 2);
    DC_InvalidateRange(&(status->pwrMgtMode), 2);

    if (status->aid != 0 && status->pwrMgtMode != 1) {
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    DC_InvalidateRange(&(status->mp_flag), 4);

    if (status->mp_flag == TRUE) {
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    if ((recvBufSize & 0x3f) != 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if ((sendBufSize & 0x1f) != 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    DC_InvalidateRange(&(status->mp_ignoreSizePrecheckMode), sizeof(status->mp_ignoreSizePrecheckMode));

    if (status->mp_ignoreSizePrecheckMode == FALSE) {
        if (recvBufSize < Ov105_WM_GetMPReceiveBufferSize()) {
            return WM_ERRCODE_INVALID_PARAM;
        }

        if (sendBufSize < Ov105_WM_GetMPSendBufferSize()) {
            return WM_ERRCODE_INVALID_PARAM;
        }
    }

    Ov105_WMi_SetCallbackTable(WM_APIID_START_MP, callback);

    {
        WMStartMPReq Req;

        MI_CpuClear32(&Req, sizeof(Req));

        Req.apiid = WM_APIID_START_MP;
        Req.recvBuf = (u32 *)recvBuf;
        Req.recvBufSize = (u32)(recvBufSize / 2);
        Req.sendBuf = (u32 *)sendBuf;
        Req.sendBufSize = (u32)sendBufSize;

        MI_CpuClear32(&Req.param, sizeof(Req.param));
        MI_CpuCopy32(tmpParam, &Req.tmpParam, sizeof(Req.tmpParam));

        result = Ov105_WMi_SendCommandDirect(&Req, sizeof(Req));
        WM_CHECK_RESULT(result);
    }

    return WM_ERRCODE_OPERATING;
}
