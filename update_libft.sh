#!/bin/bash
rm -rf ./libft
cp -r ~/Repos/libft ./
rm -rf ./libft/.git
rm -f ./libft/.gitignore
cd ./libft
make all clean
cd ../
