#include "bridge.h"
#include "tim.h"
#include "bno08.hpp"
#include <cstdint>




class BNO {
public:
  /**
   * @brief Default constructor.
   */
  BNO() = default;

  /**
   * @brief Default destructor.
   */
  ~BNO() = default;

  /**
   * @brief Initialize the Free_Wheel object.
   */
  void init();

  /**
   * @brief Read data from encoders and update the robot state.
   */
  void read_data();

  /**
   * @brief Process the collected data.
   */
  void send_data();

  CommunicationData send;

  Bno08 bno = Bno08(&huart3, BNO_RST_GPIO_Port, BNO_RST_Pin);

  uint8_t sending_bytes[sizeof(CommunicationData) + 2];

};
