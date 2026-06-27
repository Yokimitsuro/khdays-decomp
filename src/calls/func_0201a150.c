extern void SND_SetPlayerChannelPriority(int player, int priority);

struct S { unsigned char *volatile p; };

void func_0201a150(struct S *s, int priority)
{
    if (s->p) {
        SND_SetPlayerChannelPriority(s->p[0x3c], priority);
    }
}
