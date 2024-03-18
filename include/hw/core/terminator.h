/*
 * QEMU device to kill the running simulation and exit to OS.
 *
 * Copyright (c) 2024 Peer Adelt <peer.adelt@hshl.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_TERMINATOR_H
#define HW_TERMINATOR_H

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "hw/qdev-properties.h"

#define TYPE_TERMINATOR "terminator"
#define TERMINATOR_SIZE 4
#define TERMINATOR_ADDR_DEFAULT 0x10037004
OBJECT_DECLARE_SIMPLE_TYPE(Terminator, TERMINATOR)

typedef struct Terminator
{
	/* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

	uint64_t address;
} Terminator;

#endif