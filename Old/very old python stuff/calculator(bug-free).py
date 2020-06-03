from PIL import Image
import sound
import time
import ui
import console
import canvas
import matplotlib.pyplot as plt
import numpy as np
from random import choice

value = None
while value is None:
	try:
		value = int(raw_input())
	except ValueError:
		print 'Please enter a number!'


def again():

	answer = raw_input("Again?(y/n) ")
	if answer == 'y':
		console.clear()
		calculator()
	elif answer == 'n':
		pass
	else:
		print 'Invalid Input'
		again()

def dnd():
	numbers = []
	for num in range(1,81):
		numbers.append(num)
	x = str(choice(numbers))
	w = 1024
	h = 1024
	canvas.set_size(w,h)
	canvas.set_fill_color(1,0,0)
	canvas.draw_text(x,384,400,font_name='AmericanTypewriter-Bold',font_size = 200)
	canvas.draw_path()
	again()


def add():
	num = None
	while num == None:
		try:
			a = 0
			num = int(raw_input('How many numbers? '))
			for i in range(num):
				x = float(raw_input('Number: '))
				a = a + x
			print  a
		except ValueError:
			print 'Invalid input.'
			again()

def substract():
	a = None
	b = None
	while a or b == None:
		try:
			a = float(raw_input('First number: '))
			b = float(raw_input('Second number: '))
			print  a - b
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def multiply():
	a = 1
	num = None
	while num ==  None:
		try:
			num = int(raw_input('How many numbers?'))
			for i in range(num):
				x = float(raw_input('Number: '))
				a = a*x
			print  a
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def divide():
	a = None
	b = None
	while a or b ==  None:
		try:
			a = float(raw_input('First number: '))
			b = float(raw_input('Second number: '))
			print a/b
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def root():
	a = None
	b = None
	while a or b == None:
		try:
			a = float(raw_input('Number: '))
			b = float(raw_input('Root: '))
			print a**(1/b)
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def power():
	ans = raw_input('Is the number whole?(y/n) ')
	if ans == 'y':
		a = None
		b = None
		while a or b ==  None:
			try:
				a = int(raw_input('Number: '))
				b = int(raw_input('Power: '))
				print  a**b
				again()
			except ValueError:
				print 'Invalid Input'
				again()
	elif ans == 'n':
		a = None
		b = None
		while a or b ==  None:
			try:
				a = float(raw_input('Number: '))
				b = int(raw_input('Power: '))
				print  a**b
				again()
			except ValueError:
				print 'Invalid Input'
				again
	else:
		print 'Invalid Input'
		power()
	again()

def factorial():
	factorial = 1
	a = None
	while a ==  None:
		try:
			a = int(raw_input('Number '))
			for i in range(1,a+1):
				factorial = factorial*i
			print str(factorial)
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def  arythmeticmedium():
	a = float(0)
	b = None
	while b == None:
		try:
			b = int(raw_input('How many numbers? '))
			for i in range(b):
				x = float(raw_input('Number: '))
				a = a + x
			print float(a/b)
			again()
		except ValueError:
			print 'Invalid Input'
			again()


def geometricmedium():
	a = float(1)
	b = None
	while b ==  None:
		try:
			b = float(raw_input('How many numbers? '))
			for i in range(int(b)):
				x = float(raw_input('Number: '))
				a = a*x
			print a**(1/b)
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def harmonicmedium():
	a = float(0)
	b = None
	while b == None:
		try:
			b = int(raw_input('How many numbers? '))
			for i in range(b):
				x = float(raw_input('Number: '))
				a = a + (1/x)
			print (1/a)*b
			again()
		except ValueError:
			print 'Invalid Input'
			again()
	
