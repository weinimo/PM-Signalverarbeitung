#ifndef BASICDEFINITIONS_H
#define BASICDEFINITIONS_H

#include <stdint.h>

#define SPROC_NBUFFERCHUNKS      2
#define SPROC_SAMPLEDATASIZE 10000

typedef struct
{
    int32_t data[SPROC_SAMPLEDATASIZE];
} bufferchunk;

typedef struct
{

} procdata;

#endif // BASICDEFINITIONS_H
