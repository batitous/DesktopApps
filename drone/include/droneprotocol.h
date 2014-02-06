#ifndef DRONEPROTOCOL_H
#define DRONEPROTOCOL_H

/* Drone packet structure
 * ----------------------
 *
 * Emitter to Drone :
 * byte 0-3 : Magic
 * byte 4   : Address
 * byte 5   : Command
 * byte 6-7 : Specific Command Size (depends of the Command)
 * byte 8-14: Command's specific content
 *
 * Drone to Emitter:
 * byte 0-3 : Magic
 * byte 4   : Address
 * byte 5   : Command
 * byte 6   : Command result
 * byte 7-8 : Specific content (size for next packet ?)
 */

typedef enum _drone_command_
{
    DRONE_CMD_PING      = 0x00,
    DRONE_CMD_LOG_SIZE  = 0x01,
    DRONE_CMD_LOG       = 0x02,
    DRONE_CMD_MEMORY    = 0x03,
    DRONE_CMD_MEMORY_READ = 0x04,

    DRONE_CMD_RESET     = 0x5A
} DroneCmd;


typedef enum _drone_command_result_
{
    DRONE_CMD_FAILED    = 0x00,
    DRONE_CMD_RESULT_OK = 0x01
} DroneCmdResult;


#define DRONE_PK_MAGIC          0xDD00FFEE
#define DRONE_PK_HEADER_SIZE    15

#define DRONE_PK_ACK_SIZE       9

#define DRONE_STREAM_SIZE       512

#define MASTER          0x1
#define DRONE           0x2

#define SET_ADDRESS(sender, receiver)   ((sender <<4) | receiver)
#define GET_RECEIVER(a)                 (a & 0x0F)
#define GET_SENDER(a)                   ((a & 0xF0) >> 4)





#endif // DRONEPROTOCOL_H
