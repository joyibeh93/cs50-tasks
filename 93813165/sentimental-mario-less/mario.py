# TODO
def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
            else:
                print("Height must be between 1 and 8, inclusive.")
        except ValueError:
            print("Invalid input. Please enter a positive integer between 1 and 8.")

def print_half_pyramid(height):
    for i in range(1, height + 1):
        spaces = " " * (height - i)
        hashes = "#" * i
        print(f"{spaces}{hashes}")

if __name__ == "__main__":
    height = get_height()
    print_half_pyramid(height)
