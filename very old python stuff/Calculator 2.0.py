def calculator():
	
	def tryagain():
		P = raw_input("Again?(Yes/No)")
		first = P[0]
		second = P[1]
		third = P[2]
		P = P[0].upper() + P[1] + P[2] 
		
		
		if P == "Yes":
			calculator()
		elif P == "No":
			t = raw_input("Press Enter to continue")
		else:
			print "Input invalid"
			tryagain()

	def add(a,b):
		print a + b

	def subtract(a,b):
		print a - b

	def multiply(a,b):
		print a * b

	def divide(a,b):
		print a / b

	def power(a,b):
		print a**b

	def root(a,b):
		print a**(1/b)
	print "1. Addition"
	print "2. Subtraction"
	print "3. Multiplication"
	print "4. Division"
	print "5. Power"
	print "6. Root"
	X = int(raw_input("Choose what to do: "))


	if X == 1:
		add(float(raw_input("Write the first number: ")),float(raw_input("Write the second number: ")))
		tryagain()

	elif X == 2:
		subtract(float(raw_input("Write the first number: ")), float(raw_input("Write the second number: ")))
		tryagain()

	elif X == 3:
		multiply(float(raw_input("Write the first number: ")),float(raw_input("Write the second number: ")))
		tryagain()

	elif X == 4:
		divide(float(raw_input("Write the first number: ")),float(raw_input("Write the second number: ")))
		tryagain()

	elif X == 5:
		power(float(raw_input("Write the first number: ")),float(raw_input("Write the second number: ")))
		tryagain()

	elif X == 6:
		root(float(raw_input("Write the first number: ")),float(raw_input("Write the second number: ")))
		tryagain()
	else:
		print "Input invalid"
		tryagain()

calculator()