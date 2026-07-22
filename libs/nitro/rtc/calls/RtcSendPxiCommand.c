/* Sends one RTC command through PXI channel 5; true when the FIFO accepted it. */
extern int func_020093e8(int channel, int data, int flag);

int RtcSendPxiCommand(int cmd) {
    return func_020093e8(5, (cmd << 8) & 0x7f00, 0) >= 0;
}
