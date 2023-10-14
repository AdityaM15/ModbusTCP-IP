#include <iostream>
#include <modbus.h>

int main() {
    modbus_t* ctx = nullptr;

    // Create a Modbus context for TCP communication
    ctx = modbus_new_tcp("0.0.0.0", 502); // Listen on all interfaces

    if (ctx == nullptr) {
        std::cerr << "Failed to create Modbus context." << std::endl;
        return 1;
    }

    // Set slave ID (unit identifier)
    modbus_set_slave(ctx, 1);

    // Listen for incoming Modbus TCP requests
    if (modbus_listen(ctx, 1) == -1) {
        std::cerr << "Modbus listen failed." << std::endl;
        modbus_free(ctx);
        return 1;
    }

    uint16_t holding_registers[100] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // Sample data

    while (1) {
        modbus_mapping_t* mapping = modbus_mapping_new(0, 0, 100, 0);
        if (mapping == nullptr) {
            std::cerr << "Failed to create Modbus mapping." << std::endl;
            modbus_free(ctx);
            return 1;
        }

        // Set data in the holding registers
        for (int i = 0; i < 100; ++i) {
            mapping->tab_registers[i] = holding_registers[i];
        }

        // Respond to Modbus requests
        modbus_tcp_accept(ctx, &mapping);
        modbus_mapping_free(mapping);
    }

    // Clean up and close the connection
    modbus_free(ctx);

    return 0;
}
