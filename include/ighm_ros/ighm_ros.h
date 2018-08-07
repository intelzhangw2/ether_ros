
#ifndef IGHM_ROS_LIB_H
#define IGHM_ROS_LIB_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include <errno.h>
// #include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
// #include <malloc.h>
// #include <arpa/inet.h>
#include <pthread.h>
#include <stddef.h>
#include "ecrt.h"
#include "ethercat_slave.h"
#include "ethercat_communicator.h"
#include "ethercat_input_data_handler.h"
#include "ethercat_output_data_handler.h"

// Application parameters
#define CLOCK_TO_USE CLOCK_MONOTONIC
// #define MEASURE_TIMING 2
// #define RUN_TIME 60 // run time in seconds
#if MEASURE_TIMING == 1
#define SAMPLING_FREQ 10
#endif
/****************************************************************************/

#define NSEC_PER_SEC (1000000000L)
// #define PERIOD_NS (NSEC_PER_SEC / FREQUENCY)
#define DIFF_NS(A, B) (((B).tv_sec - (A).tv_sec) * NSEC_PER_SEC + \
                       (B).tv_nsec - (A).tv_nsec)

#define TIMESPEC2NS(T) ((uint64_t)(T).tv_sec * NSEC_PER_SEC + (T).tv_nsec)

#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        ROS_FATAL(msg);          \
        exit(EXIT_FAILURE);      \
    } while (0)

/****************************************************************************/

typedef struct slave_struct
{
    std::string slave_name;
    int id;
    EthercatSlave slave;
} slave_struct;

extern slave_struct * ethercat_slaves;
extern uint8_t *domain1_pd;
extern uint8_t * process_data_buf;
extern size_t total_process_data;
extern size_t num_process_data_in;
extern size_t num_process_data_out;
extern int log_fd;
extern ec_master_t *master;
extern ec_master_state_t master_state;
extern ec_master_info_t master_info;
extern ec_domain_t *domain1;
extern ec_domain_state_t domain1_state;
extern pthread_spinlock_t lock;
extern EthercatCommunicator ethercat_comm;
extern EthercatInputDataHandler ethercat_input_data_handler;
extern EthercatOutputDataHandler ethercat_output_data_handler;
extern int PERIOD_NS;
extern int FREQUENCY;
extern int RUN_TIME;
#endif /* IGHM_ROS_LIB_H */
