//
//  shard.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef SHARD_H
#define SHARD_H

#include <stdint.h>
#include <stdlib.h>

typedef struct sskr_shard_struct {
    uint16_t identifier;
    uint8_t group_index;
    uint8_t group_threshold;
    uint8_t group_count;
    uint8_t member_index;
    uint8_t member_threshold;
    uint8_t value_len;
    uint8_t value[32];
} sskr_shard_t;

#endif /* SHARD_H */
