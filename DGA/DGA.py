# Patrick Sacchet
# This file will contain the algorithm used for producing AGDs 

# Our algorithm works as follows:
    # 1) Define our TLDs and random letter/number list, of which is at least 127 entries long 
    # 2) Grab the current day integer value for today's date
    # 3) Calculate our seed via the ASCII value of the letter/number of the index into our random array
    # 4) Generate our list fo 10 domains:
        # a) While total strings in our array is less than 10
        # b) While our length of our current string is less than 10
            # 1) Calculate our offset into our random array as either the difference between our seed and total count or the sum
            # 2) Add the corresponding index value into our random array as a letter in our current domain string
            # 3) Increment our string index
            # 4) Increment our overall index into our random array (or set to 0 if at end)
        # c) Add a corresponding TLD to the end of our string 
        # d) Increment our TLD index; set to 0 if at end of array
        # e) Add our string to our array of AGDs
        # f) Increment our string counter by 1 

from datetime import date
from datetime import datetime

# Accepted TLDs: .csc840.lan, .com, .press, .me, .cc
# Length: 9-15
# Alphabet: No vowels, numbers acceptable
# Non-deterministic

# Possible TLDs
tlds = ['.csc840.lan', '.com', '.press', '.me', '.cc']

# In order to be non-deterministic we cross reference the current day (date) with an random assortment of letters and numbers
    # Then, we get the ASCII value for that letter to use as a seed, so the highest this could go would be 127
    # No vowels
rand_letters = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

curr_day = date.today().day


# Take the current day, use that as an index into our random number list, then get the ascii equivalent as our seed
def generateSeed() -> int:
    seed = 0 
    letter = rand_letters[curr_day]
    seed = ord(letter)

    return seed


# Generate our AGD list
def generateAGDs(seed : int) -> list:
    agds = []
    count = 0 # the total number of domains we've generated
    tld_index = 0 # our index into our tld array
    offset_add = 0 # will use this to continously walk through our letters

    # Generate 10 domains, each between 9-15 characters (we will do 10)
    while (count < 10):
        agd_count = 0 # total number of agd letters       
        agd = '' # empty string to add letters to

        # Use the salt to grab our letters and form our domain
        while (agd_count < 10): # we are hard setting this to 10 characters since we cannot be random
            offset = 0

            # Make sure we dont go over 127
            if (seed + offset_add > len(rand_letters)):
                offset = seed - offset_add 

            else:
                offset = seed + offset_add

            agd += rand_letters[offset] # offset seed with our agd count 
            agd_count += 1

            # 10 letters * 10 strings mean this should only be 100 at most... 
            if (offset_add == 127):
                offset_add = 0

            else:
                offset_add += 1

        # Done with our letters so add our TLD then add to list
        if (tld_index > 4):
            tld_index = 0 # reset our tld index 
        
        agd += tlds[tld_index]
        tld_index += 1

        agds.append(agd)
        count += 1

    return agds


# Get the current day, generate our seed, generate our AGD list, then print and write them out to a log
def main():
    print(f"Current day is {curr_day}")

    seed = generateSeed()
    print(f"Seed is {seed}")

    print("Generating first 10 AGDs...")
    agds = generateAGDs(seed)

    if (len(agds) == 0):
        print("ERROR: No AGDs generated!")
        return
    
    # Otherwise print the outputs for the user and write them to a log 
    else:
        filename = datetime.now().strftime("dga_out_" + "%Y-%m-%d_%H:%M:%S" + ".txt")
        log = open(filename, 'w')

        print("DGAs:")
        for entry in agds:
            print(f"\t{entry}")
            log.write(entry + "\n")

        log.close()
        print(f"AGDs available in {filename}")

    return


if __name__ == '__main__':
    main()