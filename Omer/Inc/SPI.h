/**
 * This file will be responsible for all SPI definitions and functions.
 */

#ifndef RTG_ARM_PROJECT_SPI
#define RTG_ARM_PROJECT_SPI

#include "RTG.h"

// SPI HANDLES:
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

// SPI
#define SPI_1 &hspi1					//SPI Master
#define SPI_2 &hspi4					//SPI Slave





#endif
