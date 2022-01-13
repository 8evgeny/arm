#pragma once
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"

static uint32_t ReceivedByteCount, SentByteCount, SkippedByteCount;
#define BUFFER_LENGTH                        100
static uint8_t Buffer[BUFFER_LENGTH];
