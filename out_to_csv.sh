git fetch gitlab
git merge gitlab/true_measurement
python3 readDataToCSV.py
git add .
git commit -m "csv results"
git push gitlab
