//
//  sss-constants.h
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef SSS_CONSTANTS_H
#define SSS_CONSTANTS_H

#if defined(TARGET_NANOS)
#define SSS_MAX_SHARE_COUNT 10
#else
#define SSS_MAX_SHARE_COUNT 16
#endif
#define SSS_MIN_SECRET_SIZE 16
#define SSS_MAX_SECRET_SIZE 32

#define SSS_ERROR_SECRET_TOO_LONG       (-101)
#define SSS_ERROR_TOO_MANY_SHARES       (-102)
#define SSS_ERROR_INTERPOLATION_FAILURE (-103)
#define SSS_ERROR_CHECKSUM_FAILURE      (-104)
#define SSS_ERROR_SECRET_TOO_SHORT      (-105)
#define SSS_ERROR_SECRET_NOT_EVEN_LEN   (-106)
#define SSS_ERROR_INVALID_THRESHOLD     (-107)

#endif /* SSS_CONSTANTS_H */
