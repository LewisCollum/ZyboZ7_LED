#include "xgpio.h"

#define baseAddress XPAR_AXI_GPIO_0_BASEADDR
#define buttonDataAddress (baseAddress + XGPIO_DATA_OFFSET)
#define buttonDirectionAddress (baseAddress + XGPIO_TRI_OFFSET)
#define ledDataAddress (baseAddress + XGPIO_DATA2_OFFSET)
#define ledDirectionAddress (baseAddress + XGPIO_TRI2_OFFSET)

#define output 0x0
#define input 0xF

typedef struct {
	uint32_t* dataAddress;
	uint32_t* directionAddress;
} PeripheralAddress;

void setPeripheralAsInput(PeripheralAddress);
void setPeripheralAsOutput(PeripheralAddress);
void setLedDataToButtonData();

PeripheralAddress led = {(uint32_t*)ledDataAddress, (uint32_t*)ledDirectionAddress};
PeripheralAddress button = {(uint32_t*)buttonDataAddress, (uint32_t*)buttonDirectionAddress};


int main() {
	setPeripheralAsInput(button);
	setPeripheralAsOutput(led);

	while(1) setLedDataToButtonData();

	return XST_SUCCESS;
}


void setPeripheralAsInput(PeripheralAddress peripheral) {
	*peripheral.directionAddress |= input;
}

void setPeripheralAsOutput(PeripheralAddress peripheral) {
	*peripheral.directionAddress &= output;
}

void setLedDataToButtonData() {
	*led.dataAddress = *button.dataAddress;
}


