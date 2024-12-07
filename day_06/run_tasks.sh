for i in {0..129}; do
    python3 main.py input $i &
done
wait