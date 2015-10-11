echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
./phonebook_orig
echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
./phonebook_opt
