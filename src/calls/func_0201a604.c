extern void SND_PauseSeq(int player, int flag);

void func_0201a604(unsigned char *p, int flag) {
    if (p == 0 || flag == p[0x2e]) return;
    SND_PauseSeq(p[0x3c], flag);
    p[0x2e] = (unsigned char)flag;
}
