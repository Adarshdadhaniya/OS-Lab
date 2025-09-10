# #!/bin/bash

# echo "ENTER THREE NUMBERS"
# read num1
# read num2
# read num3

# if [[ $num1>$num2 ]]
# then
#     largest=$num1
# else
#     largest=$num2
# fi

# if [[ $largest<$num3 ]]
# then
#     largest=$num3
# fi

# echo "THE LARGEST OF THREE NUMBERS IS $largest"





# # iii. Maximum of three numbers


# #!/bin/bash
# echo "ENTER THREE NUMBERS"
# read num1
# read num2
# read num3
# if [[ $num1 > $num2 ]]
# then largest=$num1
# else
# largest=$num2
# fi
# if [[ $largest < $num3 ]]
# then largest=$num3
# fi
# echo "THE LARGEST OF THREE NUMBERS IS $largest"







#!/bin/bash
echo "Enter num1:"
read num1
echo "Enter num2:"
read num2
echo "Enter num3:"
read num3
if [ $num1 -gt $num2 ] && [ $num1 -gt $num3 ]
then
  echo "$num1"
elif [ $num2 -gt $num1 ] && [ $num2 -gt $num3 ]
then
  echo "$num2"
else
  echo "$num3"
fi