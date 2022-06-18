import re
import string


#Function to count the frequency of every single word in the file
def countAllWords():
    #Create dictionary
    frequency = {}
    #Open file
    text = open('CS210_Project_Three_Input_File.txt', 'r')
    #Assing it to variable and make it lowercase
    text_string = text.read().lower()
    pattern = re.findall(r'\b[a-z]{3,15}\b', text_string) #use findall function to find pattern

    #Loop through every word and one to count when the word is found
    for word in pattern:
        count = frequency.get(word, 0)
        frequency[word] = count + 1

    #Display words and their frequency
    frequency_list = frequency.keys()
    print ("Displaying Items and Their Frequency: \n")
    for words in frequency_list:
        print (" * ", words, frequency[words])
    #close file
    text.close()


#function to count the frequency of a single word in the file
def countSingleWord(word):

    # open text file in read only mode
    text = open('CS210_Project_Three_Input_File.txt', "r")
    # read data from file
    read_data = text.read()
    # convert to lower case and count the word
    count = read_data.lower().count(word)
    # print word and count
    print(word, "appears: ")
    return count

#function to create a new file frequency.dat 
def createFile():
    #create dict
    frequency = {}
    #open file
    text = open('CS210_Project_Three_Input_File.txt', 'r')
    #assing to variable and make it all lowercase
    text_string = text.read().lower()
    pattern = re.findall(r'\b[a-z]{3,15}\b', text_string)
    #Loop through text and add one to count when word is founf
    for word in pattern:
        count = frequency.get(word, 0)
        frequency[word] = count + 1

    frequency_list = frequency.keys()
    #Create and open new file
    f = open("frequency.dat", "w")
    #Loop through text and write items in new file
    for words in frequency_list:
        write = (words + " " + str(frequency[words]))
        f.write(str(write) + "\n") #make variable a string before writing on file
        #close files
    f.close()
    text.close()

