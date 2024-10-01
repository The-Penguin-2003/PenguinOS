#ifndef __PCI_H__
#define __PCI_H__

#include <types.h>

#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC

typedef struct
{
	uint16_t vendor_id;
	uint16_t device_id;
	uint8_t class_code;
	uint8_t subclass;
	uint8_t prog_if;
	uint8_t revision_id;
	uint8_t bus;
	uint8_t device;
	uint8_t function;
} pci_device_t;

void scan_pci_bus();

#endif /* __PCI_H__ */
