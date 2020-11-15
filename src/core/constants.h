#ifndef Constants
#define Constants
#define MINUTE 5             // 1 minute in simulator equals to 5 seconds
#define STOP 0               // flag that stop infinte loop
#define CONTINUE 1           // flag that keeps infinite loop running
#define CELL_H 20            // height of one cell
#define CELL_W 20            // width of one cell
#define WINDOW_H CELL_H * 20 // window global height
#define WINDOW_W CELL_W * 60 // window global width
enum Mode
{
    onlyTrain,
    TrainWithTraveler
};
#endif