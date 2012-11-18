#ifndef BASICDEFINITIONS_H
#define BASICDEFINITIONS_H

#include <stdint.h>

#define SPROC_NBUFFERCHUNKS     3
#define SPROC_SAMPLEDATASIZE 1000                                               // Size of a buffer chunk in 32 bit words. Number must be multiple of 2.


typedef union {
    struct
    {
        int32_t         first[SPROC_SAMPLEDATASIZE/2];
        int32_t         second[SPROC_SAMPLEDATASIZE/2];
    } channels;
    int32_t             data[SPROC_SAMPLEDATASIZE];
} bufferchunk;

typedef union {
    struct
    {
        uint8_t         protocolVersion;
        uint8_t         clientID;
        uint16_t        packetCounter;
        uint16_t        direction;
        uint16_t        powerLevel;
    } fields;
    uint32_t            words[2];
} procdata;

#endif // BASICDEFINITIONS_H
