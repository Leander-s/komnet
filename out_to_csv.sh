git fetch gitlab
git merge gitlab/main
python3 readDataToCSV.py
git add .
git commit -m "csv results"
git push gitlab
