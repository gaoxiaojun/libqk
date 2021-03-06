/******************************************************************************
 * Quantitative Kit Library                                               *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#ifndef QK_VERSION_H
#define QK_VERSION_H

// Quantitative Trading Library

#define QK_VERSION_MAJOR 1
#define QK_VERSION_MINOR 11
#define QK_VERSION_PATCH 1
#define QK_VERSION_IS_RELEASE 0
#define QK_VERSION_SUFFIX "dev"

#define QK_VERSION_HEX  ((QK_VERSION_MAJOR << 16) | \
                         (QK_VERSION_MINOR <<  8) | \
                         (QK_VERSION_PATCH))

#endif // QK_VERSION_H
