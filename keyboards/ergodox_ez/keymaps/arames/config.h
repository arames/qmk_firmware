#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 200

#ifdef PERMISSIVE_HOLD
#undef PERMISSIVE_HOLD
#endif

#define IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

#endif
