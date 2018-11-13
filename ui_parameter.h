//2018 Jack
#ifndef UI_PARAMETER_H
#define UI_PARAMETER_H
#define PORT 9487
#define CORETRONIC_MEG "CORETRONIC_EAGLE360"

static bool mUdp_Check(false);

typedef enum Action{
    CORETRONIC_CONNECT      = 0,
    CORETRONIC_DISCONNECT   = 1,
    CORETRONIC_STARTCAMERA  = 2,
    CORETRONIC_CLOSECAMERA  = 3,
    CORETRONIC_UPLOADVIDEO  = 4,
}Eagle_Action;

#endif // UI_PARAMETER_H
