/* Slot-2 tick of the ov257 trail helper: both parts take the +8 source pose. */
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x30]; Srt pose; };
struct Helper { struct Part *a; struct Part *b; Srt *src; };

void func_ov257_020d291c(int *node)
{
    struct Helper *h = (struct Helper *)node[1];

    h->a->pose = *h->src;
    h->b->pose = *h->src;
}
