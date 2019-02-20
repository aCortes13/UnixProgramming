#!/bin/sh

#   Name:       Edward Anthony Cortes
#   ID Number:  A04196581
#   Assignment: 1
#   Due Date:   2/18/2019 

if [[ $# -ne 3 ]]
then 
    echo "Usage: $0 INT1 INT2 INT3" >&2
    exit 1
fi

#function to determine if number is prime
isPrime() { 
    #flag variable 
    f=0 
    i=2
  
    #running a loop from 2 to number/2 
    while test $i -le `expr $1 / 2`  
    do
  
    #checking if i is factor of number 
    if test `expr $1 % $i` -eq 0  
    then
        f=1 
    fi
  
    #increament the loop variable 
    i=`expr $i + 1` 
    done
    if test $f -eq 1  
    then
        echo "$1 is not prime"
    else
        echo "$1 is prime"
    fi
    
}

first=$1
second=$2
third=$3

clear
echo "The numbers are $1 $2 $3"
echo 
echo "$first + $second + $third = $(($first + $second + $third))"
echo "$first * $second * $third = $(($first * $second * $third))"
echo

#output all the even numbers between 1 && the first parameter
echo "All even numbers from 1 - $1"
i=1
while [ "$i" -le "$1" ]; do
if ((i % 2 == 0))
then 
    echo "$i"
fi
    i=$((i + 1))
done
echo

#output all the odd numbers between 1 && the first parameter
echo "All odd numbers from 1 - $1"
i=1
while [ "$i" -le "$1" ]; do
if ((i % 2 == 1)) 
then 
    echo "$i"
fi
i=$((i +1))
done
echo 

#output the lengths of the parameters
echo "$first has ${#first} digits"
echo "$second has ${#second} digits"
echo "$third has ${#third} digits"
echo

#function to tell if parameters are prime
isPrime $first
isPrime $second
isPrime $third

echo "exiting.."
exit 0
