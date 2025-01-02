#ifdef __cplusplus
#include <stdint.h>
extern "C" {
#endif

  void run_code(void);

/* #define START_BYTE_PACK 0xAA */
/* #define END_BYTE_PACK 0xBB */
/* #define USED_UART huart3 */

  typedef struct __attribute__((packed)) {

    float ax;
    float ay;
    float az;

    float roll;
    float pitch;
    float yaw;
    
  } CommunicationData;

#ifdef __cplusplus
}
#endif
