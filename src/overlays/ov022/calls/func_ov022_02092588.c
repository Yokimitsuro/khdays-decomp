/* ov022: post the actor's contact packet, if the sender is listening.
 *
 * Builds a twenty-byte packet on the stack from the source record: its point,
 * two counters that always start at zero, and a packed word carrying the kind,
 * a fixed mode, and two ids of twelve and eight bits.
 *
 * The packed word is never initialised as a whole, only field by field, which
 * is why every one of its stores reads it back first.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define PACKET_CHANNEL 0xa
#define PACKET_MODE 6

struct Vec3 {
    int x, y, z;
};

struct Source {
    u8 nKind;                    /* 0x00 */
    u8 pad01[3];
    struct Vec3 vec;             /* 0x04 */
    u8 pad10[6];
    u16 nId;                     /* 0x16 */
    u16 nExtra;                  /* 0x18 */
};

struct Packet {
    struct Vec3 vec;             /* 0x00 */
    u16 nSent;                   /* 0x0c */
    u16 nAcked;                  /* 0x0e */
    unsigned nKind : 2;          /* 0x10 bits 0-1 */
    unsigned nSpare : 3;         /* bits 2-4 */
    unsigned nMode : 4;          /* bits 5-8 */
    unsigned nPad9 : 2;          /* bits 9-10 */
    unsigned nId : 12;           /* bits 11-22 */
    unsigned nExtra : 8;         /* bits 23-30 */
    unsigned nPad31 : 1;         /* bit 31 */
};

extern int func_02030694(void);
extern void func_02031258(int nChannel, struct Packet *pPacket, int nSize);

void func_ov022_02092588(int nUnused, struct Source *pSrc)
{
    struct Packet packet;

    if (func_02030694() == 0) {
        return;
    }
    packet.vec = pSrc->vec;
    packet.nSent = 0;
    packet.nAcked = 0;
    packet.nKind = pSrc->nKind;
    packet.nSpare = 0;
    packet.nMode = PACKET_MODE;
    packet.nId = pSrc->nId;
    packet.nExtra = pSrc->nExtra;
    func_02031258(PACKET_CHANNEL, &packet, 0x14);
}
