#ifndef CANFRAME_H
#define CANFRAME_H

#define CAN_MAX_DLEN 8

typedef __UINT32_TYPE__ canid_t;

struct can_frame
{
    canid_t can_id;
    __UINT8_TYPE__ can_dlc;
    __UINT8_TYPE__ data[CAN_MAX_DLEN] __attribute__((aligned(8)));
}__attribute__((packed));

#endif // CANFRAME_H
