//
//  sskr-constants.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef SSKR_CONSTANTS_H
#define SSKR_CONSTANTS_H

#include "sss-constants.h"

#define SSKR_METADATA_LENGTH_BYTES       5
#define SSKR_MIN_STRENGTH_BYTES          16
#define SSKR_MAX_STRENGTH_BYTES          32
#define SSKR_MAX_GROUP_COUNT             1
#define SSKR_MIN_SERIALIZED_LENGTH_BYTES (SSKR_METADATA_LENGTH_BYTES + SSKR_MIN_STRENGTH_BYTES)

#define SSKR_ERROR_NOT_ENOUGH_SERIALIZED_BYTES (-1)
#define SSKR_ERROR_SECRET_TOO_SHORT            (-2)
#define SSKR_ERROR_INVALID_GROUP_THRESHOLD     (-3)
#define SSKR_ERROR_INVALID_SINGLETON_MEMBER    (-4)
#define SSKR_ERROR_INSUFFICIENT_SPACE          (-5)
#define SSKR_ERROR_INVALID_RESERVED_BITS       (-6)
#define SSKR_ERROR_SECRET_LENGTH_NOT_EVEN      (-7)
#define SSKR_ERROR_INVALID_SHARD_SET           (-8)
#define SSKR_ERROR_EMPTY_SHARD_SET             (-9)
#define SSKR_ERROR_DUPLICATE_MEMBER_INDEX      (-10)
#define SSKR_ERROR_NOT_ENOUGH_MEMBER_SHARDS    (-11)
#define SSKR_ERROR_INVALID_MEMBER_THRESHOLD    (-12)
#define SSKR_ERROR_INVALID_PADDING             (-13)
#define SSKR_ERROR_NOT_ENOUGH_GROUPS           (-14)
#define SSKR_ERROR_INVALID_SHARD_BUFFER        (-15)
#define SSKR_ERROR_SECRET_TOO_LONG             (-16)
#define SSKR_ERROR_INVALID_GROUP_LENGTH        (-17)
#define SSKR_ERROR_INVALID_GROUP_COUNT         (-18)

#endif /* SSKR_CONSTANTS_H */
