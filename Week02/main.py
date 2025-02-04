
def binary_search(array:list, target: int):

	left = 0
	right = len(array) - 1
	while (left <= right):
		mid = left + ((right - left) // 2)

		print(f"L:{left}, R:{right}, M:{mid}")
		print(f"array:{array[left:right]}\nmid = {array[mid]}")

		if (array[mid] == target):
			return mid
		elif (array[mid] < target):
			left = mid + 1
		elif (array[mid] > target):
			right = mid - 1


	return -1


def main():

	nums = [i + 3 for i in range(50)]
	target = nums[0]

	print(binary_search(nums, target))

	return

if __name__ == '__main__':
	main()




"""
Wrong Answer
def binary_search(array: list, target: int) :

	length = len(array)
	idx = length // 2
	print(array[idx])

	if (target not in array):
		return -1

	if (array[idx] == target):
		return idx
	elif (array[idx] < target):
		return binary_search(array[idx:], target)
	elif (array[idx] > target):
		return binary_search(array[:idx], target)

"""


