#include <modbus.h>

int main() {
    modbus_t* ctx = nullptr;

    // Create a new Modbus context
    ctx = modbus_new_tcp("192.168.56.1", 510);  // Replace with your device's IP and port

    if (ctx == nullptr) {
        // Handle initialization error
        return 1;
    }

    // Connect to the Modbus device
    if (modbus_connect(ctx) == -1) {
        // Handle connection error
        modbus_free(ctx);
        return 1;
    }

    uint16_t data[16] = { 0 }; // Buffer to hold received data

    // Read holding registers (example: registers 0 to 15)
    int num_registers = 16;
    int start_address = 0;
    int ret = modbus_read_registers(ctx, start_address, num_registers, data);

    if (ret == -1) {
        // Handle read error
    }
    else {
        // Process and use the received data
        for (int i = 0; i < num_registers; ++i) {
            // Print data[i] or perform other operations
        }
    }

    // Clean up and close the connection
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}