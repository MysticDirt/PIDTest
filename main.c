#include "pid.h"
#include <stdio.h>
#include <stdlib.h>

/*
This program simulates PID (somewhat) to give a better understanding of how it works and how to apply it
On the graph, * is the setpoint and # is the measurement value
The # overrides the * if it matches
*/

typedef struct graph_struct{
    //Struct to store rows and columns along with the array itself
    char** table;
    int rows;
    int cols;   
}Graph;


void display(Graph graph){
    /*
    Displays the graph on the terminal
    @graph: the graph struct to display
    */
    for (int i = 0; i < graph.rows; ++i){
        printf("%2d", i);
        for (int j = 0; j < graph.cols; ++j){
            printf("  %c", graph.table[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int j = 0; j < graph.cols; ++j){
        printf(" %2d", j);
    }
    printf("\n");
}

float increment(PIDController* pid, float setpoint, float measurement){
    /*
    Simulates a change in the measured value after the PID update (right now it is update squared divided by 2 while keeping the sign)
    @pid: the pid struct
    @setpoint: the target the pid tries to reach
    @measurement: the current value that is trying to reach the setpoint
    @returns: the total increment to change the measurement
    */
    float update = PIDController_Update(pid, setpoint, measurement);
    //printf("%f ", setpoint - measurement);
    if (update < 0){
        return -(update * update / 2.0f);
    }
    return (update * update / 2.0f);
}

void populate(Graph graph, PIDController* pid, float setpoint, float measurement){
    /*
    Calculates the pid changes and makes a graph out of it
    @pid: the pid struct
    @setpoint: the target the pid tries to reach
    @measurement: the current value that is trying to reach the setpoint
    */
    float result = measurement;
    for (int k = 0; k < graph.cols; ++k){
        float inc = increment(pid, setpoint, result);
        result += inc;
        if (result > 19.0f){
            result = 19.0f;
        } else if (result < 0.0f){
            result = 0.0f;
        }
        //printf("%f\n", result);
        for (int i = 0; i < graph.rows; ++i){
            if ((int)result == i){
                graph.table[i][k] = '#';
            } else if((int)setpoint == i){
                graph.table[i][k] = '*';
            } else {
                graph.table[i][k] = '-';
            }
        }
    }
}

void make_space(Graph* graph){
    /*
    Creates heap space for the graph table
    @graph: the graph struct pointer to make space for
    */
    graph->table = (char**)malloc(graph->rows * sizeof(char*));
    for(int i = 0; i < graph->rows; ++i){
        graph->table[i] = (char*)malloc(graph->cols * sizeof(char*));
    }
}

void free_space(Graph* graph){
    /*
    Frees the heap space for the graph table
    @graph: the graph struct pointer to free the table
    */
    for(int i = 0; i < graph->rows; ++i){
        free(graph->table[i]);
    }
    free(graph->table);
    graph->table = NULL;
}

int main(){
    //main function
    float setpoint = 10.0f; //can change value
    float measured = 0.0f; //can change value
    PIDController pid;
    Graph graph;
    graph.rows = 20; //can change value
    graph.cols = 40; //can change value
    PIDController_Init(&pid); //Sets values to 0
    /*Set Limits:
    PID pointer, Tau (Greater than 1), Integrator Min, Integrator Max, Output Min, Output Max
    All changeable*/
    PIDController_SetLimits(&pid, 1.2f, -0.5f, 0.5f, -5.0f, 5.0f);
    /*Set Terms:
    PID pointer, Kp, Ki, Kd, Time
    All changeable*/
    PIDController_SetTerms(&pid, 1.0f, 0.01f, 0.0f, 1.0f);
    make_space(&graph);
    populate(graph, &pid, setpoint, measured);
    display(graph);
    free_space(&graph);
    return 0;
}