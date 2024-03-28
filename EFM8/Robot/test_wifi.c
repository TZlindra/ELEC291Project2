#include <EFM8LB1.h>
#include <stdio.h>

#define WIFI_SSID "yourSSID"
#define WIFI_PASSWORD "yourPassword"
#define SERVER_IP "192.168.1.100" // Replace with your laptop's IP address
#define SERVER_PORT "12345" // Replace with your server's listening port

void UART_Init(void) {
    // Configure UART for 115200 baud, 8-N-1 format
    // You'll need to adjust this according to your specific EFM8 model's UART configuration routines
    // This is a generic placeholder
    SCON0 = 0x10;  // Set SCON0 to 8-bit variable baud rate
    // Further initialization as per your specific EFM8 model's requirements
}

void UART_SendChar(char c) {
    SBUF0 = c; // Transmit the character
    while (TI0 == 0); // Wait for the transmit to complete
    TI0 = 0; // Clear the transmit interrupt flag
}

void UART_SendString(const char* str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}

void DelayMs(unsigned int ms) {
    // Implement a delay function, depending on your EFM8 clock setup
    // Placeholder for a simple blocking delay
}

void checkESP8266(void) {
    UART_SendString("AT\r\n"); // Check if ESP-01S is ready
    DelayMs(1000); // Wait for a response (adjust based on your testing)
}

void connectToWiFi(void) {
    char cmd[100];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);
    UART_SendString(cmd);
    DelayMs(5000); // Wait for connection to establish
}

void connectToServer(void) {
    char cmd[100];
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", SERVER_IP, SERVER_PORT);
    UART_SendString(cmd);
    DelayMs(2000); // Wait for connection to establish
}

void sendData(const char* data) {
    char cmd[50];
    sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(data));
    UART_SendString(cmd);
    DelayMs(1000); // Wait for prompt
    UART_SendString(data);
}

void main(void) {
    UART_Init();
    checkESP8266(); // Check if the ESP-01S is ready
    connectToWiFi(); // Connect to WiFi
    connectToServer(); // Connect to the TCP server
    sendData("Hello, server!"); // Send a message to the server

    while(1) {
        // Loop indefinitely
        // Additional code can be added here
    }
}
