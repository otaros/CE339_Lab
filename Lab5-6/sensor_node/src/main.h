#ifndef __MAIN__
#define __MAIN__

#define SDA_GPIO_PIN 23 
#define SCL_GPIO_PIN 22 
#define ID 1
#define PAIRED (1 << 0)
enum msg_type
{
    PAIRING,
    PAIRING_RESPONSE,
    DATA,
    DATA_RESPONSE,
};

#endif // !__MAIN__