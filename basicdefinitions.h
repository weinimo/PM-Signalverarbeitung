#ifndef BASICDEFINITIONS_H
#define BASICDEFINITIONS_H

#include <stdint.h>

#define SPROC_NBUFFERCHUNKS      2
#define SPROC_SAMPLEDATASIZE 10000

typedef struct
{
    int32_t             data[SPROC_SAMPLEDATASIZE];
} bufferchunk;

typedef union {
    struct {
        uint8_t         protocolVersion;
        uint8_t         clientID;
        uint16_t        packetCounter;
        uint16_t        direction;
        uint16_t        powerLevel;
    } fields;
    uint32_t            words[2];
} procdata;

#endif // BASICDEFINITIONS_H
