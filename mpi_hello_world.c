// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header in tact.
//
// An intro MPI hello world program that uses MPI_Init, MPI_Comm_size,
// MPI_Comm_rank, MPI_Finalize, and MPI_Get_processor_name.
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void game_life(int * map, int x_length, int y_length, int generation){

  int (*startDataBuffer)[x_length] = malloc(sizeof(int[y_length+2][x_length+2]));

  for(int i = 1; i<= y_length; i++)
    for(int j = 1 ;j<= x_length; j++)
    {
        startDataBuffer[i][j] = map[(i-1)*x_length+(j-1)];
    }


    //***** game of life iteration


    //****************************




  for(int i = 1; i<= y_length; i++)
    for(int j = 1 ;j<= x_length; j++)
    {
        //startDataBuffer[i][j] = map[(i-1)*x_length+(j-1)];
        map[(i-1)*x_length+(j-1)] = startDataBuffer[i][j];
    }


 // return map;
}

int main(int argc, char** argv) {
 
  // File IO setup and buffer definition

    // char *mode = "r";
    // FILE *fp, *ofp;
    // fp = fopen("life.data_1_1", mode);
    // ofp = fopen("life.out_1_1", "w");
    int x_coord = 0;
    int y_coord = 0;
    int input_coords[500][2];
    int x_limit = 250;
    int y_limit = 250;
    int generation = 100;
    int tag = 42;
    MPI_Status  status;
    int * map_piece;
    int ** map;
    FILE *fp, *ofp;
    int * temp;

   //  if (fp == NULL) {
   //      fprintf(stderr, "Can't open input file in.list!\n");
   //      exit(1);
   //  }
    
    
   //  if (ofp == NULL) {
   //      fprintf(stderr, "Can't open out file \n");
   //      exit(1);
   //  }
    
    
    
   //  int i = 0;
   //  while (fscanf(fp, "%d %d", &x_coord, &y_coord) != EOF) {
   //      input_coords[i][0] = x_coord;
   //      input_coords[i][1] = y_coord;
   //      i++;
   //  }
    
    
    
    
   //  //******* buffer initializaiton, two buffers to swap at the end of each interaiton
   //  int x_space = x_limit;
   //  int y_space = y_limit;
   //  int ** map;
   //  map = malloc(y_space * sizeof(int*));
   //  int * temp = malloc(y_space * x_space * sizeof(int));
   //  for (int i = 0; i < y_space; i++) {
   //      map[i] = temp + (i * x_space);
   //  }

    
   //  int ** nextmap;
   //  nextmap = malloc(y_space * sizeof(int*));
   //  int ** nexttemp = malloc(y_space * x_space * sizeof(int));
   //  for (int i = 0; i < y_space; i++) {
   //      nextmap[i] = nextmap + (i * x_space);
   //  }

   // // if(&map[3][4]==NULL)
   //  //    fprintf(stderr, "error");
   // // printf("%d\n,  ",map[3][4]);
    
   //  for (int j = 0; j<i; j++) {
   //      // The coordinate is shifted one to right and upper for the boundary condition
   //      map[ input_coords[j][0]][ input_coords[j][1]] = 1;
   //  }






  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);


  int nrow = y_limit/world_size;
  //fprintf(stderr, "world_size %d",world_size);







  //******* data initilization
  if(world_rank==0)
  {

    char *mode = "r";
    //FILE *fp, *ofp;
    fp = fopen("life.data_1_1", mode);
    ofp = fopen("life.out_1_1", "w");

     if (fp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        MPI_Finalize();
        exit(1);
    }
    
    
    if (ofp == NULL) {
        fprintf(stderr, "Can't open out file \n");
        MPI_Finalize();
        exit(1);
    }
    
    
    
    int i = 0;
    while (fscanf(fp, "%d %d", &x_coord, &y_coord) != EOF) {
        input_coords[i][0] = x_coord;
        input_coords[i][1] = y_coord;
        i++;
    }
    
    
    
    
    //******* buffer initializaiton, two buffers to swap at the end of each interaiton
    int x_space = x_limit;
    int y_space = y_limit;
    //int ** map;
    map = malloc(y_space * sizeof(int*));
    temp = malloc(y_space * x_space * sizeof(int));
    for (int i = 0; i < y_space; i++) {
        map[i] = temp + (i * x_space);
    }

    
    for (int j = 0; j<i; j++) {
        // The coordinate is shifted one to right and upper for the boundary condition
        map[ input_coords[j][0]][ input_coords[j][1]] = 1;
    }


    fprintf(stderr, "reading \n");
    for (int i=0; i<x_limit; i++) {
        for (int j = 0; j<y_limit; j++) {
            if (map[i][j]==1) {
                //fprintf(ofp, "%d %d\n", i, j);
                fprintf(stderr, "%d %d\n", i, j);

            }
        }
    }

    //****** send data to rank 1 to size-1
    for(int i = 0; i<world_size-1; i++){
        MPI_Send(&map[nrow*i][0], nrow*x_limit, MPI_INT, i+1, tag, MPI_COMM_WORLD);
    }


  }else{
    map_piece = (int*)malloc(nrow*x_limit*sizeof(int));
    MPI_Recv (map_piece, nrow*x_limit, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    // int (*startDataBuffer)[x_limit] = malloc(sizeof(int[nrow+2][x_limit]));
    // for (int i = 0; i < nrow; i++)
    // for(int j = 0; j<x_limit;j++)
    // {
    //   startDataBuffer[i][j] = map_piece[i(x_limit+j)];
    // }
  }
  


  //******** game of life core code
  // if (rank%2==0)
  // {
  //  MPI_Send(&map[nrow*i][], nrow*x_limit, MPI_INT, i+1, tag, MPI_COMM_WORLD);

  // }







  //********** receive the returned map from nodes and assemble the total map
  if(world_rank==0)
  {
    int * tempBuffer = (int*)malloc(nrow*x_limit*sizeof(int));
    for(int i =1; i<world_size; i++)
    {
        MPI_Recv (tempBuffer, nrow * x_limit, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
        for(int j = 0 ;j<nrow;j++)
          for(int k = 0; k < x_limit; k++)
          {
            map[(i-1)*nrow+j][k] = tempBuffer[j*x_limit+k];
          }
    }


    fprintf(stderr, "output \n");
    for (int i=0; i<x_limit; i++) {
        for (int j = 0; j<y_limit; j++) {
            if (map[i][j]==1) {
                fprintf(ofp, "%d %d\n", i, j);
                fprintf(stderr, "%d %d\n", i, j);

            }
        }
    }


   if (fp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        MPI_Finalize();
        exit(1);
    }
    
    
    if (ofp == NULL) {
        fprintf(stderr, "Can't open out file \n");
        MPI_Finalize();
        exit(1);
    }
    fclose(fp);
    fclose(ofp);
    free(map);
    free(temp);
  }else{
    MPI_Send(map_piece, nrow*x_limit, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }


  
    
    
   
   
    //free(nexttemp);

  // Print off a hello world message
  printf("Hello world from processor %s, rank %d out of %d processors\n",
         processor_name, world_rank, world_size);

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
