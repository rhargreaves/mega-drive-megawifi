#pragma once
#include "mw/megawifi.h"

#define ERR_BASE 100
#define ERR_INVALID_APPLE_MIDI_SIGNATURE ERR_BASE;
#define ERR_UNEXPECTED_CHANNEL (ERR_BASE + 1)
#define ERR_APPLE_MIDI_EXCH_PKT_TOO_SMALL (ERR_BASE + 2)
#define ERR_INVALID_TIMESYNC_PKT_LENGTH (ERR_BASE + 3)

#define MEGADRIVE_SSRC 0x9E915150
#define CH_CONTROL_PORT 1
#define CH_MIDI_PORT 2

#define NAME_LEN 16

#define UDP_PKT_LEN (16 + NAME_LEN)
#define UDP_PKT_BUFFER_LEN 64
#define APPLE_MIDI_EXCH_PKT_MIN_LEN 17

#define TIMESYNC_PKT_LEN (9 * 4)

#define APPLE_MIDI_SIGNATURE 0xFFFF

typedef enum mw_err mw_err;

union AppleMidiTimeSyncPacket {
    u8 byte[TIMESYNC_PKT_LEN];
    struct {
        u16 signature;
        char ck[2];
        u32 senderSSRC;
        u8 count;
        u8 padding[3];
        u32 timestamp1Hi;
        u32 timestamp1Lo;
        u32 timestamp2Hi;
        u32 timestamp2Lo;
        u32 timestamp3Hi;
        u32 timestamp3Lo;
    };
};

typedef union AppleMidiTimeSyncPacket AppleMidiTimeSyncPacket;

union AppleMidiExchangePacket {
    u8 byte[UDP_PKT_LEN];
    struct {
        u16 signature;
        char command[2];
        u32 version;
        u32 initToken;
        u32 senderSSRC;
        char name[NAME_LEN];
    };
};

typedef union AppleMidiExchangePacket AppleMidiExchangePacket;

mw_err recv_event(void);