def quad():
	a = None
	b = None
	c = None
	while a or b or c ==  None:
		try:
			a = float(raw_input('a = '))
			b = float(raw_input('b = '))
			c = float(raw_input('c = '))
			plt.grid(True)
			plt.title('Function Plot')
			x = np.linspace((-1.0*b/2.0*a), 1)
			p1 = plt.plot(x, a*(x**2) + b*x + c, lw = 2, c = 'b')
			plt.legend([p1[0]], ["Quadratic Equation"], loc=4)
			plt.show()
			d = b**2.0 - 4.0*a*c
			if d < 0:
				print 'No roots'
				x = (-1.0*b)/(2.0*a)
				y = (-1.0*d)/(4.0*a)
				print 'Maximum: ' + 'x = ' + str(x) + '    y = ' + str(y)
				again()
			elif d == 0:
				x = (-1.0*b)/(2.0*a)
				root = 'x = ' + str(x)
				print root
				x = (-1.0*b)/(2.0*a)
				y = (-1.0*d)/(4.0*a)
				print 'Maximum: ' + 'x = ' + str(x) + '    y = ' + str(y)
				again()
			else:
				x = (-1.0*b + d**(1.0/2.0))/(2.0*a)
				y = (-1.0*b - d**(1.0/2.0))/(2.0*a)
				t = 'x = '  + str(x)
				v = 'x = '  + str(y)
				print t,v
				x = (-1.0*b)/(2.0*a)
				y = (-1.0*d)/(4.0*a)
				print 'Maximum: ' + 'x = ' + str(x) + '    y = ' + str(y)
				again()
		except ValueError:
			print 'Invalid Input'
			again()

def prime():
	number = None
	while number == None:
		try:
			number = int(raw_input('Input a number: '))
			for n in range(2,number):
				if number % n == 0:
					print str(number) + ' is not prime.'
					again()
				else:
					print str(number) + ' is prime.'
					again()
		except ValueError:
			print 'Invalid Input'
			again()

def random():
	min = None
	max = None
	while min or max == None:
		try:
			min = int(raw_input('Input the minimum number: '))
			max = int(raw_input('Input the maximum number: '))
			numbers = range(min,max+1)
			random = choice(numbers)
			print random
			again()
		except ValueError:
			print 'Invalid Input'
			again()

def calculator():
	print '1. Addition'
	print '2. Substraction'
	print '3. Multiplication'
	print '4. Division'
	print '5. Root'
	print '6. Power'
	print '7. Factorial'
	print '8. Arythmetic Medium'
	print '9. Geometric Medium'
	print '10. Harmonic Medium'
	print '11. Quadratic Equation'
	print '12. Prime Checker'
	print '13. DnD Random Loot'
	print '14. Random'
	action = raw_input("Choose an action: ")
	if action == '1':
		add()
	elif action == '2':
		substract()
	elif action ==  '3':
		multiply()
	elif action == '4':
		divide()
	elif action == '5':
		root()
	elif action ==  '6':
		power()
	elif action == '7':
		factorial()
	elif action == '8':
		arythmeticmedium()
	elif action == '9':
		geometricmedium()
	elif action == '10':
		harmonicmedium()
	elif action == '11':
		quad()
	elif action == '12':
		prime()
	elif action == '13':
		dnd()
	elif action == '14':
		random()
	elif action == 'Iluminatti':
		im = Image.open('_Image_3')
		im.show()
		notes = 'Piano_G4#','Piano_G4','Piano_F4#','Piano_F4','Piano_E4','Piano_D4#','Piano_D4','Piano_C4#','Piano_C4','Piano_B3','Piano_A3#','Piano_A3','Piano_G3#','Piano_G3','Piano_F3#','Piano_F3','Piano_D3#','Piano_D3','Piano_C3#','Piano_C3'
		for note in notes:
			sound.play_effect(note)
			time.sleep(0.3)
		again()
	else:
		print 'Invalid Input'
		calculator()

def password():
	o = '1234'
	x = raw_input('Please enter the password: ')
	if x == o:
		w = 1024
		h = 512
		canvas.set_size(w,h)
		canvas.set_fill_color(1,0,0)
		canvas.draw_text('Welcome!',384,400,font_name='AmericanTypewriter-Bold',font_size = 100)
		canvas.draw_path()
		calculator()
	else:
		print('Invalid password. Try again.')
		password()
console.clear()
password()
