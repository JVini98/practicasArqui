# !/bin/bash

if ! (test -r $1);
then
  echo "please insert a valid readeable file"
  exit 1
else

  tail +10 $1 > /tmp/ugly_flight_tmp.csv

  cut -d ' ' -f 2- /tmp/ugly_flight_tmp.csv > flights.csv

  sed -E 's/  +/,/g' flights.csv | sed -E 's/\t+/,/g' > /tmp/ugly_flight_tmp.csv
  sed -E 's/([0-9]{4})-([0-9]{2})-([0-9]{2})/\3-\2-\1/' /tmp/ugly_flight_tmp.csv > flights.csv
  sed '/##/d' flights.csv > /tmp/ugly_flight_tmp.csv

  cp /tmp/ugly_flight_tmp.csv flights.csv
  rm /tmp/ugly_flight_tmp.csv
  cat flights.csv

fi;
