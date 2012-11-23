#ifndef BASICDEFINITIONS_H
#define BASICDEFINITIONS_H

#include <stdint.h>

#include <QMetaType>

#define SPROC_NBUFFERCHUNKS       4
#define SPROC_SAMPLEDATASIZE  10000                                             // Size of a buffer chunk in 32 bit words. Number must be multiple of 2.


typedef union bc_union_t {
    struct bc_struct_t
    {
        double           first[SPROC_SAMPLEDATASIZE/2];
        double           second[SPROC_SAMPLEDATASIZE/2];
    } channels;
    double               data[SPROC_SAMPLEDATASIZE];
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
    uint64_t            doubleword;
} procdata;

Q_DECLARE_METATYPE(bufferchunk)
Q_DECLARE_METATYPE(bufferchunk*)
//Q_DECLARE_METATYPE(bufferchunk*const)
Q_DECLARE_METATYPE(procdata)
Q_DECLARE_METATYPE(procdata*)

#endif // BASICDEFINITIONS_H
