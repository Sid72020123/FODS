def print_menu():
    print("\n===== MENU =====")
    print("1. Create/Write File")
    print("2. Read File")
    print("3. Update a Line")
    print("4. Delete a Line")
    print("5. Exit")


def get_int_input(prompt, max_tries=3):
    for attempt_count in range(max_tries + 1):
        try:
            return True, int(input(prompt))
        except ValueError:
            print(
                f"[{max_tries + 1 - (attempt_count + 1)} attempt(s) remaining] Entered input is invalid. Please try again..."
            )
    print("Maximum tires exceeded. Please try again...")
    return False, None


def main():
    choice = ""
    while choice != 5:
        print_menu()
        validated, choice = get_int_input("Enter an option: ")
        if not validated and (choice not in range(1, 6)):
            print("Invalid input! Please try again...\n\n")
            continue


if __name__ == "__main__":
    main()
