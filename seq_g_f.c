//
//  main.c
//  CMSC702HW1
//
//  Created by zhaoz on 2/18/15.
//  Copyright (c) 2015 zhaoz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, const char * argv[])
{
    clock_t begin, end;
    double time_spent;
    begin = clock();

    // insert code here...
    printf("Hello, World!\n");
    char *mode = "r";
    FILE *fp, *ofp;
    fp = fopen("final.data", mode);
    ofp = fopen("final.out", "w");
    int x_coord = 0;
    int y_coord = 0;
    int input_coords[2000][2];
    int x_limit = 500;
    int y_limit = 500;
    int generation = 500;
    
    
    
    if (fp == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        exit(1);
    }
    
    
    if (ofp == NULL) {
        fprintf(stderr, "Can't open out file \n");
        exit(1);
    }
    
    int i = 0;
    while (!feof(fp)) {
        
        fscanf(fp, "%d %d", &x_coord, &y_coord);
        fprintf(stderr, "%d %d\n", x_coord, y_coord);
        input_coords[i][0] = x_coord;
        input_coords[i][1] = y_coord;
        i++;
    }
    
    
    
    //int i = 0;
//    while (fscanf(fp, "%d %d", &x_coord, &y_coord) != EOF) {
//        input_coords[i][0] = x_coord;
//        input_coords[i][1] = y_coord;
//       // printf("%d, %d\n", x_coord,y_coord);
//        i++;
//       // fprintf(ofp, "%d %d\n", x_coord, y_coord);
//    }
    
    printf("%d\n",i);
    
    
    
    
  //  int map[600][600] ={0};
  //  int buffer[600][600] = {0};
    
    //******* buffer initializaiton, two buffers to swap at the end of each interaiton
    int x_space = x_limit+2;
    int y_space = y_limit+2;
    int ** map;
    map = malloc(y_space * sizeof(int*));
    int * temp = malloc(y_space * x_space * sizeof(int));
    for (int i = 0; i < y_space; i++) {
        map[i] = temp + (i * x_space);
    }
    
    
    
    int ** nextMap;
    nextMap = malloc(y_space * sizeof(int*));
    int * nextTemp = malloc(y_space * x_space * sizeof(int));
    for (int i = 0; i < y_space; i++) {
        nextMap[i] = nextTemp + (i * x_space);
    }

    
//    int ** nextmap;
//    nextmap = malloc(y_space * sizeof(int*));
//    int ** nexttemp = malloc(y_space * x_space * sizeof(int));
//    for (int i = 0; i < y_space; i++) {
//        nextmap[i] = nexttemp + (i * x_space);
//    }

    if(&map[3][4]==NULL)
        fprintf(stderr, "error");
   // printf("%d\n,  ",map[3][4]);
    
    for (int i = 0; i<y_space; i++) {
        for (int j = 0; j< x_space; j++) {
            map[i][j]=0;
            nextMap[i][j]=0;

        }
    }
    
    
    for (int j = 0; j<i; j++) {
        // The coordinate is shifted one to right and upper for the boundary condition
        map[ input_coords[j][0] +1 ][ input_coords[j][1] +1 ] = 1;
    }
    
//    
//    for (int i = 0; i<y_space+2; i++) {
//        for (int j = 0; j< x_space+2; j++) {
//            map[i][j]=0;
//        }
//    }
    
    
//    
//    for (int i=1; i<=x_limit+1; i++) {
//        for (int j = 1; j<=y_limit+1; j++) {
//            if (map[i][j]==1) {
//                fprintf(ofp, "%d %d 111\n", i-1, j-1);
//               // fprintf(ofp, "%d, ", map[i][j]);
//            }
//        }
//      //  fprintf(ofp, "%d, DDD\n", i);
//
//    }
    
   // fprintf(stderr, "error");

   // fprintf(stderr, "%d %d",map[251][1],map[251][0]);

    for (int k = 0; k<generation; k++) {
        
        for (int i=1; i<x_limit+1; i++) {
            for (int j = 1; j<y_limit+1; j++) {
                
                //caculate the number of existing cellls as neighbour
                int number_cell_neighbour = map[i-1][j-1]+map[i-1][j]+map[i-1][j+1]+
                map[i][j-1]+map[i][j+1]+
                map[i+1][j-1]+map[i+1][j]+map[i+1][j+1];
                
                if(map[i][j]==1){
                    if ((number_cell_neighbour>=0&&number_cell_neighbour<=1)||
                        (number_cell_neighbour>=4&&number_cell_neighbour<=8)) {
                        //map[i][j] = 0;
                        nextMap[i][j] = 0;

                    }
                    else if (number_cell_neighbour>8)
                    {
                        printf("error in counint number of living neighbours. %d %d \n", i,j);
                    }
                    else{
                        nextMap[i][j] = 1;
                    }
                    //                else if (number_cell_neighbour>=2&number_cell_neighbour<=3)
                    //                {
                    //                }
                }
                else{
                    if (number_cell_neighbour==3)
                    //map[i][j] = 1;
                        nextMap[i][j] = 1;
                    else{
                        nextMap[i][j] = 0;
                    }
                }
            }
            
        }
        
        int **transtemp = nextMap;
        nextMap = map;
        map = transtemp;
    }
    
    
    for (int i=1; i<=x_limit; i++) {
        for (int j = 1; j<=y_limit; j++) {
            if (map[i][j]==1) {
                fprintf(ofp, "%d %d\n", i-1, j-1);

            }
        }
    }
    
    
   // printf("%d\n", map[40][50]);
    
    fclose(fp);
    fclose(ofp);
    free(map);
    free(nextMap);
    free(temp);
    free(nextTemp);
    
    end = clock();
    time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("%f\n",time_spent);
    
    return 0;
}

