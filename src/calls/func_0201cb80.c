extern char data_0204b62c[];
extern void SNDi_FreeVoiceChannel();

void func_0201cb80(int arg0) {
    int i = 0;
    char *entry = data_0204b62c;
    do {
        if (*(int *)(entry + 0x110) << 31 >> 31) {
            SNDi_FreeVoiceChannel(entry, arg0);
        }
        i++;
        entry += 0x174;
    } while (i < 4);
}
