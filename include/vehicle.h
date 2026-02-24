typedef struct {
    unsigned int id;
    unsigned int entry_time;
    unsigned int parking_duration; // number of steps parking
    unsigned int queue_time;
} Vehicle;

void init_vehicle(Vehicle *ptr_vehicle) {}