#include<stdio.h>


__global__ void add(int *a, int *b, int *c, int size) {
  int row=threadIdx.y;
  int col = threadIdx.x;
  c[row + (size*col)] = a[row + (size*col)] + b[row + (size*col)];
  printf("The value of c is: %d \n", c[row + (size*col)]);
}

void random_ints(int* a, int X){
   int i;
 
   for (i = 0; i < X; i++){
     
    	a[i] = rand()%10; 
     
   }
}


int main(void) {
  int *a, *b, *c;      // host copies of a, b, c
  dim3 threadM(10, 10);

  // device copies of a, b, c
  int* d_a;
  int* d_b;
  int* d_c;    
  int size = sizeof(int);

  int i=0;

  
  a = (int*)malloc(10*10*size);
  b = (int*)malloc(10*10*size);
  c = (int*)malloc(10*10*size);



  random_ints(a,10*10);
  random_ints(b,10*10);

  


  // Allocate space for device copies of a, b, c

  cudaMalloc((void **)(&d_a), 10*10*size);
  cudaMalloc((void **)(&d_b), 10*10*size);
  cudaMalloc((void **)(&d_c), 10*10*size);
  
  // Copy inputs to device
  cudaMemcpy(d_a, a, 10*10*size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, 10*10*size, cudaMemcpyHostToDevice);
  
  printf("Memory coppied from host to device!\n");

  // Launch add() kernel on GPU
  add<<<1, threadM>>>(d_a, d_b, d_c, 10);

  // Copy result back to host
  cudaMemcpy(c, d_c, 10*10*size, cudaMemcpyDeviceToHost);
  printf("Memory coppied from device to host!\n");

  // Cleanup
  //cudaFree(*d_a); cudaFree(*d_b); cudaFree(*d_c);

  
  printf("Matrix a: \n");
  for(i=0; i<100; i++){
    if(i%10==0) printf("\n");
    printf("%d ", a[i]);
    
  }
	
  printf("\n");
  printf("Matrix b: \n");
  for(i=0; i<100; i++){
    if(i%10==0) printf("\n");
    printf("%d ", b[i]);
    
  }
  
  printf("\n");
  printf("Matrix c: \n");
  for(i=0; i<100; i++){
    if(i%10==0) printf("\n");
    printf("%d ", c[i]);
    
  }
  printf("\n\n");

 
  return 0;
}
