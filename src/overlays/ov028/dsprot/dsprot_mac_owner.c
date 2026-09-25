/* DS Protect 1.10, emulator check (ov028 0x0208abd0-0x0208acf0): the console's MAC address and
 * owner profile against the defaults of an early emulator (MAC 00:09:BF:00:00:31 with a 1/1
 * birthday and no nickname), or an all-zero MAC. Both checks run inside encrypted ranges.
 * Reconstruction after taxicat1/dsprot (branch 1.10). */
#include "dsprot_types.h"
#include "dsprot_ranges.h"

#define KEY_MAC_OWNER_1     0x66f2
#define KEY_MAC_OWNER_2     0x2f11
#define MAC_ADDRESS_SIZE    6
#define MAC_ENCODE_BYTE     0xff

/* The emulator's MAC, stored inverted (ov028 .rodata 0x0208b560, see
 * src/overlays/ov028/data/ov028_dsprot_bad_mac_0208b560.c). */
extern const u8 data_ov028_0208b560[MAC_ADDRESS_SIZE];

/* MACOwner_IsBad */
u32 func_ov028_0208abd0(void)
{
    u8 macAddress[MAC_ADDRESS_SIZE];
    OSOwnerInfo ownerInfo;
    int i;

    /* both zeroings are needed: the range markers stop the compiler from merging them */
    i = 0;
    OS_GetMacAddress(&macAddress[0]);

    DSPROT_RANGE_BEGIN(KEY_MAC_OWNER_1)
    for (i = 0; i < MAC_ADDRESS_SIZE; i++) {
        if (data_ov028_0208b560[i] != (macAddress[i] ^ MAC_ENCODE_BYTE)) {
            break;
        }
    }
    DSPROT_RANGE_END(KEY_MAC_OWNER_1)

    func_02003a20(&ownerInfo);

    DSPROT_RANGE_BEGIN(KEY_MAC_OWNER_2)
    /* `i` doubles as the result */
    if (i == MAC_ADDRESS_SIZE && ownerInfo.birthday.month == 1 && ownerInfo.birthday.day == 1
        && ownerInfo.nickNameLength == 0) {
        i = 1;
        goto exit;
    }
    for (i = 0; i < MAC_ADDRESS_SIZE; i++) {
        if (macAddress[i] != 0) {
            i = 0;
            goto exit;
        }
    }
    i = 1;
exit:
    DSPROT_RANGE_END(KEY_MAC_OWNER_2)

    return i;
}
