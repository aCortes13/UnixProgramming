#!/bin/bash
clear
echo "CS 4350 --    Unix System Programming"
echo "Name:         Edward Cortes"
echo "Serial:       12"
echo "Assignment:   2"
echo "Due Date:     2/27/19"
echo 
echo "The function of this script is to:"
echo -e "\t 1.  Make directory by checking existence"
echo -e "\t 2.  Test if File Exist. If it exists then Read the File,"
echo -e "\t     display number of words , number of lines in the file, and its contents." 
echo -e "\t     Display a message it does not exist"
echo -e "\t 3.  Append “Learning Scripts and Shell Programming “ to an existing File." 
echo -e "\t     Display a message if it does not exist"
echo -e "\t 4.  Delete an existing file"
echo -e "\t 5.  Parse Current Date"
echo -e "\t 9.  Exit"
echo 

makeDir() {
    echo #for additional space

    # test if exists
    if [ -d $1 ]; then
        #will enter here if $1 exists
        echo -e "Directory $1 already exists\n"
    else
        #if the code reaches this point, the 1 does not exist so create it
        mkdir $1
        echo "Directory created: $1"
        echo
    fi
}

readFile() {
    echo #for additional space
    if [ -f $1 ]; then
        #1 exists
        fileInfo=($(wc $1))    
        echo "Number of lines and words: ${fileInfo[0]} ${fileInfo[1]}"
        echo
        echo "File content:"
        cat $1
        echo
    else
        #if code reaches this point the 1 does not exist
        echo "$1 does not exist.."
        echo
    fi
}

appendMsg() {
    fileName=$1 && shift
    arr=($@)
    if [ -f $fileName ]; then
        echo -e "\nFile content before append:"
        cat $fileName
        echo ${arr[@]} >> $fileName
        echo -e "\nFile content after append:"
        cat $fileName
        echo
    else
        echo -e "\n$fileName does not exist."
        echo
    fi
}

delFile() {
    if [ -f $1 ]; then 
        rm $1
        echo -e "\n$1 has been deleted\n"
    else
        echo -e "\nfile does not exist\n"
    fi
}

parseDate() {
    set $(date)
    echo -e "\nCurrent date is: $3-$2-$6"
    echo -e "Current time is: $4\n"
}

echo
while true; do
read -p "Enter your choice " choice
case "$choice" in 
    1)
        echo
        read -p "Enter the name of the directory: " directory
        makeDir $directory
        ;;
    2)
        echo
        read -p "Enter file name: " file
        readFile $file
        ;;
    3)
        msg=("Learning" "Scripts" "and" "Shell" "Programming")
        unset file
        echo
        read -p "Enter file name: " file
        appendMsg $file ${msg[@]} 
        ;;
    4)
        unset file
        echo
        read -p "Enter file name to be deleted: " file
        delFile $file    
        ;;
    5)
        parseDate
        ;;
    9)
        echo -e "\nexiting..\n"
        echo "Edward Anthony Cortes 2-27-2019"
        break
        ;;
    *)
        echo "Incorrect Choice, Try again"
        continue
        ;;
esac
done

