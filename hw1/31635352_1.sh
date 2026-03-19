#!/bin/bash

	


echo "Welcome to the Bash Number Guessing Game!"
echo "Think of a number between 1 and 50."
echo "You have 7 attempts to guess it!"

while true;
do
	number_to_guess=$((RANDOM % 50 + 1))
	attempt_counter=0

	while [ $attempt_counter -lt 7 ]; do
		echo "Attempts remaining: $((7 - attempt_counter))"
		read user_guess

		if ((user_guess < 1 || user_guess > 50)); then
			echo "Invalid input! Please enter a number between 1 and 50."
		elif ((user_guess < number_to_guess )); then
			echo "Too low! Try a higher number."
		elif ((user_guess > number_to_guess )); then
			echo "Too high! Try a lower number."
		else
			echo "Congratulations! You guessed the number $number_to_guess in $attempt_counter attempts!"
			break
		fi

		attempt_counter=$((attempt_counter + 1))
	done
	
	if (( attempt_counter == 7 && user_guess != number_to_guess )); then
		echo "Game over! The number was $number_to_guess. Better luck next time!"
	fi

	echo "Do you want to play again? Type yes to continue playing and no to end the program."
	read user_response

	if [ "$user_response" != "yes" ]; then
		echo "Bye bye!"
		break
	fi
done


