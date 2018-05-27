#include<stdio.h>

__global__ void add(int *a, int *b, int *c) {
  c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
  printf("The value of c is: %d \n", c[blockIdx.x]);
}

void random_ints(int* a, int N){
   int i;
   for (i = 0; i < N; ++i)
    a[i] = rand()%10;
}


int main(void) {
  int *a, *b, *c;      // host copies of a, b, c
  int *d_a, *d_b, *d_c;    // device copies of a, b, c
  int size = sizeof(int);

  a = (int*)malloc(512*size);
  b = (int*)malloc(512*size);
  c = (int*)malloc(512*size);
  
  random_ints(a,512);
  random_ints(b,512);

  // Allocate space for device copies of a, b, c
  cudaMalloc((void **)&d_a, 512*size);
  cudaMalloc((void **)&d_b, 512*size);
  cudaMalloc((void **)&d_c, 512*size);

  // Copy inputs to device
  cudaMemcpy(d_a, a, 512*size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, 512*size, cudaMemcpyHostToDevice);

  // Launch add() kernel on GPU
  add<<<512,1>>>(d_a, d_b, d_c);

  // Copy result back to host
  cudaMemcpy(c, d_c, 512*size, cudaMemcpyDeviceToHost);

  // Cleanup
  cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

  int i=0;
  printf("Array a: \n");
  for(i=0; i<512; i++){
    printf("%d ", a[i]);
  }
  printf("\n\n");

  printf("Array b: \n");
  for(i=0; i<512; i++){
    printf("%d ", b[i]);
  }
  printf("\n\n");

  printf("Array c: \n");
  for(i=0; i<512; i++){
    printf("%d ", c[i]);
  }
  printf("\n\n");

 
  return 0;
}
