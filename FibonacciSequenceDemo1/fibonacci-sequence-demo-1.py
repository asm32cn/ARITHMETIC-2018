#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# fibonacci-sequence-demo-1.py

# feb 1
def feb(max):
	n, a, b = 0, 0, 1
	while n < max:
		print b
		a, b = b, a + b
		n = a + 1

feb(5)

# feb 2
class Feb(object):
	def __init__(self, max):
		self.max = max
		self.n, self.a, self.b = 0, 0, 1
	def __iter__(self):
		return self
	def next(self):
		if self.n < self.max:
			r = self.b
			self.a, self.b = self.b, self.a + self.b
			self.n = self.n + 1
			return r
		raise StopIteration()

for n in Feb(5):
	print n

# feb 3
def feb1(max):
	n, a, b = 0, 0, 1
	while n < max:
		yield b
		# print b
		a, b = b, a + b
		n = n + 1

for n in feb1(5):
	print n
