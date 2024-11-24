#!/bin/bash
# This line specifies the shell to use for interpreting the script.

# Function to create a database
create_database() {
    # Prompt the user to enter the database name.
    echo -n "Enter the name of your database: "
    read db_filename

    # Check if the user input is empty.
    if [[ -z "$db_filename" ]]; then
        echo "Database name cannot be empty!"
        return  # Exit the function.
    fi

    # Check if a file with the entered name already exists.
    if [[ -f "$db_filename" ]]; then
        echo "Database file '$db_filename' already exists!"
    else
        # Create a new file and provide feedback on success or failure.
        touch "$db_filename" && echo "Database file '$db_filename' created successfully!" || echo "Failed to create database file!"
    fi
}

# Function to insert a record into the database
insert_record() {
    # Prompt the user to specify the database to insert the record into.
    echo -n "Enter the name of the database to insert record: "
    read db_filename

    # Check if the database file exists.
    if [[ ! -f "$db_filename" ]]; then
        echo "Database file '$db_filename' does not exist. Create one before inserting records!"
        return
    fi

    # Prompt the user to enter details for the new record.
    echo "Enter details of the user:"
    read -p "Name: " name
    read -p "Email: " email
    read -p "Mobile: " mobile
    read -p "Address: " address

    # Ensure that all fields are filled out.
    if [[ -z "$name" || -z "$email" || -z "$mobile" || -z "$address" ]]; then
        echo "All fields are required!"
        return
    fi

    # Create a record in CSV format.
    record="${name},${email},${mobile},${address}"

    # Append the record to the database file and provide feedback.
    echo "$record" >> "$db_filename" && echo "Record inserted successfully!" || echo "Failed to insert record!"
}

# Function to search for a record in the database
search_record() {
    # Prompt the user to specify the database to search.
    echo -n "Enter the name of the database to search record (with extension): "
    read db_filename

    # Check if the database file exists.
    if [[ ! -f "$db_filename" ]]; then
        echo "Database file '$db_filename' does not exist."
        return
    fi

    # Prompt the user to enter the search term (name).
    echo -n "Enter the name to search in the address book: "
    read search_id

    # Check if the search term is empty.
    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    # Search for a record starting with the entered name.
    if grep -q "^$search_id," "$db_filename"; then  
        record=$(grep "^$search_id," "$db_filename")
        # Split the record into fields using IFS and display the details.
        IFS=',' read -r name email mobile address <<< "$record"
        echo "Record found! Details are as follows:"
        echo "Name: $name"
        echo "Email: $email"
        echo "Mobile Number: $mobile"
        echo "Address: $address"
    else
        # If no record is found, inform the user.
        echo "No record with name: $search_id!"
    fi
}

# Function to modify a record in the database
modify_record() {
    # Prompt the user to specify the database to modify a record in.
    echo -n "Enter the name of the database to modify record (with file extension): "
    read db_filename

    # Check if the database file exists.
    if [[ ! -f "$db_filename" ]]; then
        echo "Database with filename '$db_filename' does not exist"
        return
    fi

    # Prompt the user to enter the name of the record to modify.
    echo -n "Enter the User Name to modify: "
    read search_id

    # Check if the search term is empty.
    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    # Check if a matching record exists.
    if grep -q "^$search_id," "$db_filename"; then
        record=$(grep "^$search_id," "$db_filename")
        IFS=',' read -r name email mobile address <<< "$record"
        
        # Display the existing record and prompt for new details.
        echo "Record found with following details:"
        echo "Name: $name"
        echo "Email: $email"
        echo "Mobile Number: $mobile"
        echo "Address: $address"

        echo "Enter new modified details (leave unmodified details blank)"
        read -p "Name [$name]: " new_name
        read -p "Email [$email]: " new_email
        read -p "Mobile Number [$mobile]: " new_mobile
        read -p "Address [$address]: " new_address

        # Retain old values if new values are not provided.
        new_name=${new_name:-$name}
        new_email=${new_email:-$email}
        new_mobile=${new_mobile:-$mobile}
        new_address=${new_address:-$address}

        # Create the updated record.
        new_record="${new_name},${new_email},${new_mobile},${new_address}"

        # Replace the old record with the new one.
        sed -i "s/^$record$/$new_record/" "$db_filename" && echo "Record updated successfully!" || echo "Failed to update record!"
    else
        echo "No matching record with name: $search_id"
    fi
}

# Function to delete a record from the database
delete_record() {
    # Prompt the user to specify the database to delete a record from.
    echo -n "Enter the name of the database to delete record (with file extension): "
    read db_filename

    # Check if the database file exists.
    if [[ ! -f "$db_filename" ]]; then
        echo "Database with filename '$db_filename' does not exist"
        return
    fi

    # Prompt the user to enter the name of the record to delete.
    echo -n "Enter the User Name to delete: "
    read search_id

    # Check if the search term is empty.
    if [[ -z "$search_id" ]]; then
        echo "Search name cannot be empty!"
        return
    fi

    # Check if a matching record exists and delete it.
    if grep -q "^$search_id," "$db_filename"; then
        sed -i "/^$search_id,/d" "$db_filename" && echo "Record deleted successfully!" || echo "Failed to delete record!"
    else
        echo "No matching record with name: $search_id"
    fi
}

# Function to display the menu
show_menu() {
    # Display the options available to the user.
    echo "+------------------+"
    echo "|     Main Menu    |"
    echo "+------------------+"
    echo "|1. Create Database|"
    echo "|2. Insert Record  |"
    echo "|3. Search Record  |"
    echo "|4. Modify Record  |"
    echo "|5. Delete Record  |"
    echo "|6. Exit           |"
    echo "+------------------+"
}

# Function to handle menu choices
handle_choice() {
    # Call the appropriate function based on the user's choice.
    case $1 in
    1) create_database ;;  # Create a database.
    2) insert_record ;;    # Insert a record.
    3) search_record ;;    # Search for a record.
    4) modify_record ;;    # Modify a record.
    5) delete_record ;;    # Delete a record.
    6) echo "Exiting..."; exit 0 ;;  # Exit the script.
    *) echo "Invalid choice. Please try again!" ;;  # Handle invalid inputs.
    esac
}

# Main loop
while true; do
    # Display the menu and process the user's choice.
    show_menu
    read -p "Enter your choice: " choice
    handle_choice "$choice"
    echo ""  # Print a blank line for better readability.
done

#touch address.sh
#save code in the text file
# chmod +x  address.sh
#  ./address.sh
