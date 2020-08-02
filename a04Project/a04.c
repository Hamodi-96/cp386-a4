//Issaasbah
//Hamodi-96
//url: https://github.com/Hamodi-96/cp386-a4.git


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int current[1024][1024], maximum_claim[1024][1024], available[1024];
int allocation[1024][1024];
int maxres[1024][1024], running[1024], safe = 0;
int counter = 0, i, j, exec, resources, processes, k = 1;

int main(int argc, char *argv[])
{
	// amount of resources
	resources = argc - 1;

	//open file
	FILE *fptr = fopen("./sample4_in.txt", "r");
	if(fptr == NULL) //file errors
    {
        printf("sample file not found!");   
        exit(1);             
    } else { //read each line in file and set maximum of resources for each thread
		int bufferLength = 255;
		char line[bufferLength];
		int thread_num = 0;

		while(fgets(line, bufferLength, fptr)) { //reads each line
			// printf("%s\n", line);
			// adds max values to maxres array
			char *part = strtok(line, " ,\n");
			maxres[thread_num][0] = atoi(part);
			for (i = 1; i < resources; i++) {
				maxres[thread_num][i] = atoi(strtok(NULL, " ,\n"));
			}
			thread_num++; // next thread
		}
		// set number of processes
		processes = thread_num;
    }

	printf("Number of customers: %d", processes);
	//scanf_s("%d", &processes);
	for (i = 0; i < processes; i++)
	{
		running[i] = 1;
		counter++;
	}


	printf("\nCurrently Available resources: ");
	// printf("\nEnter number of resources: ");
	// scanf_s("%d", &resources);

	// resources available from the program arguements
	for (i = 0; i < resources; i++)
	{
		available[i] = atoi(argv[i + 1]);
		printf("%d ", available[i]);
	}

	printf("\nMaximum resources from file:  ");
	// print file numbers
	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{	
			printf("%d", maxres[i][j]);
			if (j < resources - 1) { printf(","); }
		}
		printf("\n");
	}
	// Old code
	// printf("\nEnter Claim Vector:");
	// for (i = 0; i < resources; i++)
	// {
	// 	scanf_s("%d", &maxres[i]);
	// }

	// printf("\nEnter Allocated Resource Table:\n");
	// for (i = 0; i < processes; i++)
	// {
	// 	for (j = 0; j < resources; j++)
	// 	{
	// 		scanf_s("%d", &current[i][j]);
	// 	}
	// }

	// printf("\nEnter Maximum Claim Table:\n");
	// for (i = 0; i < processes; i++)
	// {
	// 	for (j = 0; j < resources; j++)
	// 	{
	// 		scanf_s("%d", &maximum_claim[i][j]);
	// 	}
	// }



	int is_run = 1;
	// loops commands before running
	// ex RQ, RL, *, Run.
	while(is_run) {
		char input[1024];
		printf("Enter Command: ");
		scanf("%[^\n]s", input);
		// needs fix
		if (strcmp(input,"")) {
			printf("please input command\n");
			//flush scanf
			int c;
			while ( (c = getchar()) != '\n' && c != EOF ) { }
			continue;
		}

		//get the first 2 str token of the command input
		char *part = strtok(input, " \n");


		char *thread_num_s = strtok(NULL, " \n");
		int thread_num = atoi(thread_num_s);

		// checks for commands
		// space after commands may be required
		if (strcmp(part,"RQ ")) {
			// adds the request values to allocation array
			for (i = 0; i < resources; i++) {
				int part_val = atoi(strtok(NULL, " \n"));
				allocation[thread_num][i] += part_val;
			}

			// for testing
			// for (i = 0; i < resources; i++) {
			// 	printf("%d ", allocation[thread_num][i]);
			// }
			// puts("");
		}
		else if (strcmp(part,"RL ")) {}
		else if (strcmp(part,"*")) {}
		else if (strcmp(part,"Run")) {

			// stop loop to run real code
			is_run = 0;
		}
		else {printf("wrong command");}
		//flush scanf
		int c;
		while ( (c = getchar()) != '\n' && c != EOF ) { }
	}
	printf("\nThe Claim Vector is: ");
	for (i = 0; i < resources; i++)
	{
		for (j = 0; j < resources; j++)
		{
			printf("\t%d", maxres[i][j]);
		}	
	}
	printf("\nThe Allocated Resource Table:\n");
	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{
			printf("\t%d", current[i][j]);
		}
		printf("\n");
	}

	printf("\nThe Maximum Claim Table:\n");
	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{
			printf("\t%d", maximum_claim[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{
			allocation[i][j] += current[i][j];
		}
	}

	printf("\nAllocated resources:");
	for (i = 0; i < resources; i++)
	{
		for (j = 0; j < resources; j++)
		{
			printf("\n%d", allocation[i][j]);
		}
	}

	for (i = 0; i < resources; i++)
	{
		available[i] = maxres[i] - allocation[i];
	}

	printf("\nAvailable resources:");
	for (i = 0; i < resources; i++)
	{
		printf("\t%d", available[i]);
	}
	printf("\n");

	while (counter != 0)
	{
		safe = 0;
		for (i = 0; i < processes; i++)
		{
			if (running[i])
			{
				exec = 1;
				for (j = 0; j < resources; j++)
				{
					if (maximum_claim[i][j] - current[i][j] > available[j])
					{
						exec = 0;
						printf("\n");
						break;
					}
				}
				if (exec)
				{
					printf("\nProcess%d is executing\n", i + 1);
					running[i] = 0;
					counter--;
					safe = 1;

					for (j = 0; j < resources; j++)
					{
						available[j] += current[i][j];
					}
					printf("\n");
					break;
				}
			}
		}
		if (!safe)
		{
			printf("\nThe processes are in unsafe state.\n");
			printf("\n");
			break;
		}
		else
		{
			printf("\nThe process is in safe state");
			printf("\nAvailable vector:");

			for (i = 0; i < resources; i++)
			{
				printf("\t%d", available[i]);
			}

			printf("\n");
		}
	}
	return 0;
}