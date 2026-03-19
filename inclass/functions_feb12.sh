#!/bin/bash

# functions in bash
# functions are treated as mini-scripts in bash

function func_name(){
	echo "ya mama"
	#by default all function data is global in bash
	return 0; # exit status
}

# local keywird makes a variable local scope

