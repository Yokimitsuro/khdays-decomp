/* PXI command veneer: forwards to RtcSendPxiCommand with command 0x27. */
extern void *RtcSendPxiCommand();

void *RTCi_WriteRawStatus2Async() {
    return RtcSendPxiCommand(0x27);
}
