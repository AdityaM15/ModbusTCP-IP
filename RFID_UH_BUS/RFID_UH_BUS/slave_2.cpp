#include <modbus.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    modbus_t* ctx;
    uint16_t registers[2] = { 123, 456 };  // Values to write to registers

    // Create a Modbus TCP context
    ctx = modbus_new_tcp("192.168.1.100", 502);  // Replace with your slave's IP and port

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

    // Write to holding registers
    int num_written = modbus_write_registers(ctx, 0, 2, registers);
    if (num_written == -1) {
        fprintf(stderr, "Modbus write error: %s\n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }

    printf("Registers written successfully\n");

    // Close the Modbus connection and free the context
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
