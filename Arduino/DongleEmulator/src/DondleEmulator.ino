const uint8_t packet_size = 32;

void setup() {
    Serial.begin(9600);
    while (!Serial) {;}
}


void loop() {
    for (uint8_t j = 0; j < packet_size; j++)
    {
        for (uint8_t i = 0; i < packet_size; i++)
        {
            if (i == j)
            {
                Serial.print(100);
            }
            else
            {
                Serial.print(i);
            }
            if (i != (packet_size - 1))
            {
                Serial.print(" ");
            }
        }
        Serial.println();
        _delay_ms(100);
    }
}
