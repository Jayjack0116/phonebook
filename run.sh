echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
perf stat -e cache-misses,cache-references,instructions,cycles ./phonebook_orig
echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
perf stat -e cache-misses,cache-references,instructions,cycles ./phonebook_opt
