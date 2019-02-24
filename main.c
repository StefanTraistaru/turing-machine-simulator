// Traistaru Stefan

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ----- Turing Machine Structure */
typedef struct MT{
    int N, M, P;
    /* --- States */
    char state[1000][100];
    char final_state[1000][100];
    char initial_state[100];
    /* --- Transitions */
    char current_state[10000][100];
    char t1_read_symb[10000], t2_read_symb[10000];
    char next_state[10000][100];
    char t1_write_symb[10000], t2_write_symb[10000];
    char t1_direction[10000], t2_direction[10000];
    /* --- The 2 tapes */
    char Tape1[10000], Tape2[10000];
}MT;

int main() {

    MT machine;
    int i = 0;
    char a[10000], b[10000];        /* Used for Tape reading */
    int cursor1 = 1, cursor2 = 1;   /* The 2 tape heads use for reading */
    int check_blocked = 0;
    int check_final = 0;
    char current[100];

    /* ----- Open reading and writing files */
    FILE *input_file, *output_file;
    input_file = fopen("input", "rt");
    output_file = fopen("output", "wt");
    if (input_file == NULL) {
        fprintf(stderr, "ERROR: Can't open file");
        return -1;
    }

    /* ----- Read the number of states(N) and the N states */
    fscanf(input_file, "%d\n", &machine.N);
    for(i = 0; i < machine.N; i++) {
        fscanf(input_file, "%s", machine.state[i]);
    }

    /* ----- Read the number of final states(M) and the M final states */
    fscanf(input_file, "%d", &machine.M);
    for(i = 0; i < machine.M; i++) {
        fscanf(input_file, "%s", machine.final_state[i]);
    }

    /* ----- Read the initial state */
    fscanf(input_file, "%s", machine.initial_state);

    /* ----- Read the number of transitions(P) and the P transitions */
    fscanf(input_file, "%d\n", &machine.P);
    for(i = 0; i < machine.P; i++) {
        fscanf(input_file, "%s ", machine.current_state[i]);
        fscanf(input_file, "%c ", &machine.t1_read_symb[i]);
        fscanf(input_file, "%c ", &machine.t2_read_symb[i]);
        fscanf(input_file, "%s ", machine.next_state[i]);
        fscanf(input_file, "%c ", &machine.t1_write_symb[i]);
        fscanf(input_file, "%c ", &machine.t1_direction[i]);
        fscanf(input_file, "%c ", &machine.t2_write_symb[i]);
        fscanf(input_file, "%c ", &machine.t2_direction[i]);
    }

	/* ----- Read the 2 tapes
	 *	Initialize the tapes with "#"
	 *	Read the 2 tapes in a and b variables
	 *	Copy the contents of a and b in Tape1 and Tape2
     */
    for (i=0; i<9999; i++) {
        machine.Tape1[i] = '#';
        machine.Tape2[i] = '#';
    }
    machine.Tape1[9999] = '\0';
    machine.Tape2[9999] = '\0';

    fscanf(input_file, "%s", a);
    fscanf(input_file, "%s", b);

    for (i=0; i<strlen(a); i++) {
        machine.Tape1[i] = a[i];
    }
    for (i=0; i<strlen(b); i++) {
        machine.Tape2[i] = b[i];
    }

    /* ----- Setting the current state as the initial state */
    strcpy(current, machine.initial_state);

    /* ----- TM Run
     *  Looks for the current state in machine.current_state
     *  When I find a transitions with the same current_state I check t1_read_symb si t2_read_symb
     *  After I find the correct transition I make the changes idicated by the transition:
     *  	- modify current_state with the value machine.next_state
     *  	- modify machine.Tape1[cursor1] with the element from machine.t1_write_symb[tranzitia gasita]
     *  	- modify the value of cursor1 with -1/0/+1 according to machine.t1_direction L/H/R (Left/Hold/Right)
     *  	- the same for machine.Tape2
     *  Check if the current state is a final state
     *  Check if the machine is blocked(no transitions were performed)
     */
    while (check_final == 0) {
        check_blocked = 0;

        for (i = 0; i < machine.P; i++) {
            if (strcmp(current, machine.current_state[i]) == 0) {
                if (machine.Tape1[cursor1] == machine.t1_read_symb[i] && machine.Tape2[cursor2] == machine.t2_read_symb[i]) {

                    strcpy(current, machine.next_state[i]);
                    machine.Tape1[cursor1] = machine.t1_write_symb[i];
                    machine.Tape2[cursor2] = machine.t2_write_symb[i];

                    if (machine.t1_direction[i] == 'L') {
                        cursor1--;
                    }
                    if (machine.t1_direction[i] == 'R') {
                        cursor1++;
                    }
                    if (machine.t2_direction[i] == 'L') {
                        cursor2--;
                    }
                    if (machine.t2_direction[i] == 'R') {
                        cursor2++;
                    }
                    check_blocked = 1;
                    break;
                }
            }
        }

        for (i = 0; i < machine.M; i++) {
            if (strcmp(current, machine.final_state[i]) == 0) {
                check_final = 1;
            }
        }

        if (check_blocked == 0) {
            break;
        }
    }

    /* ----- Write in file */
    if (check_blocked == 0) {
        fprintf(output_file, "The machine has blocked!\n");
    } else {
        fprintf(output_file, "%s\n", machine.Tape1);
        fprintf(output_file, "%s\n", machine.Tape2);
    }

    /* ----- Closing files */
    fclose(input_file);
    fclose(output_file);

    return 0;
}