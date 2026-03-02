#include "../include/stats.h"
/*
PSEUDOCODE

FUNCTION init_simstats()
    
    Allocate Memory for SimStats Function wrte adress in ptr_simstats

    IF ptr_simstats == NULL (memory allocation failed)
        OUTPUT Memory Allocation Filed
        return NULL
    END IF

    set all field to 0 
    return ptr_simstats
END FUNCTION

FUNCTION create_output_file(config)
    


    return ptr_output_file

END FUNCTION

FUNCTION update_simstats(SimStats (Adress)ptr_stats, Parking (Adress)ptr_parking, Queue (Adress)ptr_queue)
    
    // calculate rel occupancy
    ptr_stats->temp_rel_occupancy_precent = (ptr_parking->occupied_count / ptr_parking->total_capacity) * 100

    IF ptr_stats->temp_rel_occupancy_precent == 100 THEN
        ptr_stats->time_full_occupancy = ptr_stats->time_full_occupancy + 1
    END IF

    // update queue length
    ptr_stats->temp_queue_lenght = ptr_queue->size
    return ptr_output_file

END FUNCTION

FUNCTION update_peak((Adress)ptr_simstats)
    IF ptr_simstats->temp_rel_occupancy_precent > ptr_simstats->peak_rel_occupancy THEN // check whether current occupancy is higher then saved peak
        ptr_simstats->peak_rel_occupancy = ptr_simstats->temp_rel_occupancy_precent
        ptr_simstats->step_highest_occupancy = ptr_simstats->step_num
    END IF
    IF ptr_simstats->temp_queue_lenghth > ptr_simstats->peak_queue_lenght THEN // check wheather current queue lenght is higher than saved peak
        ptr_simstats->peak_queue_lenght = ptr_simstats->temp_queue_lenghth
        ptr_simstats->step_longest_queue = ptr_simstats->step_num
    END IF
END FUNCTION

FUNCTION save_temp_dataset()

END FUNCTION


FUNCTION save_final_dataset()

END FUNCTION

END PSEUDOCODE
*/