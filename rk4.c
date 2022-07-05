// Solver params
#define DT 1e-4
#define TMIN 100.0
#define TMAX 1100.0

// Lorenz system params
#define SIGMA 10.0
#define RHO 28.0
#define BETA (8.0/3.0) 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


int main() {

    clock_t begin = clock();
    
    // Initial condition
    double x = 1.0;
    double y = 1.0;
    double z = 1.0;
    double t = 0;
    
    // RK4 coefficients
    double k1x, k1y, k1z, k2x, k2y, k2z, k3x, k3y, k3z, k4x, k4y, k4z;
    
    // Burn-in
    // We put this into a separate loop for better performance
    while (t < TMIN) {
        
        // Calculate RK4 coefficients
        k1x = SIGMA*(y - x);
        k1y = x*(RHO - z) - y;
        k1z = x*y - BETA*z;
        
        k2x = SIGMA*((y+k1y*DT/2) - (x+k1x*DT/2));
        k2y = (x+k1x*DT/2)*(RHO - (z+k1z*DT/2)) - (y+k1y*DT/2);
        k2z = (x+k1x*DT/2)*(y+k1y*DT/2) - BETA*(z+k1z*DT/2);
        
        k3x = SIGMA*((y+k2y*DT/2) - (x+k2x*DT/2));
        k3y = (x+k2x*DT/2)*(RHO - (z+k2z*DT/2)) - (y+k2y*DT/2);
        k3z = (x+k2x*DT/2)*(y+k2y*DT/2) - BETA*(z+k2z*DT/2);
        
        k4x = SIGMA*((y+k3y*DT) - (x+k3x*DT));
        k4y = (x+k3x*DT)*(RHO - (z+k3z*DT)) - (y+k3y*DT);
        k4z = (x+k3x*DT)*(y+k3y*DT) - BETA*(z+k3z*DT);
        
        // Next step
        x += (k1x + 2*k2x + 2*k3x + k4x)*DT/6.0; 
        y += (k1y + 2*k2y + 2*k3y + k4y)*DT/6.0;
        z += (k1z + 2*k2z + 2*k3z + k4z)*DT/6.0;
        t += DT;
    }
    
    clock_t end = clock();
    printf("[%fs] Finished burn-in period of length %f\n", (double)(end - begin) / CLOCKS_PER_SEC, TMIN);
        
    // Actual simulation
    FILE *f = fopen("result_t1000_dt1e-4.csv", "w");
    if (f == NULL) {
        printf("Error opening output file!\n");
        exit(-1);
    }
    
    
    while (t < TMAX) {
        // Write current values to file
        fprintf(f, "%f,%f,%f,%f\n", t, x, y, z);
        
        // Calculate RK4 coefficients
        k1x = SIGMA*(y - x);
        k1y = x*(RHO - z) - y;
        k1z = x*y - BETA*z;
        
        k2x = SIGMA*((y+k1y*DT/2) - (x+k1x*DT/2));
        k2y = (x+k1x*DT/2)*(RHO - (z+k1z*DT/2)) - (y+k1y*DT/2);
        k2z = (x+k1x*DT/2)*(y+k1y*DT/2) - BETA*(z+k1z*DT/2);
        
        k3x = SIGMA*((y+k2y*DT/2) - (x+k2x*DT/2));
        k3y = (x+k2x*DT/2)*(RHO - (z+k2z*DT/2)) - (y+k2y*DT/2);
        k3z = (x+k2x*DT/2)*(y+k2y*DT/2) - BETA*(z+k2z*DT/2);
        
        k4x = SIGMA*((y+k3y*DT) - (x+k3x*DT));
        k4y = (x+k3x*DT)*(RHO - (z+k3z*DT)) - (y+k3y*DT);
        k4z = (x+k3x*DT)*(y+k3y*DT) - BETA*(z+k3z*DT);
        
        // Next step
        x += (k1x + 2*k2x + 2*k3x + k4x)*DT/6.0; 
        y += (k1y + 2*k2y + 2*k3y + k4y)*DT/6.0;
        z += (k1z + 2*k2z + 2*k3z + k4z)*DT/6.0;
        t += DT;
    }
    
    end = clock();
    printf("[%fs] Finished simulation period of length %f\n", (double)(end - begin) / CLOCKS_PER_SEC, TMAX-TMIN);
    
    fclose(f);
    

return 0;
}
