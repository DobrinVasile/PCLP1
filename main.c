#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a 2D array
int** allocate2DArray(int rows, int cols) {
    int **array = (int**) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        array[i] = (int*) malloc(cols * sizeof(int));
    }
    return array;
}

// Function to free memory for a 2D array
void free2DArray(int **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// Function to perform image convolution
void convolution(int **image, int **kernel, int **output, int imgRows, int imgCols, int kernelSize) {
    int kCenter = kernelSize / 2;
    for (int i = 0; i < imgRows; i++) {
        for (int j = 0; j < imgCols; j++) {
            int sum = 0;
            for (int m = 0; m < kernelSize; m++) {
                for (int n = 0; n < kernelSize; n++) {
                    int x = i + m - kCenter;
                    int y = j + n - kCenter;
                    if (x >= 0 && x < imgRows && y >= 0 && y < imgCols) {
                        sum += image[x][y] * kernel[m][n];
                    }
                }
            }
            output[i][j] = sum;
        }
    }
}

int main() {
    int imgRows = 5, imgCols = 5;
    int kernelSize = 3;

    // Allocate memory for image, kernel, and output
    int **image = allocate2DArray(imgRows, imgCols);
    int **kernel = allocate2DArray(kernelSize, kernelSize);
    int **output = allocate2DArray(imgRows, imgCols);

    // Initialize the image with some values
    for (int i = 0; i < imgRows; i++) {
        for (int j = 0; j < imgCols; j++) {
            image[i][j] = i + j;
        }
    }

    // Initialize the kernel with some values
    int kernelVals[3][3] = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
    };
    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            kernel[i][j] = kernelVals[i][j];
        }
    }

    // Perform convolution
    convolution(image, kernel, output, imgRows, imgCols, kernelSize);

    // Print the output image
    printf("Output Image:\n");
    for (int i = 0; i < imgRows; i++) {
        for (int j = 0; j < imgCols; j++) {
            printf("%d ", output[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    free2DArray(image, imgRows);
    free2DArray(kernel, kernelSize);
    free2DArray(output, imgRows);

    return 0;
}
