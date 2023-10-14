#include <modbus.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    modbus_t* ctx;
    int num_registers = 10;
    uint16_t registers[num_registers];

    // Create a Modbus TCP context
    ctx = modbus_new_tcp("192.168.22.1", 502);  // Replace with your slave's IP and port

    if (ctx == NULL) {
        fprintf(stderr, "Failed to create Modbus context\n");
        return -1;
    }

    // Connect to the Modbus TCP server
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Modbus connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // Set the Modbus slave address (unit ID)
    modbus_set_slave(ctx, 1);  // Replace with your slave's address

    // Read holding registers
    int num_read = modbus_read_registers(ctx, 0, num_registers, registers);
    if (num_read == -1) {
        fprintf(stderr, "Modbus read error: %s\n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }

    // Print the received data
    for (int i = 0; i < num_read; ++i) {
        printf("Register %d: %d\n", i, registers[i]);
    }

    // Close the Modbus connection and free the context
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
