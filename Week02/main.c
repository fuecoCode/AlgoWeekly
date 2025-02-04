#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t binary_search_recursive(uint32_t *array, uint32_t target, uint32_t left, uint32_t right){
	uint32_t mid = left + (uint32_t)((right - left) / 2);

	if(left > right){
		return -1;
	}

	if (array[mid] == target){
		return mid;
	}else if(array[mid] < target){
		binary_search_recursive(array, target, mid+1, right);
	}else if(array[mid] > target){
		binary_search_recursive(array, target, left, mid-1);
	}
}

uint32_t binary_search(uint32_t *array, uint32_t length, uint32_t target){

	uint32_t left = 0;
	uint32_t right = length - 1;
	uint32_t mid;
	while(left <= right){
		mid = left + (uint32_t)((right - left) / 2);
		
		printf("L:%d, R:%d, M:%d\n", left, right, mid);
		printf("mid=%d\n", array[mid]);

		if (target == array[mid]){
			return mid;
		}else if(array[mid] < target){
			left = mid + 1;
		}else if(array[mid] > target){
			right = mid - 1;
		}
	}
	return -1;
}


int main(int argc, char const *argv[])
{
	/* code */

	uint32_t array[] = {1, 3, 5, 7, 9, 10, 15, 17, 31, 35};
	uint32_t length = sizeof(array) / sizeof(array[0]);
	uint32_t target = 7;
	printf("target:%d, result:%d\n", target, binary_search(array, length, target));
	printf("target:%d, result_recursive:%d\n", target, binary_search_recursive(array, target, 0, length - 1));

	return 0;
}