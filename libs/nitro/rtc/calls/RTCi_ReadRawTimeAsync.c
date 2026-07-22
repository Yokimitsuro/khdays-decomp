/* PXI command veneer: forwards to RtcSendPxiCommand with command 0x12. */
extern void *RtcSendPxiCommand();

void *RTCi_ReadRawTimeAsync() {
    return RtcSendPxiCommand(0x12);
}
