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

#include "hw/core/terminator.h"
#include "exec/address-spaces.h"

static Property terminator_properties[] = {
    DEFINE_PROP_UINT64("address", Terminator, address, TERMINATOR_ADDR_DEFAULT),
    DEFINE_PROP_END_OF_LIST(),
};

static uint64_t terminator_read(void *opaque, hwaddr addr, unsigned int size)
{
    return 0;
}

static void terminator_write(void *opaque, hwaddr addr,
                             uint64_t val64, unsigned int size)
{
    fprintf(stderr, "TERMINATOR: wrote '0x%08x', (ADDR_OFFSET: 0x%08x)\n", (uint32_t)(val64 & 0xffffffff), (uint32_t)(addr & 0xffffffff));
    // Exit QEMU and return to OS.
    exit(1);
}

static const MemoryRegionOps terminator_ops = {
    .read = terminator_read,
    .write = terminator_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4}};

static void terminator_realize(DeviceState *dev, Error **errp)
{
    Terminator *d = TERMINATOR(dev);
    memory_region_init_io(&d->mmio, NULL, &terminator_ops, d,
                          TYPE_TERMINATOR, TERMINATOR_SIZE);
    MemoryRegion *sys_mem = get_system_memory();
    memory_region_add_subregion(sys_mem, d->address, &d->mmio);
}

static void terminator_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->desc = "Simulation exit device";
    dc->realize = terminator_realize;
    dc->user_creatable = true;
    device_class_set_props(dc, terminator_properties);
}

static const TypeInfo terminator_info =
{
    .name = TYPE_TERMINATOR,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(Terminator),
    .class_init = terminator_class_init,
};

static void terminator_register_type(void)
{
    type_register_static(&terminator_info);
}

type_init(terminator_register_type);
