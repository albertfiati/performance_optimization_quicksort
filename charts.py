def main():

# solver for question 1
def scenario1():
	print 'Scenario 1'
	
	performComputations()
	
	x = np.array([1024, 10240, 102400, 1024000, 2000000])
	y = np.array([0, 0, 0.01, 0.34, 0.75])

	plt.plot(x, y, linewidth=2)

	plt.xlabel('Size of dataset')
	plt.ylabel('Response time')
	plt.grid(True)
	plt.legend()
	plt.show()

def scenario2():
	print 'Scenario 2'
	
	performComputations()
	
	x = np.array([1024, 10240, 102400, 1024000, 2000000])
	y = np.array([0, 0, 0.03, 0.35, 0.80])

	plt.plot(x, y, linewidth=2)

	plt.xlabel('Size of dataset')
	plt.ylabel('Response time')
	plt.grid(True)
	plt.legend()
	plt.show()

if __name__ == '__main__':
	main()	