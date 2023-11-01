import tkinter as tk
from tkinter import messagebox

# Function to validate the login
def validate_login():
    username = entry_username.get()
    password = entry_password.get()

    # Check if the username and password are correct
    if username == "user" and password == "password":
        messagebox.showinfo("Login Successful", "Welcome, " + username + "!")
    else:
        messagebox.showerror("Login Failed", "Invalid username or password")

# Function to open the account creation window
def open_account_creation_window():
    # Create a new window for the account creation form
    account_window = tk.Toplevel(window)
    account_window.title("Account Creation")

    # Create and place labels and entry fields for account creation
    label_new_username = tk.Label(account_window, text="New Username:")
    label_new_username.pack(pady=5)
    entry_new_username = tk.Entry(account_window)
    entry_new_username.pack(pady=5)

    label_new_password = tk.Label(account_window, text="New Password:")
    label_new_password.pack(pady=5)
    entry_new_password = tk.Entry(account_window, show="*")  # Password entry, obscures characters
    entry_new_password.pack(pady=5)

    # Create and place the "Create Account" button with blue color
    create_account_button = tk.Button(account_window, text="Create Account", command=create_account, bg="blue", fg="white")
    create_account_button.pack(pady=10)

# Function to create a new account (Replace with your own logic)
def create_account():
    new_username = entry_new_username.get()
    new_password = entry_new_password.get()
    
    # Replace this with your account creation logic
    messagebox.showinfo("Account Created", "Account created successfully!")

# Create the main window
window = tk.Tk()
window.title("Login Page")

# Set background color for the main window
window.configure(bg="lightgray")

# Create and place labels and entry fields with padding
label_username = tk.Label(window, text="Username:")
label_username.pack(pady=5)
entry_username = tk.Entry(window)
entry_username.pack(pady=5)

label_password = tk.Label(window, text="Password:")
label_password.pack(pady=5)
entry_password = tk.Entry(window, show="*")  # Password entry, obscures characters
entry_password.pack(pady=5)

# Create and place the login button with blue color
login_button = tk.Button(window, text="Login", command=validate_login, )
login_button.pack(pady=10)

# Create and place the "Create Account" button with blue color
create_account_button = tk.Button(window, text="Create Account", command=open_account_creation_window,)
create_account_button.pack(pady=10)

# Run the main event loop
window.mainloop()
