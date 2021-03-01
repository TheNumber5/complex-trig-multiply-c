#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //TODO: Try using less libraries

//Program that multiplies 2 complex numbers in trigonometric form
//Version: 1.0 (01.FEB.2021)

typedef struct complex_trig {
    float modulus, argument;
};

float pi = 3.14159265;

struct complex_trig function_multiply(struct complex_trig trig_1, struct complex_trig trig_2) {
    struct complex_trig result;
    result.modulus = trig_1.modulus*trig_2.modulus;
    result.argument = trig_1.argument+trig_2.argument;
    if(result.argument>2*pi) {
        do {
            result.argument -= 2*pi;
        } while(result.argument>2*pi);
    }
return result;
}

int main(int argc, char** argv) {
    struct complex_trig number_1, number_2, multiply;
    if(!strcmp("-d", argv[1])) {
        number_1.modulus = atof(argv[2]);
        number_1.argument = atof(argv[3]);
        number_2.modulus = atof(argv[4]);
        number_2.argument = atof(argv[5]);
        multiply = function_multiply(number_1, number_2);
        printf("%f %f", multiply.modulus, multiply.argument);
    }
    else if(!strcmp("-f", argv[1])) {
        FILE *in_file, *out_file;
        in_file = fopen(argv[2], "rb");
        out_file = fopen(argv[3], "wb");
        do {
            fscanf(in_file, "%f %f %f %f", &number_1.modulus, &number_1.argument, &number_2.modulus, &number_2.argument);
            multiply = function_multiply(number_1, number_2);
            fprintf(out_file, "%f %f\n", multiply.modulus, multiply.argument);
        } while(!feof(in_file));
    fclose(in_file);
    fclose(out_file);
    }
    else if(!strcmp("-b", argv[1])) {
        int i = atoi(argv[2]);
        clock_t tick = clock();
        for(int v=0; v<i; v++) {
            number_1.modulus = rand()%1000000;
            number_2.modulus = rand()%1000000;
            number_1.argument = rand()%10000;
            number_1.argument /= 1000;
            number_2.argument = rand()%10000;
            number_2.argument /= 1000;
            multiply = function_multiply(number_1, number_2);
        }
        clock_t tock = clock();
        double benchmark_time = (double)(tock-tick)/CLOCKS_PER_SEC;
        printf("Benchmark time: %fms", benchmark_time);
    }
return 0;
}
