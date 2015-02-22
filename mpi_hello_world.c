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

void game_life(int * startDataBuffer, int x_length, int y_length, int * upperpatch, int * bottompatch){


  /******   a (x_length+2)*(y_length+2) matrix    *****/
 // int (*map)[x_length] = malloc(sizeof(int[y_length+2][x_length+2]));

  //******* could be c99 bug that the dynamic 2d Array definition is well supported. 
 // int (*nextlocalmap)[x_length] = malloc(sizeof(int[y_length+2][x_length+2]));



    int ** map = malloc((y_length+2) * sizeof(int*));
    int  *temp = malloc( (y_length+2) * (x_length+2) * sizeof(int));
    for (int i = 0; i < y_length+2; i++) {
        map[i] = temp + (i * (x_length+2));
    }


    int ** nextlocalmap = malloc((y_length+2) * sizeof(int*));
    int  *nexttemp = malloc( (y_length+2) * (x_length+2) * sizeof(int));
    for (int i = 0; i < y_length+2; i++) {
        nextlocalmap[i] = nexttemp + (i * (x_length+2));
    }





  for(int i = 1; i<= y_length; i++)
    for(int j = 1 ;j<= x_length; j++)
    {
        map[i][j] = startDataBuffer[(i-1)*x_length+(j-1)];
    }




    /***** adding patch ******/
    if(upperpatch!=NULL)
    {
      for(int i = 0; i < x_length; i++)
      {
        //map[i+1][0] = upperpatch[i];
        map[0][i+1] = upperpatch[i];
      }
    }
    if(bottompatch!=NULL)
    {
      for(int i = 0; i < x_length; i++)
      {
      //  map[i+1][y_length+1] = bottompatch[i];
        map[y_length+1][i+1] = bottompatch[i];
      }
    }



    //***** game of life iteration
   for (int i=1; i<y_length+1; i++) 
   { for (int j = 1; j<x_length+1; j++) {
                   
                   //caculate the number of existing cellls as neighbour
                   int number_cell_neighbour = map[i-1][j-1]+map[i-1][j]+map[i-1][j+1]+
                   map[i][j-1]+map[i][j+1]+
                   map[i+1][j-1]+map[i+1][j]+map[i+1][j+1];
                   
                   if(map[i][j]==1){
                       if ((number_cell_neighbour>=0&&number_cell_neighbour<=1)||
                           (number_cell_neighbour>=4&&number_cell_neighbour<=8)) {
                           nextlocalmap[i][j] = 0;
   
                       }
                       else if (number_cell_neighbour>8)
                       {
                           printf("error in counint number of living neighbours.");
                       }
                       else{
                           nextlocalmap[i][j] = 1;
                       }
                   }
                   else{
                       if (number_cell_neighbour==3)
                       //map[i][j] = 1;
                           nextlocalmap[i][j] = 1;
                       else{
                           nextlocalmap[i][j] = 0;
                       }
                   }
               }
   }
    //****************************




  for(int i = 1; i<= y_length; i++)
    for(int j = 1 ;j<= x_length; j++)
    {
        //startDataBuffer[i][j] = map[(i-1)*x_length+(j-1)];
        startDataBuffer[(i-1)*x_length+(j-1)] = nextlocalmap[i][j];
    }

if(map !=NULL)
free(map);
if(nextlocalmap!=NULL)
free(nextlocalmap);

free(temp);
free(nexttemp);

return;
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
    int (*divisionMap)[x_limit];

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
    ofp = fopen("life.out_1_1_new", "w");

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
    for(int i = 1; i<world_size; i++){
       // MPI_Send(&map[nrow*i][0], nrow*x_limit, MPI_INT, i+1, tag, MPI_COMM_WORLD);
        MPI_Send(&map[y_limit-nrow*(world_size-1)+(i-1)*nrow][0], nrow*x_limit, MPI_INT, i, tag, MPI_COMM_WORLD);
    }


  }else{
    divisionMap = malloc(sizeof(int[nrow][x_limit]));
    map_piece = (int*)malloc(nrow*x_limit*sizeof(int));
    MPI_Recv (map_piece, nrow*x_limit, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    // int (*startDataBuffer)[x_limit] = malloc(sizeof(int[nrow+2][x_limit]));
    for (int i = 0; i < nrow; i++)
    for(int j = 0; j<x_limit;j++)
    {
      divisionMap[i][j] = map_piece[i*x_limit+j];
    }
  }
  


  //******** game of life core code
  // if (rank%2==0)
  // {
  //  MPI_Send(&map[nrow*i][], nrow*x_limit, MPI_INT, i+1, tag, MPI_COMM_WORLD);

  // }

  MPI_Barrier(MPI_COMM_WORLD);
  //while()
  for(int i = 0; i<generation; i++){
    // if(world_rank!=0){

    //    //******* update the first and last rows of the block
    //   /* code */

    //    game_life( map_piece,  x_limit,  nrow);
    // }
    // else{

    //    int *tempBuffer = (int *)malloc( (y_limit - nrow * (world_size - 1)) * x_limit * sizeof(int) );
    //    for(int j =0;j < y_limit - nrow * (world_size - 1); j++)
    //     for(int k = 0; k < x_limit; k++)
    //     {
    //       tempBuffer[j * x_limit + k] = map[nrow * (world_size - 1) + j][k];
    //     }

    //     game_life(tempBuffer, x_limit; y_limit - nrow * (world_size - 1))

    //    for(int j =0;j < y_limit - nrow * (world_size - 1); j++)
    //     for(int k = 0; k < x_limit; k++)
    //     {
    //       //tempBuffer[j * x_limit + k] = map[nrow * (world_size - 1) + j][k];
    //       map[nrow * (world_size - 1) + j][k] = tempBuffer[j * x_limit + k]
    //     } 

    // }

      if(world_rank==0){

        //******** wait for node 2 to send the first line of block 2
        /****  code *****/
        int * bottompatch = (int *) malloc(x_limit*sizeof(int));
        //MPI_Send(&map[nrow*i][0], x_limit, MPI_INT, world_size-2, tag, MPI_COMM_WORLD);
        MPI_Send(&map[ y_limit - nrow*(world_size-1) -1 ][0], x_limit, MPI_INT, 1, tag, MPI_COMM_WORLD);
      //  fprintf(stderr, " send / recv %d\n", world_rank);
        MPI_Recv (bottompatch, x_limit, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);

      //  fprintf(stderr, " from node %d\n", world_rank);
      //  fprintf(stderr, " send / recv %d\n", world_rank);

        int *tempBuffer = (int *)malloc( (y_limit - nrow * (world_size - 1)) * x_limit * sizeof(int) );
         for(int j =0;j < y_limit - nrow * (world_size - 1); j++)
          for(int k = 0; k < x_limit; k++)
          {
           // tempBuffer[j * x_limit + k] = map[nrow * (world_size - 1) + j][k];
            tempBuffer[j * x_limit + k] = map[j][k];
          }


        //TODO add pathed version of game_life: bottompatch needed, all zeros upper patch needed too
        game_life(tempBuffer, x_limit, y_limit - nrow * (world_size - 1), NULL, bottompatch);

         for(int j =0;j < y_limit - nrow * (world_size - 1); j++)
          for(int k = 0; k < x_limit; k++)
          {
            //tempBuffer[j * x_limit + k] = map[nrow * (world_size - 1) + j][k];
            map[j][k] = tempBuffer[j * x_limit + k];
          }

        free(bottompatch);


      }else if(world_rank==world_size-1){
        //******** wait for node size - 2 to send the first line of block 2
        /****  code *****/
        int * upperpatch = (int *) malloc(x_limit*sizeof(int));
        MPI_Recv (upperpatch, x_limit, MPI_INT, world_size-2, tag, MPI_COMM_WORLD, &status);
        //fprintf(stderr, " rec / send from node %d\n", world_rank);
        MPI_Send(&divisionMap[y_limit- nrow][0], x_limit, MPI_INT, world_size-2, tag, MPI_COMM_WORLD);

           //     fprintf(stderr, " from node %d\n", world_rank);
      //  fprintf(stderr, " send / recv %d\n", world_rank);

          //***** patched version of game of life, patch the uppter line with patch ,and the bottom line with all zeros
        for(int i = 0; i < nrow; i++)
        for(int j = 0; j<x_limit;j++)
        {
           map_piece[i*x_limit+j] =  divisionMap[i][j];
        }
          game_life( map_piece,  x_limit,  nrow, upperpatch, NULL);
        for(int i = 0; i < nrow; i++)
        for(int j = 0; j<x_limit;j++)
        {
          divisionMap[i][j] =  map_piece[i*x_limit+j] ;
        }

        free(upperpatch);

       
         

      }else{

          //******* update the first  and last line of this block
          /*** code ****/
        int * upperpatch = (int *) malloc(x_limit*sizeof(int));
        int * bottompatch = (int *) malloc(x_limit*sizeof(int));

        if(world_rank%2==0)
        {
          //***** send first
         MPI_Send(&divisionMap[0][0], x_limit, MPI_INT, world_rank-1, tag, MPI_COMM_WORLD);
         MPI_Recv (upperpatch, x_limit, MPI_INT, world_rank-1, tag, MPI_COMM_WORLD, &status);

         MPI_Send(&divisionMap[nrow-1][0], x_limit, MPI_INT, world_rank+1, tag, MPI_COMM_WORLD);
         MPI_Recv (bottompatch, x_limit, MPI_INT, world_rank+1, tag, MPI_COMM_WORLD, &status);


        }else{
          //***** receive first
         MPI_Recv (upperpatch, x_limit, MPI_INT, world_rank-1, tag, MPI_COMM_WORLD, &status);
         MPI_Send(&divisionMap[0][0], x_limit, MPI_INT, world_rank-1, tag, MPI_COMM_WORLD);


         MPI_Recv (bottompatch, x_limit, MPI_INT, world_rank+1, tag, MPI_COMM_WORLD, &status);
         MPI_Send(&divisionMap[nrow-1][0], x_limit, MPI_INT, world_rank+1, tag, MPI_COMM_WORLD);



        }
      //  fprintf(stderr, " send / recv %d\n", world_rank);

        for(int i = 0; i < nrow; i++)
        for(int j = 0; j<x_limit;j++)
        {
           map_piece[i*x_limit+j] =  divisionMap[i][j];
        }

        game_life( map_piece,  x_limit,  nrow, upperpatch, bottompatch);

        for(int i = 0; i < nrow; i++)
        for(int j = 0; j<x_limit;j++)
        {
         divisionMap[i][j] =  map_piece[i*x_limit+j] ;
        }

        free(upperpatch);
        free(bottompatch);


      }


  }








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
           // map[(i-1)*nrow+j][k] = tempBuffer[j*x_limit+k];
            map[ y_limit - nrow*(world_size-1) + (i-1)*nrow + j][k] = tempBuffer[j*x_limit+k];
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
    free(map_piece);
    free(divisionMap);
  }


  
    
    
   
   
    //free(nexttemp);

  // Print off a hello world message
  printf("Hello world from processor %s, rank %d out of %d processors\n",
         processor_name, world_rank, world_size);

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}












