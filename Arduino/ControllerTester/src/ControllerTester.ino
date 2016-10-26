#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

struct payload_t
{
    uint8_t axis_lh;
    uint8_t axis_lv;
    uint8_t axis_rh;
    uint8_t axis_rv;
    uint8_t button_r;
    uint8_t button_g;
    uint8_t button_b;
    uint8_t button_p;
    uint8_t button_rs;
    uint8_t button_ls;
    uint8_t button_ru;
    uint8_t button_rd;
    uint8_t button_lu;
    uint8_t button_ld;
    uint8_t mode;
};


const uint16_t this_node = 00;
const uint16_t other_node = 01;

RF24 radio(9,10);
RF24Network network(radio);

payload_t payload;


void setup(void)
{
    Serial.begin(57600);
    SPI.begin();

    radio.begin();
    network.begin(90, this_node);
    Serial.println("Controller testing firmware v1.0");
}


void loop(void)
{
    network.update();
    while (network.available())
    {
        RF24NetworkHeader header;
        payload_t payload;
        network.read(header,&payload,sizeof(payload));
        Serial.print("Received: ");
        print(payload.axis_lh);
        print(payload.axis_lv);
        print(payload.axis_rh);
        print(payload.axis_rv);
        print(payload.button_r);
        print(payload.button_g);
        print(payload.button_b);
        print(payload.button_p);
        print(payload.button_rs);
        print(payload.button_ls);
        print(payload.button_ru);
        print(payload.button_rd);
        print(payload.button_lu);
        print(payload.button_ld);
        print(payload.mode);
        Serial.println();
        delay(50);
    }
}

inline void print(uint8_t data)
{
    Serial.print(data);
    Serial.print(" ");
}
