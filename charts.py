import matplotlib.pyplot as plt
import numpy as np 

def main():
	scenario1()
	scenario2()
	optimizations()

# solver for question 1
def scenario1():
	print 'Scenario 1'
	
	x = np.array([1024, 10240, 102400, 1024000, 2000000])
	y = np.array([0, 0, 0.01, 0.34, 0.75])

	plt.plot(x, y, linewidth=2)

	plt.xlabel('Size of dataset')
	plt.ylabel('Response time ( seconds )')
	plt.grid(True)
	plt.legend()
	plt.show()

def scenario2():
	print 'Scenario 2'
	
	x = np.array([1024, 10240, 102400, 1024000, 2000000])
	y = np.array([0, 0, 0.03, 0.35, 0.80])

	plt.plot(x, y, linewidth=2)

	plt.xlabel('Size of dataset')
	plt.ylabel('Response time ( seconds )')
	plt.grid(True)
	plt.legend()
	plt.show()

def optimizations():
	print 'Perfoemance optimizations'
	
	objects = ('Insertion Sort', 'Quick Sort', 'Quick sort with OpenMP')
	y_pos = np.arange(len(objects))
	performance = [6.98, 0.11, 0.06]
	 
	plt.bar(y_pos, performance, align='center', alpha=0.5)
	plt.xticks(y_pos, objects)
	plt.ylabel('Response time ( seconds )')
	plt.xlabel('Algorithms')
	 
	plt.show()


if __name__ == '__main__':
	main()	