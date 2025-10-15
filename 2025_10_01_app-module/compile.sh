CPP_FILES="io.cpp sort.cpp main.cpp"
APP=bubble-sort

if [ -f $APP ]; then rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP
