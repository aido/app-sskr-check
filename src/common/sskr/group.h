//
//  group.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef GROUP_H
#define GROUP_H

#include <stdlib.h>
#include <stdint.h>

typedef struct sskr_group_descriptor_struct {
    uint8_t threshold;
    uint8_t count;
} sskr_group_descriptor_t;

#endif /* GROUP_H */
