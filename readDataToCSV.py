import csv
import re
import os

# Locations of measurements
directory_names = ['results_92', 'results_93', 'results_infiniband']

def write_csv_datei(filename):
    # Open and read the file
    with open(filename, 'r') as file:
        input_text = file.read()

    # extract the values
    pattern = re.compile(r'Results for (\d+\^\d+):|Half-round-trip latency was ([\d\.]+) ms\.')
    matches = pattern.findall(input_text)

    # Initialize variables
    current_exponent = None
    data = []

    # Process the matches
    for match in matches:
        if match[0]:
            current_exponent = match[0]
        else:
            data.append([current_exponent, match[1]])

    # Test for file format
    if filename.endswith('.csv'):
        print("This file is already in CSV format")
    else:
        # Write the data to a CSV file
        csv_file_name = filename + '.csv'
        with open(csv_file_name, 'w', newline='') as csvfile:
            csvwriter = csv.writer(csvfile)
            csvwriter.writerow(['Exponent', 'Latency (ms)'])
            csvwriter.writerows(data)
        print(f"Data has been successfully written to {csv_file_name}")


# Write a CSV file for every file in a directory/folder
def write_multiple_csv(directory):
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        if os.path.isfile(file_path):
            write_csv_datei(file_path)


for dirname in directory_names:
    write_multiple_csv(dirname)