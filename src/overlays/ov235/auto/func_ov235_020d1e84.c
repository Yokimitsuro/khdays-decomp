/* Pose sync of an ov235 helper: both of its parts (+4 and +8) copy the +0xc source pose into their
 * +0x30 pose. */
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x30]; Srt pose; };
struct Helper { int owner; struct Part *a; struct Part *b; Srt *src; };

void func_ov235_020d1e84(int node)
{
    struct Helper *h = *(struct Helper **)(node + 4);

    h->a->pose = *h->src;
    h->b->pose = *h->src;
}
