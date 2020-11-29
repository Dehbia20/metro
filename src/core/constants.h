#ifndef Constants
#define Constants
#define MINUTE_AS_SEC 2            // 1 minute in simulator equals to 5 seconds
#define STOP 0                     // flag that stop infinte loop
#define CONTINUE 1                 // flag that keeps infinite simulator loop running
#define CELL_H 20                  // height of one cell
#define CELL_W 20                  // width of one cell
#define WINDOW_H CELL_H * 20       // window global heights
#define WINDOW_W CELL_W * 60       // window global width
#define FRAME_U_SLEEP 50           // frame is updated each 50 ms => 20 frames / seconds
#define N_TRAIN_CELL 20            // number of used cell to display train
#define TV_GEN_PAUSE_TIME 100      // DEFAULT VALUE : a passenger is generated each 500 ms
#define MAX_WAITING_PASSENGER 300  // max passenger waiting for a train
#define MIN_TV_GEN_PAUSE_TIME 100  // min speed gen => 1 passenger per 250 ms
#define MAX_TV_GEN_PAUSE_TIME 1000 // max speed gen => 1 passenger per second
#define TRAIN_GATE_SPACING 3       // each 3 train cells there is a gate
#define TRAIN_RIGHT_STOP_CELL 33   // cell where train comming from left to right stops
#define TRAIN_RIGHT_START_CELL 0   // cell where train comming from letft to right first appear
#define TRAIN_RIGHT_ROW_IDX 8      // train (comming from left to right) will appear and slide over row 8
#define TRAIN_LEFT_STOP_CELL 26    // cell where train comming from right to left stops
#define TRAIN_LEFT_START_CELL 59   // cell where train comming from right to left first appear
#define TRAIN_LEFT_ROW_IDX 11      // train (comming from right to left) will appear and slide over row 11

enum Mode
{
    ONLY_TRAIN,
    TRAIN_TRAVELLER
};
enum Train_Direction
{
    RIGHT,
    LEFT
};
enum Signal_Type
{
    UPDATE_DISPLAYED_TIME,
    SHOW_TRAIN
};
enum Separtor
{
    SHOW,
    HIDE
};
enum T_animation
{
    ARRIVAL,
    DEPARTURE
};
enum Trace
{
    DEBUG,
    NONE
};
enum DestStatus
{
    REACHED,
    NOT_REACHED
};
enum P_Direction
{
    P_LEFT,
    P_RIGHT,
    P_UP,
    P_DOWN
};
#endif