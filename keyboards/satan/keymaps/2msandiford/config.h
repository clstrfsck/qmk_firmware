/*
Copyright 2018 Martin Sandiford

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define DEBOUNCING_DELAY 5

/* Don't need mechanical locking support. */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

/* Grave Esc stuff. */
#define GRAVE_ESC_ALT_OVERRIDE
#define GRAVE_ESC_CTRL_OVERRIDE

/* Don't need this, as all modifiers present on all layers. */
#define PREVENT_STUCK_MODIFIERS

// Not sure why this isn't default
#define PERMISSIVE_HOLD

// Enable breathing
#undef BACKLIGHT_BREATHING

#endif // CONFIG_USER_H
