/** ************************************************************************
 * @file mutex.h
 * @brief Mutural exclusion
 * @author John Yu buyi.yu@wne.edu
 *
 * This file is part of mRTOS.
 *
 * Copyright (C) 2018 John Buyi Yu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************/
#ifndef H19FA4BCD_7A56_4B7D_A67A_063B3FFE82A9
#define H19FA4BCD_7A56_4B7D_A67A_063B3FFE82A9

#include "util.h"
#include "thread.h"

/*
 * Type declarations
 */
struct mutex_cblk_s;
struct mutex_schinfo_s;

typedef struct mutex_cblk_s mutex_cblk_t;
typedef struct mutex_schinfo_s mutex_schinfo_t;

/*
 * Mutex control block
 */
struct mutex_cblk_s
{
	volatile uint_t lock_depth;          /* lock depth      */
	struct thd_cblk_s *volatile p_owner; /* owner thread    */
	struct sch_qprio_s q_wait;           /* waiting threads */
};

/*
 * Mutex wait flag
 */
typedef enum
{
	MUTEX_PEEK = (1<<0)
} mutex_wait_flag_t;

/*
 * Mutex scheduling info
 */
struct mutex_schinfo_s
{
	volatile bool_t result;    /* wait result */
	volatile uint_t wait_flag; /* wait flag   */
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initialization functions
 */
UTIL_UNSAFE void mutex_init( mutex_cblk_t *p_mutex );
UTIL_UNSAFE void mutex_schinfo_init( mutex_schinfo_t *p_schinfo, uint_t wait_flag );
UTIL_UNSAFE void mutex_delete_static( mutex_cblk_t *p_mutex, sch_cblk_t *p_sch );

#ifdef __cplusplus
}
#endif

#endif /* H19FA4BCD_7A56_4B7D_A67A_063B3FFE82A9 */
