import sys

def esDivisible(a,b):
	"Sirve para comprobar si es divisible"
	return a%b==0

#a=int(raw_input('Introduce el primer numero : '))
#b=int(raw_input('Introduce el segundo numero: '))

print sys.argv

a=int(sys.argv[1])
b=int(sys.argv[2])

if esDivisible(a,b):
    print "Es divisible"
else:
    print "No es divisible"
