# TODO

from cs50 import get_float

def get_positive_float(prompt):
    while True:
        value = get_float(prompt)
        if value >= 0:
            return value

def main():
    # Prompt the user for the change owed
    dollars = get_positive_float("Change owed: $")

    # Convert dollars to cents
    cents = round(dollars * 100)

    # Define the coin values
    quarters = 25
    dimes = 10
    nickels = 5
    pennies = 1

    # Calculate the minimum number of coins
    num_coins = 0

    while cents > 0:
        if cents >= quarters:
            cents -= quarters
        elif cents >= dimes:
            cents -= dimes
        elif cents >= nickels:
            cents -= nickels
        else:
            cents -= pennies
        num_coins += 1

    # Print the minimum number of coins
    print(num_coins)

if __name__ == "__main__":
    main()
