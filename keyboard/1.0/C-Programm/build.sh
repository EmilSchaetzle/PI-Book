echo "Building"
gcc main.c keyboard.c interrupt.c -lm -o main
echo "Starting app"
./main
