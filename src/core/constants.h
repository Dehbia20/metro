#ifndef Constants
#define Constants
#define MINUTE_AS_SEC 2      // 1 minute in simulator equals to 5 seconds
#define STOP 0               // flag that stop infinte loop
#define CONTINUE 1           // flag that keeps infinite loop running
#define CELL_H 20            // height of one cell
#define CELL_W 20            // width of one cell
#define WINDOW_H CELL_H * 20 // window global height
#define WINDOW_W CELL_W * 60 // window global width
#define DEBUG 1              // enable / disable debug trace log
#define FRAME_U_SLEEP 50     // frame is updated each 50 ms => 20 frames / seconds
#define N_TRAIN_CELL 20      // number of used cell to display train
enum Mode
{
    onlyTrain,
    TrainWithTraveler
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
#endif