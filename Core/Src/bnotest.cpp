#include "bnotest.hpp"
#include "arm_math.h"
#include "easy_crc.h"
#include "gpio.h"
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "usbd_cdc_if.h"
#include <memory.h>

BNO bno;

void run_code() {
  bno.init();
  uint32_t loop_tick = 0;
  uint32_t now;
  uint32_t thing = HAL_GetTick();

  while (1) {
    now = HAL_GetTick();

    if (now - loop_tick < 5) continue;

    loop_tick = HAL_GetTick();

    bno.read_data();

    // bno.send_data();

    printf("\n\nroll:%i\npitch:%i\nyaw:%i\nax:%i\nay:%i\naz:%i\n\n",
	   (int)(bno.send.roll * 100),
	   (int)(bno.send.pitch * 100),
	   (int)(bno.send.yaw * 100),
	   (int)(bno.send.ax * 100),
	   (int)(bno.send.ay * 100),
	   (int)(bno.send.ax * 100)
	   );

    if (HAL_GetTick() - thing > 500) {
      HAL_GPIO_TogglePin(BLINK_LED_GPIO_Port, BLINK_LED_Pin);
      thing = HAL_GetTick();
    }

  }
}

//@brief Initializes the Free_Wheel object.
void BNO::init() {
  bno.init();
}

void BNO::read_data() {
 // printf("cnt: %ld %ld %ld\n", total_mid_count, total_right_count, total_left_count);


  if (!bno.connected()) return;

  Bno08::ImuData imu = bno.get_data();


  send.ax = imu.accel_x;
  send.ay = imu.accel_y;
  send.az = imu.accel_z;

  send.roll = imu.roll;
  send.pitch = imu.pitch;
  send.yaw = imu.yaw;

  sending_bytes[0] = 0xA5;

  memcpy(sending_bytes+1, &send, sizeof(CommunicationData));

  sending_bytes[sizeof(CommunicationData)+1] = 
    calculate_cr8x_fast((uint8_t *)(sending_bytes + 1), sizeof(CommunicationData));

}



void BNO::send_data() {
  CDC_Transmit_FS(sending_bytes, sizeof(sending_bytes));
}
