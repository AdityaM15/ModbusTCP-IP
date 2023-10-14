#include <iostream>
#include <modbus.h>

int main() {
    modbus_t* ctx = nullptr;

    // Create a Modbus context for TCP communication
    ctx = modbus_new_tcp("127.0.0.1", 502); // Replace with slave's IP and port

    if (ctx == nullptr) {
        std::cerr << "Failed to create Modbus context." << std::endl;
        return 1;
    }

    // Set slave ID (unit identifier)
    modbus_set_slave(ctx, 1); // Replace with your slave's ID

    // Connect to the Modbus slave
    if (modbus_connect(ctx) == -1) {
        std::cerr << "Modbus connection failed." << std::endl;
        modbus_free(ctx);
        return 1;
    }

    uint16_t data[64] = { 0 }; // Buffer to hold received data
    int start_address = 0;   // Address of the first register to read
    int num_registers = 10;  // Number of registers to read

    // Read holding registers from the slave
    int ret = modbus_read_registers(ctx, start_address, num_registers, data);
    if (ret == -1) {
        std::cerr << "Modbus read error." << std::endl;
    }
    else {
        // Print the received data
        std::cout << "Received data from slave: ";
        for (int i = 0; i < num_registers; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Clean up and close the connection
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
